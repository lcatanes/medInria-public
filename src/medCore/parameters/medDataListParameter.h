/*=========================================================================

 medInria

 Copyright (c) INRIA 2013. All rights reserved.
 See LICENSE.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#pragma once

#include <medAbstractParameter.h>
#include <QIcon>

#include <medCoreExport.h>

class QComboBox;
class QWidget;
class QStringList;

class medDataIndex;

class medDataListParameterPrivate;
class MEDCORE_EXPORT medDataListParameter: public medAbstractParameter
{
    Q_OBJECT

public:
    medDataListParameter(QString name = "Unknown data list parameter", QObject* parent = 0);
    virtual ~medDataListParameter();

    void setValues(QList<medDataIndex> values);
    void clear();

    QList <medDataIndex> &values() const;

    virtual QWidget* getWidget();

signals:
    void valuesChanged (QList <medDataIndex>);
    
private:
    medDataListParameterPrivate* d;
};
