#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"

class LoginScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    CREATE_FUNC(LoginScene);

protected:
	float m_scale;

	cocos2d::Node* rootNode;
	cocos2d::ui::TextField* txt_username;
	cocos2d::ui::TextField* txt_password;
	cocos2d::ui::Button* btn_gg_login;
	cocos2d::ui::Button* btn_fb_login;
	cocos2d::ui::Button* btn_register;
	cocos2d::ui::Button* btn_getpass;
	cocos2d::ui::Button* btn_login;
	
	void RegisterAccount();
	void GetPasswordAccount();
	void EnableAllButton();
	void DisableAllButton();

};

#endif // __LOGIN_SCENE_H__
