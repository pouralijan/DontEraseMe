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
    if (!Layer::init())
    {
        return false;
    }
   
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto currentScoreLable = Label::createWithTTF("Play", "fonts/Marker Felt.ttf", 24);

    UserDefault *userDefault = UserDefault::getInstance();

    auto highScore = userDefault->getIntegerForKey("HIGHSCORE", 0);

    if(Game::getInstancd()->getScore() > highScore)
    {
        highScore = Game::getInstancd()->getScore();
        userDefault->setIntegerForKey("HIGHSCORE", highScore);
        userDefault->flush();
    }

    auto scoreLabel = Label::createWithTTF(StringUtils::toString("Current Score: " + StringUtils::toString(Game::getInstancd()->getScore())), "fonts/Marker Felt.ttf", 24);
    scoreLabel->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 50);
    this->addChild(scoreLabel);

    auto highScoreLabel = Label::createWithTTF(StringUtils::toString("High Score: " + StringUtils::toString(highScore)), "fonts/Marker Felt.ttf", 24);
    highScoreLabel->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100);
    this->addChild(highScoreLabel);

    auto backLable = Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 24);
    auto menu_item0 = MenuItemLabel::create(backLable, CC_CALLBACK_1(GameOverLayer::backToMainMenu, this));

    auto *menu = Menu::create(menu_item0, nullptr);
    menu->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 4 + origin.y);
    this->addChild(menu);

    Game::getInstancd()->reset();

    return true;
}

void GameOverLayer::backToMainMenu(Ref *pSender)
{
    auto mainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFlipX::create(1,mainMenuScene));
}
