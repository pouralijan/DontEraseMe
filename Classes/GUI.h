//
// Created by hassan on 4/24/18.
//

#pragma once

#include "cocos2d.h"
#include "Game.h"

class GUI {
public:
    GUI(cocos2d::Layer *layer, GameState gameState);

    void show_game_over(cocos2d::Layer *layer);

private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    GameState *gameState;
    void retry(cocos2d::Ref *p_sender);
    void go_to_home(cocos2d::Ref *p_sender);
    void pause_game(cocos2d::Ref *p_sender);

    cocos2d::Menu *pause_menu;
    cocos2d::Sprite *pause_background;
};