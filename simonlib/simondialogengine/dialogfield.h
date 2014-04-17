/*
 *   Copyright (C) 2014 Benjamin Bowley-Bryant <benbb@utexas.edu>
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

#include <QString>
#include <QDomDocument>
#include <QDomElement>
#include <QSharedPointer>
#include <fcntl.h>
#include <kdebug.h>

//TODO:  Implement the parser class and have this use it to get/set the variable.
//TODO:  Split the DialogFieldValue and DialogFieldInfo classes into their own separate files.

template <class T>
class DialogField;
class DialogFieldBase;

class QDomElement;
class QDomDocument;

class DialogFieldTypeInfo
{
  public:
    typedef DialogFieldBase* (*deSerializeFunction)(const QDomElement& elem);
    typedef DialogFieldBase* (*createFunction)(const QString& name, const QString& value);

    const QString id_;
    const QString name_;
    const QString description_;

    const deSerializeFunction dsf;
    const createFunction cf;

    DialogFieldTypeInfo(const QString id, const QString name, const QString desc, const deSerializeFunction dfs_ptr,
			const createFunction cf_ptr) : id_(id), name_(name), description_(desc),
							dsf(dfs_ptr), cf(cf_ptr) { }
};

template <class T>
class DialogFieldValue
{
  private:
    const QSharedPointer<T> ptr;
    const bool isValidCast;
  public:
    DialogFieldValue<T>() : ptr(), isValidCast(false) { }
    DialogFieldValue<T>(const DialogFieldValue<T>& cpy) : ptr(cpy.ptr), isValidCast(cpy.isValidCast) { }
    explicit DialogFieldValue<T>(const QSharedPointer<T>& pointer) : ptr(pointer), isValidCast(true) { }

    T* data() { return this->ptr.data(); }

    bool isValid() { return this->isValidCast; }
};

class DialogFieldBase {
  protected:
    virtual const QString& getType() const = 0;
  public:
    DialogFieldBase() {}
    virtual ~DialogFieldBase() {}
    virtual QString toString() = 0;

    virtual bool deSerialize(const QDomElement& elem) = 0;
    virtual QDomElement serialize(QDomDocument * doc) = 0;

    template <class T>
    DialogFieldValue<T> getValue()
    {
      if(DialogField<T> * casted_this = dynamic_cast<DialogField<T>*>(this))
      {
	return casted_this->getVal();
      }
      else
      {
	kWarning() << "Get value cast failed!";
	return DialogFieldValue<T>();
      }
    }
};

template <class T>
class DialogField : public DialogFieldBase
{
  protected:
    typedef T VariableType;

    QString name;
    QSharedPointer<VariableType> value;

    DialogField<T>() : name(), value() { }
    DialogField<T>(const QString& n) : name(n), value() { }
    virtual const QString& getType() const = 0;

    //TODO: Overload this so QDomElement is an option as well.
    virtual QSharedPointer<VariableType> parseValue(const QString& value) = 0;
  private:
      class Parser {} parser;
  public:
      DialogField<T>(const QString& n, const VariableType& val) : name(n), value(new VariableType(val)) { }
      DialogFieldValue<T> getVal() const
      {
	return DialogFieldValue<T>(value);
      }

      QString getName() const
      {
	return name;
      }

      virtual QDomElement serialize(QDomDocument * doc)
      {
	if(!doc)
	{
	  kWarning() << "Doc submitted to serialize was null!";
	  return QDomElement();
	}

	QDomElement elem = doc->createElement("field");

	QDomElement name = doc->createElement("name");
	QDomElement value = doc->createElement("value");
	QDomElement type = doc->createElement("type");

	QDomText name_value = doc->createTextNode(this->name);
	name.appendChild(name_value);

	//TODO: Change this to allow different
	QDomText value_value = doc->createTextNode(this->toString());
	value.appendChild(value_value);

	QDomText type_value = doc->createTextNode(this->getType());
	type.appendChild(type_value);

	elem.appendChild(name);
	elem.appendChild(type);
	elem.appendChild(value);

	return elem;
      }

      virtual bool deSerialize(const QDomElement& elem)
      {
	//Assumption; elem is a "field" elem
	if(elem.isNull()) return false;
	if(elem.firstChildElement("type").text() != getType()) return false;

	this->name = elem.firstChildElement("name").text();
	this->value = this->parseValue(elem.firstChildElement("value").text());

	if(this->value.isNull())
	{
	  return false;
	}

	return true;
      }

      virtual QString toString() = 0;
};

//TODO: Separate this into its own file called "standarddialogfields.h"/"standarddialogfields.cpp"

class DialogIntegerField : public DialogField<int>
{
  protected:
    virtual const QString& getType() const { return DialogIntegerField::typeInfo.id_; }
    virtual QSharedPointer<VariableType> parseValue(const QString& value);

    DialogIntegerField() : DialogField< int >() { }
    DialogIntegerField(const QString& n) : DialogField< int >(n) { }
  public:
    static const DialogFieldTypeInfo typeInfo;
    static DialogFieldBase* deSerializeDialogIntegerField(const QDomElement& elem);
    static DialogFieldBase* createDialogIntegerField(const QString& name, const QString& value);

    DialogIntegerField(const QString& name, const VariableType& val) : DialogField<int>(name,val) { }

    virtual QString toString() { return QString::number(*getVal().data()); }
};
