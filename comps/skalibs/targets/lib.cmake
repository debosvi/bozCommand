
###############################################################################
set(COMP_SRC_PROFILE "library")

set(COMP_SRC_LIB_TYPE "both")
set(COMP_SRC_LIB_NAME "skarnet")

###############################################################################
set(LOCAL_SRC_DIR_SUFFIX src)

file(GLOB BYTESTR_FILES
    RELATIVE ${LOCAL_SRC_ROOTDIR}/${LOCAL_SRC_DIR_SUFFIX}
    ${LOCAL_SRC_ROOTDIR}/${LOCAL_SRC_DIR_SUFFIX}/byte_*.c
)

file(GLOB STRALLOC_FILES
    RELATIVE ${LOCAL_SRC_ROOTDIR}/${LOCAL_SRC_DIR_SUFFIX}
    ${LOCAL_SRC_ROOTDIR}/${LOCAL_SRC_DIR_SUFFIX}/stralloc_*.c
)

file(GLOB SIOVEC_FILES
    RELATIVE ${LOCAL_SRC_ROOTDIR}/${LOCAL_SRC_DIR_SUFFIX}
    ${LOCAL_SRC_ROOTDIR}/${LOCAL_SRC_DIR_SUFFIX}/siovec_*.c
)

file(GLOB GENSETDYN_FILES
    RELATIVE ${LOCAL_SRC_ROOTDIR}/${LOCAL_SRC_DIR_SUFFIX}
    ${LOCAL_SRC_ROOTDIR}/${LOCAL_SRC_DIR_SUFFIX}/gensetdyn_*.c
)

file(GLOB BITARRAY_FILES
    RELATIVE ${LOCAL_SRC_ROOTDIR}/${LOCAL_SRC_DIR_SUFFIX}
    ${LOCAL_SRC_ROOTDIR}/${LOCAL_SRC_DIR_SUFFIX}/bitarray_*.c
)

set(LOCAL_SRC_FILES
    alloc.c
    alloc_0.c
    genalloc_deepfree.c
    ${BITARRAY_FILES}
    ${BYTESTR_FILES}
    ${GENSETDYN_FILES}
    ${SIOVEC_FILES}
    ${STRALLOC_FILES}
)

