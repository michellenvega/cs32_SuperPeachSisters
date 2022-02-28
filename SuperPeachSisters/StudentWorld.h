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
    
    // // // // // // // //
    //      ACTORS
    // // // // // // // //
    
    // goodies
    bool addFlower(int x, int y) const;
    bool addStar(int x, int y) const ;
    bool addMushroom(int x, int y) const;
    // projectiles
    bool addShell(int x, int y, int dir);
    void addPeachFireball(int x, int y, int dir);
    void addPiranhaFireball(int x, int y, int dir);

    
    // // // // // // // //
    //      WORLD
    // // // // // // // //
    
    //  Check Position
    bool checkPos(int x, int y, Actor* act) const;
    
    //  Bonk Peach
    void bonkPeach(Actor* bonker) const;
    
    // if Peach overlaps, bonk the second actor
    bool overlapThenBonk(Actor* a1) const;
    
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
    bool overlapsPeach(Actor* a) const ;
    
    //  find out how far actor is from peach
    int getPeachTargetingInfo(Actor* a) const;
    
    // Set Peach's hit points to hp.
    void setPeachHP(int hp) const;
    
    // Grant Peach invincibility for this number of ticks.
    void grantInvincibility(int ticks) const;
    
    // Grant Peach Shoot Power.
    void grantShootPower() const;
    
    // Grant Peach Jump Power.
    void grantJumpPower() const;
    
    // Return true if a overlaps an enemy; otherwise, return false.
    bool overlapWithEnemy(Actor* primary) const;
    
    // if blocking position, bonk the second actor
    bool blockThenBonk(int x, int y, Actor* a1, bool bonk) const;
    
    // if blocking position, set true
    bool isBlocked(int x, int y, Actor* a1) const;
    
    //  Return main character
    Peach* getPeach() const;
    
    //  is this spot empty?
    bool isEmpty(double x, double y) const;
    
    // overlap
    bool overlap(int x1, int y1, int x2, int y2) const;
    
    // Signify we have started the game
    void startTheGame();
    
    //  Signify we have finished this level
    void finishedLevel(bool done);
    
    //  Signify we have won the game
    void wongame(bool done);

private:
    Peach* m_peach;
    EndLevel* m_flag;
    vector<Actor*> actors;
    int levels = 0;
    bool marioisHere = false;
    bool startedGame = false;
    bool stage_complete = false;
    bool wonGame = false;
};

#endif // STUDENTWORLD_H_
