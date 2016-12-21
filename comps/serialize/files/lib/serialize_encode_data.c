
#include "private/serialize_p.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
char* serialize_encode_data(const char const *data, const unsigned int length) {
    const unsigned int al=2*length;
    base64_encodestate es;
    char* buf=0;
    char *p=0;
    int lg=0;
    
    if(!data || !length) return 0;
    
    buf=alloc(al);
    if(!buf) return 0;    
    memset(buf, 0, al);
    
    p=buf;
    base64_init_encodestate(&es);
    lg=base64_encode_block(data, length, buf, &es);
    p+=lg;
    lg=base64_encode_blockend(p, &es);
    p+=lg;
    (*p)=0;
    
    return buf;    
}
