
#include "private/serialize_p.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
boz_serialize_type_t boz_unserialize_get_type(const char const *buf) {
    
    int _ret=BOZ_SERIALIZE_NONE;
    binn_t head=BINN_INVALID;
    binn_t type=BINN_INVALID;
    char *str=0;
       
    if(!buf) goto exit;
    
    head=json_to_binn(buf);
    if(binn_object_get_item(head, boz_serialize_type_fieldname, &type)) goto exit;
    if(binn_to_string(type, &str)) goto exit;
    if(!str) goto exit;
    
    _ret=serialize_get_command_type(str);    
    
exit:
    binn_free(type);    
    binn_free(head);    
    return _ret;
}

