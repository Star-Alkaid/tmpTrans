import { hilog } from '@kit.PerformanceAnalysisKit';
import testNapi from 'libentry.so';

@Entry
@Component
struct Index {
  @State miniAudioTitle:string = 'MINIAudio OHOS'

  @State loadPCM: string = 'loadPCM';
  @State loadOGG: string = 'loadOGG';
  @State loadWAV: string = 'loadWAV';
  @State Ogg2Pcm: string = 'convert OGG to PCM';
  @State Ogg2Pcm_vorbis: string = 'vorbis convert OGG to PCM';
  @State play: string = 'play';
  @State pause: string = 'pause';
  @State resume: string = 'resume';
  @State stop: string = 'stop';
  @State release: string = 'release';

  @State custom_vorbis_init: string = 'custom_vorbis_init';
  @State custom_vorbis_play: string = 'custom_vorbis_play';
  @State custom_vorbis_stop: string = 'custom_vorbis_stop';

  build() {
    Column() {
      Row() {
        Text(this.miniAudioTitle)
          .fontSize(40)
          .fontWeight(FontWeight.Bold)
      }
      .margin({ top: 10, bottom: 20 })
      .width('100%')

        Row() {
          Button(this.loadPCM)
            .fontSize(30)
            .fontWeight(FontWeight.Bold)
            .onClick(() => {
              testNapi.loadPCM();
            })
        }
        .width('100%')
        .margin({ top: 10, bottom: 10, left:30})

        Row() {
          Button(this.loadOGG)
            .fontSize(30)
            .fontWeight(FontWeight.Bold)
            .onClick(() => {
              testNapi.loadOGG();
            })
        }
        .width('100%')
        .margin({ top: 10, bottom: 10, left:30})

        Row() {
          Button(this.loadWAV)
            .fontSize(30)
            .fontWeight(FontWeight.Bold)
            .onClick(() => {
              testNapi.loadWAV();
            })
        }
        .width('100%')
        .margin({ top: 10, bottom: 10, left:30})

      //   Row() {
      //     Button(this.Ogg2Pcm)
      //       .fontSize(30)
      //       .fontWeight(FontWeight.Bold)
      //       .onClick(() => {
      //         testNapi.convertOgg2Pcm();
      //       })
      //   }
      //   .width('100%')
      //   .margin({ top: 10, bottom: 10, left:30})
      //
      //
      // Row() {
      //   Button(this.Ogg2Pcm_vorbis)
      //     .fontSize(20)
      //     .fontWeight(FontWeight.Bold)
      //     .onClick(() => {
      //       testNapi.convertOgg2Pcm_vorbis();
      //     })
      // }
      // .width('100%')
      // .margin({ top: 10, bottom: 10, left:30})

        Row() {
          Button(this.play)
            .fontSize(30)
            .fontWeight(FontWeight.Bold)
            .onClick(() => {
              testNapi.engine_play();
              AppStorage.set('miniAudio_status', 'playing');
            })
        }
        .width('100%').margin({ top: 10, bottom: 10, left:30})

        // Row() {
        //   Button(this.pause)
        //     .fontSize(30)
        //     .fontWeight(FontWeight.Bold)
        //     .onClick(() => {
        //       testNapi.pause();
        //     })
        // }
        // .width('100%').margin({ top: 10, bottom: 10, left:30})


        // Row() {
        //   Button(this.resume)
        //     .fontSize(30)
        //     .fontWeight(FontWeight.Bold)
        //     .onClick(() => {
        //       testNapi.resume();
        //     })
        // }
        // .width('100%').margin({ top: 10, bottom: 10, left:30})

        Row() {
          Button(this.stop)
            .fontSize(30)
            .fontWeight(FontWeight.Bold)
            .onClick(() => {
              testNapi.engine_stop();
              AppStorage.set('miniAudio_status', 'stop');
            })
        }
        .width('100%').margin({ top: 10, bottom: 10, left:30})


      // Row() {
      //   Button(this.custom_vorbis_init)
      //     .fontSize(20)
      //     .fontWeight(FontWeight.Bold)
      //     .onClick(() => {
      //       testNapi.custom_vorbis_init();
      //     })
      // }
      // .width('100%')
      // .margin({ top: 10, bottom: 10, left:30})
      //
      // Row() {
      //   Button(this.custom_vorbis_play)
      //     .fontSize(20)
      //     .fontWeight(FontWeight.Bold)
      //     .onClick(() => {
      //       testNapi.custom_vorbis_play();
      //     })
      // }
      // .width('100%')
      // .margin({ top: 10, bottom: 10, left:30})
      //
      // Row() {
      //   Button(this.custom_vorbis_stop)
      //     .fontSize(20)
      //     .fontWeight(FontWeight.Bold)
      //     .onClick(() => {
      //       testNapi.custom_vorbis_stop();
      //     })
      // }
      // .width('100%')
      // .margin({ top: 10, bottom: 10, left:30})

      // Row() {
      //   Button(this.release)
      //     .fontSize(30)
      //     .fontWeight(FontWeight.Bold)
      //     .onClick(() => {
      //       testNapi.release();
      //     })
      // }
      // .width('100%').margin({ top: 10, bottom: 10, left:30})

      }
  }
}
