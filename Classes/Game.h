//
// Created by hassan on 2/18/18.
//

#pragma once
#include <cocos2d.h>
//#include "BacktorySDK.h"

enum class GameState {
    NEW,
    PLAYING,
    PAUSED,
    STARTED,
    GAMEOVER,
    END,
};

class Game {
public:
    static Game *getInstancd();
    int getScore() const;
    void setScore(int score);
    void setScoreLable(cocos2d::Label *scoreLable);
    float getMoveSpeed() const;
    void setMoveSpeed(float moveSpeed);
    int getChangeShapeTime() const;
    void setChangeShapeTime(int changeShapeTime);
    int getSpwanShapeTime() const;
    void setSpwanShapeTime(int spwanShapeTime);
	int getLevel() const;
	void setLevel(int level);
	int getMistake() const;
	void setMistake(int level);
    cocos2d::Layer *getLayer() const;
    void setLayer(cocos2d::Layer *layer);
    cocos2d::Label *getScoreLable() const;
    GameState getGameState() const;
    void setGameState(GameState gameState);
    void setChangeShapeTime(float changeShapeTime);
    void setSpwanShapeTime(float spwanShapeTime);
	const std::vector<std::string> &getShapeList() const;
	void setShapeList();
    void changeShape();
    std::string getRandomShape();
    const std::string &getCurrentShape() const;
    void setCurrentShape(const std::string &currentShape);
    const std::string &getNextShape() const;
    void setNextShape(const std::string &nextShape);
	cocos2d::ProgressTimer *getLifeBar() const;
	void setLifeBar(cocos2d::ProgressTimer *lifeBar);
    void reset();
    void isMistake();
private:
    Game(){};
    static Game *pGame;
    cocos2d::Label *scoreLable;
	cocos2d::Layer *layer;
	cocos2d::ProgressTimer *lifeBar;

    GameState gameState = GameState::NEW;
    int score = 0;
    float life = 100.0;
    float moveSpeed = 10.0;
    float changeShapeTime = 10.0;
    float spwanShapeTime = 1.0;
    int level = 1;
    int mistake = 0;

	std::vector<std::string> shapeList;
    std::string currentShape;
    std::string nextShape;
};

