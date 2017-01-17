//----------------------------------------------------------------------------------------------------------------------------------------
// MyThread.h file for MyThread Class , (Implements QThread)
// Purpose: Run the Texture Functionality behind the scenes so that the GUI
// operates without interference
// Developer: Michael Royal - mgro224@g.uky.edu
// October 12, 2015 - Spring Semester 2016
// Last Updated 09/26/2016 by: Michael Royal

// Copyright 2015 (Brent Seales: Volume Cartography Research)
// University of Kentucky VisCenter
//----------------------------------------------------------------------------------------------------------------------------------------

#pragma once

#include <QLabel>
#include <QString>
#include <QThread>

#include <vtkCleanPolyData.h>

#include "core/util/MeshMath.h"
#include "meshing/ACVD.h"
#include "texturing/AngleBasedFlattening.h"
#include "texturing/CompositeTextureV2.h"

#include "GlobalValues.h"

class MyThread : public QThread
{

public:
    explicit MyThread(GlobalValues* globals);
    void run();

private:
    GlobalValues* _globals;

    static const uint16_t CLEANER_MIN_REQ_POINTS = 100;
};
