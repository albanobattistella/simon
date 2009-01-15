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


#include "grammarviewprivate.h"
#include "ImportGrammar/importgrammarwizard.h"
#include "MergeTerminals/mergeterminalswizard.h"
#include "RenameTerminal/renameterminalwizard.h"

#include <KMessageBox>
#include <KGlobal>
#include "grammarmanager.h"


GrammarViewPrivate::GrammarViewPrivate(QWidget* parent): QWidget( parent)
{
	ui.setupUi(this);
	ui.pbImportTexts->setIcon(KIcon("document-open"));
	ui.pbRename->setIcon(KIcon("document-properties"));
	ui.pbMerge->setIcon(KIcon("arrow-down-double"));


	connect(GrammarManager::getInstance(), SIGNAL(structuresChanged()), this, SLOT(load()));



	
	connect(ui.pbImportTexts, SIGNAL(clicked()), this, SLOT(showImportWizard()));
	connect(ui.pbMerge, SIGNAL(clicked()), this, SLOT(showMergeWizard()));

	//should be covered by structuresChanged() from the grammarmanager

	connect(ui.kcfg_GrammarStructures, SIGNAL(changed()), this, SLOT(slotChanged()));
	
	connect (ui.pbRename, SIGNAL(clicked()), this, SLOT(showRenameWizard()));
	
	load();
}

void GrammarViewPrivate::askForSave()
{
	if (KMessageBox::questionYesNo(this, i18n("You are about to starts a process that needs the grammar to be saved first.\n\nIf you want to keep the changes that you possibly made since the last time you stored your grammar, please save the grammar now.\n\nDo you want to save your grammar now?"), i18n("Save Grammar")) == KMessageBox::Yes)
		save();
}

void GrammarViewPrivate::slotChanged()
{
	save();
}

void GrammarViewPrivate::showRenameWizard()
{
	askForSave();

	RenameTerminalWizard *renameTerminalWizard = new RenameTerminalWizard(this);
	renameTerminalWizard->restart();
	renameTerminalWizard->exec();
	renameTerminalWizard->deleteLater();
}



void GrammarViewPrivate::load()
{
	ui.kcfg_GrammarStructures->setItems(GrammarManager::getInstance()->getStructures());
}

void GrammarViewPrivate::save()
{
	GrammarManager::getInstance()->setStructures(ui.kcfg_GrammarStructures->items());
	GrammarManager::getInstance()->save();
}

void GrammarViewPrivate::defaults()
{
	ui.kcfg_GrammarStructures->clear();
	save();
}


void GrammarViewPrivate::mergeGrammar(QStringList grammar)
{
	QStringList toInsert;
	
	QStringList currentStructures = ui.kcfg_GrammarStructures->items();
	for (int i=0; i < grammar.count(); i++)
	{
		if (!currentStructures.contains(grammar[i]))
			toInsert << grammar[i];
	}
	ui.kcfg_GrammarStructures->insertStringList(toInsert);
}


void GrammarViewPrivate::showImportWizard()
{
	ImportGrammarWizard *importGrammarWizard = new ImportGrammarWizard(this);
	connect(importGrammarWizard, SIGNAL(grammarCreated(QStringList)), this, SLOT(mergeGrammar(QStringList)));
	importGrammarWizard->exec();
	importGrammarWizard->deleteLater();
	save();
}

void GrammarViewPrivate::showMergeWizard()
{
	askForSave();

	MergeTerminalsWizard *mergeTerminalsWizard = new MergeTerminalsWizard(this);
	mergeTerminalsWizard->restart();
	mergeTerminalsWizard->exec();
	mergeTerminalsWizard->deleteLater();
}


GrammarViewPrivate::~GrammarViewPrivate()
{
}