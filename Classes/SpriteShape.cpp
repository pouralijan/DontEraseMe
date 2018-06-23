#include <cocos/audio/include/SimpleAudioEngine.h>
#include <cmath>

#include "SpriteShape.h"
#include "Game.h"

USING_NS_CC;


SpriteShape::SpriteShape()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = CC_CALLBACK_2(SpriteShape::onTouchBegan, this);
	//touchListener->onTouchMoved = CC_CALLBACK_2(SpriteShape::onTouchMoved, this);
//	touchListener->onTouchEnded = CC_CALLBACK_2(SpriteShape::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

SpriteShape::~SpriteShape()
{
}


void SpriteShape::setRemovable(bool removable)
{
	this->removable = removable;
}

SpriteShape * SpriteShape::create(const std::string& filename)
{
	SpriteShape * pSprite = new SpriteShape();
	
	if (pSprite->initWithFile(filename))
	{
		pSprite->autorelease();
		
		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return nullptr;
}

SpriteShape * SpriteShape::create()
{

	SpriteShape * pSprite = new SpriteShape();

	if (pSprite->init())
	{
		pSprite->autorelease();

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return nullptr;
}

bool SpriteShape::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	auto target = static_cast<SpriteShape*>(event->getCurrentTarget());

	Point locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size targetContentSize = target->getContentSize();
	Rect rect = Rect(0, 0, targetContentSize.width, targetContentSize.height);

	if (rect.containsPoint(locationInNode))
	{
        if (target->getResourceName() != Game::getInstancd()->getCurrentShape())
        {

			if (target->isRemovable())
			{
                CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/dry-eraser-swipe.mp3");
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/dry-eraser-swipe.mp3");

                target->setRemovable(false);
                target->stopAllActions();
                target->removeFromParent();

                Game::getInstancd()->setScore(Game::getInstancd()->getScore() + 1);
                auto particle = ParticleExplosion::create();
                particle->setPosition(touch->getLocation().x, touch->getLocation().y);
                particle->setDuration(.1);
                particle->setLife(.1);
                particle->setEmissionRate(500);
                particle->setAngle(-90);
                particle->setAngleVar(45);
                particle->setSpeed(300);
                particle->setPosVar(Vec2(0,0));
                particle->setGravity(Vec2(0, -500));
//                CCLOG("%s", StringUtils::toString(target->getResourceName().c_str()));
//                particle->setTexture(Director::getInstance()->getTextureCache()->addImage(StringUtils::toString(target->getResourceName().c_str())));
                Game::getInstancd()->getLayer()->addChild(particle);


			}

			const int time_maximume = 10;
			const int time_minimume = 1;
			const float time_decrease_rate = 40;
			
			Game::getInstancd()->setMoveSpeed(time_minimume + (time_maximume - time_minimume) /( exp(Game::getInstancd()->getScore() / time_decrease_rate)));

			return true;
        }
		else
		{
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/dart-hitting.mp3");
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/dart-hitting.mp3");
			Game::getInstancd()->isMistake();
		}
	}
	return false;
}

void SpriteShape::setBody() {
    auto spriteBody = PhysicsBody::createBox(this->getContentSize(),
                                             PhysicsMaterial(0, 0, 0));
    spriteBody->setDynamic(false);
    spriteBody->setCollisionBitmask(1);
    spriteBody->setContactTestBitmask(true);
    this->setPhysicsBody(spriteBody);

}

void SpriteShape::setAction() {
    auto shapeMoveAction = MoveBy::create(Game::getInstancd()->getMoveSpeed(), Point(0, -visibleSize.height));
    auto easeBackIn = EaseSineOut::create(shapeMoveAction);
    auto remove = RemoveSelf::create();
    auto sequence = Sequence::create(easeBackIn, remove, nullptr);
    this->runAction(sequence);
}

const std::string &SpriteShape::getResourceName() const {
    return resourceName;
}

void SpriteShape::setResourceName(const std::string &resourceName) {
    SpriteShape::resourceName = resourceName;
}

