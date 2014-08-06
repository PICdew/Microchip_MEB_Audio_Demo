#include <stdio.h>
#include "plib.h"
#include "Audio.h"
#include "WM8731Drv.h"

#define AUDIO_START		(0)

WM8731_CODEC codec;
STEREO_AUDIO_DATA codecBuf[1152*2];
STEREO_AUDIO_DATA rcordBuf[1152*2];

extern WM8731_CODEC * pCodecHandle; 
extern BOOL PlayPressed;

extern BOOL RecPressed;
extern int AudioState;
extern short wav[];

//extern const short frogwav[];
extern unsigned long returnsize();

void AudioTask(void){
    //STEREO_AUDIO_DATA * audio;
    static BOOL AudioPlaying = FALSE;

    switch(AudioState){
        case 1:             // Play Sound...
            if(AudioPlaying == FALSE){
                WM8731CodecStartAudio(pCodecHandle);
            }
            AudioPlaying = TRUE;
            if(flCurAddr < flEndAddr){
                //WM8731CodecWrite(pCodecHandle,  (STEREO_AUDIO_DATA *)&frogwav[flCurAddr],1152);   // Playback
                WM8731CodecWrite(pCodecHandle,  (STEREO_AUDIO_DATA *)&wav[flCurAddr],1152);   // Playback
                flCurAddr += 1152*2;
            }else{
                flCurAddr = AUDIO_START+ 4;                         // Play from the beginning
            }
            break;
        case 2:             // Stop Sound...
            if(AudioPlaying == TRUE){                               // Audio is playing. Stop the audio, and clear the TX buffer
                AudioPlaying = FALSE;
                WM8731CodecStopAudio(pCodecHandle);
                WM8731ClearTxBuffer(pCodecHandle);
                flCurAddr = 0;
            }
            break;
        case 3:             // Record Sound...
            if(AudioPlaying == FALSE){
                WM8731CodecStartAudio(pCodecHandle);
            }
            AudioPlaying = TRUE;
            if(flCurAddr < flEndAddr){
                WM8731CodecRead(pCodecHandle, (STEREO_AUDIO_DATA *)&wav[flCurAddr],1152);          // Record...
                flCurAddr += 1152*2;
            }else{
                flCurAddr = AUDIO_START+ 4;				// Play from the beginning
            }
            break;
    }
}
    
void AudioPlayInit(void) {
    
    //flEndAddr = returnsize(frogwav);                                    // Returns the size of the Audio sample array in terms of 16bits per count
   // if (flEndAddr > 0x200000)                                         // no bigger than 2Mbyte
     //   flEndAddr = 0x200000;
    flEndAddr = returnsize(wav);
    if (flEndAddr > 0xD000)                                             
        flEndAddr = 0xD000;
    flCurAddr = AUDIO_START+ 4;

    //pCodecHandle = WM8731CodecOpen(&codec,codecBuf ,0, O_WRONLY);	// Open the Audio Codec and return respective handle
    pCodecHandle = WM8731CodecOpen(&codec,codecBuf ,rcordBuf, O_RDWR);	// Open the Audio Codec and return respective handle
    WM8731CodecSetVolume(55);                                           // Set volume up... (Max 75)
    WM8731CodecLoadStartup(pCodecHandle);				// Configure the Codec with the startup values.
    WM8731CodecStartAudio(pCodecHandle);				// Start the Audio Codec
}