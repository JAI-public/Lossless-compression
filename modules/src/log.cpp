/****************************************************************************
 * modules/src/log.cpp
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
#include <algorithm>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <string>

#include "log.hpp"

jaids::lossless::Log::Log(const std::string& conffile) {
    if (std::filesystem::exists(conffile)) {
        auto log_filename = GetLogFileName(conffile);
        log_.open(log_filename, std::ios::app);
    }
    else {
        std::string home;
#ifdef _WIN32
        size_t buf;
        char buffer[1024];
        if (!getenv_s(&buf, buffer, 1024, "UserProfile")) {
            if (buf != 0) {
                home = std::string(buffer);
            }
        }
#else
        char* strenv;
        if ((strenv = getenv("HOME")) != nullptr) {
            home = strenv;
        }
#endif
        if (home != "") {
            auto fullpath = home + "\\.jaids\\" + conffile;
            if (std::filesystem::exists(fullpath)) {
                auto log_filename = GetLogFileName(fullpath);
                log_.open(log_filename, std::ios::app);
            }
            else {
                log_.open("jaids.log", std::ios::app);
            }
        }
        else {
            log_.open("jaids.log", std::ios::app);
        }
    }
}

jaids::lossless::Log::~Log() {

}

jaids::lossless::Log& jaids::lossless::Log::GetInstance(const std::string& filename) {
    static Log instance(filename);
    return instance;
}

std::filesystem::path jaids::lossless::Log::GetLogFileName(const std::filesystem::path& conffile) const noexcept {
    std::filesystem::path log_file;

    try {
        std::ifstream ifs(conffile);
        if (ifs.fail()) {
            throw;
        }
        std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        std::string chars = " ";
        str.erase(std::remove_if(str.begin(),
                                 str.end(),
                                 [&chars](const char& c) { 
                                    return chars.find(c) != std::string::npos;
                                 }),
                  str.end());
        std::string key = "log.filename=\"";
        auto pos = str.find(key);
        if (pos == std::string::npos) {
            return std::filesystem::path("jaids.log");
        }
        auto begin = pos + key.length();
        auto end = str.find('\"', begin);
        log_file = std::filesystem::path(str.substr(begin, end - begin));
    }
    catch (...) {
        log_file = std::filesystem::path("jaids.log");
    }

    return log_file;
}

std::string jaids::lossless::Log::GetEpocTimeString() {
    auto now = std::chrono::system_clock::now();
    auto end_time = std::chrono::system_clock::to_time_t(now);
    auto loc = std::localtime(&end_time);
    auto epoc = (uint32_t)std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();

    uint32_t year = loc->tm_year + 1900;
    uint32_t month = loc->tm_mon + 1;
    uint32_t day = loc->tm_mday;
    uint32_t hour = loc->tm_hour;
    uint32_t minute = loc->tm_min;
    uint32_t sec = loc->tm_sec;
    uint32_t msec = epoc % 1000000;

    std::stringstream ss;
    ss << "["
       << year << month << day
       << "-"
       << std::setw(2)<< std::setfill('0') << hour
       << std::setw(2) << std::setfill('0') << minute
       << std::setw(2)<< std::setfill('0') << sec
       << "."
       << std::setw(9) << std::setfill('0') << std::left << msec
       << "]";
    return ss.str();
}
