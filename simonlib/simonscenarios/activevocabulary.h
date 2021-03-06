/*
 *   Copyright (C) 2009 Peter Grasch <peter.grasch@bedahr.org>
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

#ifndef SIMON_ACTIVEVOCABULARY_H_F80688D5A2B74774BF83C3A4C9EF13C2
#define SIMON_ACTIVEVOCABULARY_H_F80688D5A2B74774BF83C3A4C9EF13C2

#include "simonmodelmanagement_export.h"
#include "vocabulary.h"
#include <QBrush>
#include <simonscenariobase/scenarioobject.h>

class MODELMANAGEMENT_EXPORT ActiveVocabulary : public Vocabulary, public ScenarioObject
{

  private:
    QBrush recogNone;

    void buildBrushes();

    //Model methods
    QVariant data(const QModelIndex &index, int role) const;

  protected:
    ActiveVocabulary(Scenario *parent);

  public:
    static ActiveVocabulary* createVocabulary(Scenario *parent, const QDomElement&);
    bool addWords(QList<Word*> w);
    bool addWord(Word* w);
    bool reOrder(Word* w);
    bool removeWord(Word* w, bool deleteWord=true);
    bool takeWord(Word*);
    bool deSerialize(const QDomElement&);
    QDomElement serialize(QDomDocument *doc);
    bool renameCategory(const QString& from, const QString& to);
    bool empty();
};
#endif
