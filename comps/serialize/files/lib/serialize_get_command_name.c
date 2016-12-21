
#include "private/serialize_p.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static const char* const serialize_names[] = {
    "unknown",
    "send_data",
    "receive_data",
    "event_data",    
    "unknown"    
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
const char const* serialize_get_command_name(const boz_serialize_type_t type) {
    if((type<BOZ_SERIALIZE_SEND) || (type>=BOZ_SERIALIZE_COUNT) )
        return 0;
    return serialize_names[type];
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
boz_serialize_type_t serialize_get_command_type(const char* const str) {
    boz_serialize_type_t _ret=BOZ_SERIALIZE_NONE;
    
    if(!str) goto exit;
    
    for(int i=BOZ_SERIALIZE_SEND; i<BOZ_SERIALIZE_COUNT; i++) {
        char *p=(char*)serialize_names[i];
        if(!strncmp(str, p, strlen(p))) {
            _ret=i;
            break;
        }
    }

exit:
    return _ret;
}

