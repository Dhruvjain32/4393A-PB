#include "main.h"
#include "lemlib/api.hpp"
#include "devices.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

void graphing() {
    lemlib::Pose currentPos = chassis.getPose();
    pros::screen::set_pen(0xffffff);
    pros::screen::fill_rect(0, 0, 480, 240);
    pros::screen::set_pen(0x000000);
    pros::screen::draw_line(0, 240 - 180, 480, 240 - 180);
    pros::screen::set_pen(0x00ff00);
    pros::screen::draw_line(0, 120, 480, 120);

    int x = 0;
    const int frameTime = 17; // ~60Hz

    while (true) {
        int startTime = pros::millis();

        currentPos = chassis.getPose();

        pros::screen::set_pen(0x0000ff);
        pros::screen::draw_pixel(x, -currentPos.theta + 240);

        pros::screen::set_pen(0xff0000);
        pros::screen::draw_pixel(x, -currentPos.y * 6 + 240);

        pros::screen::set_pen(0x00ff00);
        pros::screen::draw_pixel(x, -(leftDrive.get_voltage() / 1000) + 120);

        x++;
        // if (x >= 480) { // Reset when reaching the screen edge
        //     x = 0;
        //     pros::screen::set_pen(0xffffff);
        //     pros::screen::fill_rect(0, 0, 480, 240);
        // }

        int elapsed = pros::millis() - startTime;
        int delayTime = frameTime - elapsed;
        if (delayTime < 10) delayTime = 10; // prevent too fast updates
        pros::delay(delayTime);
    }
}



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
   // chassis.tunerInit(); // initialize the chassis tuner
    // print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
			// graphing();
            // print robot location to the brain screen
            displaySelection();
            // pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            // pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            // pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // delay to save resources
            pros::delay(50);
        }
    });

    pros::lcd::register_btn0_cb(on_left_button);
    pros::lcd::register_btn1_cb(on_center_button);
    pros::lcd::register_btn2_cb(on_right_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}


void competition_initialize() {}

void autonomous() {
switch (selectedAuton) {
        case Auton::redSAWP:
		    redSAWP();
            break;
        case Auton::redLeft:
            redLeft();
            break;
		case Auton::redRight:
			redRight();
			break;
        case Auton::blueSAWP:
            blueSAWP();
            break;
        case Auton::blueLeft:
            blueLeft();
            break;
        case Auton::blueRight: 
            blueRight();
            break;
        case Auton::skills: 
            skills();
            break;
		case Auton::testDrive:
            testDrive();
            break;
		case Auton::testTurn:
            testTurn();
            break;
        default:
            pros::lcd::print(3, "Invalid mode selected.");
            break;
    }
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	while (true) {

		if (!pros::competition::is_connected()) {
    		if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
      		pros::MotorBrake preference = pros::MotorBrake::coast;
      		autonomous();
      		leftDrive.set_brake_mode(preference);
      		rightDrive.set_brake_mode(preference);
			}
		}
        // get left y and right y positions
        int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        // int rightY = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

        // move the robot
        chassis.arcade(leftY, rightX);

        if(master.get_digital(DIGITAL_R1)) {
            intake.move(127);
            pivot.move(127);
            backScore.move(-127);
        } else if(master.get_digital(DIGITAL_L2)) {
            intake.move(127);
            pivot.move(-127);
            backScore.move(127);
        } else if (master.get_digital(DIGITAL_R2)) {
            intake.move(-127);
            pivot.move(0);
            backScore.move(0); 
        } else {
            intake.move(0);
            pivot.move(0);
            backScore.move(0); 
        }

        //Lifing Logic
        if(master.get_digital_new_press(DIGITAL_UP)) {
            frontScorePneumatic.toggle();
            backScorePneumatic.toggle();
        }

        if(master.get_digital_new_press(DIGITAL_RIGHT)) {
            if(frontScorePneumatic.is_extended() == false) {
                frontScorePneumatic.toggle();
                backScorePneumatic.toggle();
            }
            wing.toggle();
        }

        if(frontScorePneumatic.is_extended() == false) {
            wing.retract();
        }

        if(master.get_digital_new_press(DIGITAL_L1)) {
            storing.toggle();
        }


        if(master.get_digital_new_press(DIGITAL_A)) {
            
            if(frontScorePneumatic.is_extended() == false) {
                frontScorePneumatic.extend();
                backScorePneumatic.extend();
            }
            loader.toggle();
        }

        // if(master.get_digital_new_press(DIGITAL_L2)) {
        //     storing.toggle();
        // }

        if(master.get_battery_level() < 20 || pros::battery::get_capacity() < 30) {
            master.rumble("..");
        }
        // delay to save resources
        pros::delay(10);
    }

}