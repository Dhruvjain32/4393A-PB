#pragma once

#include "main.h"
#include "lemlib/api.hpp"

// \\inline pros::Controller master;

// Drivetrain Side defs
inline pros::MotorGroup leftDrive({-18, 8, -9}, pros::MotorGear::blue, pros::MotorUnits::deg);
inline pros::MotorGroup rightDrive({7, -6, 21}, pros::MotorGear::blue, pros::MotorUnits::deg);

inline lemlib::Drivetrain drivetrain(&leftDrive, // left motor group
                              &rightDrive, // right motor group
                              10.75, // track width
                              lemlib::Omniwheel::NEW_325, // wheel diameter
                              450, // rpm
                              2); // horizontal drift

// Other System Motors
inline pros::Motor intake(-4, pros::MotorGear::blue, pros::MotorUnits::deg);
inline pros::Motor pivot(16, pros::MotorGear::green, pros::MotorUnits::deg);
inline pros::Motor backScore(5, pros::MotorGear::green, pros::MotorUnits::deg);


// Sensor Defs
inline pros::Rotation horizontalOdom(10);
inline pros::Rotation verticalOdom(20);
inline pros::Imu imu(19);

inline lemlib::TrackingWheel horizontal_tracking_wheel(&horizontalOdom, 2.0, -0.5);
inline lemlib::TrackingWheel vertical_tracking_wheel(&verticalOdom, 2.0, -.7);

inline lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
inline lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP) //63.65
                                              0, // integral gain (kI)
                                              52, // derivative gain (kD) //11.3
                                              0, // anti windup
                                              .5, // small error range, in inches                 // make this .5 inches
                                              100, // small error range timeout, in milliseconds   // this is fine
                                              2, // large error range, in inches                   // make this 2 inches
                                              300, // large error range timeout, in milliseconds   // make this 300ms
                                              0 // maximum acceleration (slew)
);

// angular PID controller
inline lemlib::ControllerSettings angular_controller(5.8, // proportional gain (kP) // 5.00 // THIS IS TOO HIGH RIGHT NOW, LOWER IT
                                              0.001, // integral gain (kI)
                                              55, // derivative gain (kD) // 55.3
                                              0, // anti windup
                                              1, // small error range                          // make this 1 degree
                                              100, // small error range timeout, in milliseconds // make this 100ms
                                              1.5, // large error range, in inches               // make this 2 degrees
                                              500, // large error range timeout, in milliseconds // make this 300ms
                                              0 // maximum acceleration (slew)
);

// kP 1.8
// kD 11.3
// these work for 90, try scaling by ~50 to test for higher values


inline lemlib::ExpoDriveCurve throttle_curve(5, // joystick deadband out of 127
                                     5, // minimum output where drivetrain will move out of 127
                                     1.014 // expo curve gain
);

// input curve for steer input during driver control
inline lemlib::ExpoDriveCurve steer_curve(5, // joystick deadband out of 127
                                  5, // minimum output where drivetrain will move out of 127
                                  1.014 // expo curve gain
);

inline lemlib::Chassis chassis(drivetrain,
                        lateral_controller,
                        angular_controller,
                        sensors,
                        &throttle_curve, 
                        &steer_curve
);

// Pneumatics
inline pros::adi::Pneumatics wing('G', false);
inline pros::adi::Pneumatics backScorePneumatic('H', true);
inline pros::adi::Pneumatics loader('E', false);
inline pros::adi::Pneumatics frontScorePneumatic('D', true);
inline pros::adi::Pneumatics storing('F', false);
