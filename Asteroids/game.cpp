//
//  game.cpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/7/20.
//

#include "game.hpp"

#include <limits> // for getClosestDistance()
#include <algorithm>
#include "movingObject.hpp"

// initialization
void Game::setUpScreen(Point tl, Point br) {
    center.setXY(0, 0); // center of screen
    screenLeft   = tl.getX();
    screenRight  = br.getX();
    screenBottom = br.getY();
    screenTop    = tl.getY();
    score.set(Point(center.getX(), screenTop - 10));
    level.set(Point(screenRight, screenTop - 10));
    i = 0;
    j = 0;
}

void Game::initializeHeldKeys() {
    heldKeys = {
        {'l', false}, // left
        {'r', false}, // right
        {'s', false}, // space
        {'u', false}, // up
        {'d', false}  // down
    };
}

void Game::fireLaser() {
    // handle "machine gun firing here"
    // define firing rate above
    // (at desired rate:)
    // get new laser from ship.fire()
    // push new laser onto lasers (vector<>)
    lasers.push_back(ship.fire());
}

Rock* createRock(int whichRock) {
    Rock* newRock = NULL;
    switch(whichRock) {
        case bigRock:
            newRock = new BigRock;
            break;
        case mediumRock:
            newRock = new BigRock; // TODO: update once MediumRock class is defined
            break;
        case smallRock:
            newRock = new BigRock; // TODO: update once SmallRock class is defined
            break;
    }
    return newRock;
}

void Game::asteroidBelt() {
    for (int i = 0; i < Rock::amountInit; i++) {
        std::cout << "asteroid belt " << i << std::endl;
        rocks.push_back(createRock(bigRock));
    }
}

void Game::wrap(MovingObject* obj) {
    bool debug = false;
    if (debug) printf("wrap() called ");
    
    /* SCREEN SIDE VALS REFERENCE
     * screen left   == topLeft.getX() - obj->getRadius()
     * screen right  == bottomRight.getX() + obj->getRadius()
     * screen bottom == bottomRight.getY() - obj->getRadius()
     * screen top    == topLeft.getY() + obj->getRadius()
     */

    // obj x < screen left => screen right
    if (obj->getPoint().getX() < screenLeft - obj->getRadius()) {
        obj->setPointX(screenRight + obj->getRadius());
        if (debug) printf("//  Wrap left -> right");
    }
    
    // obj x > screen right => screen left
    else if (obj->getPoint().getX() > screenRight + obj->getRadius()) {
        obj->setPointX(screenLeft - obj->getRadius());
        if (debug) printf("//  Wrap right -> left");
    }
    
    // obj y < screen bottom => screen top
    if (obj->getPoint().getY() < screenBottom - obj->getRadius()) {
        obj->setPointY(screenTop + obj->getRadius());
        if (debug) printf("//  Wrap bottom -> top");
    }
    
    // obj y > screen top => screen bottom
    else if (obj->getPoint().getY() > screenTop + obj->getRadius()) {
        obj->setPointY(screenBottom - obj->getRadius());
        if (debug) printf("//  Wrap top -> bottom");
    }
    
    if (debug) printf("\n");
}

void Game::wrapObjects() {
    // wrap ship
    wrap(&ship);

    // wrap lasers
    for (std::vector<Laser>::iterator it = lasers.begin(); it < lasers.end(); ++it, ++i) {
        wrap(&lasers[i]);
    }
    
    i = 0;

    // wrap rocks
    for (std::vector<Rock*>::iterator it = rocks.begin(); it < rocks.end(); ++it, ++i) {
        wrap(rocks[i]);
    }
    
    i = 0;
}

void Game::handleCollisions() {
    // all collisions involve rocks
    for (std::vector<Rock*>::iterator rIt = rocks.begin(); rIt != rocks.end(); ++rIt, ++i) {
        
        // collision between ship and rock
        handleCollision(&ship, rocks[i]);
        
        // handle collision between laser and rock
        for (std::vector<Laser>::iterator lIt = lasers.begin(); lIt != lasers.end(); ++lIt, ++j)
            handleCollision(&lasers[j], rocks[i]);
 
        j = 0;
    }
    
    i = 0;
}

void Game::handleCollision(MovingObject* obj1, MovingObject* obj2) {
    float tooClose = obj1->getRadius() + obj2->getRadius();
    if (getClosestDistance(*obj1, *obj2) < tooClose) {
        std::cout << "collision between " << obj1->getName() << " and " << obj2->getName() << std::endl;
    }
}

float Game::getClosestDistance(const MovingObject &obj1, const MovingObject &obj2) {
    // find the maximum distance traveled
    float dMax = std::max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
    dMax = std::max(dMax, abs(obj2.getVelocity().getDx())); // Between previous max and |obj2.dx|
    dMax = std::max(dMax, abs(obj2.getVelocity().getDy())); // Between previous max and |obj2.dy|
    dMax = std::max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.

    float distMin = std::numeric_limits<float>::max();
    for (float i = 0.0; i <= dMax; i++) {
        Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
        Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));

        float xDiff = point1.getX() - point2.getX();
        float yDiff = point1.getY() - point2.getY();

        float distSquared = (xDiff * xDiff) +(yDiff * yDiff);

        distMin = std::min(distMin, distSquared);
    }

    return sqrt(distMin);
}
