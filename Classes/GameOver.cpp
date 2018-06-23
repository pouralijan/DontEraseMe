//
// Created by hassan on 3/27/18.
//

#include "GameOver.h"
#include "MainMenu.h"
#include "Game.h"

USING_NS_CC;

Scene * GameOverScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOverLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameOverLayer::init() {
    if(!Layer::init())
        return false;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

//    Sprite *backgroud = Sprite::create("gameover.png");
//    backgroud->setPosition(SonarCocosHelper::UI::GetScreenCenter());
//    backgroud->setContentSize(Size(visibleSize.width * 80 / 100, visibleSize.width * 80 / 100));
//    addChild(backgroud, 9999);
//
//    Sprite *retry_item_normal = Sprite::create("back_normal.png");
//    Sprite *retry_item_selected = Sprite::create("back_touched.png");
//    retry_item_normal->setContentSize(Size(backgroud->getContentSize().width * 20 /100, backgroud->getContentSize().width * 20 /100));
//    retry_item_selected->setContentSize(Size(backgroud->getContentSize().width * 20 /100, backgroud->getContentSize().width * 20 /100));
//
//    MenuItemSprite *retry_item = MenuItemSprite::create(retry_item_normal, retry_item_selected,CC_CALLBACK_1(GUI::retry, this));
//    retry_item->setPosition(Vec2(-backgroud->getContentSize().width / 6, -backgroud->getContentSize().height / 4));
//
//    Sprite *home_item_normal = Sprite::create("cancel_normal.png");
//    Sprite *home_item_selected = Sprite::create("cancel_touched.png");
//    home_item_normal->setContentSize(Size(backgroud->getContentSize().width * 20 /100, backgroud->getContentSize().width * 20 /100));
//    home_item_selected->setContentSize(Size(backgroud->getContentSize().width * 20 /100, backgroud->getContentSize().width * 20 /100));
//
//
//    UserDefault *userDefault = UserDefault::getInstance();
//
//    auto highScore = userDefault->getIntegerForKey("HIGHSCORE", 0);
//
//    if(Game::getInstancd()->getScore() > highScore)
//    {
//        highScore = Game::getInstancd()->getScore();
//        userDefault->setIntegerForKey("HIGHSCORE", highScore);
//        userDefault->flush();
//    }
//
//    auto scoreLabel = Label::createWithTTF(StringUtils::toString("Current Score: " + StringUtils::toString(Game::getInstancd()->getScore())), "fonts/Marker Felt.ttf", 24);
//    scoreLabel->setPosition(SonarCocosHelper::UI::GetScreenCenter());
//    scoreLabel->setColor(Color3B::BLUE);
//    layer->addChild(scoreLabel, 9999);
//
//    auto highScoreLabel = Label::createWithTTF(StringUtils::toString("High Score: " + StringUtils::toString(highScore)), "fonts/Marker Felt.ttf", 24);
//    highScoreLabel->setPosition(SonarCocosHelper::UI::GetScreenCenter());
//    highScoreLabel->setColor(Color3B::BLUE);
//    layer->addChild(highScoreLabel, 9999);
//
//    MenuItemSprite *home = MenuItemSprite::create(home_item_normal, home_item_selected, CC_CALLBACK_1(GUI::go_to_home, this));
//    home->setPosition(Vec2(backgroud->getContentSize().width / 6, -backgroud->getContentSize().height / 4));
//
//
//
//    Menu *menu = Menu::create(home, retry_item, NULL);
//    menu->setPosition(SonarCocosHelper::UI::GetScreenCenter());
//
//    layer->addChild(menu, 999);


    Game::getInstancd()->reset();

    return true;
}

void GameOverLayer::backToMainMenu(Ref *pSender)
{
    auto mainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFlipX::create(1,mainMenuScene));
}
