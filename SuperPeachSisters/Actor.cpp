#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp



// // // // // // // // // // // // // // //
//      END OF LEVEL DECLARATIONS
// // // // // // // // // // // // // // //


 void EndLevel::doSomething(){  //   must check to see if it is alive, and if not, it must do nothing.
     if(!checkifAlive()) return;
     
     
     if(getWorld()->overlapsPeach(this))    //  e Flag must see if it currently overlaps with Peach. If so:
     {
         getWorld()->increaseScore(1000);   //  It will increase the player’s score by 1000 points
         
         die();     //  It will immediately set its state to not-alive
         
         getWorld()->finishedLevel(true);
     }
 }

// // // // // // // // // // // // // // //
//    GOODIES AND BLOCK IMPLEMENTATIONS
// // // // // // // // // // // // // // //


// // // // //
// MUSHROOM
// // // // //


void Mushroom::doSomething(){
    if(!checkifAlive()) return;
    if(getWorld()->overlapsPeach(this)){ // Mushroom object must see if it currently overlaps with Peach.
        //   It will increase the player’s score by 75 points
        getWorld()->increaseScore(75);
        //   It will inform the Peach object that it now has the Jump Power
        getWorld()->grantJumpPower();
        //  It will set Peach’s hit points to 2
        getWorld()->setPeachHP(2);
        //  It will immediately set its state to not-alive
        die();
        setVisible(false);
        //  It will play a sound of SOUND_PLAYER_POWERUP using GameWorld’s playSound() method
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        //  It will do nothing else and immediately return
        return;
    }
    /*
     Mushroom object must determine if there is an object just beneath
     it that would block it from falling two pixels downward. If there is no such
     blocking object beneath the Mushroom, it will:
     */
        //  Use the moveTo() method to move downward 2 pixels

    int x2 = getX(); int y2 = getY();
  
        if(getWorld()->checkPos(x2,y2,this)) {
            y2--;
            if(getWorld()->checkPos(x2,y2,this)) {
                y2--;
           
            }}
    moveTo(x2,y2);
    

    /*
     The Mushroom object will then determine what direction it is facing (0 or 180
     degrees) and try to move in that direction by 2 pixels:
     */
    
    int d = getDirection();
    int testX = getX(); int testY = getY();
    // The Mushroom will calculate a target x,y position first (2 pixels greater or  less than its current x position)
    //  Check to see if there is an object that would block movement to this destination position
    //  The Mushroom will reverse its direction (from 0 to 180, or vice versa)
    
    
    if(d == 180) {
      //&& getWorld()->blockThenBonked(testX-2, testY-1, this)
        if(getWorld()->blockThenBonk(testX-2, testY, this, false) && getWorld()->blockThenBonk(testX-1, testY, this, false)){
            d = 0;
        setDirection(d);
        return;
        }
    }
    else{
        if(getWorld()->blockThenBonk(testX+2, testY, this, false) && getWorld()->blockThenBonk(testX+1, testY, this, false)){
        d = 180;
        setDirection(d);
        return;
        }
    }

    
    // Otherwise, the Mushroom will update its location 2 pixels leftward or rightward depending on the direction it’s facing.
    if(d==0)    moveTo(getX()+2, getY());
    else       moveTo(getX()-2, getY());
    
   }


// // // // //
//  FLOWER
// // // // //


