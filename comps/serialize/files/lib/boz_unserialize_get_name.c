
#include "private/serialize_p.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
char* boz_unserialize_get_name(const char const *buf) {
    
    char* _ret=0;
    binn_t head=BINN_INVALID;
    binn_t name=BINN_INVALID;
       
    if(!buf) goto exit;
    
    head=json_to_binn(buf);
    if(binn_object_get_item(head, boz_serialize_name_fieldname, &name)) goto exit;
    if(binn_to_string(name, &_ret)) goto exit;
        
exit:
    binn_free(name);    
    binn_free(head);    
    return _ret;
}

