/*
 *   Copyright (C) 2009 Peter Grasch <grasch@simon-listens.org>
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


#ifndef SIMON_SCENARIOMANAGER_H
#define SIMON_SCENARIOMANAGER_H

/**
 *	@class ScenarioManager
 *	@author Peter Grasch
*/

#include <QObject>
#include <QStringList>
#include <QList>
#include <simonrecognitionresult/recognitionresult.h>
#include <simonactions/greedyreceiver.h>

#include "command.h"
#include "commandlauncher.h"
#include "speechmodel.h"
#include "vocabulary.h"
#include "simonmodelmanagement_export.h"

class Word;
class Scenario;
class ScenarioDisplay;
class ShadowVocabulary;
class Command;
class Action;
class CommandManager;

class MODELMANAGEMENT_EXPORT ScenarioManager : public QObject {
Q_OBJECT

signals:
	void scenariosChanged();
	void shadowVocabularyChanged();
	void baseModelChanged();

private:
	bool m_inGroup;
	bool m_baseModelDirty;
	bool m_scenariosDirty;
	bool m_shadowVocabularyDirty;
	bool setupScenario(Scenario *s);
	void touchBaseModelAccessTime();

public:
	static ScenarioManager *getInstance() {
		if (!instance) instance = new ScenarioManager();
		return instance;
	}
	
	ScenarioManager(QObject *parent=0);
	~ScenarioManager();

	QList<Scenario*> getScenarios() { return scenarios; }
	void registerScenarioDisplay(ScenarioDisplay *display) {
		scenarioDisplays.append(display);
	}

	Scenario *getScenario(const QString& id);
	Scenario *getCurrentScenario() { return currentScenario; }

	bool init();
	ShadowVocabulary* getShadowVocabulary();

	bool storeScenario(const QString& id, const QByteArray& data);

	QStringList getTerminals(SpeechModel::ModelElements elements);
	bool renameTerminal(const QString& terminal, const QString& newName, SpeechModel::ModelElements affect);

	QList<Word*> findWords(const QString& name, SpeechModel::ModelElements elements, Vocabulary::MatchType);
	QList<Word*> findWordsByTerminal(const QString& name, SpeechModel::ModelElements elements);

	QStringList getExampleSentences(const QString& name, const QString& terminal, int count, SpeechModel::ModelElements elements);
	bool setupScenarios(bool forceChange=false);

	QStringList getAllAvailableScenarioIds();


	bool triggerCommand(const QString& type, const QString& trigger);
	bool processResult(RecognitionResult recognitionResult);

	CommandList* getCommandList();
	QList<CommandLauncher*> getLauncherList();

	void startGroup();
	bool commitGroup(bool silent=false);

	void setPluginFont(const QFont& font);

	int baseModelType();
	void setBaseModelType(int);
	QString baseModelHMMName();
	QString baseModelTiedlistName();
	QString baseModelMacros();
	QString baseModelStats();
	void setBaseModel(int modelType, const QString& hmmName, const QString& tiedlistName, 
			const QString& macrosName, const QString& statsName);
	
public slots:
	// If force is true, every registered display will switch to this scenario
	// if not, only displays that already display the scenario will be updated
	void updateDisplays(Scenario* scenario, bool force=false);

	void slotBaseModelChanged();

private:
	static ScenarioManager *instance;
	ShadowVocabulary *shadowVocab;
	Scenario *currentScenario;
	
	QList<Scenario*> scenarios;
	QList<ScenarioDisplay*> scenarioDisplays;

};

#endif
