//
/// /// // Created by hassan on 2/16/18.
//

//#include <dirent.h>
#include <iostream>
#include <cocos/ui/UISlider.h>
#include "GameLayer.h"
//#include "SpriteShape.h"
#include "Game.h"
#include "GameOver.h"

USING_NS_CC;

bool GameLayer::init() {

    if (!Layer::init())
        return false;


    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    centerPos = Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

    shapeSize = int(visibleSize.width * 15 / 100);
    currentShapeSize = int(visibleSize.width * 10 / 100);
    nextShapeSize = int(visibleSize.width * 7 / 100);

    // Add background
    auto background = Sprite::create("background.png");
    background->setPosition(centerPos);
    float scale = MAX(visibleSize.width / background->getContentSize().width,
                      visibleSize.height / background->getContentSize().height);
    background->setScale(scale);
    this->addChild(background, -1);

    // Add headers
    auto header = Sprite::create("header.png");
    header->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y);
    header->setContentSize(
            Size(visibleSize.width + origin.x, (visibleSize.height + origin.y) * 25 / 100));
    float scaleX = visibleSize.width / header->getContentSize().width;
    header->setScaleX(scaleX);
    this->addChild(header, 1);

    // Add score label
    auto scoreLabel = Label::createWithTTF(StringUtils::toString(Game::getInstancd()->getScore()),
                                           "fonts/Marker Felt.ttf", 24);
    scoreLabel->setPosition(origin.x + scoreLabel->getContentSize().width +
                            (visibleSize.width + origin.x + scoreLabel->getContentSize().width) *
                            4 / 100,
                            visibleSize.height + origin.y - scoreLabel->getContentSize().height);
    scoreLabel->setColor(Color3B::WHITE);
    this->addChild(scoreLabel, 1000);
    Game::getInstancd()->setScoreLable(scoreLabel);

    currentShape = SpriteShape::create(Game::getInstancd()->getCurrentShape().c_str());
    currentShape->setResourceName(Game::getInstancd()->getCurrentShape());
    currentShape->setRemovable(false);
    currentShape->setContentSize(Size(currentShapeSize, currentShapeSize));
    currentShape->setPosition(Point(visibleSize.width / 4 + origin.x,
                                    visibleSize.height + origin.y -
                                    currentShape->getContentSize().height / 2 -
                                    (visibleSize.height * 2 / 100)));
    this->addChild(currentShape, 2);


    nextShape = SpriteShape::create(Game::getInstancd()->getNextShape().c_str());
    nextShape->setResourceName(Game::getInstancd()->getNextShape());
    nextShape->setRemovable(false);
    nextShape->setContentSize(Size(nextShapeSize, nextShapeSize));

    Point nextShapePoint = Point(
            visibleSize.width / 4 + origin.x + currentShape->getContentSize().width,
            visibleSize.height + origin.y - currentShape->getContentSize().height / 2 -
            (visibleSize.height * 2 / 100));

    progressTimer = ProgressTimer::create(nextShape);
    progressTimer->setType(ProgressTimer::Type::BAR);
    progressTimer->setPosition(nextShapePoint);
    progressTimer->setBarChangeRate(Vec2(0, 1));
    progressTimer->setMidpoint(Vec2(0.0, 0.0));
    progressTimer->setPercentage(0);
    this->addChild(progressTimer, 3);
    progressTimer->runAction(
            ProgressFromTo::create(Game::getInstancd()->getChangeShapeTime(), .0f, 100.0f));


    
    Sprite *lifebar_boarder = Sprite::create("lifebar_boarder.png");
    lifebar_boarder->setAnchorPoint(Vec2(0.5, 0.5));
    Size lifebarSize = Size(visibleSize.width / 2 - currentShapeSize - nextShapeSize, nextShapeSize);
    lifebar_boarder->setContentSize(lifebarSize);
    Point lifePosition = Point(
        ((visibleSize.width + origin.x) - (lifebar_boarder->getContentSize().width / 2) - ((visibleSize.width + origin.x) * 2 / 100)),
        ((visibleSize.height + origin.y) - (lifebar_boarder->getContentSize().height / 2) - ((visibleSize.height + origin.y) * 2 / 100)));

    lifebar_boarder->setPosition(lifePosition);
    this->addChild(lifebar_boarder, 5);

    Sprite *lifebar_content = Sprite::create("lifebar_content.png");
    lifebar_content->setContentSize(lifebarSize);
    lifebar_content->setAnchorPoint(Vec2(0.0, 0.0));
    lifebar_content->setPosition(Vec2(0.0, 0.0));

    lifeBar = ProgressTimer::create(lifebar_content);
    lifeBar->setType(ProgressTimer::Type::BAR);
    lifeBar->setAnchorPoint(Vec2(0.0, 0.0));
    lifeBar->setPosition(Vec2(0.0, 0.0));
    lifeBar->setBarChangeRate(Vec2(1, 0));
    lifeBar->setMidpoint(Vec2(0.0, 0.0));
    lifeBar->setPercentage(100);
    lifeBar->setContentSize(lifebarSize);

    Game::getInstancd()->setLifeBar(lifeBar);
    lifebar_boarder->addChild(lifeBar, 10);

    auto laser = Node::create();
    laser->setPosition(visibleSize.width / 2, visibleSize.height * 2 / 100);

    auto bodyLaser = PhysicsBody::createBox(Size(visibleSize.width, 1),
                                            PhysicsMaterial(0, 0, 0));
    bodyLaser->setDynamic(false);
    bodyLaser->setCollisionBitmask(0);
    bodyLaser->setContactTestBitmask(true);
    laser->setPhysicsBody(bodyLaser);
    addChild(laser);


    gui = new GUI(this, Game::getInstancd()->getGameState());
    Game::getInstancd()->setGameState(GameState::PLAYING);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    this->schedule(schedule_selector(GameLayer::SpawnShape),
                   Game::getInstancd()->getSpwanShapeTime());
    this->schedule(schedule_selector(GameLayer::ShapeChaleng),
                   Game::getInstancd()->getChangeShapeTime());
    this->scheduleUpdate();


    return true;
}

