#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

void Mushroom::doSomething(){
    if(!isVisible()) return;
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
    bool canMove = false;
    int x2 = getX(); int y2 = getY();
  
        if(getWorld()->checkPos(x2,y2,this)) {
            y2--;
            if(getWorld()->checkPos(x2,y2,this)) {
                y2--;
           
            } else canMove = true;
        } else
            canMove = true;
    moveTo(x2,y2);
    
    while(getWorld()->checkPos(x2,y2,this)){
        y2--;
        }
    moveTo(x2,y2);
    /*
     The Mushroom object will then determine what direction it is facing (0 or 180
     degrees) and try to move in that direction by 2 pixels:
     */
    if(getWorld()->getPeachTargetingInfo(this) > 0)
        setDirection(0);
    else if(getWorld()->getPeachTargetingInfo(this) < 0) setDirection(180);
    
    int d = getDirection();
    int testX = getX(); int testY = getY();
    // The Mushroom will calculate a target x,y position first (2 pixels greater or  less than its current x position)
    //  Check to see if there is an object that would block movement to this destination position
    //  The Mushroom will reverse its direction (from 0 to 180, or vice versa)
    
    
    if(d == 180) {
      //&& getWorld()->blockThenBonked(testX-2, testY-1, this)
        if(getWorld()->blockThenBonk(testX-2, testY, this) && getWorld()->blockThenBonk(testX-1, testY, this)){
            d = 0;
        setDirection(d);
        return;
        }
    }
    else{
        if(getWorld()->blockThenBonk(testX+2, testY, this) && getWorld()->blockThenBonk(testX+1, testY, this)){
        d = 180;
        setDirection(d);
        return;
        }
    }

    
    // Otherwise, the Mushroom will update its location 2 pixels leftward or rightward depending on the direction it’s facing.
    if(d==0 && canMove)    moveTo(getX()+2, getY());
    else if(canMove)       moveTo(getX()-2, getY());
    
   }


void Flower::doSomething(){
    if(!isVisible()) return;
    if(getWorld()->overlapsPeach(this)){ // Flower object must see if it currently overlaps with Peach.
        //   It will increase the player’s score by 50 points
        getWorld()->increaseScore(50);
        //   It will inform the Peach object that it now has the Shoot Power
        getWorld()->grantShootPower();
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
    
    while(getWorld()->checkPos(x2,y2,this)){
        y2--;
        }
    moveTo(x2,y2);
    /*
     The Flower object will then determine what direction it is facing (0 or 180
     degrees) and try to move in that direction by 2 pixels:
     */
    
   
    int testX = getX(); int testY = getY();
    
    if(getWorld()->getPeachTargetingInfo(this) > 0)
        setDirection(0);
    else if(getWorld()->getPeachTargetingInfo(this) < 0) setDirection(180);
    
    // The Flower will calculate a target x,y position first (2 pixels greater or  less than its current x position)
    //  Check to see if there is an object that would block movement to this destination position
    //  The Flower will reverse its direction (from 0 to 180, or vice versa)
    int d = getDirection();
    if(d == 180) {
        if(getWorld()->blockThenBonk(testX-2, testY, this) && getWorld()->blockThenBonk(testX-1, testY, this)){
            d = 0;
        setDirection(d);
        return;
        }
    }
    else{
        if(getWorld()->blockThenBonk(testX+2, testY, this) && getWorld()->blockThenBonk(testX+1, testY, this)){
        d = 180;
        setDirection(d);
        return;
        }
    }

    
    // Otherwise, the Flower will update its location 2 pixels leftward or rightward depending on the direction it’s facing.
    if(d==0 )    moveTo(getX()+2, getY());
    else       moveTo(getX()-2, getY());
    
}

void Star::doSomething(){
    if(!isVisible()) return;
    if(getWorld()->overlapsPeach(this)){ // Star object must see if it currently overlaps with Peach.
        //   It will increase the player’s score by 100 points
        getWorld()->increaseScore(100);
        //  It will inform the Peach object that it now has the Star Power for 150 game ticks
        getWorld()->grantInvincibility(150);
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
           
            }
        }
    moveTo(x2,y2);
    
    while(getWorld()->checkPos(x2,y2,this)){
        y2--;
        }
    moveTo(x2,y2);
    /*
     The Star object will then determine what direction it is facing (0 or 180
     degrees) and try to move in that direction by 2 pixels:
     */
    
   
    int testX = getX(); int testY = getY();
    
    if(getWorld()->getPeachTargetingInfo(this) > 0)
        setDirection(0);
    else if(getWorld()->getPeachTargetingInfo(this) < 0) setDirection(180);
    
    // The Star will calculate a target x,y position first (2 pixels greater or  less than its current x position)
    //  Check to see if there is an object that would block movement to this destination position
    //  The Star will reverse its direction (from 0 to 180, or vice versa)
    int d = getDirection();
    if(d == 180) {
        if(getWorld()->blockThenBonk(testX-2, testY, this) && getWorld()->blockThenBonk(testX-1, testY, this)){
            d = 0;
        setDirection(d);
        return;
        }
    }
    else{
        if(getWorld()->blockThenBonk(testX+2, testY, this) && getWorld()->blockThenBonk(testX+1, testY, this)){
        d = 180;
        setDirection(d);
        return;
        }
    }

    
    // Otherwise, the Star will update its location 2 pixels leftward or rightward depending on the direction it’s facing.
    if(d==0 )    moveTo(getX()+2, getY());
    else       moveTo(getX()-2, getY());
    }



