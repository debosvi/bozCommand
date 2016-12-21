
#ifndef __BOZ_SERIALIZE_PRIVATE_H__
#define __BOZ_SERIALIZE_PRIVATE_H__

#include <stdlib.h>
#include <string.h>

#include <boz/serialize.h>
#include <restricted/serialize_r.h>

#include <binn/json.h>

#include <b64/cencode.h>
#include <b64/cdecode.h>

#include <skalibs/alloc.h>
#include <skalibs/siovec.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const char* boz_serialize_type_fieldname;
extern const char* boz_serialize_name_fieldname;
extern const char* boz_serialize_data_fieldname;

extern const char const* serialize_get_command_name(const boz_serialize_type_t type);
extern boz_serialize_type_t serialize_get_command_type(const char* const str);

extern char* serialize_encode_data(const char const *data, const unsigned int length);
extern int serialize_decode_data(const char const *buf, siovec_t *v);

#ifdef __cplusplus
}
#endif

#endif // __BOZ_SERIALIZE_PRIVATE_H__
