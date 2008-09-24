//
// C++ Implementation: internetextensionsettings
//
// Description: 
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "internetextensionsettings.h"
#include "../SimonLib/Settings/settings.h"
#include <QIcon>

InternetExtensionSettings::InternetExtensionSettings(QWidget* parent): QWidget(parent) //SystemWidget(i18n("Internet-Erweiterungen"), KIcon("document-open-remote"), i18n("Konfigurieren der URLS der Erweiterungs-Downloads"), parent)
{
// 	help = i18n("Hier können Sie URLS konfigurieren, um simon mit optionale Komponenten aus dem Internet zu erweitern");
	ui.setupUi(this);

	connect(ui.kcfg_WikiDumpPrefix, SIGNAL(textChanged(QString)), this, SLOT(makeExample()));
	connect(ui.kcfg_WikiDumpPostfix, SIGNAL(textChanged(QString)), this, SLOT(makeExample()));

	makeExample();
}


InternetExtensionSettings::~InternetExtensionSettings()
{
}


// bool InternetExtensionSettings::apply()
// {
// 	Settings::set("Internet/TextOnlineUpdate", ui.leTextUpdateURL->text());
// 	Settings::set("Internet/WikiDumpOverview", ui.leWikiDumpUrls->text());
// 	Settings::set("Internet/WikiDumpPrefix", ui.leWikiPrefix->text());
// 	Settings::set("Internet/WikiDumpPostfix", ui.leWikiPostfix->text());
// 	return true;
// }

// bool InternetExtensionSettings::init()
// {
// 	ui.leTextUpdateURL->setText(Settings::getS("Internet/TextOnlineUpdate"));
// 	ui.leWikiDumpUrls->setText(Settings::getS("Internet/WikiDumpOverview"));
// 	ui.leWikiPrefix->setText(Settings::getS("Internet/WikiDumpPrefix"));
// 	ui.leWikiPostfix->setText(Settings::getS("Internet/WikiDumpPostfix"));
// 	return true;
// }

void InternetExtensionSettings::makeExample()
{
	QString example;
	example += ui.kcfg_WikiDumpPrefix->text();
	example += "xxwiktionary/xxxxxxxx";
	example += ui.kcfg_WikiDumpPostfix->text();
	ui.lbExample->setText(example);
}

// bool InternetExtensionSettings::isComplete()
// {
// 	return true; //nothing is mandatory
// }

// bool InternetExtensionSettings::reset()
// {
// 	return init();
// }
