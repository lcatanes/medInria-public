/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include <medAlgorithmInitializer.h>

#include <medManualSegProcess.h>
#include <medAlgorithmPaintToolbox.h>
#include <medToolBoxFactory.h>

#include <dtkCore/dtkAbstractProcessFactory.h>

medAlgorithmInitializer::medAlgorithmInitializer()
{
}

medAlgorithmInitializer::~medAlgorithmInitializer()
{
}

bool medAlgorithmInitializer::initialize()
{
    bool ret = initializeProcesses();
    ret &= initializeWidgets();
    return ret;
}

bool medAlgorithmInitializer::initializeProcesses()
{
    if(!medManualSegProcess::registered())
    {
        dtkWarn() << "Unable to register PaintSegmentation type";
    }

    if ( !medManualSegProcess::registered() )
    {
        dtkWarn() << "Unable to register PaintSegmentation toolbox";
    }

    return true;
}

bool medAlgorithmInitializer::initializeWidgets()
{
    bool ret (true);
    medToolBoxFactory * factory = medToolBoxFactory::instance();

    ret &= factory->registerToolBox<medAlgorithmPaintToolbox>();

    return ret;
}
