# the minimum version of CMake.
cmake_minimum_required(VERSION 3.5.0)
project(MINIAudioApp CXX C)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(MA_DEBUG_OUTPUT true)
add_compile_definitions(-DMA_DEBUG_OUTPUT
-DSTB_VORBIS_INCLUDE_STB_VORBIS_H -DMA_HAS_VORBIS
#-DMA_NO_WAV -DMA_NO_MP3 -DMA_NO_FLAC -DMA_NO_LIBOPUS -DMA_NO_OPUS -DMA_NO_VORBIS
#-DMINIAUDIO_IMPLEMENTATION
)

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include
                    ${NATIVERENDER_ROOT_PATH}/miniaudio
                    ${NATIVERENDER_ROOT_PATH}/miniaudio_t
                    ${NATIVERENDER_ROOT_PATH}/baseLog
                    ${NATIVERENDER_ROOT_PATH}/vorbis
                    ${NATIVERENDER_ROOT_PATH}/vorbis_t
                    ${NATIVERENDER_ROOT_PATH}/opus
                    ${NATIVERENDER_ROOT_PATH}/ogg
                    )

set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/${OHOS_ARCH})
set(STATIC_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/staticLibs)

#add_library(vorbis SHARED IMPORTED)
#set_target_properties(vorbis PROPERTIES IMPORTED_LOCATION ${LIB_PATH}/libvorbis.so.0.4.9)
#
#add_library(vorbisenc SHARED IMPORTED)
#set_target_properties(vorbisenc PROPERTIES IMPORTED_LOCATION ${LIB_PATH}/libvorbisenc.so.2.0.12)
#
#add_library(vorbisfile SHARED IMPORTED)
#set_target_properties(vorbisfile PROPERTIES IMPORTED_LOCATION ${LIB_PATH}/libvorbisfile.so.3.3.8)

add_library(vorbis STATIC IMPORTED)
set_target_properties(vorbis PROPERTIES IMPORTED_LOCATION ${STATIC_LIB_PATH}/libvorbis.a)

add_library(vorbisenc STATIC IMPORTED)
set_target_properties(vorbisenc PROPERTIES IMPORTED_LOCATION ${STATIC_LIB_PATH}/libvorbisenc.a)

add_library(vorbisfile STATIC IMPORTED)
set_target_properties(vorbisfile PROPERTIES IMPORTED_LOCATION ${STATIC_LIB_PATH}/libvorbisfile.a)

add_library(opus STATIC IMPORTED)
set_target_properties(opus PROPERTIES IMPORTED_LOCATION ${STATIC_LIB_PATH}/libopus.a)

add_library(opusfile STATIC IMPORTED)
set_target_properties(opusfile PROPERTIES IMPORTED_LOCATION ${STATIC_LIB_PATH}/libopusfile.a)

add_library(opusurl STATIC IMPORTED)
set_target_properties(opusurl PROPERTIES IMPORTED_LOCATION ${STATIC_LIB_PATH}/libopusurl.a)

add_library(ogg STATIC IMPORTED)
set_target_properties(ogg PROPERTIES IMPORTED_LOCATION ${STATIC_LIB_PATH}/libogg.a)

add_library(entry SHARED napi_init.cpp
miniaudio/miniaudio.c
miniaudio_t/miniaudio_t.cpp
miniaudio_t/miniaudio_custom_vorbis.cpp
vorbis_t/vorbis_t.cpp)

target_link_libraries(entry PUBLIC libace_napi.z.so libohaudio.so clang_rt.builtins pthread libhilog_ndk.z.so)
target_link_libraries(entry PUBLIC ogg)
target_link_libraries(entry PUBLIC vorbis)
target_link_libraries(entry PUBLIC vorbisenc)
target_link_libraries(entry PUBLIC vorbisfile)
target_link_libraries(entry PUBLIC opus opusfile opusurl)