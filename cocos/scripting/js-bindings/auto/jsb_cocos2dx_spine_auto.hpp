#pragma once
#include "base/ccConfig.h"

#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"

extern se::Object* __jsb_spine_SkeletonRenderer_proto;
extern se::Class* __jsb_spine_SkeletonRenderer_class;

bool js_register_spine_SkeletonRenderer(se::Object* obj);
bool register_all_cocos2dx_spine(se::Object* obj);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_setTimeScale);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_getDebugSlotsEnabled);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_setAttachment);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_setBonesToSetupPose);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_initWithData);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_setDebugSlotsEnabled);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_initWithJsonFile);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_setSlotsToSetupPose);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_initWithBinaryFile);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_setToSetupPose);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_setDebugMeshesEnabled);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_isTwoColorTint);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_getBlendFunc);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_initialize);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_setDebugBonesEnabled);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_getDebugBonesEnabled);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_getTimeScale);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_setTwoColorTint);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_getDebugMeshesEnabled);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_setBlendFunc);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_setVertexEffect);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_setSkin);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_updateWorldTransform);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_getSkeleton);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_drawDebug);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_createWithFile);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonRenderer_SkeletonRenderer);

extern se::Object* __jsb_spine_SkeletonAnimation_proto;
extern se::Class* __jsb_spine_SkeletonAnimation_class;

bool js_register_spine_SkeletonAnimation(se::Object* obj);
bool register_all_cocos2dx_spine(se::Object* obj);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_setTrackCompleteListener);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_findAnimation);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_setCompleteListener);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_setMix);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_setTrackStartListener);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_addEmptyAnimation);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_setDisposeListener);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_setTrackInterruptListener);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_onTrackEntryEvent);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_setEndListener);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_getState);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_setTrackDisposeListener);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_setEventListener);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_setEmptyAnimation);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_setTrackEventListener);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_clearTrack);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_setInterruptListener);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_onAnimationStateEvent);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_setEmptyAnimations);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_clearTracks);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_setTrackEndListener);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_setStartListener);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_createWithBinaryFile);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_create);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_createWithJsonFile);
SE_DECLARE_FUNC(js_cocos2dx_spine_SkeletonAnimation_SkeletonAnimation);

