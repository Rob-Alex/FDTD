//
//  view_delegate.h
//  plasma_sim
//
//  Created by Robbie Alexander on 08/11/2023.
//

#ifndef view_delegate_h
#define view_delegate_h
#include "config.hpp"
#include "renderer.hpp"

class MTKViewDelegate : public MTK::ViewDelegate
{
private:
    Renderer* _pRenderer;
public:
    MTKViewDelegate( MTL::Device* pDevice );
    virtual ~MTKViewDelegate() override;
    virtual void drawInMTKView( MTK::View* pView ) override;
};

#endif /* view_delegate_h */
