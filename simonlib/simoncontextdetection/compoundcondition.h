/*
 *   Copyright (C) 2011 Adam Nash <adam.t.nash@gmail.com>
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

#ifndef COMPOUNDCONDITION_H
#define COMPOUNDCONDITION_H

/** \file compoundcondition.h
 * \brief The file containing the CompoundCondition baseclass header.
 */

#include <QAbstractItemModel>
#include "condition.h"

/**
 *	@class CompoundCondition
 *	@brief The CompoundCondition class provides a container for Condition objects.  It monitors the collective state of the Conditions
 *
 *	Every scenario has a CompoundCondition which holds and monitors the Condition objects that are required to
 *      activate the Scenario.  Signals are sent to the CompoundCondition when the Condition objects change, and
 *      if this change changes the state of the CompoundCondition, the CompoundCondition sends a signal
 *      to its scenario.
 *
 *      A CompoundCondition without any Condition objects will always be satisfied.  Therefore, Scenarios without
 *      any Condition objects (this is the default) will never be automatically deactivated.
 *
 *      CompoundCondition objects have a proxy model that provides simple compatibility with view objects such
 *      as KListView.  See CompoundConditionModel and ContextViewPrivate for more details.
 *
 *	\sa Condition, Scenario, CompoundConditionModel, ContextViewPrivate
 *
 *	@version 0.1
 *	@date 7.7.2011
 *	@author Adam Nash
 */

class SIMONCONTEXTDETECTION_EXPORT CompoundCondition : public QAbstractItemModel
{
    Q_OBJECT
    
public:
    /**
     * \brief Constructor
     */
    explicit CompoundCondition(QObject *parent = 0);
    CompoundCondition (const CompoundCondition& other);
    CompoundCondition& operator=(const CompoundCondition& other);
    
    static QDomElement createEmpty(QDomDocument *doc);
    
    /**
     * \brief The current satisfaction of the CompoundCondition
     *
     * \return If the CompoundCondition is satisfied: True
     * \return Otherwise: False
     */
    bool isSatisfied() {return m_satisfied;}

    /**
     * \brief Serializes the CompoundCondition
     *
     * This function serializes the CompoundCondition which mainly consists of serializing
     * all of its component Condition objects.  It uses the QDomDocument \var doc.
     *
     * \return A QDomElement specification of the CompoundCondition
     */
    QDomElement serialize(QDomDocument *doc);

    /**
     * \brief Creates a new CompoundCondition from a QDomElement specification
     *
     * This function creates a new instance of a CompoundCondition object,
     * gives it properties as specified by the QDomElement \var elem, and does
     * an initial evaluation of the CompoundCondition.
     *
     * \return If \var elem is valid: A CompoundCondition derived from the QDomElement
     * \return Otherwise: A NULL pointer
     * \sa deSerialize(), evaluateConditions()
     */
    static CompoundCondition* createInstance(const QDomElement &elem);

    /**
     * \brief Adds a Condition to the CompoundCondition
     *
     * Adds the Condition \var condition to the CompoundCondition
     *
     * \return If the Condition was successfully added: True
     * \return Otherwise: False
     */
    bool addCondition(Condition* condition);

    /**
     * \brief Removes a Condition from the CompoundCondition
     *
     * Removes the Condition \var condition from the CompoundCondition
     *
     * \return If the Condition was successfully removed: True
     * \return Otherwise: False
     */
    bool removeCondition(Condition* condition);

    /**
     * \brief Returns a QList of pointers to the Condition objects of which the CompoundCondition is composed
     *
     * \return A QList of pointers to the Condition objects of which the CompoundCondition is composed
     */
    QList<Condition*> getConditions() {return m_conditions;}

private:
    ~CompoundCondition();

    /**
     * \brief DeSerializes the CompoundCondition from a QDomElement specification
     *
     * DeSerializes the CompoundCondition from the QDomElement specification \var elem.
     *
     * \return If the CompoundCondition was successfully deSerialized: True
     * \return Otherwise: False
     */
    bool deSerialize(const QDomElement &elem);

    /**
     * \brief The boolean value that indicates whether or not the CompoundCondition is satisfied
     *
     */
    bool m_satisfied;

    /**
     * \brief The QList of pointers to the Condition objects of which the CompoundCondition is composed
     *
     */
    QList<Condition*> m_conditions;

signals:
    /**
     * \brief Emitted when the satisfaction of the CompoundCondition is being reevaluated
     *
     */
    void conditionBeingEvaluated();

    /**
     * \brief Emitted when the satisfaction of the CompoundCondition changes
     *
     */
    void conditionChanged(bool);

    /**
     * \brief Emitted when a Condition is added to or removed from the CompoundCondition
     *
     */
    void modified();

protected:
    /**
     *
     * \return The index of the item in the model with the given \var row, \var column, and \var parent.
     */
    QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const;

    /**
     *
     * \return The item flags for the given \var index
     */
    Qt::ItemFlags flags(const QModelIndex &index) const;

    /**
     *
     * \return The data for the given \var role in the header with the specified \var orientation.
     */
    QVariant headerData(int, Qt::Orientation orientation,
      int role = Qt::DisplayRole) const;

    /**
     *
     * \return The index of the parent of the item with the given \var index
     */
    QModelIndex parent(const QModelIndex &index) const;

    /**
     *
     * \return The number of rows under the given \var parent.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    /**
     *
     * \return The data stored under the given \var role for the item referred to by \var index.
     */
    virtual QVariant data(const QModelIndex &index, int role) const;

    /**
     *
     * \return The number of columns under the given \var parent.
     */
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

public slots:
    /**
     * \brief Executed when the Condition objects of the CompoundCondition must be reevaluated
     *
     */
    void evaluateConditions();
    
private slots:
    /**
     * \brief Emits the appropriate signal to notify of changing data in the model
     */
    void updateConditionDisplay();
};

#endif // COMPOUNDCONDITION_H