void Flower::doSomething(){
    if(!checkifAlive() || !isVisible()) return;
    if(getWorld()->overlapsPeach(this)){ // Flower object must see if it currently overlaps with Peach.
        //   It will increase the player’s score by 50 points
        getWorld()->increaseScore(50);
        //   It will inform the Peach object that it now has the Shoot Power
        getWorld()->grantShootPower();
        //  It will set Peach’s hit points to 2
        getWorld()->setPeachHP(2);
        //  It will immediately set its state to not-alive
        die();
        //  It will play a sound of SOUND_PLAYER_POWERUP using GameWorld’s playSound() method
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        //  It will do nothing else and immediately return
        return;
    }
    /*
     Flower object must determine if there is an object just beneath
     it that would block it from falling two pixels downward. If there is no such
     blocking object beneath the Flower, it will:
     */
        //  Use the moveTo() method to move downward 2 pixels
   
    int x2 = getX(); int y2 = getY();
  
        if(getWorld()->checkPos(x2,y2,this)) {
            
            y2--;
            if(getWorld()->checkPos(x2,y2,this)) {
                y2--;
           
            }
        }
    moveTo(x2,y2);
    

    /*
     The Flower object will then determine what direction it is facing (0 or 180
     degrees) and try to move in that direction by 2 pixels:
     */
    
   
    int testX = getX(); int testY = getY();

    // The Flower will calculate a target x,y position first (2 pixels greater or  less than its current x position)
    //  Check to see if there is an object that would block movement to this destination position
    //  The Flower will reverse its direction (from 0 to 180, or vice versa)
    int d = getDirection();
    if(d == 180) {
        if(getWorld()->blockThenBonk(testX-2, testY, this, false) && getWorld()->blockThenBonk(testX-1, testY, this, false)){
            d = 0;
        setDirection(d);
        return;
        }
    }
    else{
        if(getWorld()->blockThenBonk(testX+2, testY, this, false) && getWorld()->blockThenBonk(testX+1, testY, this, false)){
        d = 180;
        setDirection(d);
        return;
        }
    }

    
    // Otherwise, the Flower will update its location 2 pixels leftward or rightward depending on the direction it’s facing.
    if(d==0 )    moveTo(getX()+2, getY());
    else       moveTo(getX()-2, getY());
    
}


// // // // //
//   STAR
// // // // //


void Star::doSomething(){
    if(!checkifAlive()) return;
    if(getWorld()->overlapsPeach(this)){ // Star object must see if it currently overlaps with Peach.
        //   It will increase the player’s score by 100 points
        getWorld()->increaseScore(100);
        //  It will inform the Peach object that it now has the Star Power for 150 game ticks
        getWorld()->grantInvincibility(150);
        //  It will set Peach’s hit points to 2
        getWorld()->setPeachHP(2);
        //  It will immediately set its state to not-alive
        die();
        //  It will play a sound of SOUND_PLAYER_POWERUP using GameWorld’s playSound() method
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        //  It will do nothing else and immediately return
        return;
    }
    /*
     Star object must determine if there is an object just beneath
     it that would block it from falling two pixels downward. If there is no such
     blocking object beneath the Star, it will:
     */
        //  Use the moveTo() method to move downward 2 pixels
   
    int x2 = getX(); int y2 = getY();
  
        if(getWorld()->checkPos(x2,y2,this)) {
            y2--;
            if(getWorld()->checkPos(x2,y2,this)) {
                y2--;
           
            }}
    moveTo(x2,y2);
    
    /*
     The Star object will then determine what direction it is facing (0 or 180
     degrees) and try to move in that direction by 2 pixels:
     */
    
   
    int testX = getX(); int testY = getY();
    

    // The Star will calculate a target x,y position first (2 pixels greater or  less than its current x position)
    //  Check to see if there is an object that would block movement to this destination position
    //  The Star will reverse its direction (from 0 to 180, or vice versa)
    int d = getDirection();
    if(d == 180) {
        if(getWorld()->blockThenBonk(testX-2, testY, this, false) && getWorld()->blockThenBonk(testX-1, testY, this, false)){
            d = 0;
        setDirection(d);
        return;
        }
    }
    else{
        if(getWorld()->blockThenBonk(testX+2, testY, this, false) && getWorld()->blockThenBonk(testX+1, testY, this, false)){
        d = 180;
        setDirection(d);
        return;
        }
    }

    
    // Otherwise, the Star will update its location 2 pixels leftward or rightward depending on the direction it’s facing.
    if(d==0 )    moveTo(getX()+2, getY());
    else       moveTo(getX()-2, getY());
    }



