###############################################################################
#
# Description       : CMake build script for libTSB
# 
###############################################################################


include(CheckLibraryExists)
check_library_exists(m sqrt "" HAVE_LIBM)

# generate configuration for this system
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/common/libtsb-config-common.h.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/common/libtsb-config-common.h"
  )

# Replace: @PACKAGE_VERSION@ and @LIBTSB_VERSION_NUMERIC@
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/common/libtsb-version.h.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/common/libtsb-version.h"
  )

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/common/libtsb-namespace.h.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/common/libtsb-namespace.h"
  )
  

###############################################################################
#
# mark header files for installation
#
foreach(dir annotation common compress conversion extension math units util validator xml  )

  file(GLOB header_files "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*.h")
  install(FILES ${header_files} DESTINATION include/tsb/${dir})

endforeach(dir)

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${files} DESTINATION include/tsb)

# install generated headers
install(FILES 
       "${CMAKE_CURRENT_BINARY_DIR}/common/libtsb-version.h"
       "${CMAKE_CURRENT_BINARY_DIR}/common/libtsb-config-common.h"
       "${CMAKE_CURRENT_BINARY_DIR}/common/libtsb-namespace.h"
        DESTINATION include/tsb/common)

###############################################################################
#
# specify include directories
#
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(BEFORE ${LIBSBML_INCLUDE_DIR})
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/..)
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR}/..)

if (EXTRA_DEFS)
add_definitions(${EXTRA_DEFS})
endif()

###############################################################################
#
# Find all sources
#

foreach (directory common tsb )

  set(dir ${directory})

  if ("${directory}" STREQUAL "tsb")
    set(dir ".")
  endif()


  file(GLOB temp
      ${dir}/*.cpp
      ${dir}/*.c
      ${dir}/*.h)

  # create source group for IDEs
  source_group(${directory} FILES ${temp})

  # add to libtsb sources
  set(LIBTSB_SOURCES ${LIBTSB_SOURCES} ${temp})

endforeach()

###############################################################################
#
# this is a directory level operation!
#
if (MSVC)
if (WITH_STATIC_RUNTIME)
  foreach(flag_var
    CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
    CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
    CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
    CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)

    if(${flag_var} MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    endif(${flag_var} MATCHES "/MD")


  endforeach(flag_var)
  add_definitions( -D_MT)
endif(WITH_STATIC_RUNTIME)
endif(MSVC)

###############################################################################
#
# Build library
#

if (NOT LIBTSB_SKIP_SHARED_LIBRARY)

add_library (${LIBTSB_LIBRARY} SHARED ${LIBTSB_SOURCES} )

if (LIBTSB_SHARED_VERSION)
  set_target_properties(${LIBTSB_LIBRARY} PROPERTIES COMPILE_DEFINITIONS "LIBTSB_EXPORTS=1")
  set_target_properties(${LIBTSB_LIBRARY} PROPERTIES
                      SOVERSION ${LIBTSB_VERSION_MAJOR}
                      VERSION ${LIBTSB_VERSION_MAJOR}.${LIBTSB_VERSION_MINOR}.${LIBTSB_VERSION_PATCH})
endif()

target_link_libraries(${LIBTSB_LIBRARY} ${LIBSBML_LIBRARY}  ${EXTRA_LIBS})

INSTALL(TARGETS ${LIBTSB_LIBRARY}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

endif()

add_library (${LIBTSB_LIBRARY}-static STATIC ${LIBTSB_SOURCES} )
if (WIN32 AND NOT CYGWIN)
  # don't decorate static library 
  set_target_properties(${LIBTSB_LIBRARY}-static PROPERTIES COMPILE_DEFINITIONS "LIBTSB_STATIC=1")
endif(WIN32 AND NOT CYGWIN)

target_link_libraries(${LIBTSB_LIBRARY}-static ${LIBSBML_LIBRARY}  ${EXTRA_LIBS})

INSTALL(TARGETS ${LIBTSB_LIBRARY}-static
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
