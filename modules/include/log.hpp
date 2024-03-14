/****************************************************************************
 * modules/include/log.hpp
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
#include <memory>
#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

namespace jaids {
    namespace lossless {
        // Singleton class
        class Log {
        public:
            Log(const Log&) = delete;
            Log& operator=(const Log&) = delete;
            Log(Log&&) = delete;
            Log& operator=(const Log&&) = delete;
            virtual ~Log();

            // Singleton instance
            static Log& GetInstance(const std::string& = "");

            std::string GetEpocTimeString();

            template <typename... Args>
            std::string Format(const std::string& fmt, Args... args) {
                size_t len = std::snprintf(nullptr, 0, fmt.c_str(), args...);
                std::vector<char> buf(len + 1);
                std::snprintf(&buf[0], len + 1, fmt.c_str(), args...);
                return std::string(&buf[0], &buf[0] + len);
            }

            template <typename... Args>
            void Info(const std::string& fmt, Args... args) {
                std::stringstream ss;
                ss << GetEpocTimeString() << "[info] " << Format(fmt, std::forward<Args>(args)...);
                log_ << ss.str() << std::endl;
                log_.flush();
            }

            template <typename... Args>
            void Error(const std::string& fmt, Args... args) {
                std::stringstream ss;
                ss << GetEpocTimeString() << "[error] " << Format(fmt, std::forward<Args>(args)...);
                log_ << ss.str() << std::endl;
                log_.flush();
            }

        private:
            // Singleton constructor
            Log(const std::string& = "");

            std::filesystem::path GetLogFileName(const std::filesystem::path&) const noexcept;

            std::ofstream log_;
        };
    } // namespace lossless
} // namespace jaids
