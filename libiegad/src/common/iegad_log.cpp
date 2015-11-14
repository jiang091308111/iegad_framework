﻿#include "iegad_log.h"
#include "iegad_common.in.h"



iegad::tools::_LOG::_LOG(char * argv0)
{
    if (_access("LOG", 0) != 0) {
	system(MKDIR);
    }
    google::InitGoogleLogging(argv0);
    // set the file position;
    google::SetLogDestination(google::GLOG_INFO, LOG_INF_FILE);
    google::SetLogDestination(google::GLOG_WARNING, LOG_WARN_FILE);
    google::SetLogDestination(google::GLOG_ERROR, LOG_ERR_FILE);
    google::SetLogDestination(google::GLOG_FATAL, LOG_FATAL_FILE);
    // set log file max size 100M;
    FLAGS_max_log_size = 100;
    //init charset;

#ifdef WIN32 // for win
    const char * charset = "chs";
#else // for centOS 7
    const char * charset = "zh_CN.UTF-8";
#endif // WIN32
    std::locale::global(std::locale(charset));
}


iegad::tools::_LOG::~_LOG()
{
    google::ShutdownGoogleLogging();
}
