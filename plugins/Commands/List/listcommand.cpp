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

#include "listcommand.h"
#include "commandlistwidget.h"
#include <simonactions/actionmanager.h>
#include <unistd.h>
#include <QObject>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QObject>
#include <QTableWidgetSelectionRange>
#include <QHeaderView>
#include <QApplication>
#include <QVariant>
#include <KIcon>
#include <KLocalizedString>


QStringList ListCommand::numberIdentifiers;

ListCommand::ListCommand(const QString& name, const QString& iconSrc, const QStringList& commands, 
		const QStringList& iconSrcs, const QStringList& commandTypes) : Command(name, iconSrc)
{
	this->iconsrcs = iconSrcs;
	this->commands = commands;
	this->commandTypes = commandTypes;
	
	clw = new CommandListWidget();
	connect(clw, SIGNAL(canceled()), this, SLOT(cancel()));
	connect(clw, SIGNAL(runRequest(int)), this, SLOT(runCommand(int)));
	

	if (numberIdentifiers.isEmpty())
		numberIdentifiers << i18n("Zero") << i18n("One") << i18n("Two") 
			<< i18n("Three") << i18n("Four") << i18n("Five") <<
			i18n("Six") << i18n("Seven") << i18n("Eight") << i18n("Nine");
}

void ListCommand::runCommand(int index)
{
	Q_ASSERT(commands.count() == commandTypes.count());

	if (index > commands.count())
		return;

	ActionManager::getInstance()->triggerCommand(commandTypes[index], commands[index]);
	clw->close();
	ActionManager::getInstance()->deRegisterPrompt(this, "executeSelection");
}

void ListCommand::cancel()
{
	clw->close();
	ActionManager::getInstance()->deRegisterPrompt(this, "executeSelection");
}

bool ListCommand::executeSelection(QString inputText)
{
	if (inputText.toUpper() == i18n("Cancel").toUpper())
	{
		clw->close();
		return true;
	}

	//setting correct index
	int index = 0;
	while ((index < numberIdentifiers.count()) && (numberIdentifiers.at(index).toUpper() != inputText.toUpper()))
		index++;

	kWarning() << numberIdentifiers << inputText;
	if (index == numberIdentifiers.count()) return false;
	if (index == 0)
	{
		//go back
	} else if (index == 9)
	{
		//go forward

	} else {
		//execute list entry
		// if index==1, we want it to represent the _first_ entry in the list (index==0)
		index--;

		Q_ASSERT(commands.count() == commandTypes.count());
		if (index >= commands.count())
			return false;

		clw->close();
		usleep(300000);
		ActionManager::getInstance()->triggerCommand(commandTypes[index], commands[index]);
		ActionManager::getInstance()->deRegisterPrompt(this, "executeSelection");
	}

	return true;
}

const QString ListCommand::staticCategoryText()
{
	return i18n("List");
}

const QString ListCommand::getCategoryText() const
{
	return ListCommand::staticCategoryText();
}

const KIcon ListCommand::staticCategoryIcon()
{
	return KIcon("view-choose");
}

const KIcon ListCommand::getCategoryIcon() const
{
	return ListCommand::staticCategoryIcon();
}

const QMap<QString,QVariant> ListCommand::getValueMapPrivate() const
{
	QMap<QString,QVariant> out;
	out.insert(i18n("Commands"), commands.join("\n"));
	return out;
}

bool ListCommand::triggerPrivate()
{
	if (commands.count() == 0) return false;

	Q_ASSERT(commands.count() == commandTypes.count());
	//showing list

	clw->setWindowIcon(KIcon(getIconSrc()));
	clw->setWindowTitle(getTrigger());
	clw->init(iconsrcs, commands);
	clw->show();

	ActionManager::getInstance()->registerPrompt(this, "executeSelection");

	return true;
}

ListCommand::~ListCommand()
{
	ActionManager::getInstance()->deRegisterPrompt(this, "executeSelection");
	clw->deleteLater();
}

