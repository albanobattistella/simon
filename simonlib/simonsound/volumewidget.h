/*
 *   Copyright (C) 2010 Peter Grasch <grasch@simon-listens.org>
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


#ifndef SIMON_VOLUMEWIDGET_H_33F50DCCCC3D401FADDFBFD80B4E16F4
#define SIMON_VOLUMEWIDGET_H_33F50DCCCC3D401FADDFBFD80B4E16F4

#include "simonsound_export.h"
#include <QList>
#include <QWidget>

namespace Ui
{
	class VolumeWidgetUi;
}
namespace SimonSound {
	class DeviceConfiguration;
}

class DeviceVolumeWidget;

/**
 * \class VolumeWidget
 * \author Peter Grasch
 * \date 2.06.2010
 */
class SIMONSOUND_EXPORT VolumeWidget : public QWidget {
	Q_OBJECT

private:
	Ui::VolumeWidgetUi *ui;
	QList<DeviceVolumeWidget*> devices;

	void setPrompt(const QString& text);

	void registerClient(const SimonSound::DeviceConfiguration& device);

public slots:
	void start();
	void stop();
public:
	VolumeWidget(QWidget *parent=0);
	~VolumeWidget();

	void init();

};

#endif

