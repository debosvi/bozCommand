
#include "private/serialize_p.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
char* boz_unserialize_get_data(const char const *buf) {
    
    char* _ret=0;
    char * p=0;
    siovec_t sio;
    binn_t head=BINN_INVALID;
    binn_t data=BINN_INVALID;
       
    if(!buf) goto exit;
    
    head=json_to_binn(buf);
    if(binn_object_get_item(head, boz_serialize_data_fieldname, &data)) goto exit;
    if(binn_to_string(data, &p)) goto exit;
    
    if(!serialize_decode_data(p, &sio) && sio.len) {
        _ret=sio.s;
    }        
        
exit:
    binn_free(data);    
    binn_free(head);    
    return _ret;
}

