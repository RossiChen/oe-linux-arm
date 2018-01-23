/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Quectel Co., Ltd. 2017
*
*****************************************************************************/
/*****************************************************************************
 *
 * Filename:
 * ---------
 *   ql_audio.h 
 *
 * Project:
 * --------
 *   OpenLinux
 *
 * Description:
 * ------------
 *   Audio API definition.
 *
 * Author:
 * -------
 * Jun.wu
 * -------
 *
 *============================================================================
 *             HISTORY
 *----------------------------------------------------------------------------
 * WHO                  WHEN              WHAT
 *----------------------------------------------------------------------------
 * Jun.wu               18/07/2016		  Create
 * Running.qian         13/12/2016        Implement newly-designed APIs.
 * Stanley.yong         19/12/2016        Optimize the APIs, and add comments.
 ****************************************************************************/
#ifndef __AUD_H__
#define __AUD_H__

#ifndef boolean
#define boolean unsigned int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


typedef enum {
	AUD_PLAYER_ERROR = -1,
	AUD_PLAYER_START = 0,
	AUD_PLAYER_PAUSE,
	AUD_PLAYER_RESUME,
	AUD_PLAYER_NODATA,  //Buff no data and play tread will sleep
    AUD_PLAYER_LESSDATA, //Buff has less data
	AUD_PLAYER_FINISHED,
} Enum_AudPlayer_State;

typedef enum {
	AUD_RECORDER_ERROR = -1,
	AUD_RECORDER_START = 0,
	AUD_RECORDER_PAUSE,
	AUD_RECORDER_RESUME,
	AUD_RECORDER_FINISHED,
} Enum_AudRecorder_State;


/****************************************************************************
*  Audio Volume Level Definition
***************************************************************************/
typedef enum {
	AUD_VOLUME_LEVEL1 = 0,
	AUD_VOLUME_LEVEL2,
	AUD_VOLUME_LEVEL3,
	AUD_VOLUME_LEVEL4,
	AUD_VOLUME_LEVEL5,
	AUD_VOLUME_LEVEL_END
}Enum_AudVolumeLevel;

/****************************************************************************
*  Audio Format
***************************************************************************/
typedef enum {
	AUD_STREAM_FORMAT_MP3 = 0,
	AUD_STREAM_FORMAT_AMR = 1,
	AUD_STREAM_FORMAT_PCM = 2,
	AUD_STREAM_FORMAT_END
} Enum_AudStreamFormat;

/****************************************************************************
*  Audio Direct
***************************************************************************/
typedef enum {
	AUD_LINK_REVERSE = 0,
	AUD_LINK_FORWARD = 1,
	AUD_LINK_BOTH = 2,
	AUD_LINK_INVALID
}Enum_AudStreamDirection;


/*****************************************************************
********************New Advanced Audio High API******************
* ***************************************************************/
struct wav_header {
	uint32_t riff_id;
	uint32_t riff_sz;
	uint32_t riff_fmt;
	uint32_t fmt_id;
	uint32_t fmt_sz;
	uint16_t audio_format;
	uint16_t num_channels;
	uint32_t sample_rate;
	uint32_t byte_rate;       /* sample_rate * num_channels * bps / 8 */
	uint16_t block_align;     /* num_channels * bps / 8 */
	uint16_t bits_per_sample;
	uint32_t data_id;
	uint32_t data_sz;
};

#define ID_RIFF 0x46464952
#define ID_WAVE 0x45564157
#define ID_FMT  0x20746d66
#define ID_DATA 0x61746164
#define FORMAT_PCM 1

struct ST_MediaParams {
	Enum_AudStreamFormat     format;
	Enum_AudVolumeLevel      volume;
	Enum_AudStreamDirection     direct;
};


//
// Function:  _cb_onPlayer
//
// Description:
//   This callback function handles the result of audio player.
//
// @param hdl:
//   Handle received from Ql_AudPlayer_Open().
// @param result:
//   the executing result for previous operation, such as Open, Play, Pause, Resume, Stop.
//   see the definition of Enum_AudPlayer_State for the specific meaning.
typedef int(*_cb_onPlayer)(int hdl, int result);
//
// Function:  _cb_onRecorder
//
// Description:
//   This callback function handles the result of audio recorder.
//   If result < 0, the recorder will stop the recording automatically.
//
// @param result:
//   the executing result for previous operation, such as Open, StartRecord, Pause, Resume, Stop.
//   see the definition of Enum_AudRecorder_State for the specific meaning.
// @param pBuf:
//   pointer to the output recording (PCM) data.
// @param length:
//   the length of the output recording (PCM) data.
typedef int(*_cb_onRecorder)(int result, unsigned char* pBuf, unsigned int length);  //if result < 0 will stop record, else  continue record

