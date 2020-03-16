"""
config.py
"""

import sys, os
import ConfigParser as parser

def parse(path):
    config_parsed = parser.ConfigParser()
    try:
        config_parsed.read(path)
    except:
        print "Error reading configuration file at", path
        exit(1)

def main(conf_path):
    parse(conf_path)

if __name__ == "__main__":

    if len(sys.argv) == 1:
        print "Enter path to config as second argument."
        exit
    else:
        main(sys.argv[1]) 
