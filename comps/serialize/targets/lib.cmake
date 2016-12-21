
###############################################################################
set(COMP_SRC_PROFILE "library")

set(COMP_SRC_LIB_TYPE "both")
set(COMP_SRC_LIB_NAME serialize)

set(COMP_SRC_LIB_DEPS
    binn_json
    b64
)

# set(COMP_EXT_LIB_DEPS )

###############################################################################
set(LOCAL_SRC_DIR_SUFFIX lib)

set(LOCAL_SRC_FILES
    ## internal APIs
    serialize_p.c
    serialize_get_command_name.c
    serialize_encode_data.c
    serialize_decode_data.c
    
    # public APIs
    boz_serialize.c
    boz_unserialize_get_type.c
    boz_unserialize_get_name.c
    boz_unserialize_get_data.c
)
