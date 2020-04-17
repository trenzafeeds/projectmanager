"""
config.py
"""

import sys, os, ctypes
import ConfigParser as parser

MAXSTRING = 40

# To insure an exact match between struct definitions,
# the SettingsStruct definition must be edited manually
# in this file and src/utils.c before recompiling projectmanager.
class SettingsStruct(ctypes.Structure):
    global MAXSTRING
    _fields_ = [("git", ctypes.c_int)]

class SettingsData:

    def __init__(self):
        # self.settings_dict is initialized with the DEFAULT
        # values for each setting. Default values are also
        # used to typecheck user-entered values.
        self.settings_dict = {"git" : 0}
        
        # self.settings_struct will be initialized and populated
        # once user settings are loaded into self.settings_dict
        self.settings_struct = None # SettingsStruct(values)
        

def writeb_open(filename):
    try:
        return open(filename, "wb")
    except:
        print "Error opening internal config file at", filename
        exit(1)

def py_to_ctype(py_var):
    global MAXSTRING
    if type(py_var) is int:
        return ctypes.c_int
    elif type(py_var) is str:
        if len(py_var) >= MAXSTRING:
            print "Overflow error at:"
            print py_var
            print "string values for variables must be", MAXSTRING, "characters or less."
            exit(1)
        else:
            return (ctypes.c_char * MAXSTRING)
    else:
        print "Error: settings variable type error at:"
        print py_var
        exit(1)

def parse(path):
    config_parsed = parser.ConfigParser()
    try:
        config_parsed.read(path)
    except:
        print "Error reading configuration file at", path
        exit(1)
    return config_parsed

def post_parse(config_obj):
    config_dict = {'modes':{}}
    for section in config_obj.sections():
        if section[0:5] == 'mode/':
            config_dict['modes'][section[5:]] = config_obj.items(section)
        else:
            config_dict[section] = config_obj.items(section)
    return config_dict

############################

def print_commands(command_string):
    command_list = command_string.split('|||')
    for command in command_list:
        print "$$", command.lstrip()

def print_values(dict_item):
    commands_index = None
    for values in dict_item:
        if values[0] != 'commands':
            print "{} = {}".format(values[0], values[1])
        else:
            commands_index = dict_item.index(values)
    if commands_index != None:
        print_commands(dict_item[commands_index][1])
    print "--"

def print_rest(config_dict):
    for section in config_dict.keys():
        if (section != 'settings') and (section != 'modes'):
            print "% {}".format(section)
            print_values(config_dict[section])
        elif section == 'modes':
            for mode in config_dict['modes'].keys():
                    print "%% {}".format(mode)
                    print_values(config_dict['modes'][mode])
        elif section == 'settings':
            pass

def dump_config(config_dict):
    print headerstring
    print "%%% settings"
    print_values(config_dict['settings'])
    print_rest(config_dict)

##############################

def main(conf_path, iconf_path):
    iconf_file = writeb_open(iconf_path)
    return 0

if __name__ == "__main__":

    if len(sys.argv) < 3:
        print "Enter paths to config and iconf as arguments."
        exit(1)
    else:
        exit(main(sys.argv[1], sys.argv[2]))
        
