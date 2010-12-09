/*
 *   Copyright (C) 2009-2010 Grasch Peter <grasch@simon-listens.org>
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

#ifndef SIMON_DIALOGCONFIGURATION_H_4B4956DCAE204C49977297D20CB81F09
#define SIMON_DIALOGCONFIGURATION_H_4B4956DCAE204C49977297D20CB81F09

#include <simonscenarios/commandconfiguration.h>
#include "ui_dialogconfigurationdlg.h"
#include <KSharedConfig>
#include <QPointer>
#include <QPoint>
#include <QSize>

class Avatar;
class DialogCommand;
class DialogState;
class DialogSetContainer;
class DialogCommandManager;
class DialogTemplateOptions;
class BoundValue;
class DialogBoundValues;
class AvatarModel;

class DialogConfiguration : public CommandConfiguration
{
  Q_OBJECT

  private:
    Ui::DialogConfigurationDlg ui;
    DialogCommandManager *commandManager;

    DialogTemplateOptions *templateOptions;
    DialogBoundValues *boundValues;
    
    AvatarModel *avatarModel;

    void displayStates();
    DialogState* getCurrentState();
    DialogState* getCurrentStateGraphical();
    DialogCommand* getCurrentTransition();
    DialogCommand* getCurrentTransitionGraphical();

    QString getCurrentTemplateIndex();
    QString getCurrentTemplateIndexGraphical();

    BoundValue* getCurrentBoundValue();
    BoundValue* getCurrentBoundValueGraphical();
    
    Avatar* getCurrentAvatar();
    Avatar* getCurrentAvatarGraphical();

  private slots:
    void displayCurrentState();

    void addState();
    void renameState();
    void removeState();

    void moveStateUp();
    void moveStateDown();

    void editText();
    void textSilenceChanged();
    void textAnnounceRepeatChanged();

    void addTransition();
    void editTransition();
    void removeTransition();

    void moveTransitionUp();
    void moveTransitionDown();

    void addTemplateOption();
    void editTemplateOption();
    void removeTemplateOption();

    void addBoundValue();
    void editBoundValue();
    void removeBoundValue();
    
    void addAvatar();
    void editAvatar();
    void removeAvatar();
    
    void avatarSelected(const QModelIndex& selected);
    void avatarDisplayToggled(bool show);
    
    void addText();
    void removeText();
    void updateTextSelector();
    void displaySelectedText();

  public slots:
    void init();

    virtual bool deSerialize(const QDomElement&);
    virtual QDomElement serialize(QDomDocument *doc);
    virtual void defaults();

  public:
    DialogConfiguration(DialogCommandManager* _commandManager, Scenario *parent, const QVariantList &args = QVariantList());
    ~DialogConfiguration();

    DialogTemplateOptions* getDialogTemplateOptions() { return templateOptions; }
    DialogBoundValues* getDialogBoundValues() { return boundValues; }

    bool useGUIOutput() const;
    bool useTTSOutput() const;
    QString getOptionSeparatorText() const;
    QString getRepeatAnnouncement() const;
    QStringList getRepeatTriggers() const;
    bool getRepeatOnInvalidInput() const;
    
    int getAvatarSize() const;
    bool getDisplayAvatarNames() const;
    
    Avatar* getAvatar(int id) const;

};
#endif
