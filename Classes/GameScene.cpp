#include "GameScene.h"
#include "GameLayer.h"
#include "Game.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = GameScene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    scene->getPhysicsWorld()->setGravity(Vect(0,0));

    auto layer = GameLayer::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());
    Game::getInstancd()->setLayer(layer);
    scene->addChild(layer);
    return scene;

}
