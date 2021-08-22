## @file    CMakeLists.txt
## @brief   CMake build script for example programs
## @author  Frank T. Bergmann
##
## <!--------------------------------------------------------------------------
## This file is part of SBML.  Please visit http://sbml.org for more
## information about SBML.
##
## Copyright (C) 2013-2018 jointly by the following organizations:
##     1. California Institute of Technology, Pasadena, CA, USA
##     2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
##     3. University of Heidelberg, Heidelberg, Germany
##
## Copyright (C) 2009-2013 jointly by the following organizations:
##     1. California Institute of Technology, Pasadena, CA, USA
##     2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
##
## Copyright (C) 2006-2008 by the California Institute of Technology,
##     Pasadena, CA, USA
##
## Copyright (C) 2002-2005 jointly by the following organizations:
##     1. California Institute of Technology, Pasadena, CA, USA
##     2. Japan Science and Technology Agency, Japan
##
## This library is free software; you can redistribute it and/or modify it
## under the terms of the GNU Lesser General Public License as published by
## the Free Software Foundation.  A copy of the license agreement is provided
## in the file named "LICENSE.txt" included with this software distribution.
## ------------------------------------------------------------------------ -->

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${LINKED_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../src)
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR}/../../src)

if (EXTRA_INCLUDE_DIRS)
include_directories(${EXTRA_INCLUDE_DIRS})
endif(EXTRA_INCLUDE_DIRS)

foreach(example

	createTSB
  echoTSB

)
    add_executable(example_cpp_${example} ${example}.cpp)

    if (WIN32 AND NOT CYGWIN)
    # don't decorate static library 
    if(WITH_LIBLX)
      set_target_properties(example_cpp_${example} PROPERTIES COMPILE_DEFINITIONS "LIBLX_STATIC=1;LIBTSB_STATIC=1")
    endif()
    endif(WIN32 AND NOT CYGWIN)


    set_target_properties(example_cpp_${example} PROPERTIES  OUTPUT_NAME ${example})
    target_link_libraries(example_cpp_${example} ${LIBTSB_LIBRARY}-static)


    if (WITH_ZLIB)
        target_link_libraries(example_cpp_${example} ${LIBZ_LIBRARY})
    endif(WITH_ZLIB)

endforeach()
