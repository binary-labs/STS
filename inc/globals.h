/*  * globals.h
 *
 *  Created on: Jun 8, 2014
 *      Author: design
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

//Set this to 0 for slower ADC (classic)
//Set to 1 for faster ADC (newer, less tested)
#define X_FAST_ADC 1

//codec_BUFF_LEN = Size (in samples) of the DMA rx/tx buffers:
//Each channel = codec_BUFF_LEN/2 samples
//We process the rx buffer when it's half-full and 100% full, so codec_BUFF_LEN/4 samples are processed at one time

//=2048B codec_BUFF_LEN
//=1024B each Half Transfer
//=256 samples (32-bit samples from codec, even if in 16bit mode)
#if X_FAST_ADC == 1
	#define codec_BUFF_LEN 1024 
#else
	#define codec_BUFF_LEN 2048
#endif
#define HT16_BUFF_LEN (codec_BUFF_LEN>>2)		/*256*/
#define HT16_CHAN_BUFF_LEN (HT16_BUFF_LEN>>1) 	/*128*/

/* @codec_BUFF_LEN2048:
 * 2048 bytes per DMA transfer
 * 1024 bytes/half-transfer @ 16 bits/sample = 512 samples per half-transfer
 * 512 samples/half-transfer = 256 samples per channel per half-transfer

 * 256/interrupt @ 44100Hz = interrupt runs every 5.8ms
*/
//Note: If this changes, we may have also change:
// -'make wav' section in Makefile
// -PLLI2S_N and PLLI2S_R in system_stm32f4xx.c
// -sys_tmr's timing will change

#define BASE_SAMPLE_RATE 44100
#define f_BASE_SAMPLE_RATE 44100.0 /*float version*/

//Update the FW Version anytime FLASH RAM settings format is changed
#define FW_MAJOR_VERSION 1
#define FW_MINOR_VERSION 3

//Minimum firmware version that doesn't need a calibration on the very first boot
#define FORCE_CAL_UNDER_FW_MAJOR_VERSION 0
#define FORCE_CAL_UNDER_FW_MINOR_VERSION 2

enum Flags {
	PlaySample1Changed, 	//0
	PlaySample2Changed,
	PlayBank1Changed,
	PlayBank2Changed,
	RecSampleChanged,
	RecBankChanged, 		//5
	Play1But,
	Play2But,
	RecTrig,
	Rev1Trig,
	Rev2Trig, 				//10
	PlayBuff1_Discontinuity,
	PlayBuff2_Discontinuity,
	ToggleMonitor,
	ToggleLooping1,
	ToggleLooping2, 		//15
	PlaySample1Changed_valid,
	PlaySample2Changed_valid,
	PlaySample1Changed_empty,
	PlaySample2Changed_empty,
	RecSampleChanged_light, //20
	ForceFileReload1,
	ForceFileReload2,
	AssignModeRefused,
	AssigningEmptySample,
	TimeToReadStorage, 		//25
	Play1Trig,
	Play2Trig,
	StereoModeTurningOn,
	StereoModeTurningOff,
	SkipProcessButtons, 	//30
	ViewBlinkBank1,
	ViewBlinkBank2,
	PlayBankHover1Changed,
	PlayBankHover2Changed,
	RecBankHoverChanged, 	//35
	RevertSample,
	RevertBank1,
	RevertBank2,
	RevertAll,
	RewriteIndex, 			//40
	RewriteIndexFail,
	RewriteIndexSucess,
	AssignedNextSample,
	AssignedPrevBank,
	FindNextSampleToAssign, //45
	SaveUserSettings,
	UndoSampleExists,
	UndoSampleDiffers,
	LoadBackupIndex,
	LoadIndex,				//50
	LatchVoltOctCV1,
	LatchVoltOctCV2, 
	Play1TrigDelaying,
	Play2TrigDelaying,
	BootBak,				// 55
	SystemModeButtonsDown,
	ShutdownAndBootload,

	NUM_FLAGS
};


//Error codes for g_error
enum g_Errors{
	OUT_OF_MEM					=1,
	SDCARD_CANT_MOUNT			=2,
	SPIERROR_1					=4,
	WRITE_SDRAM_ERROR			=8,
	DMA_OVR_ERROR				=16,
	sFLASH_BAD_ID				=32,
	WRITE_BUFF_OVERRUN			=(1<<6),
	READ_BUFF1_OVERRUN			=(1<<7),
	READ_BUFF2_OVERRUN			=(1<<8),
	READ_MEM_ERROR				=(1<<9),
	WRITE_SDCARD_ERROR			=(1<<10),
	WRITE_BUFF_UNDERRUN			=(1<<11),

	FILE_OPEN_FAIL				=(1<<12),
	FILE_READ_FAIL_1			=(1<<13),
	FILE_READ_FAIL_2			=(1<<14),
	FILE_WAVEFORMATERR			=(1<<15),
	FILE_UNEXPECTEDEOF			=(1<<16),
	FILE_SEEK_FAIL				=(1<<17),
	READ_BUFF_OVERRUN_RESAMPLE	=(1<<18),
	FILE_CANNOT_CREATE_CLTBL	=(1<<19),
	CANNOT_OPEN_ROOT_DIR		=(1<<20),
	FILE_REC_OPEN_FAIL			=(1<<21),
	FILE_WRITE_FAIL				=(1<<22),
	FILE_UNEXPECTEDEOF_WRITE	=(1<<23),
	CANNOT_WRITE_INDEX			=(1<<24),
	LSEEK_FPTR_MISMATCH			=(1<<25),
	HEADER_READ_FAIL			=(1<<26)


};


//Number of channels
#define NUM_PLAY_CHAN 2
#define NUM_REC_CHAN 1
#define NUM_ALL_CHAN 3

#define NUM_SAMPLES_PER_BANK 10
#define MAX_NUM_BANKS 60

#define REC (NUM_ALL_CHAN-1) /* =2 a shortcut to the REC channel */
#define CHAN1 0
#define CHAN2 1

//About 45ms delay
#define delay()						\
do {							\
  register unsigned int i;				\
  for (i = 0; i < 1000000; ++i)				\
    __asm__ __volatile__ ("nop\n\t":::"memory");	\
} while (0)


#define delay_ms(x)						\
do {							\
  register unsigned int i;				\
  for (i = 0; i < (25000*x); ++i)				\
    __asm__ __volatile__ ("nop\n\t":::"memory");	\
} while (0)


#define CCMDATA __attribute__ ((section (".ccmdata")))
//#define CCMDATA

void check_errors(void);

//extern volatile uint32_t sys_time;
//#define delay_sys(x) do{register uint32_t donetime=x+systime;__asm__ __volatile__ ("nop\n\t":::"memory");}while(sys_time!=donetime;)


#endif /* GLOBALS_H_ */
