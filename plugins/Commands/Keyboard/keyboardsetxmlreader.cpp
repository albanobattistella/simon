/*
 *   Copyright (C) 2009 Dominik Neumeister <neudob06@edvhtl.at>
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

#include "keyboardsetxmlreader.h"

#include <QString>
#include <QList>
#include <QFile>
#include <QStringList>
#include <QDomNode>
#include <QDomDocument>
#include <KFilterDev>
#include <QDebug>
#include <QDir>


KeyboardsetXMLReader::KeyboardsetXMLReader(const QString& path):XMLDomReader(path)
{ }

bool KeyboardsetXMLReader::save(QList<KeyboardSet *> * setList, const QString &path)
{
       /* if (this->doc)
                this->doc->clear();
        else doc = new QDomDocument ();

        QDomElement root = doc->createElement("keyboardsets");
        doc->appendChild(root);

        for (int i=0; i < setList->size(); i++)
        {
                KeyboardSet *kbs = dynamic_cast<KeyboardSet*>(setList->at(i));
                if (!kbs) continue;

                QDomElement set = doc->createElement("set");
                QDomElement setname = doc->createElement("setname");
                setname.appendChild(doc->createTextNode(kbs->getSetName()));
                set.appendChild(setname);

                for(int j=0; j < kbs->getTabList()->size(); j++)
                {
                    KeyboardTab *kbt = dynamic_cast<KeyboardTab*>(kbs->getTabList()->at(j));
                    if (!kbt) continue;

                    QDomElement tab = doc->createElement("tab");
                    QDomElement tabname = doc->createElement("tabname");
                    tabname.appendChild(doc->createTextNode(kbt->getTabName()));
                    tab.appendChild(tabname);

                    for(int k=0; k < kbt->getButtonList()->size(); k++)
                    {
                        KeyboardButton *kbb = dynamic_cast<KeyboardButton*>(kbt->getButtonList()->at(k));
                        if (!kbb) continue;

                        QDomElement button= doc->createElement("button");
                        QDomElement triggershown = doc->createElement("triggershown");
                        triggershown.appendChild(doc->createTextNode(kbb->getTriggerShown()));
                        QDomElement realtrigger = doc->createElement("realtrigger");
                        realtrigger.appendChild(doc->createTextNode(kbb->getTriggerReal()));
                        QDomElement valuetype = doc->createElement("valuetype");
                        valuetype.appendChild(doc->createTextNode(QString::number(kbb->getValueType())));
                        QDomElement value = doc->createElement("value");
                        value.appendChild(doc->createTextNode(kbb->getValue()));

                        button.appendChild(triggershown);
                        button.appendChild(realtrigger);
                        button.appendChild(valuetype);
                        button.appendChild(value);

                        tab.appendChild(button);
                    }
                    set.appendChild(tab);
                }
                root.appendChild(set);
        }*/

        return XMLDomReader::save(path);
}

QList<KeyboardSet *> * KeyboardsetXMLReader::load(QString path)
{
	if (!XMLDomReader::load(path))
		return NULL;

/*        QList<KeyboardSet *> *setList = new QList<KeyboardSet *>();

        QDomElement root = this->doc->documentElement();
        if(root.isNull())
		return setList;
        
	QDomElement set = root.firstChildElement();
	QDomElement setname = set.firstChildElement();
	QList<KeyboardTab *> *tabList = new QList<KeyboardTab *>();
	while(!set.isNull())
	{
		QDomElement tab = set.nextSiblingElement();
		while(!tab.isNull())
		{
		    QDomElement tabname = tab.firstChildElement();
		    QList<KeyboardButton *> *buttonList = new QList<KeyboardButton *>();

		    QDomElement button = tabname.nextSiblingElement();

		    while(!button.isNull())
		    {
			    QDomElement triggershown = button.firstChildElement();
			    QDomElement realtrigger = triggershown.nextSiblingElement();
			    QDomElement valuetype = realtrigger.nextSiblingElement();
			    QDomElement value = valuetype.nextSiblingElement();
			    button = button.nextSiblingElement();
		    	    buttonList->append(new KeyboardButton(triggershown.text(), realtrigger.text(), valuetype.text().toShort(), value.text()));
		    }

		    tab = tab.nextSiblingElement();
		    tabList->append(new KeyboardTab(tabname.text(), buttonList));
		}
		setList->append(new KeyboardSet(setname.text(), tabList));
		set = set.nextSiblingElement();
	}

        return setList;*/
	return NULL;
}

KeyboardsetXMLReader::~KeyboardsetXMLReader()
{

}
