/*
 *   Copyright (C) 2008 Peter Grasch <peter.grasch@bedahr.org>
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

#ifndef SIMON_IMPORTTRAININGTEXTSELECTSOURCEPAGE_H_F1FB4FAFF8B54EA8B5088D7D53DBFB32
#define SIMON_IMPORTTRAININGTEXTSELECTSOURCEPAGE_H_F1FB4FAFF8B54EA8B5088D7D53DBFB32

#include <QWizardPage>
#include "ui_importtrainingtextselectsourcepage.h"
class QRadioButton;
/**
 * \class ImportTrainingTextSelectSourcePage
 * \author Peter Grasch
 * \version 0.1
 * \brief Selects the type of text to import: local or remote
 */
class ImportTrainingTextSelectSourcePage :  public QWizardPage
{
  Q_OBJECT

    private:
    Ui::ImportTrainingTextSelectSourcePage ui;

  public:
    ImportTrainingTextSelectSourcePage(QWidget* parent);
    ~ImportTrainingTextSelectSourcePage();
    int nextId() const;
};
#endif
