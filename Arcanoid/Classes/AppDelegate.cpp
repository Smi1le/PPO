#include "AppDelegate.h"
#include "GameLayer.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(360, 240);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
	return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
   /* auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect("Arcanoid", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
		glview = GLViewImpl::create("Arcanoid");
#endif
		director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(960, 540, ResolutionPolicy::SHOW_ALL);

    director->setDisplayStats(false);
		
    director->setAnimationInterval(1.0 / 60);

	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
	Size frameSize = glview->getFrameSize();

	if (frameSize.height > mediumResolutionSize.height)
	{
		director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height, largeResolutionSize.width / designResolutionSize.width));
	}
	else if (frameSize.height > smallResolutionSize.height)
	{
		director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height, mediumResolutionSize.width / designResolutionSize.width));
	}
	else
	{
		director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height, smallResolutionSize.width / designResolutionSize.width));
	}*/

	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview)
	{
		glview = GLViewImpl::createWithRect("Arcanoid", Rect(0, 0, 960, 540));
		glview->setFrameSize(960, 540);
		director->setOpenGLView(glview);
	}

	Size screenSize = glview->getFrameSize();
	Size designSize(960, 540);

	glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::NO_BORDER);
	director->setDisplayStats(false);
	director->setAnimationInterval(1.f / 60.f);

    FileUtils::getInstance()->addSearchPath("res");

    auto scene = MenuScene::createScene();

    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
