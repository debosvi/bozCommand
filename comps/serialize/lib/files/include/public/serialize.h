 
#ifndef __BOZ_SERIALIZE_H__
#define __BOZ_SERIALIZE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    SERIALIZE_NONE=0,
    SERIALIZE_SEND,
    SERIALIZE_RECEIVE,
    SERIALIZE_EVENT,
    SERIALIZE_COUNT 
} boz_serialize_type_t;
    
extern char* boz_serialize(
    const boz_serialize_type_t type,
    const char const *name, 
    const void const *data, 
    const unsigned int length
    );

        
extern boz_serialize_type_t boz_unserialize_get_type(const char const *buf);
extern char* boz_unserialize_get_name(const char const *buf);
extern char* boz_unserialize_get_data(const char const *buf);
extern unsigned int boz_unserialize_get_length(const char const *buf);

#ifdef __cplusplus
}
#endif

#endif  // __BOZ_SERIALIZE_H__