// // // // //
//  BLOCK
// // // // //


void Block::bonk(Actor* bonker){
    if(typeG == "none"){
        getWorld()->playSound(SOUND_PLAYER_BONK);
        return;
    }

    
    /*  Introduce a goodie object of the appropriate type (Flower, Star or
     Mushroom) exactly 8 pixels above the block that was bonked (the
     same x coordinate as the block, but y+8 from the block)
     */
   
    if(typeG == "flower") {
        getWorld()->addFlower(getX(), getY());
        //  It has been bonked!!!
        typeG = "none";}
    if(typeG == "star") {
        //  It has been bonked!!!
        typeG = "none";
        getWorld()->addStar(getX(), getY());}
    if(typeG == "mushroom"){
        getWorld()->addMushroom(getX(), getY());
        //  It has been bonked!!!
        typeG = "none";
    }
    

    
}

// // // // // // // // // // // // // // //
//     PROJECTILES IMPLEMENTATIONS
// // // // // // // // // // // // // // //


// // // // // // // //
//   PEACH FIREBALL
// // // // // // // //

void PeachFireball::doSomething(){
    //  Peach Fireball object must see if it currently overlaps with a damageable object (other than Peach)
    //  If so:
    if(getWorld()->damageOverlappingActor(this)){   //  It will inform the object that it has been damaged.
    
        die();      //  It will immediately set its own state to not-alive
        return;     //  It will do nothing else and immediately return
    }

    
    // Peach Fireball object must determine if there is an object just beneath
    // it that would block it from falling two pixels downward
    
    int x2 = getX(); int y2 = getY();
    if(getWorld()->checkPos(x2,y2,this)) {
        y2--;
        if(getWorld()->checkPos(x2,y2,this)) {
                    y2--;
                    moveTo(x2,y2);  //  Use the moveTo() method to move downward 2 pixels
                }
            }
        
   
    int testX = getX(); int testY = getY();
    

    // The fireball will calculate a target x,y position first (2 pixels greater or  less than its current x position)
    //  Check to see if there is an object that would block movement to this destination position
    //  The fireball will reverse its direction (from 0 to 180, or vice versa)
    int d = getDirection();
    if(d == 180) {
        if(getWorld()->blockThenBonk(testX-2, testY, this, false) && getWorld()->blockThenBonk(testX-1, testY, this, false)){
            die();
        return;
        }
    }
    else{
        if(getWorld()->blockThenBonk(testX+2, testY, this, false) && getWorld()->blockThenBonk(testX+1, testY, this, false)){
            die();
        return;
        }
    }

    
    // Otherwise, the Fireball will update its location 2 pixels leftward or rightward depending on the direction it’s facing.
    if(d==0 )    moveTo(getX()+2, getY());
    else       moveTo(getX()-2, getY());
    
}



