
#set(CMAKE_PREFIX_PATH /usr/share/lib/cmake)
#
#find_package(Skarnet REQUIRED)
#message(STATUS "Skarnet found: " ${SKARNET_VERSION_STRING})
#include_directories(${SKARNET_INCLUDE_DIRS})
#link_directories(${SKARNET_LIBRARY_DIRS})

    
include_directories($ENV{HOME}/usr/include)
link_directories($ENV{HOME}/usr/lib)
link_directories($ENV{HOME}/usr/lib/skalibs)

include_directories(${PROJECT_SOURCE_DIR}/cots/include)
link_directories(${PROJECT_SOURCE_DIR}/cots/lib)
