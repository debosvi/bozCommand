
## generation profile name.
## mandatory (generates application for testing profile)
set(COMP_SRC_PROFILE "test")

## COMP_SRC_TEST_NAME var must be set to binary name (it will be automatically prefixed with 'test_' in order to identify easly appart from oyhre binaries).
## mandatory
set(COMP_SRC_TEST_NAME "base64")

## LOCAL_SRC_DIR_SUFFIX is the relative path prefix to append to component files directory in order to find source files to compile.
## optional but recommended
set(LOCAL_SRC_DIR_SUFFIX test)

## LOCAL_SRC_FILES is the list of files to compile (do not use any absolute path, automatic appending is performed by complte makefiles scheme.
## mandatory
set(LOCAL_SRC_FILES main.c)

## LOCAL_SRC_FILES_ADDED is the list of files to compile with absolute path (useful if generated files are somewhere).
## optional
# set(LOCAL_SRC_FILES_ADDED <somewhere absolute>)

## COMP_SRC_LIB_DEPS is the list of library dependencies (internal dependencies only).
## Build system will decide which static or shared is recommended.
## optional
set(COMP_SRC_LIB_DEPS b64)

## COMP_SRC_LIB_DEPS_STATIC is the list of static library dependencies (internal dependencies only).
## Be careful about system compatibility between static and shared libraries
## optional
# set(COMP_SRC_LIB_DEPS_STATIC other_static_lib)

## COMP_SRC_LIB_DEPS_SHARED is the list of shared library dependencies (internal dependencies only).
## Be careful about system compatibility between static and shared libraries.
## optional
# set(COMP_SRC_LIB_DEPS_SHARED other_shared_lib)


## COMP_EXT_LIB_DEPS is the list of external library dependencies.
## optional
# set(COMP_EXT_LIB_DEPS external_lib)