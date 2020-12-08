//
//  laser.hpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/8/20.
//

#ifndef laser_hpp
#define laser_hpp

#import <iostream>
#import "movingObject.hpp"
#import "point.hpp"
#import "velocity.hpp"
#import "uiDraw.hpp"

#define LASER_SPEED 200

class Laser : public MovingObject {

public:
    Laser(Point p_init, float angle, Velocity v_init) {
        // initialize
        name = "Laser";

        // fire laser
        setPoint(p_init);

        setVelocity(Velocity(LASER_SPEED, 0));
        
        std::cout << v.getDx() << std::endl;
        
        // debug
        std::cout << "Laser constructor called." << std::endl;
    }
    
    void display() {
        p = Point(0, 50);
        drawDot(p);
    }
};

#endif /* laser_hpp */
