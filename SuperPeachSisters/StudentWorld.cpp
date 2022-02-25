#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath): GameWorld(assetPath)
{
    m_peach = nullptr;
    actors.clear();
}


   
bool StudentWorld::overlap(int x1, int y1, int x2, int y2){
    if (x1 + SPRITE_WIDTH > x2 && x1 < x2 + SPRITE_WIDTH)
            if (y1 + SPRITE_HEIGHT > y2 && y1 < y2 + SPRITE_HEIGHT)
                return true;
        return false;
}

bool StudentWorld::overlapWithEnemy(Actor* primary){
    for (auto a : actors)
        if (a != primary)
            if (a->checkifAlive() && a->isEnemy() && overlap(primary->getX(),primary->getY(), a->getX(), a->getY()))
                return true;
    return false;
}

bool StudentWorld::overlapThenBonk(Actor* a1){
    for (auto a : actors)
        if (a != a1)
            if (a->checkifAlive() && overlap(a1->getX(),a1->getY(), a->getX(), a->getY())){
                a->bonk();
                return true;
            }
    return false;

}

bool StudentWorld::blockThenBonk(int x, int &y, Actor* a1){
    for (auto a : actors)
        if (a != a1)
            if (a->checkifAlive() && !checkPos(x, y, a1)){
                a->bonk();
                playSound(SOUND_PLAYER_BONK);
                return true;
            }
    return false;

}

int StudentWorld::init()
{
    Level lev(assetPath());
    
    //  load the first level data file
    string levelname = "level0" + to_string(getLevel()) + ".txt";
    Level::LoadResult res = lev.loadLevel(levelname);
    
    //  read it and create block and peach objects
    //  is it valid ?
    
    if (res == Level::load_fail_file_not_found || res == Level::load_fail_bad_format)
        return GWSTATUS_LEVEL_ERROR;
    else if (res == Level::load_success){
        // use two for loops to get contents of the 2d array
        for(int x = 0; x < GRID_WIDTH; x++){
            for(int y = 0; y < GRID_HEIGHT; y++){
            Level::GridEntry gE = lev.getContentsOf(x, y);
            switch(gE){
                case Level::peach:
                    m_peach = new Peach(this, x, y);
                    break;
                case Level::star_goodie_block:
                case Level::mushroom_goodie_block:
                case Level::flower_goodie_block:
                case Level::block:
                    actors.push_back (new Block(this, x, y));
                    break;
                case Level::pipe:
                    actors.push_back (new Pipe(this, x, y));
                    break;
                case Level::koopa:
                    actors.push_back(new Koopa(this, x, y));
                    break;
               case Level::goomba:
                    actors.push_back(new Goomba(this, x, y));
                    break;
                     case Level::piranha:
                    actors.push_back(new Piranha(this, x, y));
                    break;
                case Level::empty:
                    break;
                case Level::flag:
                    actors.push_back(new Flag(this, x, y));
                    break;
                case Level::mario:
                    actors.push_back(new Mario(this, x, y));
                    break;
            }
            }}
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    m_peach->doSomething();
    for(Actor *a: actors)
        a->doSomething();
    
    return GWSTATUS_CONTINUE_GAME;
    
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    // decLives();
   // return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
    for (auto a: actors)
            delete a;
        actors.clear();

    delete m_peach;
    m_peach = nullptr;
}

StudentWorld::~StudentWorld(){
    cleanUp();
}
 


bool StudentWorld::checkPosBelow(int a, int b){
    std::vector<Actor*>::iterator it;
        for(it = actors.begin(); it!=actors.end();it++){
                        if ((*it)->getX() == a && (*it)->getY() == b - 1)
                            return true;
            
        }
        return false;
}

bool StudentWorld::checkPos(int a, int b, Actor* act){
    
    for (auto c : actors){
        if (c != act) //
            if (c->checkifAlive() && c->solidObject())
                if (overlap(a, b, c->getX(), c->getY()))
                    return false;

    }
        return true;
/*
    for (auto a : actors)
            if (c != me)
                if (c->checkifAlive() && c->solidObject())
                    if (overlap(act, c))
                        return false;
        return true;
 */
}