void Block::bonk(){
    if(typeG == "none"){
        getWorld()->playSound(SOUND_PLAYER_BONK);
        return;
    }

 //  getWorld()->playSound(SOUND_POWERUP_APPEARS);
    
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

void Peach::doSomething(){
    if(!checkifAlive()) return;
    
  /* if(p_star == true)   // if has star power
       star_ticks--;    // decrement the number of remaining game ticks before she loses this invincibility power
    if(star_ticks == 0) // when tick reaches 0
        p_star = false;   // set star power as off
       
    
    
    if((p_jump || p_shoot) && !p_star && getWorld()->overlapWithEnemy(this)){ // if have jump/shoot power and overlap with enemy
        p_jump = false; p_shoot = false;}
    
    
    if(p_invincible)// if has temp invincibility
        temp_ticks--;      //  decrement the number of remaining game ticks before she loses temporary invincibility
    if(temp_ticks == 0) // when tick reaches 0
        p_invincible = false;   // set temp invinc to false (need bool then)
        
    
    */
    
    // check if in recharge mode
        // time_to_recharge_before_next_fire ticks is greater than zero
                // must decrement this tick count by one
                //if tick count == 0 and peach has shoot power
                    // can NOW shoot a fireball
    
    
    
    
    if(getWorld()->overlapThenBonk(this))  //  if overlap with another object, must bonk another object
            getWorld()->playSound(SOUND_PLAYER_BONK); //    play sound
    
    
    // jump!
    if(initiatedJump && remaining_jump_distance > 0){
       
            int x = getX(); int y = getY()+4;
            if(!getWorld()->checkPos(x, y, this)){
                getWorld()->blockThenBonk(x, y, this);
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
            
            // key up
            /*i. Check to see if there is an object that would block movement one
             pixel below her. (Such an object gives her support to jump; she
             doesn't actually move downward.) If so:
             1. Peach must set her remaining_jump_distance to the
             appropriate value:
             a. If Peach does NOT have Jump Power, then set
             remaining_jump_distance to 8.
             b. If Peach DOES have Jump Power, then set
             remaining_jump_distance to 12.
             2. Peach must play the sound SOUND_PLAYER_JUMP
             using the playSound() method in the GameWorld class.*/
            if(!getWorld()->checkPos(getX(), getY()-1, this)){
                initiatedJump = true;
                if(p_jump) remaining_jump_distance = 12;
                else remaining_jump_distance = 12;
                getWorld()->startedGame = true;
            getWorld()->playSound(SOUND_PLAYER_JUMP);
                
            }
            break;
        case KEY_PRESS_SPACE:
            //  space bar:
            /* i. If Peach doesn’t have Shoot Power, then do nothing
             ii. Otherwise, if the time_to_recharge_before_next_fire is greater
             than zero, then do nothing.
             iii. Otherwise:
             1. Play the sound SOUND_PLAYER_FIRE using the
             playSound() method in the GameWorld class.
             2. Set time_to_recharge_before_next_fire to 8, meaning that
             Peach may not fire again for another 8 game ticks
             3. Determine the x,y position directly in front of Peach that is
             4 pixels away in the direction she’s facing.
             4. Introduce a new fireball object at this location into your
             StudentWorld. The fireball must have its direction set to the
             same direction that Peach was facing when she fired.*/

            
            
            if(getWorld()->checkPos(getX(),getY()-4, this)) //check if blocked
                moveTo(getX(), getY()-4);
            break;
        default:
            break;
             
    }
    }
}
