//
// Created by Ryan Taber on 3/3/16.
//

#ifndef VC_BOOST_STATIC_LIBS
#define BOOST_TEST_DYN_LINK
#endif
#define BOOST_TEST_MODULE abf

#include <boost/test/unit_test.hpp>
#include "vc_defines.h"
#include "vc_datatypes.h"
#include "shapes.h"
#include "abf.h"
#include "parsingHelpers.h"


/***************************************************************************************
 *                                                                                     *
 *  abfTest.cpp - tests the functionality of /v-c/texturing/abf.cpp                    *
 *  The ultimate goal of this file is the following:                                   *
 *                                                                                     *
 *    Confirm that the class produces UV coordinates that match expected output.       *
 *                                                                                     *
 *  This file is broken up into a test fixture which initializes the objects           *
 *  used in each of the test cases.                                                    *
 *                                                                                     *
 *   1. PlaneABFUVTest                                                                 *
 *   2. PlaneABFLSCMOnlyUVTest                                                         *
 *   3. ArchABFUVTest                                                                  *
 *   4. ArchABFLSCMOnlyUVTest                                                          *
 *                                                                                     *
 * Input:                                                                              *
 *     No required inputs for this sample test. All objects needed for the test cases  *
 *     are constructed and destroyed by the fixtures. Note, we're only testing the     *
 *     non-enclosed shapes here. Sphere, Cone and Cube have been omitted. Pregenerated *
 *     test files were generated by vc_abfExample.                                     *
 *                                                                                     *
 * Test-Specific Output:                                                               *
 *     Specific test output only given on failure of any tests. Otherwise, general     *
 *     number of testing errors is output.                                             *
 *                                                                                     *
 * *************************************************************************************/

const double MINIMUM_VALUE = 0.00001;
const double TOLERANCE     = 0.0001;

/*
 *
 *    FIXTURES
 *
 */

struct CreatePlaneABFUVFixture{

    CreatePlaneABFUVFixture(){

        std::cerr << "Creating Plane UV map using ABF..." << std::endl;

        //Get ITK Mesh
        _in_PlaneITKMesh = _Plane.itkMesh();

        //Create uvMap from mesh
        volcart::texturing::abf abf(_in_PlaneITKMesh);
        abf.compute();
        _out_PlaneITKMesh = abf.getMesh();

        // Load pre-generated output from file
        volcart::testing::ParsingHelpers::parseObjFile("abf_Plane.obj", _SavedPlanePoints, _SavedPlaneCells);

    }

    ~CreatePlaneABFUVFixture(){std::cerr << "Destroying Plane ABF UV map..." << std::endl;}

    //declare Plane mesh and width and height
    volcart::shapes::Plane _Plane;
    VC_MeshType::Pointer _in_PlaneITKMesh;
    VC_MeshType::Pointer _out_PlaneITKMesh;

    std::vector<VC_Vertex> _SavedPlanePoints;
    std::vector<VC_Cell>   _SavedPlaneCells;
};

struct CreatePlaneABFLSCMOnlyUVFixture{

    CreatePlaneABFLSCMOnlyUVFixture(){

        std::cerr << "Creating Plane UV map using ABF (LSCM only)..." << std::endl;

        //Get ITK Mesh
        _in_PlaneITKMesh = _Plane.itkMesh();

        //Create uvMap from mesh
        volcart::texturing::abf abf(_in_PlaneITKMesh);
        abf.setUseABF(false);
        abf.compute();
        _out_PlaneITKMesh = abf.getMesh();

        // Load pre-generated output from file
        volcart::testing::ParsingHelpers::parseObjFile("abf_Plane_LSCMOnly.obj", _SavedPlanePoints, _SavedPlaneCells);

    }

    ~CreatePlaneABFLSCMOnlyUVFixture(){std::cerr << "Destroying Plane ABF (LSCM only) UV map..." << std::endl;}

    //declare Plane mesh and width and height
    volcart::shapes::Plane _Plane;
    VC_MeshType::Pointer _in_PlaneITKMesh;
    VC_MeshType::Pointer _out_PlaneITKMesh;

    std::vector<VC_Vertex> _SavedPlanePoints;
    std::vector<VC_Cell>   _SavedPlaneCells;
};

struct CreateArchABFUVFixture{

