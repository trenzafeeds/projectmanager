"""
config.py
"""

import sys, os, ctypes
import ConfigParser as parser

MAXSTRING = 100
MAXMODES = 20
MODENAMELEN = 15

# To insure an exact match between struct definitions,
# the STRUCT_FORM struct definition must be edited manually
# in this file and headers/settings_struct.h
# before recompiling projectmanager.
STRUCT_FORM = [(("git", ctypes.c_int), 0),
               (("git_readme", ctypes.c_int), 0),
               (("git_ignore", ctypes.c_int), 0),
               (("git_commit", ctypes.c_int), 0),
               (("mode_count", ctypes.c_int), 0),
               (("modes", (ctypes.c_char * MODENAMELEN) * MAXMODES), None)
               ]
TEMPLATE = [ option[0] for option in STRUCT_FORM ]
DEFAULTS = { option[0][0] : option[1] for option in STRUCT_FORM }
INTERNAL_ONLY = ["mode_count", "modes"]

# Apply the same editing rules as STRUCT_FORM to MODE_P_FORM
MODE_P_FORM = [(("special", ctypes.c_int), 0),
               (("name", ctypes.c_char * MAXSTRING), None),
               (("val", ctypes.c_char * MAXSTRING), None)
               ]
MODE_P_TEMPLATE = [ option[0] for option in MODE_P_FORM ]

class SettingsStruct(ctypes.Structure):
    global TEMPLATE
    _fields_ = TEMPLATE

class ModePStruct(ctypes.Structure):
    global MODE_P_TEMPLATE
    _fields_ = MODE_P_TEMPLATE

class SettingsData:

    def __init__(self):
        # self.settings_dict is initialized with the DEFAULT
        # values for each setting. Default values are also
        # used to typecheck user-entered values.
        global DEFAULTS
        self.settings_dict = DEFAULTS

        self.full_dict = None
        
        # self.settings_struct will be initialized and populated
        # once user settings are loaded into self.settings_dict
        self.struct_obj = None # SettingsStruct(values)

    def read_input(self, full_dict):
        self.full_dict = full_dict
        config = full_dict['settings']
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

    def add_defaults(self, arg_list):
        global MAXMODES
        global MODENAMELEN
        modec = len(self.full_dict['modes'].keys())
        c_modes = make_char_array(self.full_dict['modes'].keys(),\
                                  MODENAMELEN, MAXMODES)
        arg_list.append(modec)
        arg_list.append(c_modes)
        return 0

    def gen_struct(self):
        global TEMPLATE
        global INTERNAL_ONLY
        struct_args = []
        for field in TEMPLATE:
            if field[0] not in INTERNAL_ONLY:
                struct_args.append(self.settings_dict[field[0]])
        # Now add mode count and mode list
        self.add_defaults(struct_args)
        try:
            self.struct_obj = SettingsStruct(*struct_args)
        except:
            print "Error creating ctypes setting struct."
            exit(1)
        return 0

class ModesData:

    def __init__(self):
        self.count = 0
        self.mode_objs = {}

    def read_input(self, modes_dict):
        ret = 0
        self.modes_dict = modes_dict
        return ret

    def gen_struct(self):
        for rawmode in self.modes_dict.keys():
            self.mode_objs[rawmode] = Mode(self.modes_dict[rawmode])

class Mode:

    def __init__(self, pair_list):
        self.pairs = pair_list
        self.p_structs = []
        for pair in self.pairs:
            self.p_structs.append(ModePStruct(0,\
                                              pair[0].format('utf-8'),\
                                              pair[1].format('utf-8')))
        self.size = len(self.p_structs)
        
    
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

def make_char_array(pylist, wordc, letterc):
    arr = ((ctypes.c_char * wordc) * letterc)()
    for i in xrange(len(pylist)):
        arr[i].value = pylist[i]
    return arr

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
        elif section == 'settings':
            config_dict[section] = options_dict(config_obj, section)
        else:
            print "Error: unknown section", section, "not valid."
            exit(1)
    return config_dict

########################################

def main(conf_path, iconf_path):
    config_dict = post_parse(parse(conf_path))
    settings = SettingsData()
    modes = ModesData()
    rc = settings.read_input(config_dict)
    rc += modes.read_input(config_dict['modes'])
    print "Read config with", rc, "errors."
    # Must determine/insert mode pair counts BEFORE HERE
    modes.gen_struct()
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
        
