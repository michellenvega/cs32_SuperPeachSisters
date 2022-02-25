#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;
using namespace std;
#include <string>
//base class
class Actor : public GraphObject{
public:
    Actor(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth): GraphObject(imageID,startX* SPRITE_WIDTH,startY * SPRITE_HEIGHT, startDirection, depth), isAlive(true), m_world(world){};
    
    virtual void doSomething() = 0;
    virtual bool solidObject() = 0;
    StudentWorld* getWorld(){return m_world;}
    bool checkifAlive(){ return isAlive; }
    void die(){ isAlive = false;}
    virtual bool isEnemy(){return false;}
    virtual void bonk() {return;}
protected:
    bool isAlive;
private:
    StudentWorld* m_world;
};


class Overlapable : public Actor {
 public:
    Overlapable(StudentWorld* world, int imageID, int x_level, int y_level, int depth, int startDirection = 0) :
            Actor(world, imageID, x_level, y_level, startDirection, depth) {};

    virtual bool solidObject() {return false;}
    virtual void bonk() {return;}
 };


// flag
class Flag: public Overlapable{
    public:
    Flag(StudentWorld* world, int x_level, int y_level): Overlapable(world, IID_FLAG,  x_level, y_level, 1 , 0){};
    virtual void doSomething(){return;}
    virtual bool isEnemy(){return false;}
};

// Mario
class Mario: public Overlapable{
    public:
    Mario(StudentWorld* world, int x_level, int y_level): Overlapable(world, IID_MARIO, x_level, y_level, 1 , 0){};
    virtual void doSomething(){return;}
};


// goodies are alive!!

 class Goodie : public Overlapable {
 public:
     Goodie(StudentWorld* world, int imageID, int x_level, int y_level) :
        Overlapable(world, imageID, x_level, y_level, 1) {};
 private:
     virtual void giveGoodie() = 0;
 };

 class Star : public Goodie {
 public:
    Star(StudentWorld* world, int x_level, int y_level) :
         Goodie(world, IID_STAR, x_level, y_level) {};
     virtual void doSomething(){return;}
 private:
     virtual void giveGoodie(){return;}
 };

 class Flower : public Goodie {
 public:
 Flower(StudentWorld* world, int x_level, int y_level) :
         Goodie(world, IID_FLOWER, x_level, y_level) {};
     virtual void doSomething(){return;}
 private:
     virtual void giveGoodie(){return;}
 };
 
 class Mushroom : public Goodie {
 public:
    Mushroom(StudentWorld* world, int x_level, int y_level) :
         Goodie(world, IID_MUSHROOM, x_level, y_level) {};
     virtual void doSomething(){return;}
 private:
     virtual void giveGoodie(){return;}
 };
 

// enemies
class Enemy : public Overlapable{
public:
    Enemy(StudentWorld* world, int imageID, int x_level, int y_level) : Overlapable(world, imageID, x_level, y_level, 0, (randInt(1, 2)%2) ? 0 : 180){};
    virtual void doSomething(){return;}
    virtual void bonk() {return;}
    virtual bool isEnemy(){return true;}
    virtual bool solidObject() {return false;}
};

class Goomba : public Enemy{
public:
    Goomba(StudentWorld* world, int x_level, int y_level)  : Enemy(world, IID_GOOMBA, x_level, y_level) {};
    virtual void doSomething(){return;}
    virtual void bonk(){return;}
};


class Koopa : public Enemy{
public:
    Koopa(StudentWorld* world, int x_level, int y_level)  :  Enemy(world, IID_KOOPA, x_level, y_level){};
    virtual void doSomething(){return;}
    virtual void bonk(){return;}
};


class Piranha : public Enemy{
public:
    Piranha(StudentWorld* world, int x_level, int y_level) : Enemy(world, IID_PIRANHA, x_level, y_level){};
    virtual void doSomething(){return;}
    virtual void bonk(){return;}
private:
    int firingDelay();
};


// Overlapable(StudentWorld* world, int imageID, double x_level, double y_level, int depth, int startDirection = right)

// projectiles

class Projectile : public Overlapable {
public:
    Projectile(StudentWorld* world, int imageID, int x_level, int y_level, int direction) :
       Overlapable(world, imageID, x_level, y_level, 1) {};
    virtual void doSomething();
};

class Shell : public Projectile {
public:
    Shell(StudentWorld* world, int x_level, int y_level, int dir) :
        Projectile(world, IID_SHELL, x_level, y_level, dir) {};
    virtual void doSomething();
};

class PeachFireball : public Projectile {
public:
    PeachFireball(StudentWorld* world, int x_level, int y_level, int dir) :
        Projectile(world, IID_PEACH_FIRE, x_level, y_level, dir) {};
    virtual void doSomething();
};

class PiranhaFireball : public Projectile {
public:
    PiranhaFireball(StudentWorld* world, int x_level, int y_level, int dir) :
        Projectile(world, IID_PIRANHA_FIRE, x_level, y_level, dir)  {};
    virtual void doSomething();
};


// block
class Block: public Actor{
    public:
    Block(StudentWorld* world, int x_level, int y_level): Actor(world, IID_BLOCK, x_level, y_level, 0 , 2){};
    virtual void doSomething(){ return; }
    virtual void bonk();
    virtual bool solidObject(){return true;}
    
};

// pipe
class Pipe: public Actor{
    public:
    Pipe(StudentWorld* world, int x_level, int y_level): Actor(world, IID_PIPE, x_level, y_level, 0 , 2){};
    virtual void doSomething(){return;}
    virtual bool solidObject(){return true;}
};


//peach
class Peach: public Actor{ // check name
public:
    Peach(StudentWorld* world, int x_level, int y_level): Actor(world, IID_PEACH, x_level, y_level, 0 , 0), m_hitpoints(1), p_star(false), p_jump(false), p_shoot(false), p_invincible(false), star_ticks(0), temp_ticks(0){};
    
    virtual void doSomething();
    virtual bool solidObject(){return true;}
    // give powers
    void giveStarPower(){p_star = true;}
    void giveJumpPower(){p_jump = true;}
    void giveShootPower(){p_shoot = true;}
    void giveInvincPower(){p_invincible = true;} // temporary
    // get whether Peach has the power or not
    bool getStarPower(){return p_star;}
    bool getJumpPower(){return p_jump;}
    bool getShootPower(){return p_shoot;}
    bool getInvinPower(){return p_invincible;} // temporary
    // add health point
    void changeHit(int num){ m_hitpoints+= num;}
    
    //ticks
    int getStarTicks(){return star_ticks;}
    //  check if overlapping
    //  do two actors overlap?
  
    
private:
    double m_hitpoints;
    double m_damage;
    bool p_star, p_jump, p_shoot, p_invincible;
    int star_ticks, temp_ticks;
    // use powers
    void useStarPower();
    void useJumpPower();
    void useShootPower();
    void useInvinc(); // temporary
    
    //  jump

    bool initiatedJump = false;
    bool fallingJump = false;
    int remaining_jump_distance = 0;
};





// multiply by sprite width and height
// check each bonk
// check each size, direction, depth




#endif // ACTOR_H_
