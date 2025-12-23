#include "main.h"
#include "autons.hpp"

double loaderTime = 750;

void moveStraight(float length, int timeout, lemlib::MoveToPointParams params) {
    if (chassis.isInMotion()) chassis.waitUntilDone();
    params.forwards = length > 0;
    lemlib::Pose pose = chassis.getPose();
    chassis.moveToPoint(pose.x + length * sin(lemlib::degToRad(pose.theta)),
                           pose.y + length * cos(lemlib::degToRad(pose.theta)), timeout, params);
}

void scoreFront() {
    intake.move(127);
    pivot.move(127);
    backScore.move(0);
}

void scoreBack() {
    intake.move(127);
    pivot.move(-127);
    backScore.move(127);
}

void scoreLow() {
    intake.move(-127);
    pivot.move(-127);
    backScore.move(0);
}

void heightHigh() {
    frontScorePneumatic.extend();
    backScorePneumatic.extend();
}

void heightMiddle() {
    frontScorePneumatic.retract();
    backScorePneumatic.retract();
}

void motorStore() {
    intake.move(127);
    pivot.move(-127);
    backScore.move(-127);
}

void stopScore() {
    intake.move(0);
    pivot.move(0);
    backScore.move(0);
}

void testDrive() {
    moveStraight(24, 10000, {.forwards = true, .maxSpeed = 110});
    pros::delay(10000);
}
void testTurn() {
    chassis.turnToHeading(90, 100000, {.maxSpeed = 110});
    pros::delay(10000);
    chassis.turnToHeading(45, 100000, {.maxSpeed = 110});
    pros::delay(10000);
    chassis.turnToHeading(0, 100000, {.maxSpeed = 110});
}
void blueSAWP() {
    chassis.setPose(0, 0, 270);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);


    // angle self with loader, turn storing on
    moveStraight(32, 1700, {.forwards = true, .maxSpeed = 110});



}
void blueLeft() {
    chassis.setPose(0, 0, 270);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

    // angle self with loader, turn storing on
    moveStraight(34, 1700, {.forwards = true, .maxSpeed = 110});
    motorStore(); // turn on storing  with the motors
    chassis.turnToHeading(180, 1000, {});
    
    // grab loader, turn tongue on and off
    loader.toggle(); //enabled
    moveStraight(15.25, 1000, {.forwards = true, .maxSpeed = 70, .earlyExitRange = 2}); // drive into match loader 
    moveStraight(-2, 300, {.forwards = false, .maxSpeed = 127});
    pros::delay(750);
    loader.toggle(); // disabled

    // move away from loader
    moveStraight(-26, 1000, {.forwards = false, .maxSpeed = 110}); // check this distance, it needs to back into the goal at the right distance
    pros::delay(250);

    // drive to the goal, turn storing off, and score
    
    // storing.toggle(); // disabled  
    intake.move(-127);
    pros::delay(200);
    scoreBack();
    pros::delay(2250);
    moveStraight(20, 1000, {.forwards = false, .maxSpeed = 110});
    // storing.toggle();
    heightMiddle();
    motorStore();

    // back away from the goal
    pros::delay(1250);
    chassis.turnToHeading(48, 1000, {.direction = AngularDirection::CCW_COUNTERCLOCKWISE});
    moveStraight(42, 1500, {.forwards = true, .maxSpeed = 55});
    scoreFront();
    moveStraight(16, 1500, {.forwards = true, .maxSpeed = 80});
    pros::delay(3050);
    

}
void blueRight() {
chassis.setPose(0, 0, 270);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

    // angle self with loader, turn storing on
    moveStraight(32, 1700, {.forwards = true, .maxSpeed = 110});
    storing.toggle(); // enabled
    chassis.turnToHeading(180, 1000, {});
    
    // grab loader, turn tongue on and off
    loader.toggle(); //enabled
    intake.move(127);
    pivot.move(127);
    moveStraight(15.75, 1000, {.forwards = true, .maxSpeed = 70, .earlyExitRange = 2}); // drive into match loader //15.5 is working, check beforer match
    moveStraight(-1.5, 300, {.forwards = false, .maxSpeed = 127});
    pros::delay(750);
    loader.toggle(); // disabled

    // move away from loader
    moveStraight(-12, 1000, {.forwards = false, .maxSpeed = 110});
    pros::delay(250);

    
    // turn to goal, and stop pivot movement
    chassis.turnToHeading(0, 1200, {.direction = AngularDirection::CW_CLOCKWISE});
    pivot.move(127);
    intake.move(127);

    // drive to the goal, turn storing off, and score
    moveStraight(15, 1000, {.forwards = true, .maxSpeed = 110});
    pros::delay(700);
    storing.toggle(); // disabled  
    intake.move(-127);
    pros::delay(200);
    intake.move(0);
    pivot.move(0);
    pros::delay(2000);

    storing.toggle();

    // back away from the goal
    moveStraight(-13.5, 1000, {.forwards = false, .maxSpeed = 110});
    chassis.turnToHeading(-50, 1000, {.direction = AngularDirection::CW_CLOCKWISE});
    moveStraight(35, 1500, {.forwards = true, .maxSpeed = 55});
    pivot.move(-127);
    moveStraight(16, 1500, {.forwards = true, .maxSpeed = 80});
    pros::delay(1050);
    intake.move(-127);
    pros::delay(2000);
    storing.extend();
}
void redSAWP() {
    chassis.setPose(0, 0, 270);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);


    // angle self with loader, turn storing on
    moveStraight(32, 1700, {.forwards = true, .maxSpeed = 110});
    storing.toggle(); // enabled
    chassis.turnToHeading(180, 1000, {});
    
    // grab loader, turn tongue on and off
    loader.toggle(); //enabled
    intake.move(127);
    pivot.move(127);
    moveStraight(15.75, 1000, {.forwards = true, .maxSpeed = 70, .earlyExitRange = 2}); // drive into match loader //15.5 is working, check beforer match
    moveStraight(-1.5, 300, {.forwards = false, .maxSpeed = 127});
    pros::delay(750);
    loader.toggle(); // disabled

    // move away from loader
    moveStraight(-12, 1000, {.forwards = false, .maxSpeed = 110});
    pros::delay(250);

    
    // turn to goal, and stop pivot movement
    chassis.turnToHeading(0, 1200, {.direction = AngularDirection::CW_CLOCKWISE});
    pivot.move(127);
    intake.move(127);

    // drive to the goal, turn storing off, and score
    moveStraight(15, 1000, {.forwards = true, .maxSpeed = 110});
    pros::delay(700);
    storing.toggle(); // disabled  
    intake.move(-127);
    pros::delay(200);
    intake.move(127);
    pivot.move(127);
    pros::delay(2000);

    storing.toggle();

    // back away from the goal
    moveStraight(-13.5, 1000, {.forwards = false, .maxSpeed = 110});
    chassis.turnToHeading(50, 1000, {.direction = AngularDirection::CW_CLOCKWISE});
    moveStraight(35, 1500, {.forwards = true, .maxSpeed = 55});
    pivot.move(-127);
    moveStraight(16, 1500, {.forwards = true, .maxSpeed = 80});
    pros::delay(3050);
        storing.extend();


}
void redLeft() {
chassis.setPose(0, 0, 270);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

    // angle self with loader, turn storing on
    moveStraight(32, 1700, {.forwards = true, .maxSpeed = 110});
    storing.toggle(); // enabled
    chassis.turnToHeading(180, 1000, {});
    
    // grab loader, turn tongue on and off
    loader.toggle(); //enabled
    intake.move(127);
    pivot.move(127);
    moveStraight(15.75, 1000, {.forwards = true, .maxSpeed = 70, .earlyExitRange = 2}); // drive into match loader //15.5 is working, check beforer match
    moveStraight(-1.5, 300, {.forwards = false, .maxSpeed = 127});
    pros::delay(750);
    loader.toggle(); // disabled

    // move away from loader
    moveStraight(-12, 1000, {.forwards = false, .maxSpeed = 110});
    pros::delay(250);

    
    // turn to goal, and stop pivot movement
    chassis.turnToHeading(0, 1200, {.direction = AngularDirection::CW_CLOCKWISE});
    pivot.move(127);
    intake.move(127);

    // drive to the goal, turn storing off, and score
    moveStraight(15, 1000, {.forwards = true, .maxSpeed = 110});
    pros::delay(700);
    storing.toggle(); // disabled  
    intake.move(-127);
    pros::delay(200);
    intake.move(127);
    pivot.move(127);
    pros::delay(2000);

    storing.toggle();

    // back away from the goal
    moveStraight(-13.5, 1000, {.forwards = false, .maxSpeed = 110});
    chassis.turnToHeading(50, 1000, {.direction = AngularDirection::CW_CLOCKWISE});
    moveStraight(35, 1500, {.forwards = true, .maxSpeed = 55});
    pivot.move(-127);
    moveStraight(16, 1500, {.forwards = true, .maxSpeed = 80});
    pros::delay(3050);
    storing.extend();

}


