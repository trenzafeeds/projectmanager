"""
config.py
"""

import sys, os, ctypes
import ConfigParser as parser

MAXSTRING = 40

# To insure an exact match between struct definitions,
# the STRUCT_FORM struct definition must be edited manually
# in this file and src/utils.c before recompiling projectmanager.
STRUCT_FORM = [(("git", ctypes.c_int), 1)]
TEMPLATE = [ option[0] for option in STRUCT_FORM ]
DEFAULTS = { option[0][0] : option[1] for option in STRUCT_FORM }
 
class SettingsStruct(ctypes.Structure):
    global MAXSTRING
    global TEMPLATE
    _fields_ = TEMPLATE

class SettingsData:

    def __init__(self):
        # self.settings_dict is initialized with the DEFAULT
        # values for each setting. Default values are also
        # used to typecheck user-entered values.
        global DEFAULTS
        self.settings_dict = DEFAULTS
        
        # self.settings_struct will be initialized and populated
        # once user settings are loaded into self.settings_dict
        self.struct_obj = None # SettingsStruct(values)

    def read_input(self, config):
        error_count = 0
        for field in config.keys():
            try:
                self.settings_dict[field] =\
                type(self.settings_dict[field])(config[field])
                if type(self.settings_dict[field]) is str:
                        self.settings_dict[field].encode('utf-8')
                
            except KeyError:
                error_count += 1
                print "Invalid field", field, "not read."
                
            except ValueError:
                error_count += 1
                print "Config value", config[field],\
                    "could not be converted to type",\
                    type(self.settings_dict[field]).__name__,\
                    "for field", field + "."
                print "Maintaining default value",\
                    self.settings_dict[field] + "."

            except:
                error_count += 1
                print "Unexpected error at", field + "."
                
        return error_count

    def gen_struct(self):
        global TEMPLATE
        struct_args = []
        for field in TEMPLATE:
            struct_args.append(self.settings_dict[field[0]])
        try:
            self.struct_obj = SettingsStruct(*struct_args)
        except:
            print "Error creating ctypes setting struct."
            exit(1)
        return 0
    
######################################################

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
        print "Error: unexpected settings variable type error at:"
        print py_var
        exit(1)

def options_dict(parser, section):
    optionsd = {}
    for option in parser.options(section):
        try:
            if parser.getboolean(section, option): optionsd[option] = 1
            else: optionsd[option] = 0
        except ValueError:
            optionsd[option] = parser.get(section, option)
    return optionsd

def parse(path):
    config_parsed = parser.ConfigParser()
    if not config_parsed.read(path):
        print "Error reading configuration file at", path
        exit(1)
    return config_parsed

def post_parse(config_obj):
    config_dict = {'modes':{}}
    for section in config_obj.sections():
        if section[0:5] == 'mode/':
            config_dict['modes'][section[5:]] = config_obj.items(section)
        else:
            config_dict[section] = options_dict(config_obj, section)
    return config_dict

########################################

def main(conf_path, iconf_path):
    config_dict = post_parse(parse(conf_path))
    settings = SettingsData()
    rc = settings.read_input(config_dict['settings'])
    print "Read config with", rc, "errors."
    settings.gen_struct()
    iconf_file = writeb_open(iconf_path)
    print "Writing updated configuration to iconf file..."
    iconf_file.write(settings.struct_obj)
    iconf_file.flush()
    iconf_file.close()
    return 0

if __name__ == "__main__":

    if len(sys.argv) < 3:
        print "Enter paths to config and iconf as arguments."
        exit(1)
    else:
        exit(main(sys.argv[1], sys.argv[2]))
        
