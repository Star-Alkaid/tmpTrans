#include "napi/native_api.h"
#include "miniaudio_t.h"
#include "vorbis_t.h"

// #include "miniaudio_custom_vorbis.h"

static miniaudio_t *mini = new miniaudio_t();

static vorbis_t *vorbis = new vorbis_t();

static miniaudio_engine *engine = new miniaudio_engine();

// static miniaudio_custom_vorbis *custom_vorbis = new miniaudio_custom_vorbis();

static napi_value loadPCM(napi_env env, napi_callback_info info)
{
    mini->loadPCM();
    return nullptr;
}

static napi_value loadOGG(napi_env env, napi_callback_info info)
{
    mini->loadOGG();
    return nullptr;
}

static napi_value loadWAV(napi_env env, napi_callback_info info)
{
    mini->loadWAV();
    return nullptr;
}

static napi_value play(napi_env env, napi_callback_info info)
{
    mini->play();
    return nullptr;
}

static napi_value pause(napi_env env, napi_callback_info info)
{
    mini->pause();
    return nullptr;
}

static napi_value resume(napi_env env, napi_callback_info info)
{
    mini->resume();
    return nullptr;
}

static napi_value stop(napi_env env, napi_callback_info info)
{
    mini->stop();
    return nullptr;
}

static napi_value release(napi_env env, napi_callback_info info){
    mini->release();
    return nullptr;
}

static napi_value getState(napi_env env, napi_callback_info info){
    int stateVal = mini->getMiniAudioState();
    napi_value result;
    
    napi_create_int32(env, stateVal, &result);
    return result;
}

static napi_value convertOgg2Pcm(napi_env env, napi_callback_info info){
    mini->convertOgg2Pcm();
    return nullptr;
}

static napi_value convertOgg2Pcm_vorbis(napi_env env, napi_callback_info info){
    vorbis->convertOgg2Pcm();
    return nullptr;
}

static napi_value custom_vorbis_init(napi_env env, napi_callback_info info){
//     custom_vorbis->customVorbisDeviceInit();
    return nullptr;
}

static napi_value custom_vorbis_play(napi_env env, napi_callback_info info){
//     custom_vorbis->customVorbisDevicePlay();
    return nullptr;
}

static napi_value custom_vorbis_stop(napi_env env, napi_callback_info info){
//     custom_vorbis->customVorbisDeviceStop();
    return nullptr;
}

static napi_value engine_play(napi_env env, napi_callback_info info){
    engine->play();
    return nullptr;
}

static napi_value engine_stop(napi_env env, napi_callback_info info){
    engine->stop();
    return nullptr;
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        { "loadPCM", nullptr, loadPCM, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "loadOGG", nullptr, loadOGG, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "loadWAV", nullptr, loadWAV, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "play", nullptr, play, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "pause", nullptr, pause, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "resume", nullptr, resume, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "stop", nullptr, stop, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "release", nullptr, release, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "getState", nullptr, getState, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "convertOgg2Pcm", nullptr, convertOgg2Pcm, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "convertOgg2Pcm_vorbis", nullptr, convertOgg2Pcm_vorbis, nullptr, nullptr, nullptr, napi_default, nullptr },
        
        { "custom_vorbis_init", nullptr, custom_vorbis_init, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "custom_vorbis_play", nullptr, custom_vorbis_play, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "custom_vorbis_stop", nullptr, custom_vorbis_stop, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "engine_play", nullptr, engine_play, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "engine_stop", nullptr, engine_stop, nullptr, nullptr, nullptr, napi_default, nullptr },
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "entry",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void)
{
    napi_module_register(&demoModule);
}
