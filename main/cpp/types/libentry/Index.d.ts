export const loadPCM: () => void;
export const loadOGG: () => void;
export const loadWAV: () => void;
export const play: () => void;
export const pause: () => void;
export const stop: () => void;
export const resume: () => void;
export const release: () => void;
export const getState: ()=> number;
export const convertOgg2Pcm: ()=> void;
export const convertOgg2Pcm_vorbis:()=>void;

export const custom_vorbis_init:()=>void;
export const custom_vorbis_play:()=>void;
export const custom_vorbis_stop:()=>void;

export const engine_stop:()=>void;
export const engine_play:()=>void;
