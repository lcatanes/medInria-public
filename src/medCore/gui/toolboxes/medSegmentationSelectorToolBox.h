/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#pragma once

#include <medToolBox.h>
#include <medCoreExport.h>
#include <medProcessSelectorToolBox.h>

class medViewEventFilter;
class medSegmentationAbstractToolBox;

class medSegmentationSelectorToolBoxPrivate;
class MEDCORE_EXPORT medSegmentationSelectorToolBox : public medProcessSelectorToolBox
{
    Q_OBJECT

public:
     medSegmentationSelectorToolBox(QWidget *parent = 0, QString title="Segmentation");
    ~medSegmentationSelectorToolBox();

signals:
     void installEventFilterRequest(medViewEventFilter *filter);
     void inputChanged();

public slots:

private:
    medSegmentationSelectorToolBoxPrivate *d;
};


