//
// Created on 2024/11/26.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef MINIAUDIOAPP_MINIAUDIO_T_H
#define MINIAUDIOAPP_MINIAUDIO_T_H

#include <stdio.h>
#include <string>
#include "miniaudio/miniaudio.h"
class miniaudio_t {
public:
    miniaudio_t();
    void loadPCM();
    void loadOGG();
    void loadWAV();
    void play();
    void pause();
    void resume();
    void stop();
    void release();
    int getMiniAudioState();
    
    void convertOgg2Pcm();
    
private:
    ~miniaudio_t();
    std::string g_filePath_pcm = "/data/storage/el1/bundle/entry/resources/resfile/DIP.pcm";
//     std::string g_filePath_pcm = "/data/storage/el1/bundle/entry/resources/resfile/12.pcm";
//     std::string g_filePath_ogg = "/data/storage/el1/bundle/entry/resources/resfile/humelate.ogg";
    std::string g_filePath_ogg = "/data/storage/el1/bundle/entry/resources/resfile/JJ_sound.ogg";
//     std::string g_filePath_wav = "/data/storage/el1/bundle/entry/resources/resfile/world.wav";
    std::string g_filePath_wav = "/data/storage/el1/bundle/entry/resources/resfile/power.wav";
    std::string g_filepath_ogg_pcm = "/data/storage/el2/base/haps/entry/files/ogg2pcm.pcm";
    ma_device device;
    ma_decoder decoder;
};

class miniaudio_engine {
public:
    miniaudio_engine();
    void play();
    void stop();
private:
    ~miniaudio_engine();
    std::string g_filePath_pcm = "/data/storage/el1/bundle/entry/resources/resfile/12.pcm";
    std::string g_filePath_wav = "/data/storage/el1/bundle/entry/resources/resfile/bg32.wav";
    ma_engine engine;
};

#endif //MINIAUDIOAPP_MINIAUDIO_T_H
