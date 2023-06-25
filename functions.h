#ifndef functions_H_
#define functions_H_

#include "main.h"
//Defining motors and vrc related parts
extern pros::Motor driveLeftFront;
extern pros::Motor driveLeftBack;
extern pros::Motor driveRightFront;
extern pros::Motor driveRightBack;
extern pros::IMU inertial_sensor;
extern pros::Controller controller;

// some position defintions

extern bool driveEnabled;

//some function definitions
//not sure what these will be for yet, seems to be important though.
extern void move(float voltage);
extern void rotate(float angle);

//mainly for pid
extern int drive(float finalx, float finaly, float angle);
//E-BRAKES
extern void brake();

#endif

