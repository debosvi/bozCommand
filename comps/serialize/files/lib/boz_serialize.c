
#include "private/serialize_p.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
char* boz_serialize(const boz_serialize_type_t type, const char const *name, 
    const void const *data, const unsigned int length) {
    
    char* _ret=0, *encoded=0;
    binn_t head=BINN_INVALID;
    
    if(!name) return 0;
    if(!data) return 0;
    if(!length) return 0;
    
    head=binn_object();
    if(binn_check(head)) goto exit;
    
    if(binn_object_add_item(head, boz_serialize_type_fieldname, binn_string(serialize_get_command_name(type))))
        goto exit;
    if(binn_object_add_item(head, boz_serialize_name_fieldname, binn_string(name)))
        goto exit;
    encoded=serialize_encode_data(data, length);
    if(!encoded) 
        goto exit;
    if(binn_object_add_item(head, boz_serialize_data_fieldname, binn_string(encoded)))
        goto exit;
    
    _ret=binn_to_json_str(head);
    free(encoded);
    binn_free(head);
    
exit:
    if(!_ret) {
        binn_free(head);        
    }

    return _ret;
}

