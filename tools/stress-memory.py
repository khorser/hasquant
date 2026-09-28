#!/usr/bin/env python3
"""Run isolated FDM and seeded full-suite processes; stop at the first failure."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import platform
import subprocess
import time


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('exe', type=Path)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--compiler', default='unspecified')
    parser.add_argument('--fdm-runs', type=int, default=100)
    parser.add_argument('--suite-seeds', type=int, default=10)
    parser.add_argument('--timeout', type=int, default=600)
    args = parser.parse_args()
    if args.fdm_runs < 0 or args.suite_seeds < 0 or args.timeout <= 0:
        parser.error('run counts must be nonnegative and timeout positive')
    exe = args.exe.resolve()
    args.output.mkdir(parents=True, exist_ok=False)
    metadata = {'exe': str(exe), 'sha256': hashlib.sha256(exe.read_bytes()).hexdigest(),
                'compiler': args.compiler, 'platform': platform.platform(),
                'revision': subprocess.check_output(['git', 'rev-parse', 'HEAD'], text=True).strip(),
                'status': subprocess.check_output(['git', 'status', '--short'], text=True),
                'inherited_GHCRTS': os.environ.get('GHCRTS'), 'started': time.time()}
    (args.output / 'metadata.json').write_text(json.dumps(metadata, indent=2))
    env = dict(os.environ, HASQUANT_TRACE_FDM='1')
    env.pop('GHCRTS', None)
    for mode, rts in [('default', []), ('small-nursery', ['+RTS', '-A64k', '-RTS'])]:
        cases = [('fdm', i, ['--match', 'Fdm example', '--seed', '1'])
                 for i in range(1, args.fdm_runs + 1)]
        cases += [('suite', i, ['--randomize', '--seed', str(i)])
                  for i in range(1, args.suite_seeds + 1)]
        for kind, number, options in cases:
            name = f'{mode}-{kind}-{number}'
            command = [str(exe), *options, *rts]
            print(name, flush=True)
            with (args.output / (name + '.log')).open('w') as log:
                log.write(json.dumps({'command': command, 'started': time.time()}) + '\n')
                log.flush()
                try:
                    result = subprocess.run(command, stdout=log, stderr=subprocess.STDOUT,
                                            env=env, timeout=args.timeout, check=False)
                    code = result.returncode
                except subprocess.TimeoutExpired:
                    code = 124
                log.write(f'\nexit={code}\n')
            if code:
                raise SystemExit(f'{name} failed ({code}); see {args.output}')
    print('All stress processes passed', flush=True)


if __name__ == '__main__':
    main()
