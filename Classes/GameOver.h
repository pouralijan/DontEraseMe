//
// Created by hassan on 3/27/18.
//

#pragma one
#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene * createScene();
    CREATE_FUNC(GameOverScene);
};

class GameOverLayer : public cocos2d::Layer
{
public:
    bool init() override;
    CREATE_FUNC(GameOverLayer);
private:
    void backToMainMenu(Ref *pSender);
};


