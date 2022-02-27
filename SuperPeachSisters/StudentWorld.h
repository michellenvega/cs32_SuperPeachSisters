#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include "Level.h"
#include <string>
#include <vector>
#include <iterator>
using namespace std;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  virtual int init();
  virtual int move();
  virtual void cleanUp();
   ~StudentWorld();
    bool checkPos(int x, int y, Actor* act);
    bool checkPosBelow(int a, int b);
    void finishedLevel(){
        stage_complete = true;
    }
    
    
    // // // // // // // //
    // BEING USED
    // // // // // // // //
    
    // goodies
    bool addFlower(int x, int y);
    bool addStar(int x, int y);
    bool addMushroom(int x, int y);
    // projectiles
    bool addShell(int x, int y, int dir);
    void addPeachFireball(int x, int y, int dir);
    void addPiranhaFireball(int x, int y, int dir);
    
    
    
    
    
    
    // add actors to world
    bool addPeach(int x, int y);
    bool addMario(int x, int y);
    bool addBlock(int x, int y);
    bool addFlag(int x, int y);
    bool addPipe(int x, int y);

    // enemies
    bool addGoomba(int x, int y);
    bool addKoopa(int x, int y, string direction);
    bool addPiranha(int x, int y);
    
    
    void bonkPeach(Actor* bonker){
        m_peach->bonk(bonker);
    }
    // if Peach overlaps, bonk the second actor
    bool overlapThenBonk(Actor* a1);
    
    // If Peach overlaps bonker, bonk 'er and return true; otherwise,
    // return false.
    bool bonkOverlappingPeach(Actor* bonker) const;
    
    // If Peach overlaps damager, damage her and return true; otherwise,
    // return false.
    bool damageOverlappingPeach(Actor* damager) const;
    
    // If a non-Peach actor overlaps damager, damage that non-Peach actor
    // and return true; otherwise, return false.
    bool damageOverlappingActor(Actor* damager) const;
    
    // Return true if a overlaps Peach; otherwise, return false.
    bool overlapsPeach(Actor* a) ;
    
    //  find out how far actor is from peach
    int getPeachTargetingInfo(Actor* a) const;
    
    // Set Peach's hit points to hp.
    void setPeachHP(int hp) const{return;}
    
    // Grant Peach invincibility for this number of ticks.
    void grantInvincibility(int ticks) const;
    
    // Grant Peach Shoot Power.
    void grantShootPower() const;
    
    // Grant Peach Jump Power.
    void grantJumpPower() const;
    
    // Return true if a overlaps an enemy; otherwise, return false.
    bool overlapWithEnemy(Actor* primary);
    
    // if blocking position, bonk the second actor
    bool blockThenBonk(int x, int y, Actor* a1, bool bonk) ;
    
    // if blocking position, set true
    bool isBlocked(int x, int y, Actor* a1) ;
    
    //  Return main character
    Peach* getPeach(){return m_peach;}
    
    //  has started game
    bool startedGame = false;
    
    // overlap
    bool overlap(int x1, int y1, int x2, int y2);

private:
    Peach* m_peach;
    Flag* m_flag;
    Mario* m_mario;
    bool marioisHere = false;
    vector<Actor*> actors;
    bool stage_complete = false;
};

#endif // STUDENTWORLD_H_
