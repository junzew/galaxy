// Copyright (c) 2016, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once
#include "collector/collector.h"

#include "boost/thread/mutex.hpp"

namespace baidu {
    namespace galaxy {
        namespace cgroup {
            class Cgroup;
            
            class CgroupCollector : public baidu::galaxy::collector::Collector {
            public:
                class Metrix {
                public:
                    Metrix() :
                        timestamp(-1),
                        cpu_systime(0L),
                        cpu_usertime(0L),
                        cpu_used_in_millicore(0),
                        memory_used(0){
                        
                    }
                    int64_t timestamp;
                    int64_t cpu_systime;
                    int64_t cpu_usertime;
                    int64_t cpu_used_in_millicore;
                    int64_t memory_used;
                };
            public:
                explicit CgroupCollector(boost::shared_ptr<Cgroup> cgroup);
                ~CgroupCollector();

                baidu::galaxy::util::ErrorCode Collect();

                void Enable(bool enable);
                bool Enabled();
                bool Equal(const Collector&);
                void SetCycle(int cycle);
                int Cycle(); // unit second
                std::string Name() const;
                void SetName(const std::string& name);
                int Metrix(Metrix* metrix);

            private:
                bool enabled_;
                int cycle_;
                boost::shared_ptr<Cgroup> cgroup_;
                std::string name_;
                boost::mutex mutex_;
                
            };
        }
    }
}