    CreateArchABFUVFixture(){

        std::cerr << "Creating Arch UV map using ABF..." << std::endl;

        //get ITK Mesh
        _in_ArchITKMesh = _Arch.itkMesh();

        //Create uvMap from mesh
        volcart::texturing::abf abf(_in_ArchITKMesh);
        abf.compute();
        _out_ArchITKMesh = abf.getMesh();

        // Load pre-generated output from file
        volcart::testing::ParsingHelpers::parseObjFile("abf_Arch.obj", _SavedArchPoints, _SavedArchCells);
    }

    ~CreateArchABFUVFixture(){std::cerr << "Destroying Arch ABF UV map..." << std::endl;}

    //declare Arch mesh
    volcart::shapes::Arch _Arch;
    VC_MeshType::Pointer _in_ArchITKMesh;
    VC_MeshType::Pointer _out_ArchITKMesh;

    std::vector<VC_Vertex> _SavedArchPoints;
    std::vector<VC_Cell>   _SavedArchCells;
};

struct CreateArchABFLSCMOnlyUVFixture{

    CreateArchABFLSCMOnlyUVFixture(){

        std::cerr << "Creating Arch UV map using ABF (LSCM only)..." << std::endl;

        //get ITK Mesh
        _in_ArchITKMesh = _Arch.itkMesh();

        //Create uvMap from mesh
        volcart::texturing::abf abf(_in_ArchITKMesh);
        abf.setUseABF(false);
        abf.compute();
        _out_ArchITKMesh = abf.getMesh();

        // Load pre-generated output from file
        volcart::testing::ParsingHelpers::parseObjFile("abf_Arch_LSCMOnly.obj", _SavedArchPoints, _SavedArchCells);
    }

    ~CreateArchABFLSCMOnlyUVFixture(){std::cerr << "Destroying Arch ABF (LSCM only) UV map..." << std::endl;}

    //declare Arch mesh
    volcart::shapes::Arch _Arch;
    VC_MeshType::Pointer _in_ArchITKMesh;
    VC_MeshType::Pointer _out_ArchITKMesh;

    std::vector<VC_Vertex> _SavedArchPoints;
    std::vector<VC_Cell>   _SavedArchCells;
};

/*
 *
 *    TEST CASES
 *
 */

BOOST_FIXTURE_TEST_CASE(PlaneABFUVTest, CreatePlaneABFUVFixture){

    //check size of uvMap and number of points in mesh
    BOOST_CHECK_EQUAL(_out_PlaneITKMesh->GetNumberOfPoints(), _in_PlaneITKMesh->GetNumberOfPoints());
    BOOST_CHECK_EQUAL(_out_PlaneITKMesh->GetNumberOfPoints(), _SavedPlanePoints.size());

    //check uvmap against original mesh input pointIDs
    double value_test, value_truth;
    for (size_t point = 0; point < _SavedPlanePoints.size(); ++point){

        value_test  = _out_PlaneITKMesh->GetPoint(point)[0];
        value_truth = _SavedPlanePoints[point].x;
        if( (std::abs(value_test) > MINIMUM_VALUE) && (std::abs(value_truth) > MINIMUM_VALUE) )
            BOOST_CHECK_CLOSE_FRACTION( value_test, value_truth, TOLERANCE);

        value_test  = _out_PlaneITKMesh->GetPoint(point)[1];
        value_truth = _SavedPlanePoints[point].y;
        if( (std::abs(value_test) > MINIMUM_VALUE) && (std::abs(value_truth) > MINIMUM_VALUE) )
            BOOST_CHECK_CLOSE_FRACTION( value_test, value_truth, TOLERANCE);

        value_test  = _out_PlaneITKMesh->GetPoint(point)[2];
        value_truth = _SavedPlanePoints[point].z;
        if( (std::abs(value_test) > MINIMUM_VALUE) && (std::abs(value_truth) > MINIMUM_VALUE) )
            BOOST_CHECK_CLOSE_FRACTION( value_test, value_truth, TOLERANCE);
    }

}

