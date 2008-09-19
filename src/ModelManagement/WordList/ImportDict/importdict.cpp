//
// C++ Implementation: importdict
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "importdict.h"
#include "../../../SimonLib/Logging/logger.h"
#include "bompdict.h"
#include "lexicondict.h"
#include "wiktionarydict.h"
#include <KLocalizedString>

/**
 * \brief Constructor
 * \author Peter Grasch
 */
ImportDict::ImportDict(QObject *parent) : QThread(parent)
{
	dict=0;
	deleteFileWhenDone=false;
}

/**
 * \brief Parses the wordlist of an existing wiktioray wordlist
 * \author Peter Grasch
 */
void ImportDict::parseWordList(QString pathToDict, int type, bool deleteFileWhenDone)
{
	this->pathToDict = pathToDict;
	this->type = type;
	this->deleteFileWhenDone = deleteFileWhenDone;
	start(QThread::IdlePriority);
}

/**
 * \brief The main execution loop
 * Does the real world.
 * Uses the members pathToDict to get the location and writes the finished wordlist to the member wordList
 * \author Peter Grasch
 */
void ImportDict::run()
{
	Logger::log(i18n("[INF] Öffne Lexikon")+" \""+pathToDict+"\"");
	emit status(i18n("Öffne Wörterbuch..."));
	
	emit progress(10);
	if (dict) dict->deleteLater();
	if (type == WIKTIONARY)
		dict = new WiktionaryDict(pathToDict);
	else if (type == HADIFIXBOMP) dict = new BOMPDict(pathToDict);
	else if (type == LEXICON) dict = new LexiconDict(pathToDict);

	if (!dict) return;
	
	connect(dict, SIGNAL(loaded()), this, SLOT(openingFinished()));
	connect(dict, SIGNAL(progress(int)), this, SLOT(loadProgress(int)));
	
	emit status(i18n("Verarbeite Wörterbuch..."));
	
	dict->load(pathToDict);
	emit status(i18n("Erstelle Liste..."));
	QStringList words = dict->getWords();
	QStringList terminals = dict->getTerminals();
	QStringList pronunciations = dict->getPronuncations();
	dict->deleteLater();
	
	WordList* vocablist = new WordList();
	
	for (int i=0; i<words.count(); i++)
	{
		vocablist->append ( Word(QString(words.at(i)), 
				    QString(pronunciations.at(i)), 
					QString(terminals.at(i)), 0 ) );
		emit progress((int) ((((double) i)/((double)words.count())) *40+800));
	}
	if (type != LEXICON)
	{
		emit status(i18n("Sortiere Wörterbuch..."));
		qSort(vocablist->begin(), vocablist->end());
	}
	
	
	emit progress(1000);
	emit status(i18n("Wörterbuch wird verteilt..."));
	
	Logger::log(i18n("[UPT] ")+QString::number(words.count())+" "+i18n("Wörter aus dem lexikon")+" \""+pathToDict+"\""+i18n(" importiert"));

	if (deleteFileWhenDone)
	{
		Logger::log(i18n("[INF]")+" "+i18n("Lösche Eingabedatei"));
		
		QFile::remove(this->pathToDict);
	}
	emit finished(vocablist);
}

/**
 * \brief Translates the progress of the loading of the file to the global importing progress
 * emits the progress(int) signal with the calculated prog.
 * \author Peter Grasch
 * \param int prog
 * The progress of the loading
 */
void ImportDict::loadProgress(int prog)
{
	int globalProg =(int)  ((((double)prog)/1000)*800+10);
	emit progress(globalProg);
}

/**
 * \brief Deletes the dict
 * \author Peter Grasch
 */
void ImportDict::deleteDict()
{
	if (isRunning()) terminate();
	if (wait(2000))
		if (dict) {
			dict->deleteLater();
		}
}

/**
 * \brief Finished opening the file
 * Emits opened()
 * \author Peter Grasch
 */
void ImportDict::openingFinished()
{
	emit opened();
}

/**
 * \brief Destructor
 * \author Peter Grasch
 */
ImportDict::~ImportDict()
{
	if (dict) dict->deleteLater();
}


