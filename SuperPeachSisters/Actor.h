#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;
using namespace std;
#include <string>



// // // // // // // // // // // // // // //
//     ACTOR BASE CLASS DECLARATION
// // // // // // // // // // // // // // //



class Actor : public GraphObject{
public:
    Actor(StudentWorld* world, int imageID, int startX, int startY, int startDirection, int depth): GraphObject(imageID,startX* SPRITE_WIDTH,startY * SPRITE_HEIGHT, startDirection, depth), isAlive(true), m_world(world){};
    
    virtual void doSomething() = 0;
    virtual bool solidObject() = 0;
    StudentWorld* getWorld(){return m_world;}
    bool checkifAlive(){ return isAlive; }
    void die(){ isAlive = false;}
    virtual bool isEnemy(){return false;}
    virtual bool isDamageable(){return false;}
    virtual void damage(){return;}
    virtual void bonk(Actor* bonker) {return;}
private:
    bool isAlive;
    StudentWorld* m_world;
  
};


// // // // // // // // // // // // // // //
//      PIPE AND BLOCK DECLARATIONS
// // // // // // // // // // // // // // //



class Block: public Actor{
    public:
    Block(StudentWorld* world, int x_level, int y_level, string g = "star"): Actor(world, IID_BLOCK, x_level, y_level, 0 , 2),
                typeG(g){};
    virtual void doSomething(){ return; }
    virtual void bonk(Actor* bonker);
    virtual bool solidObject(){return true;}
    
private:
    string typeG;
};


class Pipe: public Actor{
    public:
    Pipe(StudentWorld* world, int x_level, int y_level): Actor(world, IID_PIPE, x_level, y_level, 0 , 2){};
    virtual void doSomething(){return;}
    virtual bool solidObject(){return true;}
};



// // // // // // // // // // // // // // //
//      OVERLAPABLE DECLARATION
// // // // // // // // // // // // // // //

class Overlapable : public Actor {
 public:
    Overlapable(StudentWorld* world, int imageID, int x_level, int y_level, int depth, int startDirection = 0) :
            Actor(world, imageID, x_level, y_level, startDirection, depth) {};
    virtual void doSomething(){return;}
    virtual bool solidObject() {return false;}
    virtual void bonk(Actor* bonker) {return;}
    virtual bool isDamageable(){return false;}
    virtual void damage(){return;}
 };



// // // // // // // // // // // // // // //
//      END OF LEVEL DECLARATIONS
// // // // // // // // // // // // // // //


class Flag: public Overlapable{
    public:
    Flag(StudentWorld* world, int x_level, int y_level): Overlapable(world, IID_FLAG,  x_level, y_level, 1 , 0){};
    virtual void doSomething(){return;}
};

class Mario: public Overlapable{
    public:
    Mario(StudentWorld* world, int x_level, int y_level): Overlapable(world, IID_MARIO, x_level, y_level, 1 , 0){};
    virtual void doSomething(){return;}
};




// // // // // // // // // // // // // // //
//        GOODIES DECLARATIONS
// // // // // // // // // // // // // // //



 class Goodie : public Overlapable {
 public:
     Goodie(StudentWorld* world, int imageID, int x_level, int y_level) :
        Overlapable(world, imageID, x_level, y_level, 1) {};
     virtual void doSomething(){return;}
     virtual bool isDamageable(){return false;}
     virtual void damage(){return;}
 private:
     //virtual void giveGoodie() = 0 ;
 };

class Flower : public Goodie {
public:
Flower(StudentWorld* world, int x_level, int y_level) :
        Goodie(world, IID_FLOWER, x_level, y_level) {};
    virtual void doSomething();
private:
   // virtual void giveGoodie();
};

 class Star : public Goodie {
 public:
    Star(StudentWorld* world, int x_level, int y_level) :
         Goodie(world, IID_STAR, x_level, y_level) {};
     virtual void doSomething();
 private:

 };
 
 class Mushroom : public Goodie {
 public:
    Mushroom(StudentWorld* world, int x_level, int y_level) :
         Goodie(world, IID_MUSHROOM, x_level, y_level) {};
     virtual void doSomething();
 private:
    // virtual void giveGoodie();
 };
 


