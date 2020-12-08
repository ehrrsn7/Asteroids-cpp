//
//  ship.hpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/7/20.
//

#ifndef ship_hpp
#define ship_hpp

#include <stdio.h>
#include <string>

#include "movingObject.hpp"
#include "laser.hpp"
#include "uiDraw.hpp"

#define SHIP_ROTATE_AMOUNT 10
#define SHIP_ACCELERATE_AMOUNT 2

class Ship : public MovingObject {
public:
    Ship() {
        name = "Player Ship";
        thrust = SHIP_ACCELERATE_AMOUNT;
        setRadius(2);
        a += 90.0;
    }
    
    void display() override {
        drawShip(p, a - 90.0, getRadius());
    }
    
    Laser fire() {
        return Laser(p, a, v);
    }

    void rotate(std::string direction) {
        if (direction == "left") {
            // std::cout << "turn left" << std::endl;
            setRotation(SHIP_ROTATE_AMOUNT);
        }

        if (direction == "right") {
            // std::cout << "turn right" << std::endl;
            setRotation(-SHIP_ROTATE_AMOUNT);
        }
    }
    
    void stopRotating() {
        // std::cout << "stop turning" << std::endl;
        setRotation(0.0);
    }
};

#endif /* ship_hpp */