BOOST_FIXTURE_TEST_CASE(PlaneABFLSCMOnlyUVTest, CreatePlaneABFLSCMOnlyUVFixture){

    //check size of uvMap and number of points in mesh
    BOOST_CHECK_EQUAL(_out_PlaneITKMesh->GetNumberOfPoints(), _in_PlaneITKMesh->GetNumberOfPoints());
    BOOST_CHECK_EQUAL(_out_PlaneITKMesh->GetNumberOfPoints(), _SavedPlanePoints.size());

    //check uvmap against original mesh input pointIDs
    double value_test, value_truth;
    for (size_t point = 0; point < _SavedPlanePoints.size(); ++point){

        value_test  = _out_PlaneITKMesh->GetPoint(point)[0];
        value_truth = _SavedPlanePoints[point].x;
        if( (std::abs(value_test) > MINIMUM_VALUE) && (std::abs(value_truth) > MINIMUM_VALUE) )
            BOOST_CHECK_CLOSE_FRACTION( value_test, value_truth, TOLERANCE);

        value_test  = _out_PlaneITKMesh->GetPoint(point)[1];
        value_truth = _SavedPlanePoints[point].y;
        if( (std::abs(value_test) > MINIMUM_VALUE) && (std::abs(value_truth) > MINIMUM_VALUE) )
            BOOST_CHECK_CLOSE_FRACTION( value_test, value_truth, TOLERANCE);

        value_test  = _out_PlaneITKMesh->GetPoint(point)[2];
        value_truth = _SavedPlanePoints[point].z;
        if( (std::abs(value_test) > MINIMUM_VALUE) && (std::abs(value_truth) > MINIMUM_VALUE) )
            BOOST_CHECK_CLOSE_FRACTION( value_test, value_truth, TOLERANCE);
    }

}

BOOST_FIXTURE_TEST_CASE(ArchABFUVTest, CreateArchABFUVFixture){

    //check size of uvMap and number of points in mesh
    BOOST_CHECK_EQUAL(_out_ArchITKMesh->GetNumberOfPoints(), _in_ArchITKMesh->GetNumberOfPoints());
    BOOST_CHECK_EQUAL(_out_ArchITKMesh->GetNumberOfPoints(), _SavedArchPoints.size());

    //check uvmap against original mesh input pointIDs
    double value_test, value_truth;
    for (size_t point = 0; point < _SavedArchPoints.size(); ++point){

        value_test  = _out_ArchITKMesh->GetPoint(point)[0];
        value_truth = _SavedArchPoints[point].x;
        if( (std::abs(value_test) > MINIMUM_VALUE) && (std::abs(value_truth) > MINIMUM_VALUE) )
            BOOST_CHECK_CLOSE_FRACTION( value_test, value_truth, TOLERANCE);

        value_test  = _out_ArchITKMesh->GetPoint(point)[1];
        value_truth = _SavedArchPoints[point].y;
        if( (std::abs(value_test) > MINIMUM_VALUE) && (std::abs(value_truth) > MINIMUM_VALUE) )
            BOOST_CHECK_CLOSE_FRACTION( value_test, value_truth, TOLERANCE);

        value_test  = _out_ArchITKMesh->GetPoint(point)[2];
        value_truth = _SavedArchPoints[point].z;
        if( (std::abs(value_test) > MINIMUM_VALUE) && (std::abs(value_truth) > MINIMUM_VALUE) )
            BOOST_CHECK_CLOSE_FRACTION( value_test, value_truth, TOLERANCE);
    }

}

BOOST_FIXTURE_TEST_CASE(ArchABFLSCMOnlyUVTest, CreateArchABFLSCMOnlyUVFixture){

    //check size of uvMap and number of points in mesh
    BOOST_CHECK_EQUAL(_out_ArchITKMesh->GetNumberOfPoints(), _in_ArchITKMesh->GetNumberOfPoints());
    BOOST_CHECK_EQUAL(_out_ArchITKMesh->GetNumberOfPoints(), _SavedArchPoints.size());

    //check uvmap against original mesh input pointIDs
    double value_test, value_truth;
    for (size_t point = 0; point < _SavedArchPoints.size(); ++point){

        value_test  = _out_ArchITKMesh->GetPoint(point)[0];
        value_truth = _SavedArchPoints[point].x;
        if( (std::abs(value_test) > MINIMUM_VALUE) && (std::abs(value_truth) > MINIMUM_VALUE) )
            BOOST_CHECK_CLOSE_FRACTION( value_test, value_truth, TOLERANCE);

        value_test  = _out_ArchITKMesh->GetPoint(point)[1];
        value_truth = _SavedArchPoints[point].y;
        if( (std::abs(value_test) > MINIMUM_VALUE) && (std::abs(value_truth) > MINIMUM_VALUE) )
            BOOST_CHECK_CLOSE_FRACTION( value_test, value_truth, TOLERANCE);

        value_test  = _out_ArchITKMesh->GetPoint(point)[2];
        value_truth = _SavedArchPoints[point].z;
        if( (std::abs(value_test) > MINIMUM_VALUE) && (std::abs(value_truth) > MINIMUM_VALUE) )
            BOOST_CHECK_CLOSE_FRACTION( value_test, value_truth, TOLERANCE);
    }

}