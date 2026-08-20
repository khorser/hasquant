ARG PLATFORM=linux/amd64

FROM --platform=${PLATFORM} debian:trixie AS base
RUN apt-get update \
    && apt-get install -y \
        build-essential cmake curl wget git python3-dev \
        libgmp-dev libffi-dev libtinfo-dev zlib1g-dev pkg-config \
        gdb valgrind htop locales vim zsh less vifm \
        libffi8 libgmp10 libncurses-dev libncurses6 libtinfo6 \
    && sed -i '/en_US.UTF-8/s/^# //g' /etc/locale.gen \
    && locale-gen
ENV LANG=en_US.UTF-8
ENV LC_ALL=en_US.UTF-8

# Non-root user: local dev caches ghcup/cabal/stack in named volumes mounted over
# this user's $HOME (see compose.yaml), so GHC isn't duplicated between image layers
# and the volume, and doesn't need re-downloading on every image rebuild. Only the
# steps that genuinely need root (apt installs above, boost/quantlib "make install"
# into /usr/local below) run as root.
ARG USERNAME=dev
ARG UID=1000
ARG GID=1000
RUN groupadd -g ${GID} ${USERNAME} \
    && useradd -m -u ${UID} -g ${GID} -s /bin/zsh ${USERNAME}

ARG BOOST_VERSION=1.91.0-1
FROM base AS boost-builder
ARG BOOST_VERSION
WORKDIR /build/boost
RUN wget https://github.com/boostorg/boost/releases/download/boost-${BOOST_VERSION}/boost-${BOOST_VERSION}-cmake.tar.gz && \
    tar -xzf boost-${BOOST_VERSION}-cmake.tar.gz && \
    cd boost-*/ && \
    mkdir build && cd build && \
    cmake .. \
        -DCMAKE_BUILD_TYPE=Release \
        -DBOOST_EXCLUDE_LIBRARIES=python,graph,wave \
        -DBUILD_TESTING=OFF \
        -DCMAKE_INSTALL_PREFIX=/usr/local && \
    make -j$(nproc) && \
    make install

ARG QL_VERSION=1.43
FROM boost-builder AS ql-builder
ARG QL_VERSION
WORKDIR /build/quantlib
RUN wget https://github.com/lballabio/QuantLib/releases/download/v${QL_VERSION}/QuantLib-${QL_VERSION}.tar.gz && \
    tar -xzf QuantLib-${QL_VERSION}.tar.gz && \
    cd QuantLib-${QL_VERSION} && \
    mkdir -p build && cd build && \
    cmake .. \
        -DCMAKE_BUILD_TYPE=Release && \
    make -j$(nproc) && \
    make install

FROM base AS development
ARG USERNAME=dev
COPY --from=ql-builder /usr/local/lib /usr/local/lib
COPY --from=ql-builder /usr/local/include /usr/local/include
COPY --from=ql-builder /usr/local/bin /usr/local/bin
RUN ldconfig

ARG GHC_VERSION=9.10.3
ENV GHC_VERSION=${GHC_VERSION}

RUN mkdir -p /home/${USERNAME}/.ghcup /home/${USERNAME}/.cabal /home/${USERNAME}/.stack /hasquant/.stack-work /hasquant/dist-newstyle \
    && chown -R ${UID}:${GID} /home/${USERNAME}/.ghcup /home/${USERNAME}/.cabal /home/${USERNAME}/.stack /hasquant/.stack-work /hasquant/dist-newstyle

USER ${USERNAME}
WORKDIR /home/${USERNAME}
ENV HOME=/home/${USERNAME}
ENV PATH="/home/${USERNAME}/.ghcup/bin:/home/${USERNAME}/.cabal/bin:${PATH}"
ENV CABAL_DIR=/home/${USERNAME}/.cabal

RUN curl --proto '=https' --tlsv1.2 -sSf https://get-ghcup.haskell.org | \
    BOOTSTRAP_HASKELL_NONINTERACTIVE=1 BOOTSTRAP_HASKELL_ADJUST_BASHRC=0 BOOTSTRAP_HASKELL_MINIMAL=1 \
    sh

# BUILD_MODE=local (default): defer GHC/cabal/stack install to entrypoint.sh at
# container start, into whatever's mounted over $HOME/.ghcup etc (compose.yaml's
# named volumes) -- keeps the same GHC install from being duplicated between image
# layers and the volume, and avoids re-downloading it on every image rebuild.
# BUILD_MODE=ci: no persistent volume across CI runs, so bake GHC/cabal/stack into
# this layer once instead; entrypoint.sh's own installs then no-op at container start.
ARG BUILD_MODE=local
RUN if [ "$BUILD_MODE" = "ci" ]; then \
      ghcup install ghc "${GHC_VERSION}" && ghcup set ghc "${GHC_VERSION}" && \
      ghcup install cabal recommended && \
      ghcup install stack recommended && \
      stack config set system-ghc true --global; \
    fi

RUN cat << 'EOF' > /home/${USERNAME}/entrypoint.sh
#!/bin/bash
set -e
if [ -n "$GHC_VERSION" ]; then
    if ! ghcup whereis ghc "$GHC_VERSION" > /dev/null 2>&1; then
        echo "[Entrypoint] GHC $GHC_VERSION not found. installing..."
        ghcup install ghc "$GHC_VERSION"
        ghcup set ghc "$GHC_VERSION"
    fi
    if ! ghcup whereis cabal > /dev/null 2>&1; then
        echo "[Entrypoint] Cabal not found. installing..."
        ghcup install cabal recommended
    fi
    if ! ghcup whereis stack > /dev/null 2>&1; then
        echo "[Entrypoint] Stack not found. installing..."
        ghcup install stack recommended
        stack config set system-ghc true --global
    fi
#    if ! ghcup whereis hls > /dev/null 2>&1; then
#        echo "[Entrypoint] HLS not found. installing..."
#        ghcup install hls recommended
#    fi
fi
exec "$@"
EOF

RUN chmod +x /home/${USERNAME}/entrypoint.sh
# Exec-form ENTRYPOINT doesn't expand ARG/ENV, so route through a shell that expands
# $HOME at container runtime instead of hardcoding the (overridable) username.
ENTRYPOINT ["/bin/sh", "-c", "exec \"$HOME/entrypoint.sh\" \"$@\"", "sh"]

RUN echo "set auto-load safe-path /" >> /home/${USERNAME}/.gdbinit
