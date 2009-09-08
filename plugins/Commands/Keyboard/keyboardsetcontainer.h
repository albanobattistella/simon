/*
 *   Copyright (C) 2009 Grasch Peter <grasch@simon-listens.org>
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

#ifndef KEYBOARDSETCONTAINER_H
#define KEYBOARDSETCONTAINER_H

#include "keyboardset.h"
#include <QList>
#include <QString>
#include <QStringList>
#include <QDomElement>

class KeyboardSetContainer
{
	private:
		QList<KeyboardSet *> setList;
		KeyboardSet* findSet(const QString& setName);

	public:
		KeyboardSetContainer();

		QStringList getAvailableSets();
		QStringList getAvailableTabs(const QString& set);
		KeyboardTab* getTab(const QString& set, const QString& tab);

		void clear();

		bool createSet(const QString& name);
		bool deleteSet(const QString& name);

		bool createTab(const QString& set, const QString& name);
		bool deleteTab(const QString& set, const QString& name);

		bool addButton(const QString& set, const QString& tab, KeyboardButton *button);
		bool deleteButton(const QString& set, const QString& tab, KeyboardButton *button);


		bool load();
		bool save();
		~KeyboardSetContainer();

};

#endif
