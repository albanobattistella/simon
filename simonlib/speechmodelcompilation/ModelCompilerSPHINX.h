/*
 *   Copyright (C) 2012 Vladislav Sitalo <root@stvad.org>
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


#ifndef MODELCOMPILERSPHINX_H
#define MODELCOMPILERSPHINX_H

#include "modelcompiler.h"
#include "simonmodelcompilationmanagement_export.h"

class MODELCOMPILATIONMANAGEMENT_EXPORT ModelCompilerSPHINX: public ModelCompiler
{
public:
    bool startCompilation(ModelCompiler::CompilationType compilationType, const QString& modelDestination,
                                      const QString& baseModelPath, const QHash<QString, QString>& args);

    //TODO: Implement
    bool hasBuildLog() const;
    QString getGraphicBuildLog() const;
    QString getBuildLog() const;

    void abort();

    QString information(bool condensed=false) const;

};

#endif // MODELCOMPILERSPHINX_H
