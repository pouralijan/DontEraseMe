//
// Created by hassan on 3/27/18.
//

#include "MainMenu.h"

USING_NS_CC;
Scene *MainMenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenuLayer::create();
    scene->addChild(layer);
    return scene;
}
bool MainMenuLayer::init() {
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto l = Label::createWithTTF("Play", "fonts/Marker Felt.ttf", 24);
    auto menu_item0 = MenuItemLabel::create(l, CC_CALLBACK_1(MainMenuLayer::playCallBack, this));
    auto *menu = Menu::create(menu_item0, nullptr);
    menu->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    this->addChild(menu);

    return true;

}


void MainMenuLayer::playCallBack(Ref *pSender)
{

}