void PiranhaFireball::doSomething(){
    //  Fireball object must see if it currently overlaps with a damageable object (other than Peach)
    //  If so:
    
    if(getWorld()->overlapsPeach(this) && !attacked)//  check to see if it overlaps with Peach at its current location
    {   // if so
        getWorld()->bonkPeach(this);    //      The fireball will attempt to bonk Peach
        attacked = true;
        die();
        return;     //      The fireball will immediately return
    }
    
    if(getWorld()->damageOverlappingActor(this)){   //  It will inform the object that it has been damaged.
    
        die();      //  It will immediately set its own state to not-alive
        return;     //  It will do nothing else and immediately return
    }

    // Peach Fireball object must determine if there is an object just beneath
    // it that would block it from falling two pixels downward
    
    int x2 = getX(); int y2 = getY();
    if(getWorld()->checkPos(x2,y2,this)) {
        y2--;
        if(getWorld()->checkPos(x2,y2,this)) {
                    y2--;
                    moveTo(x2,y2);  //  Use the moveTo() method to move downward 2 pixels
                }
            }
        
   
    int testX = getX(); int testY = getY();
    

    // The fireball will calculate a target x,y position first (2 pixels greater or  less than its current x position)
    //  Check to see if there is an object that would block movement to this destination position
    //  The fireball will reverse its direction (from 0 to 180, or vice versa)
    int d = getDirection();
    if(d == 180) {
        if(getWorld()->blockThenBonk(testX-2, testY, this, false) && getWorld()->blockThenBonk(testX-1, testY, this, false)){
            die();
        return;
        }
    }
    else{
        if(getWorld()->blockThenBonk(testX+2, testY, this, false) && getWorld()->blockThenBonk(testX+1, testY, this, false)){
            die();
        return;
        }
    }

    
    // Otherwise, the Fireball will update its location 2 pixels leftward or rightward depending on the direction it’s facing.
    if(d==0 )    moveTo(getX()+2, getY());
    else       moveTo(getX()-2, getY());
    
    
    
    
}



void Shell::doSomething(){

    //  Shell object must see if it currently overlaps with a damageable object (other than Peach)
    //  If so:
    
    if(getWorld()->damageOverlappingActor(this)){   //  It will inform the object that it has been damaged.
    
        die();      //  It will immediately set its own state to not-alive
        return;     //  It will do nothing else and immediately return
    }
    
    // Shell object must determine if there is an object just beneath
    // it that would block it from falling two pixels downward
    
    int x2 = getX(); int y2 = getY();
    if(getWorld()->checkPos(x2,y2,this)) {
        y2--;
        if(getWorld()->checkPos(x2,y2,this)) {
                    y2--;
                    moveTo(x2,y2);  //  Use the moveTo() method to move downward 2 pixels
                }
            }
        
   
    int testX = getX(); int testY = getY();
    

    // The shell will calculate a target x,y position first (2 pixels greater or  less than its current x position)
    //  Check to see if there is an object that would block movement to this destination position
    //  The shell will reverse its direction (from 0 to 180, or vice versa)
    int d = getDirection();
    if(d == 180) {
        if(getWorld()->blockThenBonk(testX-2, testY, this, false) && getWorld()->blockThenBonk(testX-1, testY, this, false)){
            die();
        return;
        }
    }
    else{
        if(getWorld()->blockThenBonk(testX+2, testY, this, false) && getWorld()->blockThenBonk(testX+1, testY, this, false)){
            die();
        return;
        }
    }

    
    // Otherwise, the shell will update its location 2 pixels leftward or rightward depending on the direction it’s facing.
    if(d==0 )    moveTo(getX()+2, getY());
    else       moveTo(getX()-2, getY());
    
    
    
}

// // // // // // // // // // // // // // //
//      ENEMIES IMPLEMENTATIONS
// // // // // // // // // // // // // // //


// // // // //
//   KOOPA
// // // // //

void Koopa::doSomething(){
    if(!checkifAlive()) return; //      if dead, return
    
    if(getWorld()->overlapsPeach(this))//  check to see if it overlaps with Peach at its current location
    {   // if so
        getWorld()->bonkPeach(this);    //      The Koopa will attempt to bonk Peach
        return;     //      The Koopa will immediately return
    }
    
    //      Determine if it can move 1 pixel in its current direction without running into an object that blocks movement
    //      If not, switch to the opposite direction
    
    int testX = getX(); int testY = getY();
    int d = getDirection();
    if(d == 180) {
        if(getWorld()->blockThenBonk(testX-1, testY, this, false) || getWorld()->checkPos(testX-1-SPRITE_WIDTH,testY-1,this) || getWorld()->isEmpty(testX-1, testY-4)){
            d = 0;
        setDirection(d);
        return;
        }
      
    }
    else{
        if(getWorld()->blockThenBonk(testX+1, testY, this, false) || getWorld()->checkPos(testX+1+SPRITE_WIDTH,testY-1,this) || getWorld()->isEmpty(testX+1, testY-4)){
        d = 180;
        setDirection(d);
        return;
        }
    }
    // Otherwise, the Koopa will update its location 1 pixel leftward or rightward depending on the direction it’s facing
    if(d==0 )    moveTo(getX()+1, getY());
        else       moveTo(getX()-1, getY());
}



