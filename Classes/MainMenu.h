//
// Created by hassan on 3/27/18.
//
#pragma once

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene *createScene();
    CREATE_FUNC(MainMenuScene);
};

class MainMenuLayer : public cocos2d::Layer
{
public:
    bool init() override;
    CREATE_FUNC(MainMenuLayer);

private:
    void playCallBack(cocos2d::Ref *pSender);
};
