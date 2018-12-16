/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

//
//  js_module_register.cpp
//  cocos2d_js_bindings
//
//  Created by James Chen on 7/11/17.
//
//

#define USE_VIDEO 0
#define USE_WEBVIEW 0
#define USE_EDIT_BOX 0
#define USE_AUDIO 1
#define USE_SPINE 0
#define USE_DRAGON_BONES 0
#define USE_NET_WORK 0


#include "cocos/scripting/js-bindings/manual/jsb_module_register.hpp"
#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"

#include "cocos/scripting/js-bindings/auto/jsb_cocos2dx_auto.hpp"
#include "cocos/scripting/js-bindings/auto/jsb_cocos2dx_extension_auto.hpp"
#include "cocos/scripting/js-bindings/auto/jsb_cocos2dx_network_auto.hpp"

#include "cocos/scripting/js-bindings/manual/jsb_opengl_registration.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_cocos2dx_extension_manual.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_global.h"
#include "cocos/scripting/js-bindings/manual/jsb_node.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_cocos2dx_manual.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_conversions.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_xmlhttprequest.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_websocket.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_socketio.hpp"

#if USE_VIDEO
#include "cocos/scripting/js-bindings/auto/jsb_cocos2dx_experimental_video_auto.hpp"
#endif

#if USE_WEBVIEW
#include "cocos/scripting/js-bindings/auto/jsb_cocos2dx_experimental_webView_auto.hpp"
#endif

#if USE_VIDEO || USE_WEBVIEW || USE_EDIT_BOX
#include "cocos/scripting/js-bindings/auto/jsb_cocos2dx_ui_auto.hpp"
#endif

#if USE_CREATOR_PHYSICS
#include "cocos/scripting/js-bindings/auto/jsb_creator_physics_auto.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_creator_physics_manual.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_box2d_manual.hpp"
#include "cocos/scripting/js-bindings/auto/jsb_box2d_auto.hpp"
#endif

#if USE_CREATOR_CAMERA
#include "cocos/scripting/js-bindings/auto/jsb_creator_camera_auto.hpp"
#endif

#if USE_CREATOR_GRAPHICS
#include "cocos/scripting/js-bindings/auto/jsb_creator_graphics_auto.hpp"
#endif

#if USE_AUDIO
#include "cocos/scripting/js-bindings/auto/jsb_cocos2dx_audioengine_auto.hpp"
#endif

#if USE_DRAGON_BONES
#include "cocos/scripting/js-bindings/auto/jsb_cocos2dx_dragonbones_auto.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_dragonbones_manual.hpp"
#endif

#if USE_SPINE
#include "cocos/scripting/js-bindings/auto/jsb_cocos2dx_spine_auto.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_spine_manual.hpp"
#endif


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "cocos/scripting/js-bindings/manual/JavaScriptObjCBridge.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "cocos/scripting/js-bindings/manual/JavaScriptJavaBridge.h"
#endif

#include "cocos2d.h"

using namespace cocos2d;

static bool run_prepare_script(se::Object* global)
{
    jsb_run_script("script/jsb_prepare.js");
    return true;
}

static bool run_boot_script(se::Object* global)
{
    jsb_run_script("script/jsb_boot.js");
    return true;
}

bool jsb_register_all_modules()
{
    se::ScriptEngine* se = se::ScriptEngine::getInstance();

    se->addBeforeInitHook([](){
        JSBClassType::init();
    });

    se->addBeforeCleanupHook([se](){
        se->garbageCollect();
        PoolManager::getInstance()->getCurrentPool()->clear();
        se->garbageCollect();
        PoolManager::getInstance()->getCurrentPool()->clear();
    });

    se->addRegisterCallback(jsb_register_global_variables);

    se->addRegisterCallback(run_prepare_script);

    se->addRegisterCallback(register_all_cocos2dx);
    se->addRegisterCallback(jsb_register_Node_manual);
    se->addRegisterCallback(register_all_cocos2dx_manual);
    se->addRegisterCallback(JSB_register_opengl);

#if USE_AUDIO
    se->addRegisterCallback(register_all_cocos2dx_audioengine);
#endif

#if USE_VIDEO || USE_WEBVIEW || USE_EDIT_BOX
    se->addRegisterCallback(register_all_cocos2dx_ui);
    se->addRegisterCallback(register_ui_manual);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS) && !defined(CC_TARGET_OS_TVOS)
#if USE_VIDEO
    se->addRegisterCallback(register_all_cocos2dx_experimental_video);
#endif
    
#if USE_WEBVIEW
    se->addRegisterCallback(register_all_cocos2dx_experimental_webView);
#endif
#endif

#if USE_SPINE
    se->addRegisterCallback(register_all_cocos2dx_spine);
    se->addRegisterCallback(register_all_spine_manual);
#endif
    
#if USE_DRAGON_BONES
    se->addRegisterCallback(register_all_cocos2dx_dragonbones);
    se->addRegisterCallback(register_all_dragonbones_manual);
#endif

#if USE_CREATOR_PHYSICS
    se->addRegisterCallback(register_all_box2dclasses);
    se->addRegisterCallback(register_all_box2d_manual);
    
    se->addRegisterCallback(register_all_creator_physics);
    se->addRegisterCallback(register_all_creator_physics_manual);
#endif
    
#if USE_CREATOR_CAMERA
    se->addRegisterCallback(register_all_creator_camera);
#endif
    
#if USE_CREATOR_GRAPHICS
    se->addRegisterCallback(register_all_creator_graphics);
#endif

#if USE_NET_WORK
    se->addRegisterCallback(register_all_cocos2dx_network);
    se->addRegisterCallback(register_all_xmlhttprequest);
    se->addRegisterCallback(register_all_websocket);
    se->addRegisterCallback(register_all_socketio);

    se->addRegisterCallback(register_all_creator);
    se->addRegisterCallback(register_all_creator_manual);

    se->addRegisterCallback(register_all_cocos2dx_extension);
    se->addRegisterCallback(register_all_cocos2dx_extension_manual);
#endif
    

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    se->addRegisterCallback(register_javascript_objc_bridge);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    se->addRegisterCallback(register_javascript_java_bridge);
#endif

    // run_boot_script has to be at last.
    se->addRegisterCallback(run_boot_script);

    se->addAfterCleanupHook([](){
        PoolManager::getInstance()->getCurrentPool()->clear();
        JSBClassType::destroy();
    });
    return true;
}