void GameLayer::SpawnShape(float delayTime) {

    int randomShape = RandomHelper::random_int(0, 3);
    const std::string randomString = StringUtils::toString(randomShape);
    const std::string shapeFileName = "shape/Shape-" + randomString + ".png";
    auto sprite = SpriteShape::create(shapeFileName);

    sprite->setResourceName(shapeFileName);

    sprite->setContentSize(Size(shapeSize, shapeSize));
    sprite->setAction();
    sprite->setBody();

    int start = int(sprite->getContentSize().width / 4);
    int end = int(visibleSize.width - sprite->getContentSize().width / 4);
    float x_posision = RandomHelper::random_int(start, end);

    sprite->setPosition(Point(x_posision, visibleSize.height));
    this->addChild(sprite, 0);
}

void GameLayer::ShapeChaleng(float delayTime) {
    Vector<Node*> children = _children;
    for (auto &child:children) {
        if (SpriteShape *spriteShape = dynamic_cast<SpriteShape *>(child)) {
            if (Game::getInstancd()->getCurrentShape() == spriteShape->getResourceName()) {

                if (spriteShape->isRemovable()) {
                    spriteShape->stopAllActions();
                    auto remove = RemoveSelf::create();
                    auto particle = ParticleExplosion::create();
                    particle->setPosition(spriteShape->getPosition());
                    particle->setTexture(Director::getInstance()->getTextureCache()->addImage(
                            spriteShape->getResourceName()));
                    spriteShape->runAction(remove);

                    particle->setDuration(.1);
                    particle->setLife(.1);
                    particle->setEmissionRate(500);
                    particle->setAngle(-90);
                    particle->setAngleVar(45);
                    particle->setSpeed(300);
                    particle->setPosVar(Vec2(0, 0));
                    particle->setGravity(Vec2(0, -500));
                    addChild(particle);
                }

            }
        }
    }

    Game::getInstancd()->changeShape();
    currentShape->setTexture(Game::getInstancd()->getCurrentShape());
    currentShape->setContentSize(Size(currentShapeSize, currentShapeSize));

    nextShape->setTexture(Game::getInstancd()->getNextShape());
    nextShape->setContentSize(Size(nextShapeSize, nextShapeSize));
    progressTimer->runAction(
            ProgressFromTo::create(Game::getInstancd()->getChangeShapeTime(), .0f, 100.0f));

}

bool GameLayer::onContactBegin(cocos2d::PhysicsContact &contact) {
    PhysicsBody *shapeA = contact.getShapeA()->getBody();
    PhysicsBody *shapeB = contact.getShapeB()->getBody();

    if ((0 == shapeA->getCollisionBitmask() && 1 == shapeB->getCollisionBitmask()) ||
        (1 == shapeA->getCollisionBitmask() && 0 == shapeB->getCollisionBitmask())
            ) {
        GameLayer::contact(shapeA);
        GameLayer::contact(shapeB);
    }
    return false;
}

void GameLayer::update(float delta) {
    if (Game::getInstancd()->getGameState() == GameState::GAMEOVER) {
        this->stopAllActions();
        this->unscheduleAllCallbacks();
        gui->show_game_over(this);
//        auto gameOverScene = GameOverScene::createScene();
//        Director::getInstance()->replaceScene(TransitionZoomFlipY::create(1.0f, gameOverScene));
    }

}

std::string GameLayer::randomShape() {
    return std::string();
}

cocos2d::Vector<cocos2d::SpriteFrame *> GameLayer::getAnimation(const char *format, int count) {
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<cocos2d::SpriteFrame *> animFrames;
    char str[100];
    for (int i = 1; i <= count; i++) {
        sprintf(str, format, i);
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
}

void GameLayer::contact(cocos2d::PhysicsBody *physicsBody) {
    if (dynamic_cast<SpriteShape *>(physicsBody->getNode())) {
        SpriteShape *shapeSprite = dynamic_cast<SpriteShape *>(physicsBody->getNode());
        if (shapeSprite->getResourceName() != Game::getInstancd()->getCurrentShape()) {
            Game::getInstancd()->isMistake();

        }
    }
}


