//
// Created by hassan on 2/18/18.
//

#include "Game.h"

Game *Game::pGame = nullptr;

Game *Game::getInstancd() {
    if(!pGame) {
        pGame = new Game;
        pGame->setShapeList();
    }
    return pGame;
}

int Game::getScore() const {
    return score;
}

void Game::setScore(int score) {
    Game::score = score;
    Game::scoreLable->setString(cocos2d::StringUtils::toString(Game::score));
}

void Game::setScoreLable(cocos2d::Label *scoreLable) {
    Game::scoreLable = scoreLable;
}

float Game::getMoveSpeed() const {
    return moveSpeed;
}

void Game::setMoveSpeed(float moveSpeed) {
    Game::moveSpeed = moveSpeed;
}

int Game::getChangeShapeTime() const {
    return changeShapeTime;
}

void Game::setChangeShapeTime(int changeShapeTime) {
    Game::changeShapeTime = changeShapeTime;
}

int Game::getSpwanShapeTime() const {
    return spwanShapeTime;
}

void Game::setSpwanShapeTime(int spwanShapeTime) {
    Game::spwanShapeTime = spwanShapeTime;
}

int Game::getLevel() const {
	return level;
}

void Game::setLevel(int level) {
	Game::level = level;
}

int Game::getMistake() const {
	return level;
}

void Game::setMistake(int mistake) {
	Game::mistake = mistake;
}

cocos2d::Layer *Game::getLayer() const {
    return layer;
}

void Game::setLayer(cocos2d::Layer *layer) {
    Game::layer = layer;
}

cocos2d::Label *Game::getScoreLable() const {
    return scoreLable;
}

GameState Game::getGameState() const {
    return gameState;
}

void Game::setGameState(GameState gameState) {
    Game::gameState = gameState;
}

void Game::setChangeShapeTime(float changeShapeTime) {
    Game::changeShapeTime = changeShapeTime;
}

void Game::setSpwanShapeTime(float spwanShapeTime) {
    Game::spwanShapeTime = spwanShapeTime;
}

const std::vector<std::string> &Game::getShapeList() const {
    return shapeList;
}

void Game::setShapeList() {
    Game::shapeList.push_back("shape/Shape-0.png");
    Game::shapeList.push_back("shape/Shape-1.png");
    Game::shapeList.push_back("shape/Shape-2.png");
    Game::shapeList.push_back("shape/Shape-3.png");

//    std::string shapePath =  cocos2d::FileUtils::getInstance()->getDefaultResourceRootPath() + "/shape";
////    std::string shapePath = cocos2d::FileUtils::sharedFileUtils();// + "/shape";
    CCLOG("ADD list is ok");
//    CCLOG(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
//    DIR* dirp = opendir(shapePath.c_str());
//    struct dirent * dp;
//    while ((dp = readdir(dirp)) != NULL) {
//        if (!(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0))
//            Game::shapeList.push_back(dp->d_name);
//    }
//    closedir(dirp);
}

void Game::changeShape() {
    if (Game::currentShape.empty())
        Game::currentShape = Game::getRandomShape();
    else
        Game::currentShape = Game::nextShape;

    if (Game::nextShape.empty())
        Game::nextShape = Game::getRandomShape();

    while (Game::nextShape.compare(Game::currentShape) == 0)
        Game::nextShape = Game::getRandomShape();
}

std::string Game::getRandomShape() {

    std::random_device random_device;
    std::mt19937 engine{random_device()};
    std::uniform_int_distribution<int> dist(0, (int)Game::shapeList.size() - 1);
//    int listSize = Game::shapeList.size();
//    int rand  = cocos2d::RandomHelper::random_int(0, listSize - 1);
    return Game::shapeList[dist(engine)];
}

const std::string &Game::getCurrentShape() const {
    if(Game::currentShape.empty())
        Game::getInstancd()->changeShape();
    return currentShape;
}

void Game::setCurrentShape(const std::string &currentShape) {
    Game::currentShape = currentShape;
}

const std::string &Game::getNextShape() const {
    return nextShape;
}

void Game::setNextShape(const std::string &nextShape) {
    Game::nextShape = nextShape;
}

cocos2d::ProgressTimer *Game::getLifeBar() const {
    return lifeBar;
}

void Game::setLifeBar(cocos2d::ProgressTimer *lifeBar) {
    Game::lifeBar = lifeBar;
}

void Game::reset() {
    if(pGame) {
        delete(pGame);
        pGame = new Game;
        pGame->setShapeList();
    }
}

void Game::isMistake() {
    float currentLife = Game::getInstancd()->getLifeBar()->getPercentage();
    float distinatoinLif = currentLife - 25;
    if( distinatoinLif < 0)
        Game::getInstancd()->setGameState(GameState::GAMEOVER);
    auto minsAction = cocos2d::ProgressFromTo::create(1, currentLife, distinatoinLif);
    auto plusAction = cocos2d::ProgressFromTo::create(100, distinatoinLif, 100.0f);
    auto sequenceAction = cocos2d::Sequence::create(minsAction, plusAction, nullptr);
    Game::getInstancd()->getLifeBar()->runAction(sequenceAction);

    Game::getInstancd()->setMistake(Game::getInstancd()->getMistake() + 1);
}