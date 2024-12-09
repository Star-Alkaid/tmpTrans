//
// Created on 2024/12/4.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef MINIAUDIOAPP_MINIAUDIO_CUSTOM_VORBIS_H
#define MINIAUDIOAPP_MINIAUDIO_CUSTOM_VORBIS_H

#define MA_NO_VORBIS    /* Disable the built-in Vorbis decoder to ensure the libvorbis decoder is picked. */
#define MA_NO_OPUS      /* Disable the (not yet implemented) built-in Opus decoder to ensure the libopus decoder is picked. */
#define MINIAUDIO_IMPLEMENTATION

#include "miniaudio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baseLog.h"

class miniaudio_custom_vorbis {
public:
    void customVorbisDeviceInit();
    void customVorbisDevicePlay();
    void customVorbisDeviceStop();
    ~miniaudio_custom_vorbis();
    
    ma_result result;
    ma_decoder_config decoderConfig;
    ma_decoder decoder;
    ma_device_config deviceConfig;
    ma_device device;
    ma_format format;
    ma_uint32 channels;
    ma_uint32 sampleRate;
    const char* g_filePath_ogg_custom_v = "/data/storage/el1/bundle/entry/resources/resfile/humelate.ogg";
};

#endif //MINIAUDIOAPP_MINIAUDIO_CUSTOM_VORBIS_H
