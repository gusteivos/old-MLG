
#ifndef DATA_TYPE_H_
#define DATA_TYPE_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <inttypes.h>
    #include <stdint.h>


    typedef enum data_type_type_e
    {

        DATA_TYPE_NONE = 0,

        DATA_TYPE_INT8 ,
        DATA_TYPE_INT16,
        DATA_TYPE_INT32,
        DATA_TYPE_INT64,

    } data_type_type_t;

    typedef struct data_type_s
    {

        data_type_type_t type;


        union
        {

            uint8_t i8 ;
            int16_t i16;
            int32_t i32;
            int64_t i64;

        };

    } data_type_t;


    extern data_type_t string_to_data_type(char *str);

#endif
