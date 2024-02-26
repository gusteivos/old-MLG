#include <data_type.h>


data_type_t string_to_data_type(char *str)
{

    data_type_t result;

    result.type = DATA_TYPE_NONE;


    char *endptr;

    intmax_t int_val = strtoimax(str, &endptr, 10);

    if (*endptr == '\0' && int_val >= INT8_MIN && int_val <= INT64_MAX)
    {

        if (int_val >= 0 && int_val <= UINT8_MAX)
        {

            result.type = DATA_TYPE_INT8;

            result.i8 = (uint8_t)int_val;

        }
        else if (int_val >= INT16_MIN && int_val <= INT16_MAX)
        {

            result.type = DATA_TYPE_INT16;

            result.i16 = (int16_t)int_val;

        }
        else if (int_val >= INT32_MIN && int_val <= INT32_MAX)
        {

            result.type = DATA_TYPE_INT32;

            result.i32 = (int32_t)int_val;

        }
        else
        {

            result.type = DATA_TYPE_INT64;

            result.i64 = int_val;

        }

    }


    return result;

}
