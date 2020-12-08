//
//  rocks.hpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/14/20.
//

#ifndef rocks_hpp
#define rocks_hpp

#include <stdio.h>

#include "movingObject.hpp"
#include "uiDraw.hpp"

#define ROCK_RADIUS 10
#define ROCK_SPEED 20
#define ROCK_ROTATE_SPEED 20

enum rockIndex {
    bigRock,
    mediumRock,
    smallRock
};

class Rock : public MovingObject {
public:
    Rock() {
        name = "Rock (unknown)";
        r = ROCK_RADIUS;
        dr = ROCK_ROTATE_SPEED;
        printf("unknown rock");
        printf(" created");
    }
    
    Rock(Point p_init, Velocity v_init) {
        
    }
    
    void display() override {
        // Draw asteroid at Point p and angle r
        drawLargeAsteroid(p, rotation);
    }
    
    void initializeRotation();
    
    const static int amountInit = 5;
    const static rockIndex rockIndex;
};


#define BIG_ROCK_RADIUS 10
#define BIG_ROCK_SPEED 20
#define BIG_ROCK_ROTATE_SPEED 20

class BigRock : public Rock {
public:
    BigRock() {
        name = "Big Rock";
        r = BIG_ROCK_RADIUS;
    }
};


#endif /* rocks_hpp */
