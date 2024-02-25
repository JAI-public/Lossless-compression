# ##############################################################################
# CMakeLists.txt
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
cmake_minimum_required(VERSION 3.14)

project(lossless VERSION 1.0.0 LANGUAGES CXX)
message("<<<<<<<<<build lossless version :${lossless_VERSION_MAJOR}.${lossless_VERSION_MINOR}.${lossless_VERSION_PATCH}>>>>>>>>>>")


##################################################################################
# Configure file encoding as UTF-8 for VisualStudio
##################################################################################
if(MSVC)
  add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
  add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

add_subdirectory(modules)
if (${BUILD_TESTS})
  add_subdirectory(test)
  add_subdirectory(test_app)
endif()