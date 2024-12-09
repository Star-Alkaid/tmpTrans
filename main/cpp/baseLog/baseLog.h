//
// Created on 2023/12/27.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef BaseLog_H
#define BaseLog_H

#include <stdint.h>
#include <hilog/log.h>
#include <stddef.h>

#undef APP_LOG_DOMAIN
#undef APP_LOG_TAG
#define APP_LOG_DOMAIN 0x3201 // 全局domain宏，标识业务领域
#define APP_LOG_TAG "miniAudio-example"  // 全局tag宏，标识模块日志tag

#define LOGI(...) ((void)OH_LOG_Print(LOG_APP, LOG_INFO, APP_LOG_DOMAIN, APP_LOG_TAG, __VA_ARGS__))
#define LOGD(...) ((void)OH_LOG_Print(LOG_APP, LOG_DEBUG, APP_LOG_DOMAIN, APP_LOG_TAG, __VA_ARGS__))
#define LOGW(...) ((void)OH_LOG_Print(LOG_APP, LOG_WARN, APP_LOG_DOMAIN, APP_LOG_TAG, __VA_ARGS__))
#define LOGE(...) ((void)OH_LOG_Print(LOG_APP, LOG_ERROR, APP_LOG_DOMAIN, APP_LOG_TAG, __VA_ARGS__))

#endif //BaseLog_H