// // // // // // // // // // // // // // //
//      PROJECTILE DECLARATIONS
// // // // // // // // // // // // // // //



class Projectile : public Overlapable {
public:
    Projectile(StudentWorld* world, int imageID, int x_level, int y_level, int direction) :
       Overlapable(world, imageID, x_level, y_level, 1) {};
    virtual void doSomething(){return;}
    virtual bool isDamageable(){return false;}
    virtual void damage(){return;}
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



// // // // // // // // // // // // // // //
//       ENEMY DECLARATIONS
// // // // // // // // // // // // // // //



class Enemy : public Overlapable{
public:
    Enemy(StudentWorld* world, int imageID, int x_level, int y_level) : Overlapable(world, imageID, x_level, y_level, 0, (randInt(1, 2)%2) ? 0 : 180){};
    
    virtual void doSomething(){return;}
    virtual bool isEnemy(){return true;}
    virtual bool solidObject() {return false;}
    virtual bool isDamageable(){return true;}
private:
    virtual void damage(){return;}
};

class Goomba : public Enemy{
public:
    Goomba(StudentWorld* world, int x_level, int y_level)  : Enemy(world, IID_GOOMBA, x_level, y_level) {};
    virtual void doSomething();
    virtual void bonk(Actor* bonker);
private:
    virtual void damage();
};


class Koopa : public Enemy{
public:
    Koopa(StudentWorld* world, int x_level, int y_level)  :  Enemy(world, IID_KOOPA, x_level, y_level){};
    virtual void doSomething();
    virtual void bonk(Actor* bonker);
private:
    virtual void damage();
};


class Piranha : public Enemy{
public:
    Piranha(StudentWorld* world, int x_level, int y_level) : Enemy(world, IID_PIRANHA, x_level, y_level), firingD(0){};
    virtual void doSomething();
    virtual void bonk(Actor* bonker);
private:
    int firingDelay();
    int firingD;
    virtual void damage();
};



// // // // // // // // // // // // // // //
//           PEACH DECLARATIONS
// // // // // // // // // // // // // // //

// DELETING DEAD CHARACTERS!!!!




class Peach: public Actor{ // check name
public:
    Peach(StudentWorld* world, int x_level, int y_level): Actor(world, IID_PEACH, x_level, y_level, 0 , 0), m_hitpoints(1), p_jump(false), p_shoot(false), p_invincible(false){};

    //  Basic qualities of Peach
    virtual void doSomething();
    virtual bool solidObject(){return true;}
    virtual bool isDamageable(){return false;}
    virtual void damage(){return;}

    // Suffer damage.
    void sufferDamageIfDamageable();
    
    // Set Peach's hit points.
    void setHP(int hp);
    
    // Grant Peach invincibility for this number of ticks.
    void gainInvincibility(int ticks);
    
    // Grant Peach Shoot Power.
    void gainShootPower();
    
    // Grant Peach Jump Power.
    void gainJumpPower();
    
    // Is Peach invincible?
    bool isInvincible() const{return p_invincible;}
    
    // Does Peach have Shoot Power?
    bool hasShootPower() const{return p_shoot;}
    
    // Does Peach have Jump Power?
    bool hasJumpPower() const{return p_jump;}
    
    
    
private:
    //  damage and health
    double m_hitpoints; double m_damage;
    bool p_jump, p_shoot, p_invincible, p_temp;
    int i_ticks;
    int time_to_recharge_before_next_fire = 0;
    // for use of jumping and movement
    bool initiatedJump = false;
    bool fallingJump = false;
    int remaining_jump_distance = 0;
};





#endif // ACTOR_H_
