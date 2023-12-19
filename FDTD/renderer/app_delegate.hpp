//
//  app_delegate.h
//  plasma_sim
//
//  Created by Robbie Alexander on 08/11/2023.
//

#ifndef app_delegate_hpp
#define app_delegate_hpp
#include "config.hpp"
#include "view_delegate.hpp"

class AppDelegate : public NS::ApplicationDelegate
{
private:
    NS::Window* _pWindow;
    MTK::View* _pMtkView;
    MTL::Device* _pDevice;
    MTKViewDelegate* _pViewDelegate = nullptr;
public:
    ~AppDelegate();
    NS::Menu* createMenuBar();
    virtual void applicationWillFinishLaunching( NS::Notification* pNotification ) override;
    virtual void applicationDidFinishLaunching( NS::Notification* pNotification ) override;
    virtual bool applicationShouldTerminateAfterLastWindowClosed( NS::Application* pSender ) override;
};


#endif /* app_delegate_h */
