
#include "private/serialize_p.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int serialize_decode_data(const char const *encoded, siovec_t *v) {
    const unsigned int al=strlen(encoded);
    int lg=0;
    base64_decodestate ds;
    char* buf=0;

    if(!encoded || !v) return 1;  
           
    buf=alloc(al);    
    if(!buf) return 1;    
    memset(buf, 0, al);
    
    base64_init_decodestate(&ds);
    lg=base64_decode_block(encoded, al, buf, &ds);
    if(!lg) {
        free(buf);
        return 1;
    }
    
    v->s=buf;
    v->len=lg;    
    
    return 0;    
}
