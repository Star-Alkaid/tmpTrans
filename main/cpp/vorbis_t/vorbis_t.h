//
// Created on 2024/12/3.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef MINIAUDIOAPP_VORBIS_T_H
#define MINIAUDIOAPP_VORBIS_T_H
#include <string>
#include "baseLog/baseLog.h"

class vorbis_t {
public:
    void convertOgg2Pcm();
    std::string g_filePath_ogg_v = "/data/storage/el1/bundle/entry/resources/resfile/humelate.ogg";
    std::string g_filePath_ogg_pcm_v = "/data/storage/el2/base/haps/entry/files/ogg2pcm_v.pcm";
};

#endif //MINIAUDIOAPP_VORBIS_T_H
