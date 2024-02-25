# ##############################################################################
# test_app/CMakeLists.txt
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
set(TARGET_NAME "app")
set(CMAKE_DEBUG_POSTFIX _d)

# C++17利用
set(CMAKE_CXX_STANDARD 17)

# execute_process(COMMAND ${PROJECT_SOURCE_DIR}/cmake/opencv_build.sh)
execute_process(
  COMMAND dir .
  # COMMAND ${CMAKE_COMMAND} ..
  # WORKING_DIRECTORY ${build_dir}
)
##################################################################################
# target
##################################################################################
add_executable(${TARGET_NAME})
target_sources(${TARGET_NAME}
  PRIVATE
	test_app.cpp
)


# # dependent internal modules
# target_include_directories(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)

# dependent internal modules
target_link_libraries(${TARGET_NAME} PRIVATE
      liblossless
#      Threads::Threads
     #  ${OpenCV_LIBS}
)


##################################################################################
# eBUS SDK
##################################################################################
if(MSVC)
target_link_directories(${TARGET_NAME} PUBLIC $ENV{PUREGEV_ROOT}/Libraries)
target_include_directories(${TARGET_NAME} PRIVATE $ENV{PUREGEV_ROOT}/Includes)
elseif(UNIX)
target_link_directories(${TARGET_NAME} PUBLIC $ENV{PUREGEV_ROOT}/lib)
target_include_directories(${TARGET_NAME} PRIVATE $ENV{PUREGEV_ROOT}/include)
target_link_libraries(${TARGET_NAME} PRIVATE 
  PvBase
  PvBuffer
  PvDevice
  PvGenICam
  PvStream
  PvSystem
)
endif()

##################################################################################
# 3rd-party OSS library
##################################################################################
target_include_directories(${TARGET_NAME} PRIVATE ${threadpool_SOURCE_DIR})

install(TARGETS ${TARGET_NAME} RUNTIME DESTINATION bin CONFIGURATIONS ${CMAKE_CONFIGURATION_TYPES})