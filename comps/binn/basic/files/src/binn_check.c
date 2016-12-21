
#include "private/binn_p.h"

///////////////////////////////////////////////////////////////////////////////
int binn_check(const binn_t item) {
    binn_internal_t* _p=0;
    
    if(item==BINN_INVALID) return 1;    
    
    _p = GENSETDYN_P(binn_internal_t, &binn_storage_g, item);
    if(!_p) return 0;
    return binn_is_valid(_p, 0, 0);
}