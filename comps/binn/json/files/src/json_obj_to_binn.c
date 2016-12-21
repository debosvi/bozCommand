
#include "private/json_p.h"

///////////////////////////////////////////////////////////////////////////////
binn_t json_obj_to_binn(json_t *base) {
    int _ret=0;
    binn_t item=BINN_INVALID;
    json_t  *value=0;
    const char  *key=0;
    
    switch (json_typeof(base)) {
        case JSON_OBJECT:
            item = binn_object();
            json_object_foreach(base, key, value) {
                if(binn_object_add_item(item, (char*)key, json_obj_to_binn(value))) { 
                    _ret=1;
                    goto exit;
                }
            }
            break;

        case JSON_ARRAY:
            item = binn_list();
            for (int i = 0; i < (int)json_array_size(base); i++) {
                value = json_array_get(base, i);
                if (binn_list_add_item(item, json_obj_to_binn(value)))  { 
                    _ret=1;
                    goto exit;
                }
            }
            break;

        case JSON_STRING: 
            item=binn_string((char*)json_string_value(base));
            break;

        case JSON_INTEGER:
            item=binn_int64(json_integer_value(base));
            break;

        case JSON_REAL:
            item=binn_double(json_real_value(base));
            break;

        case JSON_TRUE:
            item=binn_bool(1);
            break;

        case JSON_FALSE:
            item=binn_bool(0);
            break;

        // case JSON_NULL:
            // return binn_null();

        default:
            break;
    }
    
exit:
    if(_ret) {
        binn_free(item);
        item = BINN_INVALID;
    }
    return item;
}