//
// Created by hassan on 4/24/18.
//

#include <cocos/ui/UITextField.h>
#include "GUI.h"
#include "Game.h"
#include "MainMenu.h"
#include "cocos2d.h"
//#include "EditBox.h"

USING_NS_CC;


void GUI::show_game_over(cocos2d::Layer *layer)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto centerPos = Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    Sprite *backgroud = Sprite::create("gameover.png");
    backgroud->setPosition(centerPos);
    backgroud->setContentSize(Size(visibleSize.width * 80 / 100, visibleSize.width * 80 / 100));
    layer->addChild(backgroud, 99);

    Sprite *retry_item_normal = Sprite::create("back_normal.png");
    Sprite *retry_item_selected = Sprite::create("back_touched.png");
    retry_item_normal->setContentSize(Size(backgroud->getContentSize().width * 20 /100, backgroud->getContentSize().width * 20 /100));
    retry_item_selected->setContentSize(Size(backgroud->getContentSize().width * 20 /100, backgroud->getContentSize().width * 20 /100));

    MenuItemSprite *retry_item = MenuItemSprite::create(retry_item_normal, retry_item_selected,CC_CALLBACK_1(GUI::retry, this));
    retry_item->setPosition(Vec2(-backgroud->getContentSize().width / 6, -backgroud->getContentSize().height / 4));

    Sprite *home_item_normal = Sprite::create("cancel_normal.png");
    Sprite *home_item_selected = Sprite::create("cancel_touched.png");
    home_item_normal->setContentSize(Size(backgroud->getContentSize().width * 20 /100, backgroud->getContentSize().width * 20 /100));
    home_item_selected->setContentSize(Size(backgroud->getContentSize().width * 20 /100, backgroud->getContentSize().width * 20 /100));


    UserDefault *userDefault = UserDefault::getInstance();

    auto highScore = userDefault->getIntegerForKey("HIGHSCORE", 0);

    if(Game::getInstancd()->getScore() > highScore)
    {
        highScore = Game::getInstancd()->getScore();
        userDefault->setIntegerForKey("HIGHSCORE", highScore);
        userDefault->flush();
    }

    auto scoreLabel = Label::createWithTTF(StringUtils::toString("Current Score: " + StringUtils::toString(Game::getInstancd()->getScore())), "fonts/Marker Felt.ttf", 24);
    scoreLabel->setPosition(centerPos);
    scoreLabel->setColor(Color3B::BLUE);
    layer->addChild(scoreLabel, 9999);

    auto highScoreLabel = Label::createWithTTF(StringUtils::toString("High Score: " + StringUtils::toString(highScore)), "fonts/Marker Felt.ttf", 24);
    highScoreLabel->setPosition(centerPos.x, centerPos.y + 50);
    highScoreLabel->setColor(Color3B::BLUE);
    layer->addChild(highScoreLabel, 9999);

    MenuItemSprite *home = MenuItemSprite::create(home_item_normal, home_item_selected, CC_CALLBACK_1(GUI::go_to_home, this));
    home->setPosition(Vec2(backgroud->getContentSize().width / 6, -backgroud->getContentSize().height / 4));



    Menu *menu = Menu::create(home, retry_item, NULL);
    menu->setPosition(centerPos);

    layer->addChild(menu, 999);
    Game::getInstancd()->reset();
}

void GUI::retry(Ref *p_sender)
{

}

void GUI::go_to_home(Ref *p_sender)
{

    auto mainMenuScene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFlipX::create(1,mainMenuScene));
}

void GUI::pause_game(cocos2d::Ref *p_sender)
{
    if(GameState::PLAYING == *this->gameState)
    {
        *gameState = GameState::PAUSED;
        pause_background->runAction(FadeIn::create(.1));
        EaseBounceOut *menu_action_easing = EaseBounceOut::create(MoveTo::create(.1, Vec2(visibleSize.width/2, visibleSize.height/2)));
        pause_menu->runAction(menu_action_easing);
    }else if (GameState::PAUSED == *gameState)
    {
        *gameState = GameState::PLAYING;
        pause_background->runAction(FadeOut::create(.1));
        EaseBounceOut *menu_action_easing = EaseBounceOut::create(MoveTo::create(.1, Vec2(visibleSize.width/2, visibleSize.height/2 + visibleSize.height)));
        pause_menu->runAction(menu_action_easing);
    }

}

GUI::GUI(cocos2d::Layer *layer, GameState gameState) {
//    this->gameState = &gameState;
//    visibleSize = Director::getInstance()->getVisibleSize();
//    origin = Director::getInstance()->getVisibleOrigin();
//
//    MenuItemSprite *pauseItem = MenuItemSprite::create(Sprite::create("CloseNormal.png"), Sprite::create("CloseSelected.png"), Sprite::create("CloseNormal.png"), CC_CALLBACK_1(GUI::pause_game, this));
//
//    pauseItem->setPosition(Vec2(visibleSize.width - (pauseItem->getContentSize().width / 2) + origin.x, visibleSize.height - (pauseItem->getContentSize().height / 2) + origin.y));
//
//    Menu *menu_buttons = Menu::create(pauseItem, nullptr);
//
//    menu_buttons->setPosition(Vec2::ZERO);
//    layer->addChild(menu_buttons);
//
//    pause_background = Sprite::create("background.png");
//    pause_background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
//    pause_background->setOpacity(0);
//    layer->addChild(pause_background);
//
//
//    MenuItemImage *overlay_paused_menu_item = MenuItemImage::create("gameover.png", "gameover.png", "gameover.png",
//                                                                    nullptr);
//    MenuItemSprite *resume_item = MenuItemSprite::create(Sprite::create("CloseNormal.png"), Sprite::create("CloseSelected.png"), Sprite::create("CloseNormal.png"), CC_CALLBACK_1(GUI::pause_game, this));
//    resume_item->setPosition(Vec2(-overlay_paused_menu_item->getContentSize().width / 4, resume_item->getPositionY()));
//
//    MenuItemSprite *home_item = MenuItemSprite::create(Sprite::create("CloseNormal.png"), Sprite::create("CloseSelected.png"), Sprite::create("CloseNormal.png"), CC_CALLBACK_1(GUI::pause_game, this));
//    home_item->setPosition(Vec2(-overlay_paused_menu_item->getContentSize().width / 4, home_item->getPositionY()));
//
//    pause_menu = Menu::create(overlay_paused_menu_item, resume_item, home_item, nullptr);
//    pause_menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + visibleSize.height));
//
//    layer->addChild(pause_menu);
}

