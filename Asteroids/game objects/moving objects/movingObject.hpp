//
//  movingObject.hpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/7/20.
//

#ifndef movingObject_hpp
#define movingObject_hpp

#include <iostream>
#include <string>
#include <math.h>

#include "point.hpp"
#include "velocity.hpp"

#define FPS 60.0

class MovingObject {

protected:
    std::string name;
    Point p;
    Velocity v;
    float r; // radius
    float a; // angle
    float da; // angular velocity
    float rotation; // display angle
    float dr; // display angle angular vel.
    float thrust;
    float timer;
    bool alive;
    
    // debug
    int i;

public:
    MovingObject() {
        name    = "* Moving object";
        i       = 0;
        r       = 10.0; // in pixels
        a       = 0.0; // angle (degrees)
        da      = 0.0; // rotational velocity in degrees per second
        rotation = 0.0; // current display angle (degrees)
        dr      = 0.0; // display angle rot. vel. in deg. per second
        thrust  = 0.0; // acceleration in pixels/s/s
        timer   = 0.0; // self-destruct timer in seconds
        alive   = true; // isAlive
        
        // debug
        std::cout << name << " constructor called." << std::endl;
    }

    void update() {
        // update position
        p.add(v); // / FPS);
        // Velocity brakes = Velocity(-v.getDx() / 5, -v.getDy() / 5);
        // v.add(brakes);

        // update angle using da
        a += 100 * da / FPS;
        if (a < 0) a = 360;
        else if (a > 360) a = 0;
        
        // update rotation using dr
        rotation += 100 * dr/FPS;
        if (rotation < 0) rotation = 360;
        else if (rotation > 360) rotation = 0;

        // update timer (if timer == 0, do nothing)
        if (timer > 0) timer -= 1/FPS; // TODO: I want this to be deltaTime, not 1/FPS
        else if (timer < 0) alive = false;
    }
    
    void accelerate() {
        v.add(v.forward(a) * thrust);
    }

    void hit() { setAlive(false); }

    // polymorphism
    virtual void display() { }

    // getters
    std::string getName()   const   { return name; }
    Point getPoint()        const   { return p; }
    Velocity getVelocity()  const   { return v; }
    float getRadius()       const   { return r; }
    float getAngle()        const   { return a; }
    float getRotation()     const   { return da; }
    bool isAlive()          const   { return alive; }
    
    // setters
    void setPoint(Point new_p)       { p = new_p; }
    void setPointX(float new_x)      { p.setX(new_x); }
    void setPointY(float new_y)      { p.setY(new_y); }
    void setVelocity(Velocity new_v) { v = new_v; }
    void setRadius(float new_r)      { r = new_r; }
    void setRotation(float new_da)   { da = new_da; }
    void setAlive(bool new_alive)    { alive = new_alive; }
};

#endif /* movingObject_hpp */
