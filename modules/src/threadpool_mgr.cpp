﻿/****************************************************************************
 * modules/src/threadpool_mgr.cpp
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/
#include "threadpool_mgr.hpp"

#include "ThreadPool.h"

namespace jaids::lossless {
    ThreadPoolMgr& ThreadPoolMgr::GetInstance(const uint16_t thread_num) {
        static ThreadPoolMgr instance(thread_num);
        return instance;
    }
    ThreadPool& jaids::lossless::ThreadPoolMgr::GetPool() {
        return *pool_;
    }
    ThreadPoolMgr::ThreadPoolMgr(const uint16_t thread_num) { pool_ = new ThreadPool(thread_num); }
}  // namespace jaids::lossless
