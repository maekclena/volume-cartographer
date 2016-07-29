//
// Created by Hannah Hatch on 7/26/16.
//

#ifndef VC_CALCULATENORMALS_H
#define VC_CALCULATENORMALS_H

#include<iostream>
#include <opencv2/opencv.hpp>

#include "vc_defines.h"
#include "vc_datatypes.h"
#include "deepCopy.h"

namespace volcart{
    namespace meshing{
        class calculateNormals{
        public:
            // Construction //
            calculateNormals();
            calculateNormals( VC_MeshType::Pointer mesh) ;

            // Input/Output //
            void setMesh(VC_MeshType::Pointer mesh);
            VC_MeshType::Pointer getMesh();

            // Processing //
            void compute();

        private:
            void _computeNormals();
            void _assignToMesh();

            VC_MeshType::Pointer  _input;
            VC_MeshType::Pointer _output;

            std::vector<cv::Vec3d> _vertex_normals; // convenience vector to store calculated normals by p_id
        };
    }//meshing
}//volcart
#endif //VC_CALCULATENORMALS_H
