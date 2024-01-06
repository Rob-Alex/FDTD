//
//  renderer.h
//  plasma_sim
//
//  Created by Robbie Alexander on 08/11/2023.
//

#ifndef renderer_hpp
#define renderer_hpp

#include "config.hpp"
#include <simd/simd.h>
#include <fstream>
#include <sstream>

class Renderer
{
private:
    MTL::Device* _pDevice;
    MTL::CommandQueue* _pCmdQ;
    MTL::RenderPipelineState* _pPSO;    //render pipeline
    MTL::Buffer* _pVertPosBuffer;       //stores all vertex positions
    MTL::Buffer* _pVertColBuffer;
    MTL::Buffer* _pIndexBuffer;         //index to draw each triangle
public:
    Renderer( MTL::Device* pDevice );
    ~Renderer();
    void buildShaders();
    void buildBuffers();
    void draw( MTK::View* pView );
    float dt; //timestep
};




#endif /* renderer_hpp */
