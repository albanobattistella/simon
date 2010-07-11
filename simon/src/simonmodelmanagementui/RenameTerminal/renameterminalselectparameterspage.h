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

#ifndef SIMON_RENAMETERMINALSELECTPARAMETERSPAGE_H_634D7DC412D24E0696239562AA94C143
#define SIMON_RENAMETERMINALSELECTPARAMETERSPAGE_H_634D7DC412D24E0696239562AA94C143

#include <QWizardPage>
#include "ui_renameterminalselectparameterspage.h"
/**
  @author Peter Grasch <bedahr@gmx.net>
*/
class RenameTerminalSelectParametersPage : public QWizardPage
{
  Q_OBJECT
    private:
    Ui::RenameTerminalSelectParametersDlg ui;
  public:
    RenameTerminalSelectParametersPage(QWidget *parent);
    void initializePage();

    ~RenameTerminalSelectParametersPage();

};
#endif
