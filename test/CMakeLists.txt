# ##############################################################################
# test/CMakeLists.txt
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
set(TARGET_NAME "Test")
# C++17利用
set(CMAKE_CXX_STANDARD 17)

enable_testing()
find_package(GTest CONFIG REQUIRED)

##################################################################################
# target
##################################################################################
add_executable(
  ${TARGET_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/bitstream_test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/compressed_bitstream_test.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/line_header_v1_test.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/compressed_block_test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/two_complement_test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/testmain.cpp
)

# dependent internal modules
target_include_directories(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/modules/include)

target_link_libraries(
  ${TARGET_NAME}
  PRIVATE
  liblossless
	GTest::gtest
  GTest::gtest_main
  GTest::gmock
  GTest::gmock_main
)

install(TARGETS ${TARGET_NAME} RUNTIME DESTINATION bin CONFIGURATIONS ${CMAKE_CONFIGURATION_TYPES})