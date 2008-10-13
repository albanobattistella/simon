/*
 *   Copyright (C) 2008 Peter Grasch <grasch@simon-listens.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2,
 *   or (at your option) any later version, as published by the Free
 *   Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "recwidget.h"

#include "wavrecorder.h"
#include "wavplayer.h"
#include "postprocessing.h"
#include "soundsettings.h"

#include <simonlogging/logger.h>

#include <QGroupBox>
#include <QLabel>
#include <KPushButton>
#include <QProgressBar>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <KLocalizedString>

#include <KIcon>

#include <KMessageBox>
#include <QFile>
#include <QChar>

#include <QFont>

/**
 * \brief Constructor
 * \author Peter Grasch
 * @param QString name
 * The name that is displayed in the title of the groupbox
 * @param QString filename
 * The filename to record to; 
 * We will ressamble the file (existing or not) when we create the play/pause/delete handles
 * @param QWidget *parent
 * The parent of the object
 */
RecWidget::RecWidget(QString name, QString text, QString filename, QWidget *parent) : QWidget(parent)
{	
	this->filename = filename;
	recordingProgress=0;
	
	rec = new WavRecorder(this);
	play = new WavPlayer(this);
	postProc = new PostProcessing();

	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	//////////////////            GUI                    /////////////////
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

	QVBoxLayout *mainLay = new QVBoxLayout(this);
	gbContainer = new QGroupBox(name, this);
	mainLay->addWidget(gbContainer);

	QVBoxLayout *lay = new QVBoxLayout(gbContainer);

	toRecord = new QLabel(text, this);
	toRecord->setWordWrap(true);
	toRecord->setFont(SoundSettings::getInstance()->promptFont());
	lay->addWidget(toRecord);
	
	connect(SoundSettings::getInstance(), SIGNAL(promptFontChanged(const QFont&)),
		 this, SLOT(changePromptFont(const QFont&)));

	QHBoxLayout *hBox = new QHBoxLayout();
	pbRecord = new KPushButton(KIcon("media-record"),
				    i18n("Aufnehmen"),
				    this);
	pbRecord->setCheckable(true);
	hBox->addWidget(pbRecord);

	pbPlay = new KPushButton(KIcon("media-playback-start"),
				    i18n("Abspielen"),
				    this);
	pbPlay->setCheckable(true);
	hBox->addWidget(pbPlay);

	pbDelete = new KPushButton(KIcon("edit-delete"),
				    i18n("Löschen"),
				    this);
	hBox->addWidget(pbDelete);
	lay->addLayout(hBox);
	
	pbProgress = new QProgressBar(this);
	pbProgress->setMinimum(0);
	pbProgress->setValue(0);
	pbProgress->setMaximum(1);
	pbProgress->setFormat("00:00 / 00:00");
	
	lay->addWidget(pbProgress);


	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	
	
	if (QFile::exists(filename))
	{
		pbRecord->setEnabled(false);
		pbPlay->setEnabled(true);
		pbDelete->setEnabled(true);
	} else 
	{
		pbRecord->setEnabled(true);
		pbPlay->setEnabled(false);
		pbDelete->setEnabled(false);
	}
	
	setupSignalsSlots();

}


void RecWidget::changePromptFont(const QFont& font)
{
	toRecord->setFont(font);
}

/**
 * \brief Returns true if there is a file at the assigned filename
 * \author Peter Grasch
 * @return File exists?
 */
bool RecWidget::hasRecordingReady()
{
	return QFile::exists(this->filename);
}

/**
 * \brief Sets up the signal/slot connections
 * \author Peter Grasch
 */
void RecWidget::setupSignalsSlots()
{
	//Enable / Disable
	connect(pbRecord, SIGNAL(toggled(bool)), pbPlay, SLOT(setDisabled(bool)));
	connect(pbRecord, SIGNAL(toggled(bool)), pbDelete, SLOT(setDisabled(bool)));
	connect(pbRecord, SIGNAL(toggled(bool)), pbRecord, SLOT(setEnabled(bool)));
	connect(pbPlay, SIGNAL(toggled(bool)), pbDelete, SLOT(setDisabled(bool)));
	connect(pbDelete, SIGNAL(clicked(bool)), pbRecord, SLOT(setDisabled(bool)));
	connect(pbDelete, SIGNAL(clicked(bool)), pbPlay, SLOT(setEnabled(bool)));
	connect(pbDelete, SIGNAL(clicked(bool)), pbDelete, SLOT(setEnabled(bool)));
	
	connect(pbRecord, SIGNAL(clicked()), this, SLOT(record()));
	connect(pbPlay, SIGNAL(clicked()), this, SLOT(playback()));
	connect(pbDelete, SIGNAL(clicked()), this, SLOT(deleteSample()));
	
	connect(rec, SIGNAL(currentProgress(int)), this, SIGNAL(progress(int)));
	connect(play, SIGNAL(currentProgress(int)), this, SIGNAL(progress(int)));
	connect(rec, SIGNAL(currentProgress(int)), this, SLOT(displayRecordingProgress(int)));
	connect(play, SIGNAL(currentProgress(int)), this, SLOT(displayPlaybackProgress(int)));
	
	connect(play, SIGNAL(finished()), this, SLOT(finishPlayback()));
}


/**
 * \brief Sets the widgets title to the given title
 * \author Peter Grasch
 * @param newTitle The new title
 */
void RecWidget::setTitle(QString newTitle)
{
	gbContainer->setTitle(newTitle);
}


/**
 * \brief Displays the given progress in recording
 * \author Peter Grasch
 * Sets the Label to a string similar to "00:00 / xx:xx"
 * @param int msecs
 * How long have we been recording?
 */
