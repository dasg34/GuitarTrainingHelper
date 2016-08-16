/*
 * gh_audio_manager.c
 *
 *  Created on: Aug 16, 2016
 *      Author: lee
 */
#include "gh_main.h"
#include "gh_libfft.h"
#include "gh_audio_manager.h"

#include <audio_io.h>

#define BUF_SIZE 8192
#define SAMPLE_RATE (8000)
#define FFT_SIZE 8192
#define FFT_EXP_SIZE (13)

static float a[2], b[3], mem1[4], mem2[4];
static float freqTable[FFT_SIZE];
static void* fft;
static audio_in_h input;

static void
computeSecondOrderLowPassParameters( float srate, float f, float *a, float *b )
{
   float a0;
   float w0 = 2 * M_PI * f/srate;
   float cosw0 = cos(w0);
   float sinw0 = sin(w0);
   //float alpha = sinw0/2;
   float alpha = sinw0/2 * sqrt(2);
   a0   = 1 + alpha;
   a[0] = (-2*cosw0) / a0;
   a[1] = (1 - alpha) / a0;
   b[0] = ((1-cosw0)/2) / a0;
   b[1] = ( 1-cosw0) / a0;
   b[2] = b[0];
}

static float
processSecondOrderFilter( float x, float *mem, float *a, float *b )
{
	float ret = b[0] * x + b[1] * mem[0] + b[2] * mem[1]- a[0] * mem[2] - a[1] * mem[3];
	mem[1] = mem[0];
	mem[0] = x;
	mem[3] = mem[2];
	mem[2] = ret;
	return ret;
}


void
chord_detector_init()
{
	fft = initfft( FFT_EXP_SIZE );
	computeSecondOrderLowPassParameters( SAMPLE_RATE, 330, a, b );
	mem1[0] = 0; mem1[1] = 0; mem1[2] = 0; mem1[3] = 0;
	mem2[0] = 0; mem2[1] = 0; mem2[2] = 0; mem2[3] = 0;

	for( int i=0; i<FFT_SIZE; ++i ) {
		freqTable[i] = ( SAMPLE_RATE * i ) / (float) ( FFT_SIZE );
	}
}


Eina_Bool
chord_detect(float *f)
{
	int ret,current_index=0;
	int buffer[BUF_SIZE]={0,};
	int freq_index[5] = {-1,-1,-1,-1,-1};
	const int success_max=1000000;

	float data[FFT_SIZE];
	float datai[FFT_SIZE];

	for(int i=0;i<5;i++)
	{
		if(f[i]<0) continue;
		for(int j=current_index;j<FFT_SIZE/2;j++)
		{
			if(f[i]<freqTable[j])
			{
				freq_index[i]=j;
				current_index=j;
				break;
			}
		}
	}

	if ((ret = audio_in_read(input, (void*)buffer, FFT_SIZE)) > AUDIO_IO_ERROR_NONE) {
		for( int j=0; j<FFT_SIZE; ++j ) {
			data[j]=((float)buffer[j])/32768.0f;
		}
		for( int j=0; j<FFT_SIZE; ++j ) {
			data[j] = processSecondOrderFilter( data[j], mem1, a, b );
			data[j] = processSecondOrderFilter( data[j], mem2, a, b );
		}
		// do the fft
		for( int j=0; j<FFT_SIZE; ++j ) datai[j] = 0;
		applyfft( fft, data, datai, 0 );

		for(int i=0;i<5;i++)
		{
			if(freq_index[i] > 0)
			{
				 if(data[freq_index[i]] * data[freq_index[i]] +
						 datai[freq_index[i]] * datai[freq_index[i]] < success_max )
					 return EINA_FALSE;
			}
		}
		return EINA_TRUE;
	}
	else
	{
		return EINA_FALSE;
	}
}

int
audio_io_create()
{
    int ret;

    if ((ret = audio_in_create(8000, AUDIO_CHANNEL_STEREO ,AUDIO_SAMPLE_TYPE_S16_LE, &input)) == AUDIO_IO_ERROR_NONE) {
		ret = audio_in_ignore_session(input);
		if (ret != 0) {
			dlog_print(DLOG_ERROR, LOG_TAG, "set session mix");
			audio_in_destroy(input);
			return 0;
		}

		ret = audio_in_prepare(input);
		if (ret != 0) {
			dlog_print(DLOG_ERROR, LOG_TAG, "prepare error");
			audio_in_destroy(input);
			return 0;
		}
    }
    return 0;
}

