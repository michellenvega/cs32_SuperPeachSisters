#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

// hello
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

bool StudentWorld::addFlower(int x, int y){
    for(auto a : actors){
        if (a->getX() == x && a->getY() == y && !a->solidObject()){
            a->setVisible(true);
            a->moveTo(x, y+8);
            return true;
        }}
    return false;
}

bool StudentWorld::addStar(int x, int y){
    for(auto a : actors){
        if (a->getX() == x && a->getY() == y && !a->solidObject()){
            a->setVisible(true);
            a->moveTo(x, y+8);
            return true;
        }}
    return false;
}
bool StudentWorld::addMushroom(int x, int y){
    for(auto a : actors){
        if (a->getX() == x && a->getY() == y && !a->solidObject()){
            a->setVisible(true);
            a->moveTo(x, y+8);
            return true;
        }}
    return false;
}
   
int StudentWorld::getPeachTargetingInfo(Actor* a) const{
    int y1 = a->getY();
    int y2 = m_peach->getY();
    if (y1 + SPRITE_HEIGHT > y2 && y1 < y2 + SPRITE_HEIGHT)
        return m_peach->getX() - a->getX();
    return 0;
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

bool StudentWorld::overlapsPeach(Actor* a) {
    if (overlap(m_peach->getX(),m_peach->getY(), a->getX(), a->getY())){
        return true;
    }
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
bool StudentWorld::isBlocked(int x, int y, Actor* a1) {

   bool doesit = overlap(x, y, a1->getX(), a1->getX());
    for (auto a : actors)
        if((a->getX() == x && a->getY() == y && a->solidObject()) || doesit)
            return true;
    return false;
}
bool StudentWorld::blockThenBonk(int x, int y, Actor* a1) {

    y++;
    for (auto a : actors)
            if (a != a1)
                if (a->checkifAlive() && a->solidObject())
                    if (x + SPRITE_WIDTH > a->getX() && x < a->getX() + SPRITE_WIDTH)
                        if (y + SPRITE_HEIGHT > a->getY() && y < a->getY() + SPRITE_HEIGHT){
                                a->bonk();
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
                case Level::star_goodie_block:{
                    actors.push_back (new Block(this, x, y,"star"));
                    Star* s = new Star(this,x,y);
                    s->setVisible(false);
                    actors.push_back (s);
                    break;}
                case Level::mushroom_goodie_block:{
                    actors.push_back (new Block(this, x, y,"mushroom"));
                    Mushroom* m = new Mushroom(this,x,y);
                    m->setVisible(false);
                    actors.push_back (m);
                    break;}
                case Level::flower_goodie_block:{
                    actors.push_back (new Block(this, x, y,"flower"));
                    Flower* f = new Flower(this,x,y);
                    f->setVisible(false);
                    actors.push_back (f);
                    break;}
                case Level::block:
                    actors.push_back (new Block(this, x, y,"none"));
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
                    m_flag = new Flag(this, x, y);
                    break;
                case Level::mario:
                  //  m_mario = new Mario(this, x, y);
                    marioisHere = true;
                    break;
            }
            }}
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    m_peach->doSomething();
    m_flag->doSomething();
    for (auto it = actors.begin(); it != actors.end(); it++) {
        if ((*it)->checkifAlive()) {
            (*it)->doSomething();
        }
    }

    //  if peach has died
    if(m_peach->checkifAlive() == false){
        playSound(SOUND_PLAYER_DIE);
        return GWSTATUS_PLAYER_DIED;
    }
    
    // overlaps with flag
    /*If Peach has reached a flag (overlaps with them), then it’s time to advance to the
     next level. In this case, the move() method must:
     a. Play a SOUND_FINISHED_LEVEL sound using playSound().
     b. Immediately return with a value of GWSTATUS_FINISHED_LEVEL.
     */
    stage_complete = overlapsPeach(m_flag);
    
    if(startedGame && stage_complete){
        increaseScore(1000);
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
    stage_complete = false;
    // overlaps with mario
    /*If Peach has reached Mario (overlaps with him), then the player has won and the
     game is over. In this case, the move() method must:
     a. Play a SOUND_GAME_OVER sound using playSound().
     b. Immediately return with a value of GWSTATUS_PLAYER_WON.*/
   if(marioisHere) stage_complete = overlapsPeach(m_mario);
    
    if(stage_complete){
       increaseScore(1000);
        playSound(SOUND_GAME_OVER);
        return GWSTATUS_PLAYER_WON;
    }
    
    stage_complete = false;
    
    // delete all dead actors
   /* for(Actor *a: actors)
        if(!a->checkifAlive())
            delete a;
    */
    // update score status
    
    
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for (auto a: actors)
            delete a;
        actors.clear();

    delete m_peach;
    m_peach = nullptr;
    
    delete m_flag;
    m_flag = nullptr;
    
  
    m_mario = nullptr;
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

}
