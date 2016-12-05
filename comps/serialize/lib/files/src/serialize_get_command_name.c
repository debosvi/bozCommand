
#include "private/serialize_p.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static const char const *serialize_names[] = {
    "send_data",
    "receive_data",
    "event_data"    
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
const char const* serialize_get_command_name(const boz_serialize_type_t type) {
    if((type<SERIALIZE_SEND) || (type>=SERIALIZE_COUNT) )
        return NULL;
    return serialize_names[type];
}

