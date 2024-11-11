# Outer Space Physics Simulator

A simple gravitational physics simulator built with openFrameworks, demonstrating basic orbital mechanics and particle systems.

##Author: Youssuf Hichri

## Overview

This project creates a space-like environment with a central massive body (simulating a black hole or star), three orbiting planets, and a field of asteroids. All bodies interact through gravitational forces, creating a dynamic solar system simulation.

## Features

- Newtonian gravitational physics simulation using Euler integration
- One central fixed massive body
- Three orbiting planetary bodies with distinct colors
- Field of ~100 asteroids affected by gravity
- Interactive 3D camera controls
- Basic collision boundaries to keep objects in view

## Controls

- Left mouse button + drag: Rotate camera view
- Right mouse button + drag: Zoom in/out
- Middle mouse button + drag: Pan camera

## Physics Implementation

The simulation implements a simplified version of Newton's law of universal gravitation:
- Force = G * (m1 * m2) / r²
- Where G is the gravitational constant, m1 and m2 are the masses of the bodies, and r is the distance between them
- Euler integration is used to update positions and velocities

## Building and Running

1. Make sure you have openFrameworks installed
2. Clone this repository into your openFrameworks apps folder
3. Use the project generator to create project files
4. Build and run using your preferred IDE

## Dependencies

- openFrameworks 0.12.0 or later
- C++11 or later

## Technical Notes

- The simulation uses scaled units to keep the visualization meaningful
- Boundary conditions prevent bodies from escaping the visible area
- Small damping forces are applied to maintain stability
- Collision detection is not implemented to maintain performance
