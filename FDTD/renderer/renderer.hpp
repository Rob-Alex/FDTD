//
//  renderer.h
//  plasma_sim
//
//  Created by Robbie Alexander on 08/11/2023.
//

#ifndef renderer_hpp
#define renderer_hpp

#include "config.hpp"
#include "mesh.hpp"

class Renderer
{
private:
    MTL::Device* _pDevice;
    MTL::CommandQueue* _pCmdQ;
    MTL::RenderPipelineState* _pPSO;    //render pipeline
    MTL::Buffer* _pVertPosBuffer;       //stores all vertex positions
    MTL::Buffer* _pVertColBuffer;
public:
    Renderer( MTL::Device* pDevice );
    ~Renderer();
    void buildMeshes();
    void buildShaders();
//    void buildBuffers();                //unsure if I need this 
    void draw( MTK::View* pView );
    Mesh quadMesh;
    float dt; //timestep
};




#endif /* renderer_hpp */
