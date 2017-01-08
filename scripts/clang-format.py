#!/usr/bin/env python3

import argparse
import difflib
import logging
import os
import re
import sys
from distutils.version import LooseVersion

import common

# The version we care about
program_name = 'clang-format'


class ClangFormatter:
    def __init__(self, path_to_cf: str) -> None:
        self.path = path_to_cf
        self.toplevel = common.callo('git rev-parse --show-toplevel')

    def __str__(self):
        return self.path

    @property
    def version(self) -> LooseVersion:
        return LooseVersion(
            common.callo(' '.join([self.path, '--version'])).split()[2]
        )

    # Lint a given file - return whether or not the file is formatted correctly
    def lint(self, source_file: str, print_output: bool) -> bool:
        '''
        Lint `source_file` with clang-format, optionally showing the diff.
        '''
        # Get original and formatted text
        with open(source_file, 'r', errors='ignore') as original_file:
            original_text = original_file.read()
        formatted_text = common.callo([self.path, '--style=file', source_file])

        # Create some nice git-like metadata for the diff
        relpath = os.path.relpath(source_file, self.toplevel)
        fromfile = os.path.join('a', relpath)
        tofile = os.path.join('b', relpath)

        diff = list(
            difflib.unified_diff(
                original_text.splitlines(),
                formatted_text.splitlines(),
                fromfile=fromfile,
                tofile=tofile
            )
        )

        if diff:
            print(f'Found formatting changes for file: {source_file}')

            if show_diff:
                print(f'To fix, run "{cf} --style=file -i {source_file}"')
                print('Suggested changes:')
                for line in diff:
                    print(line.strip())
                print()

        return not diff


def parse_arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser('clang-format')
    parser.add_argument(
        '-c',
        '--clang-format-path',
        help='path to clang-format',
        metavar='PATH',
        dest='path',
    )
    parser.add_argument(
        '--print-output',
        help='hide file diff generated by clang-format',
        default=False,
        action='store_true',
    )
    parser.add_argument(
        '-A',
        '--all-files',
        help='Operate on all files under revision control',
        default=False,
        action='store_true',
    )
    parser.add_argument(
        '-v',
        '--verbose',
        help='Increase logging',
        default=False,
        action='store_true',
    )
    return parser.parse_args()


def main() -> bool:
    args = parse_arguments()

    # Set up some logging
    level = logging.INFO if not args.verbose else logging.DEBUG
    logging.basicConfig(
        stream=sys.stdout,
        level=level,
        format='%(asctime)s %(name)s %(levelname)s %(message)s',
        datefmt='%m-%d %H:%M',
    )

    # Find clang-format, validate version
    path_to_cf = common.find_binary(program_name, args.path)
    cf = ClangFormatter(path_to_cf)
    if cf.version < common.MIN_VERSION_REQUIRED:
        logging.error(
            f'''Incorrect version of {program_name}: got {cf.version} but at \
                least {common.MIN_VERSION_REQUIRED} is required'''
        )
        sys.exit(1)

    # Find changed source files.
    source_files = re.compile(r'\.(h|hpp|c|cpp)$')
    files = common.all_files() if args.all_files else common.changed_files
    changes = [f for f in files if re.search(source_files, f)]

    # Validate each with clang-format
    return all(cf.lint(f, print_output=args.print_output) for f in changes)


if __name__ == '__main__':
    sys.exit(int(not main()))    
