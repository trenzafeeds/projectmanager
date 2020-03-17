"""
config.py
"""

import sys, os
import ConfigParser as parser

headerstring = "# .tmp/iconf\n#\n# Internal configuration file for projectmanager\n# DO NOT TOUCH\n"

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
    
def main(conf_path):
    dump_config(post_parse(parse(conf_path))) 

if __name__ == "__main__":

    if len(sys.argv) == 1:
        print "Enter path to config as second argument."
        exit
    else:
        main(sys.argv[1]) 
