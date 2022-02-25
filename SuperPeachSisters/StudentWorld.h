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
    
    // add actors to world
        bool addPeach(int x, int y);
        bool addMario(int x, int y);
        bool addBlock(int x, int y);
        bool addFlag(int x, int y);
        bool addPipe(int x, int y);
        // goodies
        bool addFlower(int x, int y);
        bool addStar(int x, int y);
        bool addMushroom(int x, int y);
        // enemies
        bool addGoomba(int x, int y);
        bool addKoopa(int x, int y, string direction);
        bool addPiranha(int x, int y);
        // projectiles
        bool addShell(int x, int y, string direction);
        bool addPeachFireball(int x, int y);
        bool addPiranhaFireball(int x, int y);

    // is it overlapping an enemy
    bool overlapWithEnemy(Actor* primary);
    // if overlaps, bonk the second actor
    bool overlapThenBonk(Actor* a1);
    bool blockThenBonk(int x, int &y, Actor* a1);

private:
    Peach* m_peach;
    vector<Actor*> actors;
    bool overlap(int x1, int y1, int x2, int y2);
    
};

#endif // STUDENTWORLD_H_
