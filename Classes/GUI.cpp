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

GUI::GUI(Layer *)
{

}
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

void GUI::show_login(cocos2d::Layer *layer) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto centerPos = Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    Sprite *background = Sprite::create("gameover.png");
    background->setContentSize(Size(visibleSize.width * 75 / 100, visibleSize.width * 75 /100));
    background->setPosition(Point(-background->getContentSize().width, visibleSize.height - background->getContentSize().height/2));
    layer->addChild(background, 10000);

    MoveTo *action = MoveTo::create(1, Point(background->getContentSize().width / 2 - (background->getContentSize().width * 10 / 100), background->getPositionY()));

    background->runAction(action);

    ui::TextField *user_name = ui::TextField::create("User Name", "fonts/CHLORINR.TTF", 25);
    user_name->setPosition(Point(centerPos.x, centerPos.y + 100));
    user_name->setTextColor(Color4B::BLUE);
    user_name->setPlaceHolder("User Name");
    user_name->setPlaceHolderColor(Color3B::RED);
    user_name->setMaxLength(20);
    user_name->setParent(background);


    layer->addChild(user_name);

}

bool LogingLayer::init() {
    if(!Layer::init())
        return false;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto centerPos = Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    Sprite *background = Sprite::create("gameover.png");
    background->setContentSize(Size(visibleSize.width * 75 / 100, visibleSize.width * 75 /100));
    background->setPosition(Point(-background->getContentSize().width, visibleSize.height - background->getContentSize().height/2));
    this->addChild(background, 10000);

    MoveTo *action = MoveTo::create(1, Point(background->getContentSize().width / 2 - (background->getContentSize().width * 10 / 100), background->getPositionY()));

    background->runAction(action);

    ui::TextField *user_name = ui::TextField::create("User Name", "fonts/CHLORINR.TTF", 25);
    user_name->setPosition(Point(centerPos.x, centerPos.y + 100));
    user_name->setTextColor(Color4B::BLUE);
    user_name->setPlaceHolder("User Name");
    user_name->setPlaceHolderColor(Color3B::RED);
    user_name->setMaxLength(20);

    this->addChild(user_name);
    return true;
}