void Koopa::bonk(Actor* bonker){
    if(bonker != getWorld()->getPeach()) return; // If the bonker is not Peach, then ignore the bonk
    
    if(getWorld()->getPeach()->isInvincible())  //  If Peach has Star Power (invincibility)
    {   // then...
        
        getWorld()->playSound(SOUND_PLAYER_KICK); // Play the sound SOUND_PLAYER_KICK
        
        getWorld()->increaseScore(100); //  Increase the player’s score by 100 points
        
        die();  //  Will later be removed
        
        //  Introduce a new Shell object at the same location as Koopa, facing the same direction as Koopa
        
        getWorld()->addShell(getX(), getY(), getDirection());
        
    }
     
    
}
    
void Koopa::damage(){
    //  (a fireball fired by Peach overlaps with her)
    
    getWorld()->increaseScore(100); //  Increase the player’s score by 100 points
    
    die();  // Set it to not alive
    
    //  Introduce a new Shell object at the same location as Koopa, facing the same direction as Koopa
    getWorld()->addShell(getX(), getY(), getDirection());
    
    }


// // // // //
//  GOOMBA
// // // // //

void Goomba::doSomething(){
    if(!checkifAlive()) return; //     If not alive, return!
    
    if(getWorld()->overlapsPeach(this))//  check to see if it overlaps with Peach at its current location
    {   // if so
        getWorld()->bonkPeach(this);    //      The Koopa will attempt to bonk Peach
        return;     //      The Koopa will immediately return
    }
    
    //      Determine if it can move 1 pixel in its current direction without running into an object that blocks movement
    //      If not, switch to the opposite direction
   
    int testX = getX(); int testY = getY();
    int d = getDirection();
    
    if(d == 180) {
        if(getWorld()->blockThenBonk(testX-1, testY, this, false) || getWorld()->blockThenBonk(testX-1, testY-1, this, false)){
        setDirection(0);
        return;
        }
    }
    else{
        if(getWorld()->blockThenBonk(testX+1, testY, this, false) || getWorld()->blockThenBonk(testX+1, testY-1, this, false)){
        setDirection(180);
        return;
        }
    }
    
    d = getDirection();
    // Otherwise, the Koopa will update its location 1 pixel leftward or rightward depending on the direction it’s facing
    if(d==0 )    moveTo(getX()+1, getY());
    else       moveTo(getX()-1, getY());
    

    
    
}

    
void Goomba::bonk(Actor* bonker){
    if(bonker != getWorld()->getPeach()) return; // If the bonker is not Peach, then ignore the bonk
    
    if(getWorld()->getPeach()->isInvincible())  //  If Peach has Star Power (invincibility)
    {   // then...
        
        getWorld()->playSound(SOUND_PLAYER_KICK); // Play the sound SOUND_PLAYER_KICK
        
        getWorld()->increaseScore(100); //  Increase the player’s score by 100 points
        
        die();  //  Will later be removed
        
    }
    }
 
void Goomba::damage(){
        
    getWorld()->increaseScore(100); //  Increase the player’s score by 100 points
    die(); //   Set it to not alive
    }

    
