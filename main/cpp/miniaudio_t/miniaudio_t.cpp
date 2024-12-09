//
// Created on 2024/11/26.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

// #include "stb_vorbis.c"
// #define MA_HAS_VORBIS

#include "miniaudio_t.h"
#include "baseLog.h"
#include <atomic>
#include <cstdio>
#include <stdio.h>

static ma_format format = ma_format_s16;
static ma_uint32 channels = 2;
static ma_uint32 sampleRate = 48000;
std::FILE* pFile = nullptr;

std::FILE* wFile = nullptr;

void data_callback_pcm(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    (void)pDevice;
    (void)pInput;

    // 获取用户数据，即文件指针
    pFile = (std::FILE*)pDevice->pUserData;

    if(pOutput == nullptr){
        ma_log_postf(ma_device_get_log(pDevice), MA_LOG_LEVEL_INFO, "      data_callback_pcm pOutput is nullptr !!!\n");
        return;
    }
    
    // 读取 PCM 数据
    size_t bytesToRead = frameCount;
    size_t bytesRead = fread(pOutput, bytesToRead, 1, pFile);
    
    if(!bytesRead){
        if (ferror(pFile)) {
            ma_log_postf(ma_device_get_log(pDevice), MA_LOG_LEVEL_INFO, "      data_callback_pcm ferror file !!!\n");
        } else if (feof(pFile)) {
            ma_log_postf(ma_device_get_log(pDevice), MA_LOG_LEVEL_INFO, "      data_callback_pcm file eof signal found !!!\n");
        }
    }
}

void data_callback_ogg(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ma_log_postf(ma_device_get_log(pDevice), MA_LOG_LEVEL_INFO, "data_callback_pcm start ~~~~~\n");
    ma_log_postf(ma_device_get_log(pDevice), MA_LOG_LEVEL_INFO, "     frameCount: %{frameCount}d\n", frameCount);
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if (pDecoder == NULL) {
        return;
    }
    ma_uint64 pFramesRead = 0;
    ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, &pFramesRead);
    ma_log_postf(ma_device_get_log(pDevice), MA_LOG_LEVEL_INFO, "data_callback_pcm pFramesRead: %d\n", pFramesRead);
    
//     (void)pInput;
    ma_log_postf(ma_device_get_log(pDevice), MA_LOG_LEVEL_INFO, "data_callback_pcm end ~~~~~\n");
}

void data_callback_wav(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount){
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if (pDecoder == NULL) {
        return;
    }
    ma_uint64 pFramesRead = 0;
    ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, &pFramesRead);
    (void)pInput;   /* Unused. */
}

miniaudio_t::miniaudio_t(){
//     loadPCM();
}

/**
 * 加载pcm格式音频资源
 */
void miniaudio_t::loadPCM(){
    if(&device != NULL){
        ma_device_uninit(&device);
    }
    
    if(pFile == nullptr){
        pFile = fopen(g_filePath_pcm.c_str(), "rb");
    }
    if (pFile == NULL) {
        LOGE("loadPCM open file failure! filepath: %{public}s", g_filePath_pcm.c_str());
        return;
    }

    // 如果文件读取到了结尾则从头开始
    if(feof(pFile)){
        fseek(pFile, 0, SEEK_SET);
    }
    
    ma_device_config deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = format;
    deviceConfig.playback.channels = channels;
    deviceConfig.sampleRate = sampleRate;
    deviceConfig.dataCallback = data_callback_pcm;
    deviceConfig.pUserData = pFile;
//     deviceConfig.performanceProfile = ma_performance_profile_low_latency; // 低时延
    deviceConfig.performanceProfile = ma_performance_profile_conservative;
    deviceConfig.ohaudio.usage = ma_ohaudio_usage_game; // 使用场景，游戏
    
    // 初始化设备
    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
        LOGE("loadPCM device init failure!");
        return;
    }
}

/**
 * 加载ogg格式音频资源
 */
void miniaudio_t::loadOGG(){
    
    ma_decoder_config config = ma_decoder_config_init_default();
//     ma_decoder_config config = ma_decoder_config_init(ma_format_s16, 2, 48000);
    config.encodingFormat = ma_encoding_format_vorbis;
    
    ma_result result = ma_decoder_init_file(g_filePath_ogg.c_str(), &config, &decoder);
    if (result != MA_SUCCESS) {
        LOGE("loadOGG decoder init failure! file path: %{public}s", g_filePath_ogg.c_str());
        return;
    }
    
    ma_device_config deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = decoder.outputFormat;
    deviceConfig.playback.channels = decoder.outputChannels;
    deviceConfig.sampleRate = decoder.outputSampleRate;
    deviceConfig.dataCallback = data_callback_ogg;
    deviceConfig.pUserData = &decoder;
//     deviceConfig.performanceProfile = ma_performance_profile_low_latency; // 低时延
    // deviceConfig.performanceProfile = ma_performance_profile_conservative;
    deviceConfig.ohaudio.usage = ma_ohaudio_usage_game; // 使用场景，游戏
    
    // 初始化设备
    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
        LOGE("loadOGG device init failure");
        ma_decoder_uninit(&decoder);
        return;
    }
}

