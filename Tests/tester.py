#!/usr/bin/env python3

import argparse
import os
import timeit
import subprocess
import sys
import functools
import csv

timeit.template = """
def inner(_it, _timer{init}):
    {setup}
    _t0 = _timer()
    for _i in _it:
        retval = {stmt}
    _t1 = _timer()
    return _t1 - _t0, retval
"""


def execute(filepath, method):
    cmd = ['./iengine', method, filepath]
    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return proc.communicate()


def run_tests(file, samples):
    test_dir = os.path.dirname(os.path.realpath(__file__))
    script_name = os.path.basename(__file__)
    if not os.path.isfile(os.path.join(test_dir, file)):
        sys.stderr.write('{0}: file \'{1}\' not found\n'.format(script_name, file))
        sys.exit(0)

    result_dir = os.path.join(test_dir, 'results')
    if not os.path.exists(result_dir):
        os.mkdir(result_dir)

    filepath = os.path.join(test_dir, file)
    exe_path = os.path.join(os.path.join(test_dir, '..'), 'cmake-build-debug')
    os.chdir(exe_path)

    time_dist = open(os.path.join(result_dir, 'time-dist.csv'), 'w')
    inference_dist = open(os.path.join(result_dir, 'inference-dist.csv'), 'w')
    time_writer = csv.DictWriter(time_dist, delimiter=',', fieldnames=['method',
                                                                       'sample',
                                                                       'time'])
    inference_writer = csv.DictWriter(inference_dist, delimiter=',',
                                      fieldnames=['method', 'sample', 'inference_length'])
    time_writer.writeheader()
    inference_writer.writeheader()

    for method in ['FC', 'BC', 'TT']:
        timer = timeit.Timer(functools.partial(execute, filepath, method))
        avg = 0
        avg_path = 0

        for i in range(0, samples):
            current, (result, err) = timer.timeit(1)
            avg += current * 1000
            result = result.decode('ascii').replace(',', '').replace(':', '')
            result_list = str.split(result)[1:]
            length = len(result_list)
            if method == 'TT':
                length = int(result_list[0])
            avg_path += length
            time_writer.writerow({'method': method, 'sample': i, 'time': current})
            inference_writer.writerow({'method': method, 'sample': i, 'inference_length':
                length})

        terminology = 'inferences'
        if method == 'TT':
            terminology = 'models'

        print('Method: {0}, Average time: {1:.3f}ms, Average {2}: {3}'.format(method,
              avg / samples, terminology, avg_path / samples))

    time_dist.close()
    inference_dist.close()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Runs IEngine tests')
    parser.add_argument('file', type=str, help='The test file to execute tests on. Must '
                                               'contain TELL and ASK')
    parser.add_argument('samples', type=int, help='Number of samples to run for each '
                                                  'inference method')
    args = parser.parse_args()
    run_tests(args.file, args.samples)
