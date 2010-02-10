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


#include "simonduserconfiguration.h"
#include "simondconfiguration.h"
#include <simonddatabaseaccess/databaseaccess.h>
#include <QCryptographicHash>
#include <QDir>
#include <QFile>
#include <KMessageBox>
#include <KPasswordDialog>
#include <knewpassworddialog.h>

SimondUserConfiguration::SimondUserConfiguration(QWidget* parent, const QVariantList& args)
					: KCModule(KGlobal::mainComponent(), parent), alreadyLoaded(false)
{
	Q_UNUSED(args);
	
	ui.setupUi(this);
	
	//addConfig(SimondConfiguration::self(), this);

	kDebug() << "opening database";
	db = new DatabaseAccess(this);
	connect (ui.pbAdd, SIGNAL(clicked()), this, SLOT(addUser()));
	connect (ui.pbDelete, SIGNAL(clicked()), this, SLOT(deleteUser()));
	connect (ui.pbChangePassword, SIGNAL(clicked()), this, SLOT(changePassword()));

	ui.pbAdd->setIcon(KIcon("list-add"));
	ui.pbDelete->setIcon(KIcon("edit-delete"));
	ui.pbChangePassword->setIcon(KIcon("edit-rename"));

	//disable direct editing of the table
	ui.tvUser->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void SimondUserConfiguration::slotChanged()
{
	emit changed(true);
}

void SimondUserConfiguration::activateUserConfiguration(bool active)
{
	ui.pbAdd->setEnabled(active);
	ui.pbDelete->setEnabled(active);
	ui.tvUser->setEnabled(active);
}

void SimondUserConfiguration::initDb()
{
	if (!db->init())
	{
		KMessageBox::error(this, i18n("Couldn't connect to database"));
		activateUserConfiguration(false);
		ui.tvUser->setModel(NULL); //empty table
		KMessageBox::information(this, db->getDatabase());
	} else {
		kDebug() << "Db has been changed";
		activateUserConfiguration(true);
		ui.tvUser->setModel(db->getUsers());
	}
}

void SimondUserConfiguration::addUser()
{
	KPasswordDialog dlg( dynamic_cast<QWidget*>(parent()), 
				KPasswordDialog::ShowUsernameLine);
	dlg.setPrompt( i18n( "Add a new user" ));
	if( !dlg.exec() || dlg.username().isEmpty() )
		return;

	QString user = dlg.username();
	QString pass = dlg.password();

	if (!db->addUser(user, encryptPassword(pass)))
		KMessageBox::error(0, i18n("Couldn't add user"));
}

void SimondUserConfiguration::deleteUser()
{
	if (!ui.tvUser->currentIndex().isValid())
		return;

	if (KMessageBox::questionYesNoCancel(this, i18n("Do you really want to remove the user from the database?")) != KMessageBox::Yes)
		return;

	//delete user from db
	QString username = ui.tvUser->currentIndex().sibling(ui.tvUser->currentIndex().row(), 0).data().toString();
	if (!db->deleteUser(username))
	{
		KMessageBox::error(0, i18n("Couldn't remove User"));
		return;
	}

	QString modelDir = KStandardDirs::locateLocal("data", "simond/models/")+username+"/";
	if ((!QDir().exists(modelDir)) ||
			(KMessageBox::questionYesNoCancel(this, i18n("Do you also want to remove the speech model from the server?")) != KMessageBox::Yes))
		return;

	if (!recursiveDelete(modelDir))
		KMessageBox::sorry(this, i18n("Couldn't remove the speech model"));
}

bool SimondUserConfiguration::recursiveDelete(const QString& dirPath)
{
	bool allDeleted=true;

	QDir dir(dirPath);

	//delete all files
	QStringList files = dir.entryList(QDir::Files|QDir::NoDotAndDotDot);
	foreach (const QString& file, files)
		if (!QFile::remove(dirPath+QDir::separator()+file))
			allDeleted=false;

	//descend into subdirs
	QStringList subDirs = dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot);
	foreach (const QString& subDir, subDirs)
	{
		if (!recursiveDelete(dirPath+QDir::separator()+subDir))
			allDeleted=false;
	}

	if (allDeleted)
	{
		//we can remove this dir
		dir.cdUp();
		dir.rmdir(dirPath);
	}

	return allDeleted;
}

QByteArray SimondUserConfiguration::encryptPassword(const QString& password)
{
	return QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Sha1);
}


void SimondUserConfiguration::changePassword()
{
	if (!ui.tvUser->currentIndex().isValid())
		return;

	QString username = ui.tvUser->currentIndex().sibling(ui.tvUser->currentIndex().row(), 0).data().toString();
	KNewPasswordDialog dlg(this);
	dlg.setPrompt(i18n("Change Password for User \"%1\"", username));
	if (dlg.exec() && (!dlg.password().isEmpty()))
	{
		if (!db->setPassword(username, encryptPassword(dlg.password())))
			KMessageBox::error(0, i18n("Couldn't change Password"));
	}

}


void SimondUserConfiguration::load()
{
	if (!alreadyLoaded)
	{
		kDebug() << "LOAD!";
		initDb();
		alreadyLoaded = true;
	}
	KCModule::load();
}

void SimondUserConfiguration::save()
{
	KCModule::save();
}


SimondUserConfiguration::~SimondUserConfiguration()
{	
	db->deleteLater();
}
