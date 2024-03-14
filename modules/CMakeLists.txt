# ##############################################################################
# modules/CMakeLists.txt
#
# Licensed to the Apache Software Foundation (ASF) under one or more contributor
# license agreements.  See the NOTICE file distributed with this work for
# additional information regarding copyright ownership.  The ASF licenses this
# file to you under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License.  You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations under
# the License.
#
# ##############################################################################
# dll name
set(TARGET_NAME "liblossless")
set(CMAKE_DEBUG_POSTFIX _d)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

##################################################################################
# target
##################################################################################
file(GLOB_RECURSE SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hh
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hxx
)

add_library(${TARGET_NAME} ${SOURCES})
add_library(${TARGET_NAME}::${TARGET_NAME} ALIAS ${TARGET_NAME})

target_include_directories(${TARGET_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (UNIX)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
    target_link_libraries(
        ${TARGET_NAME}
        gcov
    )
endif()

##################################################################################
# eBUS SDK
##################################################################################
if(MSVC)
    target_link_directories(${TARGET_NAME} PUBLIC $ENV{PUREGEV_ROOT}/Libraries)
    target_include_directories(${TARGET_NAME} PRIVATE $ENV{PUREGEV_ROOT}/Includes)
elseif(UNIX)
    target_link_directories(${TARGET_NAME} PUBLIC $ENV{PUREGEV_ROOT}/lib /opt/jai/ebus_sdk/Ubuntu-22.04-x86_64/lib)
    target_include_directories(${TARGET_NAME} PRIVATE $ENV{PUREGEV_ROOT}/include /opt/jai/ebus_sdk/Ubuntu-22.04-x86_64/include)
    target_link_libraries(
        ${TARGET_NAME}
        PvBase
        PvBuffer
        PvDevice
        PvGenICam
        PvStream
        PvSystem
    )
endif()

install(TARGETS ${TARGET_NAME} RUNTIME DESTINATION bin CONFIGURATIONS ${CMAKE_CONFIGURATION_TYPES})
install(TARGETS ${TARGET_NAME} LIBRARY DESTINATION lib CONFIGURATIONS ${CMAKE_CONFIGURATION_TYPES})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
