//
// Created by hassan on 2/18/18.
//

#pragma once

#include "cocos2d.h"
class SpriteShape : public cocos2d::Sprite
{
public:

    SpriteShape();
	~SpriteShape();

	static SpriteShape * create(const std::string& filename);
	static SpriteShape * create();
	void setRemovable(bool removable);
	bool isRemovable() { return removable; }
    void setBody();
    void setAction();
    const std::string &getResourceName() const;
    void setResourceName(const std::string &resourceName);
    bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
    std::string resourceName;
	bool removable = true;
};