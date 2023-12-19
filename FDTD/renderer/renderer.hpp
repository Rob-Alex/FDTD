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
    MTL::RenderPipelineState* _pPSO;
    MTL::Buffer* _pVertPosBuffer;
    MTL::Buffer* _pVertColBuffer;
public:
    Renderer( MTL::Device* pDevice );
    ~Renderer();
    void buildShaders();
    void buildBuffers();
    void draw( MTK::View* pView );
};




#endif /* renderer_hpp */
