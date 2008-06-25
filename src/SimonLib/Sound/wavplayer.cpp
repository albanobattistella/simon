//
// C++ Implementation: wavplayer
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "wavplayer.h"
#include <QTimer>
#include <QObject>
#include <stdlib.h>
#include <string.h>
#include "../Logging/logger.h"
#include "../Settings/settings.h"
#include "wav.h"
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)

/**
 * \brief Constructor
 * \author Peter Grasch
 */
WavPlayer::WavPlayer(QObject *parent) : QObject(parent)
{
	stream = 0;
	wav= 0;
	data = 0;
	connect(&timeWatcher, SIGNAL(timeout()), this, SLOT(publishTime()));
}


int processOutputData( const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
		 const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags status, void *userData )
{
	WavPlayer *play = (WavPlayer*) userData;
	if (!play) return 1;

	int retVal = 0;
	
	if (play->getPosition()+framesPerBuffer > play->getLength())
	{
		framesPerBuffer = play->getLength()-play->getPosition();
		retVal = 1;
		play->stop();
	}
	
	
	memcpy(outputBuffer, play->getData()+play->getPosition(), framesPerBuffer*sizeof(float));
	
	play->advance(framesPerBuffer);
	
	return retVal;
}



/**
 * \brief Plays back the given file
 * \author Peter Grasch
 */
bool WavPlayer::play( QString filename )
{
	Logger::log(tr("[INF] Abspielen von %1").arg(filename)); 
	

	if (stream)
	{
// 		delete stream;
		stream = 0;
	}
	if (wav)
	{
		delete wav;
		wav = 0;
	}

	wavPosition = 0;
	length = 0;
	stopTimer = false;
	
	wav = new WAV(filename);
	short* shortData = (short*) wav->getRawData(this->length);
	if (length==0) return false;
	
	this->data = (float*) malloc(length*sizeof(float));
	
	for( unsigned int i=0; i<length; i++ ) //convert to floats
	{	//the wav file is stored using signed 16bit integers, but the
		//audio device expects 32-bit floats.
		//this (ugly) code should be replaced with a nice integrated
		//solution like phonon (once it is able to record...)
		*data = ((float) *shortData) / 32768.0f;
		data++;
		shortData++;
	}
	data -= length;
	

	PaStreamParameters  outputParameters;
	PaError             err = paNoError;

	err = Pa_Initialize();
	if( err != paNoError ) return false;

	bzero( &outputParameters, sizeof( outputParameters ) );

	int channels = wav->getChannels();
	int sampleRate = wav->getSampleRate();
	outputParameters.device = Settings::getI("Sound/OutputDevice");

	outputParameters.channelCount = channels;
	outputParameters.sampleFormat = paFloat32;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowInputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;

	/* Play some audio. -------------------------------------------- */
	
	
	err = Pa_OpenStream(
		&stream,
		NULL,                  /* &inputParameters, */
		&outputParameters,
		(double) sampleRate,
		1024, //frames per buffer
		paClipOff,      /* we won't output out of range samples so don't bother clipping them */
		processOutputData,
		(void*) this );

	if( err != paNoError ) return false;
	this->startTime = Pa_GetStreamTime(stream);
	
	
	err = Pa_StartStream( stream );
	if( err != paNoError ) return false;
	
	timeWatcher.start(100);

	return true;
}


void  WavPlayer::publishTime()
{
	if (stopTimer) 
	{
		timeWatcher.stop();
		closeStream();
	} else 
		emit currentProgress((Pa_GetStreamTime(stream) - startTime)*1000);
}



void WavPlayer::closeStream()
{
	timeWatcher.stop();
	PaError err = Pa_StopStream( stream );
	if( err != paNoError ) return;
	
	
	err = Pa_CloseStream( stream );
	if( err != paNoError ) return;
	
	stream = 0;

	Pa_Sleep( 500 );

	err = Pa_Terminate();
	if( err != paNoError ) return;
	
	delete wav; // data gets killed by WAV itself
	wav = 0;
	
	emit finished();
}

/**
 * \brief Stops the current playback
 * 
 * \author Peter Grasch
 */
void WavPlayer::stop()
{
	stopTimer = true; // to work around the issue that you can't stop the timer from a different thread
	//which would be the case if we would stop it here (this is called from the callback thread)
    //this also triggers the closing of the stream as we can't stop it here because it would still be open
    //from the callback function
}



/**
 * \brief Destructor
 * \author Peter Grasch
 */
WavPlayer::~WavPlayer()
{
	if (wav) delete wav;
}


