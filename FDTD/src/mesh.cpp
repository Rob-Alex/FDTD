//
//  mesh.cpp
//  FDTD
//
//  Created by Robbie Alexander on 06/01/2024.
//

#include "mesh.hpp"

Mesh Msh::buildQuad(MTL::Device* pDevice)
{
    Mesh mesh;
    
    Vertex vertices[4] = {
        {{ -1.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f} },
        {{  1.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f} },
        {{  1.0f,  1.0f, 0.0f}, {0.0f, 0.0f, 1.0f} },
        {{ -1.0f,  1.0f, 0.0f}, {0.0f, 1.0f, 0.0f} },
    };
    
    UInt32 indices[6] = {
        0, 1, 2, 2, 3, 0
    };
    
    //vertex buffer
    mesh.pVertexBuffer = pDevice->newBuffer(4 * sizeof(Vertex), MTL::ResourceStorageModeShared);
    memcpy(mesh.pVertexBuffer->contents(), vertices, 4 * sizeof(Vertex));
    
    //index buffer
    mesh.pIndexBuffer = pDevice->newBuffer(6 * sizeof(UInt32), MTL::ResourceStorageModeShared);
    memcpy(mesh.pIndexBuffer->contents(), indices, 6 * sizeof(UInt32));
    
    return mesh;
};