// // // // // //
//   PIRANHA
// // // // // //
    
    
void Piranha::doSomething(){
    
    if(!checkifAlive()) return; //  If not alive, return!
    
    increaseAnimationNumber();      // Cycle its sprite image using GraphObject’s increaseAnimationNumber() method
    
    if(getWorld()->overlapsPeach(this))//  Check to see if it overlaps with Peach at its current location
    {   // if so
        getWorld()->bonkPeach(this);    //      The Piranha will attempt to bonk Peach
        return;     //      The Piranha will immediately return
    }
    
    
    //  will assume total = 1.5*SPRITE_HEIGHT y coordinate
    // greater than total but less than peach
    // less than total but greater than peach
    
    int p_y = getWorld()->getPeach()->getY();
    if(p_y > getY() + 1.5*SPRITE_HEIGHT || p_y < getY() - 1.5*SPRITE_HEIGHT)
        return;
    
    
    if(firingD != 0){   //  Piranha will check if it has a firing delay, and if so:
        firingD--;          //  It will decrease the firing delay by one.
        return;             //  It will immediately return.
    }
        
    //  If there is no firing delay, then Piranha may choose to fire:
    
    int p_x = getWorld()->getPeach()->getX();   // Peach's x coord
    
    //  Compute distance between this and peach
    
    if(p_x > getX() + 8*SPRITE_WIDTH || p_x <= getX() -  8*SPRITE_WIDTH)
        return;
    //  If in range, then...
    
    // Find direction towards Peach
    
    int loc = getWorld()->getPeachTargetingInfo(this);
    
    if(loc < 0) setDirection(180);
        else
        setDirection(0);
    
  //  getWorld()->addPiranhaFireball(getX()-8, getY(), getDirection()); //  Add a new Piranha Fireball, same x, y, direction
    
    getWorld()->playSound(SOUND_PIRANHA_FIRE);  //  Play the sound SOUND_PIRANHA_FIRE
    
    firingD = 40;   //  Set its firing delay to 40
    
}


void Piranha::bonk(Actor* bonker){
    if(bonker != getWorld()->getPeach()) return; // If the bonker is not Peach, then ignore the bonk
    
    if(getWorld()->getPeach()->isInvincible())  //  If Peach has Star Power (invincibility)
    {   // then...
        
        getWorld()->playSound(SOUND_PLAYER_KICK); // Play the sound SOUND_PLAYER_KICK
        
        getWorld()->increaseScore(100); //  Increase the player’s score by 100 points
        
        die();  //  Will later be removed
        
    }
    }
    
void Piranha::damage(){
    
    getWorld()->increaseScore(100); //  Increase the player’s score by 100 points
    die(); //   Set it to not alive
    
    }




// // // // // // // // // // // // // // //
//         PEACH IMPLEMENTATIONS
// // // // // // // // // // // // // // //

void Peach::addHP(int hp){
    m_hitpoints+=hp;
}


void Peach::bonk(Actor* bonker){
    if(p_invincible) return;
    
    addHP(-1);      //  Decrement Peach’s hit points by one
    
    p_invincible = true;
    i_ticks = 10;   //  Set Peach’s temporary invincibility to 10 ticks
    
    if(p_shoot) p_shoot = false;    //  If Peach had Shoot Power, turn it off
    if(p_jump) p_jump = false;      //  If Peach had Jump Power, turn it off
    
    if(m_hitpoints > 0) {    //  If Peach has at least one hit point left
        getWorld()->playSound(SOUND_PLAYER_HURT);
        return;     //  play the SOUND_PLAYER_HURT
    }
     else if(m_hitpoints <= 0)      //  If Peach hit points reach zero
        die();
}


