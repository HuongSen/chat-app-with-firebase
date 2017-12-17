#include "LoginScene.h"
#include "SimpleAudioEngine.h"
#include "cocostudio\CocoStudio.h"

USING_NS_CC;

Scene* LoginScene::createScene()
{
    return LoginScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in LoginSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LoginScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	rootNode = CSLoader::createNodeWithVisibleSize("LoginScene.csb");
	this->addChild(rootNode);

	auto username = rootNode->getChildByName("username");
	txt_username = ui::TextField::create();
	txt_username->setPlaceHolder("username");
	txt_username->setPlaceHolderColor(Color4B::GRAY);
	txt_username->setContentSize(Size(username->getContentSize().width*0.8, username->getContentSize().height*0.8));
	txt_username->setPosition(Vec2(username->getContentSize().width*0.5, username->getContentSize().height*0.35));
	txt_username->setTextColor(Color4B::BLACK);
	username->addChild(txt_username);

	auto password = rootNode->getChildByName("password");
	txt_password = ui::TextField::create();
	txt_password->setPlaceHolder("password");
	txt_password->setPasswordEnabled(true);
	txt_password->setPlaceHolderColor(Color4B::GRAY);
	txt_password->setContentSize(Size(password->getContentSize().width*0.8, password->getContentSize().height*0.8));
	txt_password->setPosition(Vec2(password->getContentSize().width*0.5, password->getContentSize().height*0.35));
	txt_password->setTextColor(Color4B::BLACK);
	password->addChild(txt_password);

	btn_gg_login = static_cast<ui::Button*>(rootNode->getChildByName("btn_gg_login"));
	btn_fb_login = static_cast<ui::Button*>(rootNode->getChildByName("btn_fb_login"));
	btn_register = static_cast<ui::Button*>(rootNode->getChildByName("btn_create"));
	btn_register->addClickEventListener(CC_CALLBACK_0(LoginScene::RegisterAccount, this));
	btn_getpass = static_cast<ui::Button*>(rootNode->getChildByName("btn_forgot"));
    return true;
}


void LoginScene::DisableAllButton()
{
	btn_gg_login->setEnabled(false);
	btn_fb_login->setEnabled(false);
	btn_getpass->setEnabled(false);
	btn_fb_login->setEnabled(false);
}

void LoginScene::EnableAllButton()
{
	btn_gg_login->setEnabled(true);
	btn_fb_login->setEnabled(true);
	btn_getpass->setEnabled(true);
	btn_fb_login->setEnabled(true);
}


void LoginScene::RegisterAccount()
{
	DisableAllButton();
	auto nodeRegister = rootNode->getChildByName("node_register");
	nodeRegister->setVisible(true);

	auto username = nodeRegister->getChildByName("username");
	auto txt_username = ui::TextField::create();
	txt_username->setPlaceHolder("username");
	txt_username->setPlaceHolderColor(Color4B::GRAY);
	txt_username->setContentSize(Size(username->getContentSize().width*0.8, username->getContentSize().height*0.8));
	txt_username->setPosition(Vec2(username->getContentSize().width*0.5, username->getContentSize().height*0.35));
	txt_username->setTextColor(Color4B::BLACK);
	username->addChild(txt_username);

	auto password = nodeRegister->getChildByName("password");
	auto txt_password = ui::TextField::create();
	txt_password->setPlaceHolder("password");
	txt_password->setPasswordEnabled(true);
	txt_password->setPlaceHolderColor(Color4B::GRAY);
	txt_password->setContentSize(Size(password->getContentSize().width*0.8, password->getContentSize().height*0.8));
	txt_password->setPosition(Vec2(password->getContentSize().width*0.5, password->getContentSize().height*0.35));
	txt_password->setTextColor(Color4B::BLACK);
	password->addChild(txt_password);

	auto confirm_password = nodeRegister->getChildByName("confirm_password");
	auto txt_confirm_password = ui::TextField::create();
	txt_confirm_password->setPlaceHolder("confirm password");
	txt_confirm_password->setPasswordEnabled(true);
	txt_confirm_password->setPlaceHolderColor(Color4B::GRAY);
	txt_confirm_password->setContentSize(Size(password->getContentSize().width*0.8, password->getContentSize().height*0.8));
	txt_confirm_password->setPosition(Vec2(password->getContentSize().width*0.5, password->getContentSize().height*0.35));
	txt_confirm_password->setTextColor(Color4B::BLACK);
	confirm_password->addChild(txt_confirm_password);

	auto email = nodeRegister->getChildByName("email");
	auto txt_email = ui::TextField::create();
	txt_email->setPlaceHolder("email");
	txt_email->setPasswordEnabled(true);
	txt_email->setPlaceHolderColor(Color4B::GRAY);
	txt_email->setContentSize(Size(password->getContentSize().width*0.8, password->getContentSize().height*0.8));
	txt_email->setPosition(Vec2(password->getContentSize().width*0.5, password->getContentSize().height*0.35));
	txt_email->setTextColor(Color4B::BLACK);
	email->addChild(txt_email);

	auto timeline = CSLoader::createTimeline("Register.csb");
	this->stopAllActions();
	this->runAction(timeline);
	timeline->play("show", false);

}


void LoginScene::GetPasswordAccount() {

}