## @file    CMakeLists.txt
## @brief   CMake build script
## @author  Frank T. Bergmann
##
## <!--------------------------------------------------------------------------
## This file is part of libLX.  Please visit http://sbml.org for more
## information about LX, and the latest version of libLX.
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
## in the file named "LICENSE.txt" included with this software distribution
## and also available online as http://sbml.org/software/libsbml/license.html
## ------------------------------------------------------------------------ -->
include(${LIBTSB_ROOT_SOURCE_DIR}/common.cmake)

file(GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )
file(GLOB H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h )

set(TEST_FILES ${CPP_FILES} ${C_FILES} ${H_FILES})

# include_directories(${LIBLX_ROOT_SOURCE_DIR}/include/lx)
include_directories(BEFORE ${LIBTSB_ROOT_BINARY_DIR}/src)

if (EXTRA_INCLUDE_DIRS) 
 include_directories(${EXTRA_INCLUDE_DIRS})
endif(EXTRA_INCLUDE_DIRS)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_executable(test_tsb ${TEST_FILES})
target_link_libraries(test_tsb ${LIBTSB_LIBRARY}-static ${LIBTSB_LIBS} ${EXTRA_LIBS})

add_test(test_tsb_run ${CMAKE_CURRENT_BINARY_DIR}/test_tsb )
