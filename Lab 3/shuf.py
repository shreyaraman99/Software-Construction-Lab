#!/usr/bin/python

import random, sys
from optparse import OptionParser

class randline:
    def __init__(self, filename):
        if filename == "-" or filename == "":
            self.lines = sys.stdin.readlines()
        else:
            f = open(filename, 'r')
            self.lines = f.readlines()
            f.close()

    def chooseline(self, count = 1, repeat = False):
        result = []
        if repeat:
            return list(self.lines)
        return random.choice(self.lines)

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE

    Output randomly selected lines from FILE."""

    parser = OptionParser(version=version_msg, usage=usage_msg)
    parser.add_option("-i", "--input-range", action="store", dest="lo_hi", default=False, help="treat each number LO through HI as an input line")
    parser.add_option("-n", "--head-count", action="store", dest="count", default="untilEOF", help="output at most COUNT lines")
    parser.add_option("-r", "--repeat", action="store_true", dest="repeat", default=False, help="output lines can be repeated")

    options, args = parser.parse_args(sys.argv[1:])

    try:
        numlines = int(options.count)
    except:
        parser.error("invalid NUMLINES: {0}".format(options.count))

    if numlines < 0:
        parser.error("negative count: {0}".format(numlines))

    if len(args) != 1:
        parser.error("wrong number of operands")

    input_file = args[0]
    try:
        generator = randline(input_file)
        for i in range(numlines):
            sys.stdout.write(lines[i])
    except IOError as e:
        errno = e.errno
        strerror = e.strerror
        parser.error("I/o error({0}): {1}".format(errno, strerror))

if __name__ == "__main__":
    main()
