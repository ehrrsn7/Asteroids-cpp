//
//  velocity.hpp
//  Asteroids
//
//  Created by Elijah Harrison on 11/7/20.
//

#ifndef velocity_hpp
#define velocity_hpp

#include <math.h>
#include <iostream>

class Velocity {

private:
    float dx;
    float dy;

public:
    Velocity() {
        setDx(0.0);
        setDy(0.0);
    }

    Velocity(float dx, float dy) {
        setDx(dx);
        setDy(dy);
    }
    
    Velocity(const Velocity & rhs) {
        setDx(rhs.getDx());
        setDy(rhs.getDy());
    }
    
    // getters
    float getDx() const { return dx; }
    float getDy() const { return dy; }
    
    static Velocity forward(float angle) {
        return Velocity(cos(rad(angle)), sin(rad(angle)));
    }
    
    // setters
    void setDx(float new_dx) { dx = new_dx; }
    void setDy(float new_dy) { dy = new_dy; }
    void set(Velocity new_v) {
        setDx(new_v.getDx());
        setDy(new_v.getDy());
    }
    
    // add/subtract
    void add(Velocity &dv) {
        dx += dv.dx;
        dy += dv.dy;
    }
    
    void subtract(Velocity &dv) {
        dx -= dv.dx;
        dy -= dv.dy;
    }
    
    // operators
    Velocity & operator * (float rhs) {
        dx *= rhs;
        dy *= rhs;
        return *this;
    }
    
    Velocity & operator / (float rhs) {
        dx /= rhs;
        dy /= rhs;
        return *this;
    }
    
    
    // calculators
    static float rad(float angleDegrees) {
        // angle deg -> rad
        return angleDegrees * M_PI / 180; }

    static float deg(float angleRadians) {
        // angle rad -> deg
        return angleRadians * 180 / M_PI; }
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Velocity & pt);

#endif /* velocity_hpp */
