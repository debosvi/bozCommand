
#include "private/serialize_p.h"

static char* serialize_encode_data(const char const *data, const unsigned int length) {
    const unsigned int al=2*length;
    base64_encodestate es;
    char* buf=alloc(al);
    if(!buf) return NULL;    
    memset(buf, 0, al);
    base64_init_encodestate(&es);
    base64_encode_block(data, length, buf, &es);
    base64_encode_blockend(buf, &es);
    return buf;    
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
char* boz_serialize(const boz_serialize_type_t type, const char const *name, 
    const void const *data, const unsigned int length) {
    
    char* _ret=0, *encoded=0;
    binn_t head=0;
    
    if(!name) return (errno=EINVAL,NULL);
    if(!data) return (errno=EINVAL,NULL
    );
    if(!length) return (errno=EINVAL,NULL);
    
    head=binn_object();
    if(!head) goto exit;
    
    if(binn_object_add_item(head, "type", binn_string(serialize_get_command_name(type))))
        goto exit;
    if(binn_object_add_item(head, "name", binn_string(name)))
        goto exit;
    encoded=serialize_encode_data(data, length);
    if(!encoded) 
        goto exit;
    if(binn_object_add_item(head, "data", binn_string(data)))
        goto exit;
    
    _ret=binn_to_json_str(head);
    free(encoded);
    binn_free(head);
    
exit:
    if(!_ret) {
        if(head) binn_free(head);        
    }

    return _ret;
}

