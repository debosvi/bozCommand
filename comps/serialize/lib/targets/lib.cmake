
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
set(LOCAL_SRC_DIR_SUFFIX src)

set(LOCAL_SRC_FILES
    serialize_get_command_name.c
    serialize.c
)