void redRight() {
    chassis.setPose(0, 0, 270);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

    // angle self with loader, turn storing on
    moveStraight(32, 1700, {.forwards = true, .maxSpeed = 110});
    storing.toggle(); // enabled
    chassis.turnToHeading(180, 1000, {});
    
    // grab loader, turn tongue on and off
    loader.toggle(); //enabled
    intake.move(127);
    pivot.move(127);
    moveStraight(15.75, 1000, {.forwards = true, .maxSpeed = 70, .earlyExitRange = 2}); // drive into match loader //15.5 is working, check beforer match
    moveStraight(-1.5, 300, {.forwards = false, .maxSpeed = 127});
    pros::delay(750);
    loader.toggle(); // disabled

    // move away from loader
    moveStraight(-12, 1000, {.forwards = false, .maxSpeed = 110});
    pros::delay(250);

    
    // turn to goal, and stop pivot movement
    chassis.turnToHeading(0, 1200, {.direction = AngularDirection::CW_CLOCKWISE});
    pivot.move(127);
    intake.move(127);

    // drive to the goal, turn storing off, and score
    moveStraight(15, 1000, {.forwards = true, .maxSpeed = 110});
    pros::delay(700);
    storing.toggle(); // disabled  
    intake.move(-127);
    pros::delay(200);
    intake.move(0);
    pivot.move(0);
    pros::delay(2000);

    storing.toggle();

    // back away from the goal
    moveStraight(-13.5, 1000, {.forwards = false, .maxSpeed = 110});
    chassis.turnToHeading(-50, 1000, {.direction = AngularDirection::CW_CLOCKWISE});
    moveStraight(35, 1500, {.forwards = true, .maxSpeed = 55});
    pivot.move(-127);
    moveStraight(16, 1500, {.forwards = true, .maxSpeed = 80});
    pros::delay(1050);
    intake.move(-127);
    pros::delay(2000);
    storing.extend();
}
void skills() {
    chassis.setPose(0, 0, 270);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

    // angle self with loader, turn storing on
    moveStraight(32, 1700, {.forwards = true, .maxSpeed = 110});
    storing.toggle(); // enabled
    chassis.turnToHeading(180, 1000, {});
    
    // grab loader, turn tongue on and off
    loader.toggle(); //enabled
    intake.move(127);
    pivot.move(127);
    moveStraight(15.75, 1000, {.forwards = true, .maxSpeed = 70, .earlyExitRange = 2}); // drive into match loader //15.5 is working, check beforer match
    moveStraight(-1.5, 300, {.forwards = false, .maxSpeed = 127});
    pros::delay(1500);
    loader.toggle(); // disabled`
    intake.move(0);
    pivot.move(0);

    // move away from loader
    moveStraight(-12, 1000, {.forwards = false, .maxSpeed = 110});
    pros::delay(250);

    
    // turn to goal, and stop pivot movement
    chassis.turnToHeading(0, 1200, {.direction = AngularDirection::CW_CLOCKWISE});
    // pivot.move(127);
    // intake.move(127);

    // drive to the goal, turn storing off, and score
    moveStraight(15, 1000, {.forwards = true, .maxSpeed = 110});
    pros::delay(700);
    storing.toggle(); // disabled  
    intake.move(-127);
    pros::delay(200);
    intake.move(127);
    pivot.move(127);
    pros::delay(3500);

    storing.toggle();

    // back away from the goal
    moveStraight(-13.5, 1000, {.forwards = false, .maxSpeed = 110});
    chassis.turnToHeading(50, 1000, {.direction = AngularDirection::CW_CLOCKWISE});
    moveStraight(35, 1500, {.forwards = true, .maxSpeed = 55});
    pivot.move(-127);
    moveStraight(16, 1500, {.forwards = true, .maxSpeed = 80});
    pros::delay(3050);
    storing.extend();

}