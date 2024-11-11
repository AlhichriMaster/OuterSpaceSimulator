#include "ofApp.h"
void ofApp::setup() {
    ofSetFrameRate(60);
    ofEnableDepthTest();

    cam.setPosition(200, 200, 200);
    cam.lookAt(ofVec3f(0, 0, 0));

    // Central body (white)
    bodies.push_back(PhysicsPoint(
        ofVec3f(0, 0, 0),
        ofVec3f(0, 0, 0),
        1000,                     // Increased mass
        20,
        ofColor::white,
        true
    ));

    // Red planet
    bodies.push_back(PhysicsPoint(
        ofVec3f(100, 0, 0),
        ofVec3f(0, 8, 0),        // Increased velocity
        2,                        // Slightly more mass
        20,
        ofColor::red,
        false
    ));

    // Green planet
    bodies.push_back(PhysicsPoint(
        ofVec3f(0, 100, 0),
        ofVec3f(-8, 0, 0),
        2,
        20,
        ofColor::green,
        false
    ));

    // Blue planet
    bodies.push_back(PhysicsPoint(
        ofVec3f(0, 0, 100),
        ofVec3f(8, 8, 0),
        2,
        20,
        ofColor::blue,
        false
    ));

    // Create more asteroids with varied orbits
    const int numAsteroids = 100;  // Increased number
    for (int i = 0; i < numAsteroids; i++) {
        float radius = ofRandom(40, 180);
        float theta = ofRandom(TWO_PI);
        float phi = ofRandom(TWO_PI);

        ofVec3f pos(
            radius * cos(theta) * sin(phi),
            radius * sin(theta) * sin(phi),
            radius * cos(phi)
        );

        // More varied velocities for interesting orbits
        ofVec3f vel = pos.getCrossed(ofVec3f(0, 1, 0)).normalize() * ofRandom(3, 6);
        if (ofRandom(1.0) > 0.5) vel *= -1;  // Some asteroids orbit the other way

        asteroids.push_back(PhysicsPoint(
            pos,
            vel,
            0.2,                    // Increased mass slightly
            2,                      // Smaller size for better visibility
            ofColor(200, 200, 200),
            false
        ));
    }
}

void ofApp::update() {
    // Update planets with damping for stability
    for (size_t i = 0; i < bodies.size(); i++) {
        if (!bodies[i].isFixed) {
            // Force from central body
            ofVec3f r = bodies[0].position - bodies[i].position;
            float dist = r.length();

            if (dist > 10.0) {
                float forceMag = (G * bodies[i].mass * bodies[0].mass) / (dist * dist);
                bodies[i].addForce(r.getNormalized() * forceMag);
            }

            // Small damping force for stability
            bodies[i].velocity *= 0.999;

            bodies[i].update(timeStep);

            // Softer boundary handling
            if (bodies[i].position.length() > 300) {
                ofVec3f norm = bodies[i].position.getNormalized();
                bodies[i].position = norm * 300;
                // Reflect velocity with some energy loss
                bodies[i].velocity = (bodies[i].velocity - 2 * bodies[i].velocity.dot(norm) * norm) * 0.8;
            }
        }
    }

    // Update asteroids
    for (auto& asteroid : asteroids) {
        // Force from central body and other major bodies
        ofVec3f totalForce(0, 0, 0);

        // Force from central body
        ofVec3f r = bodies[0].position - asteroid.position;
        float dist = r.length();

        if (dist > 5.0) {
            float forceMag = (G * asteroid.mass * bodies[0].mass) / (dist * dist);
            totalForce += r.getNormalized() * forceMag;
        }

        // Small influence from planets
        for (size_t i = 1; i < bodies.size(); i++) {
            ofVec3f r = bodies[i].position - asteroid.position;
            float dist = r.length();
            if (dist > 5.0) {
                float forceMag = (G * asteroid.mass * bodies[i].mass) / (dist * dist) * 0.1;
                totalForce += r.getNormalized() * forceMag;
            }
        }

        asteroid.addForce(totalForce);
        asteroid.velocity *= 0.999;  // Small damping
        asteroid.update(timeStep);

        // Boundary handling
        if (asteroid.position.length() > 300) {
            ofVec3f norm = asteroid.position.getNormalized();
            asteroid.position = norm * 300;
            asteroid.velocity = (asteroid.velocity - 2 * asteroid.velocity.dot(norm) * norm) * 0.8;
        }
    }
}

void ofApp::draw() {
    ofBackground(0);

    cam.begin();

    ofDrawAxis(200);

    // Draw main bodies
    for (auto& body : bodies) {
        body.draw();
    }

    // Draw asteroids with additive blending
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for (auto& asteroid : asteroids) {
        asteroid.draw();
    }
    ofDisableBlendMode();

    cam.end();
}