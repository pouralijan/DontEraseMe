//
// Created by hassan on 3/27/18.
//

#include "MainMenu.h"
#include "GameScene.h"


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
    auto centerPos = Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    // Add background
    auto background = Sprite::create("background.png");
    background->setPosition(centerPos);
    float scale = MAX(visibleSize.width / background->getContentSize().width,
        visibleSize.height / background->getContentSize().height);
    background->setScale(scale);
    this->addChild(background, -1);


    Point lifePosition = Point(visibleSize.width / 2 + origin.x,visibleSize.height + origin.y - (visibleSize.height * 25 / 100));
    Sprite *border = Sprite::create("loading_boarder.png");
    border->setAnchorPoint(Vec2(0.5, 0.5));
    border->setPosition(lifePosition);
    border->setContentSize(Size(visibleSize.width * 75 /100, border->getContentSize().height));
    this->addChild(border, 5);

    Sprite *background1 = Sprite::create("loading_content.png");
    background1->setContentSize(Size(visibleSize.width * 75 / 100, background1->getContentSize().height));
    background1->setAnchorPoint(Vec2(0.0, 0.0));
    background1->setPosition(Vec2(0.0, 0.0));

    auto lifeBar = ProgressTimer::create(background1);
    lifeBar->setType(ProgressTimer::Type::BAR);
    lifeBar->setAnchorPoint(Vec2(0.0, 0.0));
    lifeBar->setPosition(Vec2(0.0, 0.0));
    lifeBar->setBarChangeRate(Vec2(1, 0));
    lifeBar->setMidpoint(Vec2(0.0, 0.0));
    lifeBar->setPercentage(0);
    lifeBar->setContentSize(Size(visibleSize.width * 75 / 100, lifeBar->getContentSize().height));
    border->addChild(lifeBar, 10);

    auto plusAction0 = cocos2d::ProgressFromTo::create(5, 0, 100);
    auto a = EaseSineIn::create(plusAction0);
    lifeBar->runAction(a);


    auto menu_item0 = MenuItemImage::create("Play.png", "Play_Touched.png", CC_CALLBACK_1(MainMenuLayer::playCallBack, this));
    //menu_item0->setContentSize(Size(visibleSize.width * 10 / 100, visibleSize.width * 10 / 100));
    menu_item0->setScale(.5);
    auto *menu = Menu::create(menu_item0, nullptr);
    menu->setContentSize(Size(visibleSize.width * 10 / 100, visibleSize.width * 10 / 100));
    menu->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    this->addChild(menu);

    return true;

}

#include "GameOver.h"
void MainMenuLayer::playCallBack(Ref *pSender)
{
    auto gameScene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionPageTurn::create(1, gameScene, true));
}