void Peach::doSomething(){
    if(!checkifAlive()) return;
    
  if(p_invincible == true)   // if has star power
      i_ticks--;    // decrement the number of remaining game ticks before she loses this invincibility power
    if(i_ticks == 0) // when tick reaches 0
        p_invincible = false;   // set star power as off
      
    
    
    if((p_jump || p_shoot) && !p_invincible && getWorld()->overlapWithEnemy(this)){
        // if have jump/shoot power and overlap with enemy
        p_jump = false;
        p_shoot = false;}
    
    
    if(p_temp)// if has temp invincibility
        i_ticks--;      //  decrement the number of remaining game ticks before she loses temporary invincibility
    if(i_ticks == 0) // when tick reaches 0
     p_temp = false;   // set temp invinc to false (need bool then)
        
    
  
    // check if in recharge mode
    if(time_to_recharge_before_next_fire>0)    // time_to_recharge_before_next_fire ticks is greater than zero
            time_to_recharge_before_next_fire--;    // must decrement this tick count by one
   
    
    
    if(getWorld()->overlapThenBonk(this))  //  if overlap with another object, must bonk another object
            getWorld()->playSound(SOUND_PLAYER_BONK); //    play sound
    
    
    // jump!
    if(initiatedJump && remaining_jump_distance > 0){
       
            int x = getX(); int y = getY()+4;
            if(!getWorld()->checkPos(x, y, this)){
                getWorld()->blockThenBonk(x, y, this, true);
                initiatedJump = false;
                remaining_jump_distance = 0;
            }else{
                moveTo(x,y);
                remaining_jump_distance--;
            }
            
        if(remaining_jump_distance==0)
        initiatedJump = false;
    }
    else if(!initiatedJump){
        int x2 = getX(); int y2 = getY();
        if(getWorld()->checkPos(x2,y2,this)) {
            y2--;
            if(getWorld()->checkPos(x2,y2,this)) {
                y2--;
                if(getWorld()->checkPos(x2,y2,this)) {
                    y2--;
                    if(getWorld()->checkPos(x2,y2,this)) {
                        y2--;
                        moveTo(x2,y2);
                    }
                }
            }
        }
        
        
        
    }
  
    
    int ch;
    if (getWorld()->getKey(ch))
    {
    // user hit a key during this tick!
    switch (ch)
    {
        case KEY_PRESS_LEFT:
            setDirection(180);
            if(getWorld()->checkPos(getX()-4,getY(), this)) //check if blocked
                moveTo(getX()-4, getY());
            break;
        case KEY_PRESS_RIGHT:
            setDirection(0);
            if(getWorld()->checkPos(getX()+4,getY(), this)) //check if blocked
                moveTo(getX()+4, getY());
            break;
        case KEY_PRESS_UP:

            if(!getWorld()->checkPos(getX(), getY()-1, this)){ // Check to see if there is an object that would block movement 1 pixel below her.
                initiatedJump = true;
                if(p_jump) remaining_jump_distance = 12;
                else remaining_jump_distance = 8;
                getWorld()->startTheGame();
            getWorld()->playSound(SOUND_PLAYER_JUMP);
                
            }
            break;
        case KEY_PRESS_SPACE:{
            
            //  If Peach doesn’t have Shoot Power, then do nothing
            //  If the time_to_recharge_before_next_fire is greater than zero, then do nothing
            if(!p_shoot || time_to_recharge_before_next_fire > 0) break;
            
            //  Otherwise:
            
            getWorld()->playSound(SOUND_PLAYER_FIRE);   //  Play the sound SOUND_PLAYER_FIRE
            
            time_to_recharge_before_next_fire = 8;  //  Set time_to_recharge_before_next_fire to 8
            
            //  Determine the x,y position directly in front of Peach that is 4 pixels away in the direction she’s facing.
            int newX;    int dir = getDirection();
            if(dir == 0) newX = getX() + 4;
                else
                newX =  getX() - 4;
            
            //  Introduce a new fireball object at new location, same direction as Peach
            getWorld()->addPeachFireball(newX, getY(), dir);
    
            break;}
        default:
            break;
             
    }
    }
}

// Grant Peach invincibility for this number of ticks.
void Peach::gainInvincibility(int ticks){
    p_invincible = true;
    i_ticks = ticks;
}

// Grant Peach Shoot Power.
void Peach::gainShootPower(){
    p_shoot = true;
}

// Grant Peach Jump Power.
void Peach::gainJumpPower(){
    p_jump = true;
}

void Peach::setHP(int hp)
{
    m_hitpoints = hp;
}
