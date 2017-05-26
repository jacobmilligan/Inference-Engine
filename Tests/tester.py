#!/usr/bin/env python3

import argparse
import os
import timeit
import subprocess
import sys
import functools
import csv
import shutil

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
    """Runs a sample via the external program
    :param filepath: The path to the file to infer
    :param method: The inference method to use
    :return: stdout, stderr
    """
    cmd = ['./iengine', method, filepath]
    proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return proc.communicate()


def run_tests(file, samples):
    """Runs all the tests in the experiment with the given file and number of samples
    :param file: The file to run the tests on
    :param samples: The number of samples to run
    :return: None
    """
    # Get the script dir, name and check if the file given exists
    test_dir = os.path.dirname(os.path.realpath(__file__))
    script_name = os.path.basename(__file__)
    if not os.path.isfile(os.path.join(test_dir, file)):
        sys.stderr.write('{0}: file \'{1}\' not found\n'.format(script_name, file))
        sys.exit(0)

    result_dir = os.path.join(test_dir, 'results')
    if not os.path.exists(result_dir):
        os.mkdir(result_dir)

    # Get a path to the build dir to run iengine and cd into it
    filepath = os.path.join(test_dir, file)
    exe_path = os.path.join(os.path.join(test_dir, '..'), 'cmake-build-debug')
    os.chdir(exe_path)

    # Open csv files for writing to
    time_dist = open(os.path.join(result_dir, 'time.csv'), 'a')
    inference_dist = open(os.path.join(result_dir, 'inference.csv'), 'a')
    time_writer = csv.DictWriter(time_dist, delimiter=',', fieldnames=['method',
                                                                       'file',
                                                                       'sample',
                                                                       'time'])
    inference_writer = csv.DictWriter(inference_dist, delimiter=',',
                                      fieldnames=['method', 'file',
                                                  'sample', 'inference_length'])
    time_writer.writeheader()
    inference_writer.writeheader()

    # Run through tests for all inference methods
    for method in ['FC', 'BC', 'TT']:
        timer = timeit.Timer(functools.partial(execute, filepath, method))
        avg = 0
        avg_path = 0

        # Run through all samples for the current inference method getting the execution
        # time and the number of inferences/models considered in the process
        for i in range(0, samples):
            print(timer.timeit(1))
            current, (result, err) = timer.timeit(1)
            avg += current * 1000
            result = result.decode('ascii').replace(',', '').replace(':', '')
            result_list = str.split(result)[1:]
            length = len(result_list)
            if method == 'TT':
                length = int(result_list[0])
            avg_path += length
            time_writer.writerow({'method': method, 'file': file, 'sample': i,
                                  'time': current})
            inference_writer.writerow({'method': method, 'file': file, 'sample': i,
                                       'inference_length': length})

        terminology = 'inferences'
        if method == 'TT':
            terminology = 'models'

        print('Method: {0}, Average time: {1:.3f}ms, Average {2}: {3}'.format(method,
              avg / samples, terminology, avg_path / samples))

    time_dist.close()
    inference_dist.close()

def description():
    return """
Runs IEngine tests, producing the following CSV files in the ./results directory:
    - inference.csv - the number of inferences/models found for every sample
    - time.csv - the execution time of every sample
These files can be then imported into excel or similar programs to produce graphs, 
get mean values, std. deviation etc."""

if __name__ == "__main__":
    parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter,
                                     description=description())
    parser.add_argument('file', type=str, help='The test file to execute tests on. Must '
                                               'contain TELL and ASK')
    parser.add_argument('samples', type=int, help='Number of samples to run for each '
                                                  'inference method')
    parser.add_argument('-o', '--overwrite',
                        help='Overwrites CSV data files instead of appending',
                        action='store_true')
    args = parser.parse_args()
    if args.overwrite:
        test_dir = os.path.dirname(os.path.realpath(__file__))
        results_dir = os.path.join(os.path.join(test_dir, 'results'))
        if os.path.exists(results_dir):
            shutil.rmtree(results_dir)


    run_tests(args.file, args.samples)
