#pragma once
#include "ofMain.h"
#include "PhysicsPoint.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    ofEasyCam cam;
    vector<PhysicsPoint> bodies;
    vector<PhysicsPoint> asteroids;  // Separate container for asteroids

    const float G = 0.5;          // Adjusted gravitational constant
    const float timeStep = 0.016;  // Normal timestep
};