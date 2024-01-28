
#ifndef IO_UTILS_H_
#define IO_UTILS_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    

    extern char *read_file_to_string(const char *file_path);

    extern char *get_basename(const char *file_path);

#endif
