
SET(MAJOR_VERSION ${${PROJECT_NAME}_VERSION_MAJOR})
SET(MINOR_VERSION ${${PROJECT_NAME}_VERSION_MINOR})
SET(PATCH_VERSION ${${PROJECT_NAME}_VERSION_PATCH})

IF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_INSTALL_PREFIX ${USR_DIR})
SET(CPACK_SET_DESTDIR "on")
SET(CPACK_PACKAGING_INSTALL_PREFIX "/tmp")
SET(CPACK_GENERATOR "TGZ;DEB")

SET(CPACK_PACKAGE_DESCRIPTION "bozCommand package")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "boz command project" ) 
SET(CPACK_PACKAGE_VENDOR "Aquaplouf Land")
SET(CPACK_PACKAGE_CONTACT "Vincent de RIBOU <v.deribou@gmail.com>")
SET(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR_VERSION}")
SET(CPACK_PACKAGE_VERSION_MINOR "${MINOR_VERSION}")
SET(CPACK_PACKAGE_VERSION_PATCH "${PATCH_VERSION}")
SET(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}_${CMAKE_SYSTEM_PROCESSOR}")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}_${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}_${CMAKE_SYSTEM_PROCESSOR}")

SET(CPACK_DEBIAN_PACKAGE_DEPENDS "skarnet (>=2.4.0.1)")
SET(CPACK_DEBIAN_PACKAGE_CONFLICTS "")

SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
SET(CPACK_DEBIAN_PACKAGE_SECTION "misc")
SET(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})

SET(CPACK_COMPONENTS_ALL Libraries ApplicationData)
INCLUDE(CPack)

ENDIF(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")

