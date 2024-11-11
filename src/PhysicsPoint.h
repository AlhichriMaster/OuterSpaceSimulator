#pragma once
#include "ofMain.h"

class PhysicsPoint {
public:
    ofVec3f position;
    ofVec3f velocity;
    ofVec3f acceleration;
    float mass;
    float size;
    bool isFixed;
    ofColor color;

    PhysicsPoint(ofVec3f pos, ofVec3f vel, float m, float s, ofColor c, bool fixed = false) {
        position = pos;
        velocity = vel;
        mass = m;
        size = s;
        color = c;
        isFixed = fixed;
        acceleration.set(0, 0, 0);
    }

    void update(float dt) {
        if (!isFixed) {
            velocity += acceleration * dt;
            position += velocity * dt;
        }
        acceleration.set(0, 0, 0);
    }

    void addForce(const ofVec3f& force) {
        if (!isFixed) {
            acceleration += force / mass;
        }
    }

    void draw() const {
        ofSetColor(color);
        ofDrawSphere(position, size);
    }
};