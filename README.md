# What's this
This is a simple C program converting INI config file (without section headers) into JSON string.

## How to use
It uses stdin for input and stdout for output. All errors are printed to stderr.

## Special chars handling

1. These characters will be treated as escape character:
    - '\\' (replaced with '\\\\')
    - '"' (replaced with '\"')

2. Blank lines and comment lines (starting with '#') will be ignored.
