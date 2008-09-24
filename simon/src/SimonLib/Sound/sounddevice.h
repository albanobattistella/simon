/***************************************************************************
*   Copyright (C) 2006 by Peter Grasch   *
*   bedahr@gmx.net   *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef SOUNDDEVICE_H
#define SOUNDDEVICE_H

#include <QList>
#include <QString>
class SoundDevice;

typedef QList<SoundDevice> SoundDeviceList;

/**
 * \class SoundDevice
 * \author Gigerl Martin, Peter Grasch
 * \brief A simple class to store all the information representing a sounddevice
 * \version 0.1
 */
class SoundDevice
{
	private:
		int deviceID;
		QString name;
		int numChannels;
		int preferredSamplerate;
	public:
		SoundDevice ( int deviceID, QString name, int numChannels, int preferredSamplerate )
		{
			this->deviceID=deviceID;
			this->name=name;
			this->numChannels = numChannels;
			this->preferredSamplerate = preferredSamplerate;
		}
		int getDeviceID() const {return this->deviceID;}
		QString getName() const {return this->name;}
		int getChannels() const {return this->numChannels;}
		int getPreferredSamplerate() const {return this->preferredSamplerate;}
		~SoundDevice()    { }
};

#endif