/**
 * 加载wav格式音频资源
 */
void miniaudio_t::loadWAV(){
    
    ma_waveform sineWave;
    ma_device_config deviceConfig;
    ma_waveform_config sineWaveConfig;
    
//     ma_decoder_config config = ma_decoder_config_init(ma_format_s16, 2, 48000);
    ma_decoder_config config = ma_decoder_config_init_default();
    config.encodingFormat = ma_encoding_format_wav;
    ma_result result = ma_decoder_init_file(g_filePath_wav.c_str(), &config, &decoder);
    
    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = decoder.outputFormat;
    deviceConfig.playback.channels = decoder.outputChannels;
    deviceConfig.sampleRate = decoder.outputSampleRate;
    deviceConfig.dataCallback = data_callback_wav;
    deviceConfig.pUserData = &decoder;
//     deviceConfig.performanceProfile = ma_performance_profile_low_latency; // 低时延
    deviceConfig.performanceProfile = ma_performance_profile_conservative;
    
    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
        LOGE("Failed to open playback device.\n");
        return;
    }
    
//     sineWaveConfig = ma_waveform_config_init(device.playback.format, device.playback.channels, device.sampleRate, ma_waveform_type_sine, 0.2, 220);
//     ma_waveform_init(&sineWaveConfig, &sineWave);
}


void miniaudio_t::convertOgg2Pcm(){
    if(wFile == nullptr){
        wFile = fopen(g_filepath_ogg_pcm.c_str(), "wb");
    }
    
     // 定义缓冲区大小和缓冲区
    const ma_uint32 frameCountPerRead = 1024;
    ma_uint64 totalFramesWritten = 0;
    size_t sampleSize = ma_get_bytes_per_sample(decoder.outputFormat);
    size_t bufferSize = frameCountPerRead * decoder.outputChannels * sampleSize;
    void* buffer = malloc(bufferSize);

    if (buffer == NULL) {
        printf("Failed to allocate memory for buffer.\n");
        fclose(wFile);
        ma_decoder_uninit(&decoder);
        return;
    }
    
    ma_uint64 framesRead;
    while (1) {
        ma_result result = ma_decoder_read_pcm_frames(&decoder, buffer, frameCountPerRead, &framesRead);
        if (framesRead == 0) {
            break; // 文件结束
        }
        fwrite(buffer, 1, framesRead * decoder.outputChannels * sampleSize, wFile);
        totalFramesWritten += framesRead;

        if (framesRead < frameCountPerRead) {
            break; // 文件结束或没有更多数据可供读取
        }
    }
    
    free(buffer);

    // 关闭输出文件
    fclose(wFile);
}


void miniaudio_t::play(){
    if (ma_device_start(&device) != MA_SUCCESS) {
        ma_device_uninit(&device);
        if(&decoder != nullptr){
            ma_decoder_uninit(&decoder);
        }
    }
}

void miniaudio_t::pause(){
//     todo
}

void miniaudio_t::resume(){
//     todo
}

void miniaudio_t::stop(){
    ma_device_stop(&device);
}

void miniaudio_t::release(){
    if(&device != NULL){
        ma_device_uninit(&device);
    }
    if(pFile != nullptr){
        fclose(pFile);
    }
}

int miniaudio_t::getMiniAudioState(){
    return ma_device_get_state(&device);
}

miniaudio_t::~miniaudio_t(){
    //清理
    if(&device != NULL){
        ma_device_uninit(&device);
    }
    if(pFile != nullptr){
        fclose(pFile);
    }
    
    if(wFile != nullptr){
        fclose(wFile);
    }
}

miniaudio_engine::miniaudio_engine() {

}
void miniaudio_engine::play() {
    ma_result result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        printf("ma_engine_init() failed with error code %d\n", result);
    }
    
    ma_engine_play_sound(&engine, g_filePath_wav.c_str(), NULL);
    //ma_sound_init_from_file(&engine, const char *pFilePath, ma_uint32 flags, ma_sound_group *pGroup, ma_fence *pDoneFence, ma_sound *pSound)
    printf("ma_engine_play_sound() succeeded\n");
}

void miniaudio_engine::stop() {
    ma_engine_uninit(&engine);
    printf("ma_engine_uninit() succeeded\n");
}
