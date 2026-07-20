ARG PLATFORM=linux/amd64

FROM --platform=${PLATFORM} debian:trixie AS base
RUN apt-get update && apt-get install -y \
    build-essential cmake curl wget git python3-dev \
    libgmp-dev libffi-dev libtinfo-dev zlib1g-dev pkg-config \
    gdb valgrind htop locales vim zsh less vifm

ARG BOOST_VERSION=1.91.0-1
ARG QL_VERSION=1.42.1

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
COPY --from=ql-builder /usr/local/lib /usr/local/lib
COPY --from=ql-builder /usr/local/include /usr/local/include
COPY --from=ql-builder /usr/local/bin /usr/local/bin

RUN echo "set auto-load safe-path /" >> /root/.gdbinit

RUN ldconfig

RUN curl -sSL https://get.haskellstack.org/ | sh
WORKDIR /app
COPY stack.yaml ./
RUN echo "name: dummy" > package.yaml && \
    stack setup && \
    rm package.yaml dummy.cabal
COPY package.yaml ./
COPY *.cpp ./
RUN stack build --only-snapshot

COPY . .
