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
#include "dbuscommandmanager.h"
#include "dbuscommand.h"
#include "createdbuscommandwidget.h"

#include <KLocalizedString>

K_PLUGIN_FACTORY( DBusCommandPluginFactory,
registerPlugin< DBusCommandManager >();
)

K_EXPORT_PLUGIN( DBusCommandPluginFactory("simondbuscommand") )

DBusCommandManager::DBusCommandManager(QObject* parent, const QVariantList& args) : CommandManager((Scenario*) parent, args)
{
}

bool DBusCommandManager::shouldAcceptCommand(Command *command)
{
  return (dynamic_cast<DBusCommand*>(command) != 0);
}

const QString DBusCommandManager::iconSrc() const
{
  return "network-connect";
}


const QString DBusCommandManager::name() const
{
  return i18n("DBus");
}


CreateCommandWidget* DBusCommandManager::getCreateCommandWidget(QWidget *parent)
{
  return new CreateDBusCommandWidget(this, parent);
}

DEFAULT_DESERIALIZE_COMMANDS_PRIVATE_C(DBusCommandManager, DBusCommand);


DBusCommandManager::~DBusCommandManager()
{
}