/*****************************************************************
* Function:     Ql_AudPlayer_Open
*
* Description:
*               Open audio play device, and specify the callback function.
*               This function can be called twice to play different audio sources.
*
* Parameters:
*               device  : a string that specifies the PCM device.
*                         NULL, means the audio will be played on the default PCM device.
*
*                         If you want to mixedly play audio sources, you can call this
*                         API twice with specifying different PCM device.
*                         The string devices available:
*                            "hw:0,0"  (the default play device)
*                            "hw:0,13" (this device can mix audio and TTS)
*                            "hw:0,14"
*
*		        cb_func : callback function for audio player. 
*                         The results of all operations on audio player
*                         are informed in callback function.
*
* Return:
*               pcm device handle
*               NULL, fail
*****************************************************************/
int  Ql_AudPlayer_Open(char* device, _cb_onPlayer cb_func);
//
// Function:  Ql_AudPlayer_Play
//
// Description:
//   this function writes pcm data to pcm device to play.
// @param hdl:
//   Handle received from Ql_AudPlayer_Open().
int  Ql_AudPlayer_Play(int hdl, unsigned char* pData, unsigned int length);
//
// Function:  Ql_AudPlayer_PlayFrmFile
//
// Description:
//   this function plays pcm data from the specified file.
// @param hdl:
//   Handle received from Ql_AudPlayer_Open().
int  Ql_AudPlayer_PlayFrmFile(int hdl, int fd, int offset);
//
// Function:  Ql_AudPlayer_Pause
//
// Description:
//   Pause playing.
// @param hdl:
//   Handle received from Ql_AudPlayer_Open().
int  Ql_AudPlayer_Pause(int hdl);
//
// Function:  Ql_AudPlayer_Resume
//
// Description:
//   Resume playing.
// @param hdl:
//   Handle received from Ql_AudPlayer_Open().
int  Ql_AudPlayer_Resume(int hdl);
//
// Function:  Ql_AudPlayer_Stop
//
// Description:
//   Stop playing audio
// hdl:
//   Handle received from Ql_AudPlayer_Open().
void Ql_AudPlayer_Stop(int hdl);
//
// Function:  Ql_AudPlayer_Close
//
// Description:
//   Close player, and free the resource.
// @param hdl:
//   Handle received from Ql_AudPlayer_Open().
void Ql_AudPlayer_Close(int hdl);


int Ql_AudPlayer_set_LessDataThreshold(int hdl, unsigned short threshSize);

int Ql_AudPlayer_get_freeSpace(int hdl);


/*****************************************************************
* Function:     Ql_AudRecorder_Open
*
* Description:
*               Open audio record device, and specify the callback function.
*
* Parameters:
*               device  : not used. MUST be NULL.
*
*		        cb_func : callback function for audio player.
*                         The results of all operations on audio recorder
*                         are informed in callback function.
*
* Return:
*               pcm device handle
*               NULL, fail
*****************************************************************/
int  Ql_AudRecorder_Open(char* device, _cb_onRecorder cb_fun);
//
// Function:  Ql_AudRecorder_StartRecord
//
// Description:
//   Start to record.
//   The record data is output in _cb_onRecorder.
int  Ql_AudRecorder_StartRecord(void);
//
// Function:  Ql_AudRecorder_Pause
//
// Description:
//   Pause recording
int  Ql_AudRecorder_Pause(void);
//
// Function:  Ql_AudRecorder_Resume
//
// Description:
//   Resume recording
int  Ql_AudRecorder_Resume(void);
//
// Function:  Ql_AudRecorder_Stop
//
// Description:
//   Stop recording
void Ql_AudRecorder_Stop(void);
//
// Function:  Ql_AudRecorder_Close
//
// Description:
//   Close recorder, and free the resource
void Ql_AudRecorder_Close(void);

//
// Function:  Ql_clt_set_mixer_value
//
// Description:
//   Close recorder, and free the resource
boolean Ql_clt_set_mixer_value(const char *device, int count, const char *value);


//****************QL TONE API************************//
struct Ql_TonePara {
    unsigned int lowFreq;   //100-4000HZ
    unsigned int highFreq;  //100-4000HZ
    unsigned int volume;    //0 -1000
    unsigned int duration;  // >0 ms
};

int Ql_AudTone_Open(char* device, _cb_onPlayer cb);//cb not support now
int Ql_AudTone_Start(int hdl, struct Ql_TonePara *para);
void Ql_AudTone_Stop(int hdl);
void Ql_AudTone_Close(int hdl);

#endif //__AUD_H__
