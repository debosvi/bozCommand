
#ifndef __BOZ_SERIALIZE_PRIVATE_H__
#define __BOZ_SERIALIZE_PRIVATE_H__

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <boz/serialize.h>
#include <restricted/serialize_r.h>

#include <binn/json.h>

#include <b64/cencode.h>
#include <b64/cdecode.h>

#include <skalibs/alloc.h>

#ifdef __cplusplus
extern "C" {
#endif

const char const* serialize_get_command_name(const boz_serialize_type_t type);

#ifdef __cplusplus
}
#endif

#endif // __BOZ_SERIALIZE_PRIVATE_H__