void RecWidget::displayRecordingProgress(int msecs)
{
 	QString textprog = QString("%1").arg((int) msecs/10, 4, 10, QChar('0'));
	textprog.insert(textprog.length()-2, ':');
	pbProgress->setFormat("00:00 / "+textprog);
	this->recordingProgress = msecs;
}

/**
 * \brief Displays the given progress in playing
 * \author Peter Grasch
 * @param int msecs
 * How long have we been playing?
 */
void RecWidget::displayPlaybackProgress(int msecs)
{
 	QString textprog = QString("%1").arg(QString::number(msecs/10), 4, QChar('0'));
	textprog.insert(2, ':');
	
	pbProgress->setFormat(pbProgress->format().replace(0,5, textprog));
	pbProgress->setValue(msecs);
}


/**
 * \brief Starts the recording
 * \author Peter Grasch
 */
void RecWidget::record()
{
	QString fName = this->filename;
	if (SoundSettings::getInstance()->processInternal())
		fName += "_tmp";
	if (!rec->record(fName))
	{
		disconnect(pbRecord, SIGNAL(toggled(bool)), pbPlay, SLOT(setDisabled(bool)));
		disconnect(pbRecord, SIGNAL(toggled(bool)), pbDelete, SLOT(setDisabled(bool)));
		disconnect(pbRecord, SIGNAL(toggled(bool)), pbRecord, SLOT(setEnabled(bool)));
		
		KMessageBox::error(this, i18n("Konnte Aufnahme nicht starten.\n\n"
						"Wahrscheinlich konnte das Aufnahmegerät nicht "
						"initalisiert werden.\n\nBitte überprüfen Sie "
						"ihre Audiokonfiguration und versuchen Sie es "
						"erneut."));
		pbRecord->toggle();
		
		connect(pbRecord, SIGNAL(toggled(bool)), pbPlay, SLOT(setDisabled(bool)));
		connect(pbRecord, SIGNAL(toggled(bool)), pbDelete, SLOT(setDisabled(bool)));
		connect(pbRecord, SIGNAL(toggled(bool)), pbRecord, SLOT(setEnabled(bool)));
	}else {
		disconnect(pbRecord, SIGNAL(clicked()), this, SLOT(record()));
		connect(pbRecord, SIGNAL(clicked()), this, SLOT(stopRecording()));
		
		pbProgress->setMaximum(0);
	}
	emit recording();
}


/**
 * \brief Finishes up the playback
 * \author Peter Grasch
 */
void RecWidget::finishPlayback()
{
	disconnect(pbPlay, SIGNAL(clicked()), this, SLOT(stopPlayback()));
	pbPlay->setChecked(false);
	connect(pbPlay, SIGNAL(clicked()), this, SLOT(playback()));
	emit playbackFinished();
	
	displayPlaybackProgress(recordingProgress);
}

/**
 * \brief Stops the recording
 * \author Peter Grasch
 */
void RecWidget::stopRecording()
{
	QString fName = this->filename;
	bool processInternal = SoundSettings::getInstance()->processInternal();
	
	if (processInternal)
		fName += "_tmp";

	if (!rec->finish())
		KMessageBox::error(this, i18n("Abschließen der Aufnahme fehlgeschlagen. Möglicherweise ist die Aufnahme fehlerhaft.\n\nTip: überprüfen Sie ob Sie die nötigen Berechtigungen besitzen um auf %1 schreiben zu dürfen!", fName));
		
	if (processInternal)
// 		if (!QFile::copy(fName, filename) || !QFile::remove(fName))
		if (!postProc->process(fName, filename, true))
			KMessageBox::error(this, i18n("Nachbearbeitung fehlgeschlagen"));
	
	
	pbProgress->setValue(0);
	pbProgress->setMaximum(1);
	
	disconnect(pbRecord, SIGNAL(clicked()), this, SLOT(stopRecording()));
	connect(pbRecord, SIGNAL(clicked()), this, SLOT(record()));
	emit recordingFinished();
}

/**
 * \brief Stops the playback
 * \author Peter Grasch
 */
void RecWidget::stopPlayback()
{
	play->stop();
}

/**
 * \brief Starts the playback
 * \author Peter Grasch
 */
void RecWidget::playback()
{
	if (play->play(this->filename))
	{	
		pbProgress->setMaximum(recordingProgress);
		disconnect(pbPlay, SIGNAL(clicked()), this, SLOT(playback()));
		connect(pbPlay, SIGNAL(clicked()), this, SLOT(stopPlayback()));
		emit playing();
	} else {
		KMessageBox::error(this, i18n("Konnte Wiedergabe nicht starten.\n\n"
						"Wahrscheinlich konnte das Wiedergabegerät nicht "
						"initalisiert werden.\n\nBitte überprüfen Sie "
						"ihre Audiokonfiguration und versuchen Sie es "
						"erneut."));	
		pbPlay->setChecked(false);
	}
}

/**
 * \brief Deletes the file at filename (member)
 * \author Peter Grasch
 */
void RecWidget::deleteSample()
{
	if(QFile::remove(this->filename))
	{
		pbProgress->setValue(0);
		pbProgress->setFormat("00:00 / 00:00");
		pbDelete->setEnabled(false);
		pbRecord->setEnabled(true);
		pbPlay->setEnabled(false);
		emit sampleDeleted();
	} else KMessageBox::error(this, 
			i18n("Konnte die Datei %1 nicht entfernen", this->filename));
}

/**
 * \brief Destructor
 * \author Peter Grasch
 */
RecWidget::~RecWidget()
{
	delete play;
 	delete rec;
}

