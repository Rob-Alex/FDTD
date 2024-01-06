//
//  mesh.hpp
//  FDTD
//
//  Created by Robbie Alexander on 06/01/2024.
//

#ifndef mesh_hpp
#define mesh_hpp

#include "config.hpp"

struct Mesh {
    MTL::Buffer* pVertexBuffer, *pIndexBuffer;
};

namespace Msh {
    Mesh buildQuad(MTL::Device* pDevice);
}

#endif /* mesh_hpp */
