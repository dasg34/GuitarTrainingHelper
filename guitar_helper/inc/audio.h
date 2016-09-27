/*
 * gh_audio_manager.h
 *
 *  Created on: Aug 16, 2016
 *      Author: lee
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include <eina_types.h>

int audio_io_create();

Eina_Bool chord_detect(float *f);

void chord_detector_init();

#endif /* AUDIO_H_ */
