
#ifndef _AUDIO_H
#define _AUDIO_H

unsigned long flCurAddr;
unsigned long flEndAddr;

//#define AudioPercent()	((flCurAddr * 2) * 100 / flEndAddr)
#define AudioPercent()	((flCurAddr * 2) * 50 / flEndAddr)

void AudioPlayInit(void);
void AudioTask(void);

#endif //_AUDIODEMO_H
