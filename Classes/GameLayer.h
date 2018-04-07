//
// Created by hassan on 2/16/18.
//

#ifndef PROJ_ANDROID_STUDIO_GAMELAYER_H
#define PROJ_ANDROID_STUDIO_GAMELAYER_H


#include "cocos2d.h"
#include "SpriteShape.h"
#include "ui/CocosGUI.h"

class GameLayer : public cocos2d::Layer
{
public:
//    static cocos2d::Scene* createScene();

    virtual bool init();
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    CREATE_FUNC(GameLayer);
    void SetPhysicsWorld(cocos2d::PhysicsWorld *world){
        sceneWorld = world;
    };

    bool onContactBegin(cocos2d::PhysicsContact &contact);
    void update(float) override;
    std::string randomShape();


private:
    cocos2d::Point centerPos;
    cocos2d::ui::Slider *slider;
    cocos2d::PhysicsWorld *sceneWorld;
    void SpawnShape(float delayTime);
    void ShapeChaleng(float delayTime);
    SpriteShape *currentShape;
    SpriteShape *nextShape;
    int shapeSize;
    int currentShapeSize;
    int nextShapeSize;
    cocos2d::Sprite *sprite;
    cocos2d::ProgressTimer* lifeBar;
    cocos2d::ProgressTimer* progressTimer;


    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char *format, int count);
    void contact(cocos2d::PhysicsBody *physicsBody);

};


#endif //PROJ_ANDROID_STUDIO_GAMELAYER_H
