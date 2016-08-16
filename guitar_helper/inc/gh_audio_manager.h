/*
 * gh_audio_manager.h
 *
 *  Created on: Aug 16, 2016
 *      Author: lee
 */

#ifndef GH_AUDIO_MANAGER_H_
#define GH_AUDIO_MANAGER_H_

int audio_io_create();

Eina_Bool chord_detect(float *f);

void chord_detector_init();

#endif /* GH_AUDIO_MANAGER_H_ */
