//
// Created by hassan on 4/24/18.
//

#pragma once

#include "cocos2d.h"

class GUI {
public:
    GUI(cocos2d::Layer *layer);

    void show_game_over(cocos2d::Layer *layer);
    void show_login(cocos2d::Layer *layer);

private:
    void retry(cocos2d::Ref *p_sender);
    void go_to_home(cocos2d::Ref *p_sender);

};

class LogingLayer : public cocos2d::Layer
{
public:
    bool init() override;
    CREATE_FUNC(LogingLayer);
};