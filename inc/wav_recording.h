/*
 * wav_recording.h
 *
 *  Created on: Jan 6, 2017
 *      Author: design
 */

#ifndef INC_WAV_RECORDING_H_
#define INC_WAV_RECORDING_H_
#define	WAV_COMMENT 	"Recorded on a 4ms Stereo Triggered Sampler" // goes into wav info chunk and id3 tag
#define	WAV_SOFTWARE 	"4ms Stereo Triggered Sampler firmware v"	 //	goes into wav info chunk and id3 tag

#include <stm32f4xx.h>

enum RecStates {
	REC_OFF,
	CREATING_FILE,
	RECORDING,
	CLOSING_FILE,
	CLOSING_FILE_TO_REC_AGAIN

};

void stop_recording(void);
void toggle_recording(void);
void record_audio_to_buffer(int16_t *src);
void write_buffer_to_storage(void);
void init_rec_buff(void);
void create_new_recording(uint8_t bitsPerSample, uint8_t numChannels);
FRESULT write_wav_chunk_size(FIL *wavfil, uint32_t file_position, uint32_t chunk_bytes);
FRESULT write_wav_info_chunk(FIL *wavfil, uint32_t *total_written);

#define RIFF_SIZE_POS	4
#define data_SIZE_POS	40

#endif /* INC_WAV_RECORDING_H_ */
