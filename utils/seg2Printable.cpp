//
// Created by Seth Parker on 9/15/15.
//

#include <stdio.h>

#include "vc_defines.h"
#include "volumepkg.h"
#include "io/ply2itk.h"
#include "io/objWriter.h"
#include "scaleMesh.h"

int main (int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " volpkg seg-id" << std::endl;
        return EXIT_FAILURE;
    }

    // Load our sources from the volpkg
    VolumePkg volpkg = VolumePkg(argv[1]);
    volpkg.setActiveSegmentation(argv[2]);

    std::string outputName = argv[2];
    outputName += "_mm.obj";

    // Get our mesh
    VC_MeshType::Pointer mesh = VC_MeshType::New();
    VC_MeshType::Pointer scaled = VC_MeshType::New();
    int width = -1, height = -1;
    if (!volcart::io::ply2itkmesh(volpkg.getMeshPath(), mesh, width, height)) {
        std::cerr << "ERROR: Could not read ply file" << std::endl;
        return EXIT_FAILURE;
    }

    // Perform the scale
    double scale_factor = volpkg.getVoxelSize() * 0.001; // pixel->um->mm unit conversion
    volcart::meshing::scaleMesh(mesh, scaled, scale_factor);

    // Write the mesh
    std::cout << "Writing scaled mesh..." << std::endl;
    volcart::io::objWriter objWriter(outputName, scaled);
    objWriter.write();
}