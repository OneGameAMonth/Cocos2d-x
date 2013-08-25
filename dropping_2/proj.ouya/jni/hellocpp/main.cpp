#include "AppDelegate.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#include "GameScene.h"

#include "cocos2d.h"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

extern "C"
{
	jint JNI_OnLoad(JavaVM *vm, void *reserved)
	{
		JniHelper::setJavaVM(vm);

		return JNI_VERSION_1_4;
	}

	void Java_org_cocos2dx_hellocpp_HelloCpp_keyPressed(JNIEnv*  env, jobject thiz, jint player, jint keyCode)
	{
		CCDirector *pDirector = CCDirector::sharedDirector();
		if(pDirector != NULL)
		{
			CCScene *scene = pDirector->getRunningScene();
			if(scene != NULL)
			{
				Game* layer = (Game*)scene->getChildByTag(1001);
				if(layer != NULL)
				{
					layer->keyControllerPressed(player, keyCode);
				}
			}
		}
	}

	void Java_org_cocos2dx_hellocpp_HelloCpp_keyReleased(JNIEnv*  env, jobject thiz, jint player, jint keyCode)
	{
		CCDirector *pDirector = CCDirector::sharedDirector();
		if(pDirector != NULL)
		{
			CCScene *scene = pDirector->getRunningScene();
			if(scene != NULL)
			{
				Game* layer = (Game*)scene->getChildByTag(1001);
				if(layer != NULL)
				{
					layer->keyControllerReleased(player, keyCode);
				}
				else
				{
					CCDirector *pDirector = CCDirector::sharedDirector();
					CCScene *scene_ = Game::scene();
					pDirector->replaceScene(scene_);
				}
			}
		}
	}

	void Java_org_cocos2dx_hellocpp_HelloCpp_controllerMotion(JNIEnv*  env, jobject thiz, jint player, jfloat LS_X, jfloat LS_Y, jfloat RS_X, jfloat RS_Y)
	{
		CCDirector *pDirector = CCDirector::sharedDirector();
		if(pDirector != NULL)
		{
			CCScene *scene = pDirector->getRunningScene();
			if(scene != NULL)
			{
				Game* layer = (Game*)scene->getChildByTag(1001);
				if(layer != NULL)
				{
					layer->controllerMotion(player, LS_X, LS_Y, RS_X, RS_Y);
				}
			}
		}
	}

	void Java_org_cocos2dx_hellocpp_HelloCpp_onResumeJNI(JNIEnv*  env, jobject thiz)
	{
		cocos2d::CCDirector::sharedDirector()->startAnimation();
	}

	void Java_org_cocos2dx_hellocpp_HelloCpp_onPauseJNI(JNIEnv*  env, jobject thiz)
	{
		cocos2d::CCDirector::sharedDirector()->stopAnimation();
	}

	void Java_org_cocos2dx_hellocpp_HelloCpp_onDestroyJNI(JNIEnv*  env, jobject thiz)
	{
		cocos2d::CCDirector::sharedDirector()->end();
	}

	void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
	{
		if (!CCDirector::sharedDirector()->getOpenGLView())
		{
			CCEGLView *view = CCEGLView::sharedOpenGLView();
			view->setFrameSize(w, h);

			AppDelegate *pAppDelegate = new AppDelegate();
			CCApplication::sharedApplication()->run();
		}
	}
}
