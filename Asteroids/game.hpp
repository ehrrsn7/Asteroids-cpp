//
//  game.hpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/7/20.
//

#ifndef game_hpp
#define game_hpp

// import
#include <iostream> // debugging
#include <stdio.h>
#include <vector> // dynamic arrays
#include <map> // held keys

#include "point.hpp" // point
#include "uiInteract.hpp" // user interaction

// import game objects
#include "movingObject.hpp"
#include "ship.hpp"
#include "laser.hpp"
#include "score.hpp"
#include "level.hpp"
#include "rocks.hpp"

// define

class Game {
private:
    // screen positioning
    float screenLeft;
    float screenRight;
    float screenBottom;
    float screenTop;
    Point center;
    
    // game objects
    Ship ship;
    std::vector<Laser> lasers;
    std::vector<Rock*> rocks;
    Level level;
    Score score;
    
    // held keys
    std::map<char, bool> heldKeys;
    
    // in game.cpp:
    void setUpScreen(Point tl, Point br);
    void initializeHeldKeys();
    void fireLaser();
    void asteroidBelt();
    void wrapObjects();
    void wrap(MovingObject* obj);
    void handleCollisions();
    void handleCollision(MovingObject* obj1, MovingObject* obj2);
    float getClosestDistance(const MovingObject &obj1, const MovingObject &obj2);
    
    // other misc attributes
    int i, j; // count trackers for iterators

public:
    Game(Point topLeft, Point bottomRight) {
        /* Set up the initial conditions of the game */
        setUpScreen(topLeft, bottomRight);
        
        /* GAME OBJECTS */
        asteroidBelt();
    }
    
    ~Game() {}
    
    void update() {
        ship.update();
        
        // update lasers
        for (std::vector<Laser>::iterator it = lasers.begin(); it < lasers.end(); ++it) {
            it->update(); // no (*it)-> here, laser vector is not *pointer vector
        }
        
        // update rocks
        for (std::vector<Rock*>::iterator it = rocks.begin(); it < rocks.end(); ++it) {
            (*it)->update(); // (*it)-> requred, rocks vector is a *pointer vector
        }

        wrapObjects();
        handleCollisions();
    }

    // 'const Interface & ui'
    // this is
    void display(const Interface & ui) {
        ship.display();
        
        // display lasers
        for (std::vector<Laser>::iterator it = lasers.begin(); it < lasers.end(); ++it) {
            it->display();
        }
        
        // display rocks
        for (std::vector<Rock*>::iterator it = rocks.begin(); it < rocks.end(); ++it) {
            rocks[i]->display();
        }
    }
    
    void handleInput(const Interface & ui) {
        
        /* DO THINGS */
        
        // up
        // accelerate ship
        if (heldKeys['u']) ship.accelerate();

        // space
        // fire laser
        if (heldKeys['s']) fireLaser();

        // left / right
        // rotate (accordingly)
        if (heldKeys['l'] || heldKeys['r']) {
            if (heldKeys['l']) ship.rotate("left");
            if (heldKeys['r']) ship.rotate("right");
        } else if (ship.getRotation() != 0.0) ship.stopRotating();
        
        /* INPUT MANAGER */

        // space
        // fire laser
        if (ui.isSpace()) heldKeys['s'] = true;
        else heldKeys['s'] = false;

        // left
        // rotate ship left
        if (ui.isLeft()) heldKeys['l'] = true;
        else heldKeys['l'] = false;

        // right
        // rotate ship right
        if (ui.isRight()) heldKeys['r'] = true;
        else heldKeys['r'] = false;
        
        // up
        // accelerate ship
        if (ui.isUp()) heldKeys['u'] = true;
        else heldKeys['u'] = false;
        
        // down
        // pause game/brake/idk
        if (ui.isDown()) heldKeys['d'] = true;
        else heldKeys['d'] = false;
    }
};


#endif /* game_hpp */
