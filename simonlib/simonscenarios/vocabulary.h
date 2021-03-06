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

#ifndef SIMON_VOCABULARY_H_99CD4459A9A24B97A96FA38373D5FEA2
#define SIMON_VOCABULARY_H_99CD4459A9A24B97A96FA38373D5FEA2
#include <QString>
#include <QList>
#include <QAbstractItemModel>

#include "simonmodelmanagement_export.h"

#include <simonscenarios/word.h>

class QDomElement;
class QDomDocument;

class MODELMANAGEMENT_EXPORT Vocabulary : public QAbstractItemModel
{

  private:
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int, Qt::Orientation orientation,
      int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

  protected:
    QStringList categories;                        //category cache
    QList<Word*> m_words;

    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    void sortWords();
    bool appendWordRaw(Word* w);
    bool insertWordRaw(int pos, Word* w);

  public:
    enum MatchType
    {
      ExactMatch=1,
      SimilarMatch=2,
      ContainsMatch=4
    };
    enum ExportFormat
    {
      SPHINX=1
    };

    Vocabulary(QObject *parent = 0);
    bool deSerialize(const QDomElement&);
    QDomElement serialize(QDomDocument *doc);
    static QDomElement createEmpty(QDomDocument *doc);

    /**
     * Adds the specified words to the vocabulary
     */
    virtual bool addWords(QList<Word*> w);
    virtual bool addWord(Word* w);

    virtual bool reOrder(Word* w);

    bool removeWord(Word* w, bool deleteWord=true);

    QString getRandomWord(const QString& category);
    bool containsWord(const QString& word);
    bool containsWord(const QString& word, const QString& category, const QString& pronunciation);

    int wordCount() { return m_words.count(); }
    QList<Word*> getWords() { return m_words; }
    virtual ~Vocabulary();

    bool renameCategory(const QString& from, const QString& to);

    QStringList getCategories();

    QList<Word*> findWords(const QString& name, Vocabulary::MatchType type);
    QList<Word*> findWordsByCategory(const QString& category);

    virtual bool empty() { return (m_words.count() == 0) ; }
    void clear();
    void deleteAll();

    bool exportToFile(const QString& path, Vocabulary::ExportFormat format);

    enum VocabularyType
    {
      ShadowVocabulary = 0,
      ActiveVocabulary = 1
    };

};
#endif
