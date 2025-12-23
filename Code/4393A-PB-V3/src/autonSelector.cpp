#include "autonSelector.hpp"
#include "devices.h"
#include "main.h"

Auton selectedAuton = Auton::skills;

static std::string formatDouble(double val, int decimals = 1) {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(decimals) << val;
    return ss.str();
}

std::string getLeftDTTemp() {
    auto motors = leftDrive.get_temperature_all();
    if (motors.empty()) return "N/A";
    double sum = 0.0;
    for (double t : motors) sum += t;
    double avg = sum / motors.size();                 // use double
    double rounded = std::round(avg * 10.0) / 10.0;   // round to 1 decimal
    return formatDouble(rounded, 1);                  // "12.3" (not "12.300000")
}

std::string getRightDTTemp() {
    auto motors = rightDrive.get_temperature_all();
    if (motors.empty()) return "N/A";
    double sum = 0.0;
    for (double t : motors) sum += t;
    double avg = sum / motors.size();
    double rounded = std::round(avg * 10.0) / 10.0;
    return formatDouble(rounded, 1);
}

void displaySelection() {
    pros::lcd::set_text(0, "Auton: " + getAutonName(selectedAuton));
    pros::lcd::print(1, "X: %f", chassis.getPose().x); // x
    pros::lcd::print(2, "Y: %f", chassis.getPose().y); // y
    pros::lcd::print(3, "Theta: %f", chassis.getPose().theta); // heading
    pros::lcd::set_text(4, "LeftDT Temp: " + getLeftDTTemp() + " | RightDT Temp: " + getRightDTTemp());
    pros::lcd::set_text(5, "11w: " + formatDouble(std::round(intake.get_temperature(0)*10.0)/10.0, 1)
                        + " | 5.5w: " + formatDouble(std::round(intake.get_temperature(1)*10.0)/10.0, 1)
                        + " | Pivot: " + formatDouble(std::round(pivot.get_temperature()*10.0)/10.0, 1));
	pros::lcd::print(7, "     Prev       Confirm      Next ");
}

std::string getAutonName(Auton mode) {
    switch (mode) {
        case Auton::redLeft: return "Red Left";
        case Auton::redRight: return "Red Right";
        case Auton::redSAWP: return "Red SAWP";
        case Auton::blueLeft: return "Blue Left";
        case Auton::blueRight: return "Blue Right";
        case Auton::blueSAWP: return "Blue SAWP";
        case Auton::testDrive: return "testDrive";
        case Auton::testTurn: return "testTurn";
        case Auton::skills: return "Skills";
        default: return "Unknown";
    }
}

void on_left_button() {
    // autonMutex.take();
    int modeCount = static_cast<int>(Auton::skills) + 1;
    selectedAuton = static_cast<Auton>((static_cast<int>(selectedAuton) - 1 + modeCount) % modeCount);
    
    // Update screen immediately
    pros::lcd::set_text(0, "Auton: " + getAutonName(selectedAuton));
    // autonMutex.give();

}

void on_center_button() {
    pros::lcd::set_text(0, "Confirmed: " + getAutonName(selectedAuton));
}

void on_right_button() {
    // autonMutex.take();
    int modeCount = static_cast<int>(Auton::skills) + 1;
    selectedAuton = static_cast<Auton>((static_cast<int>(selectedAuton) + 1) % modeCount);
    
    // Update screen immediately
    pros::lcd::set_text(0, "Auton: " + getAutonName(selectedAuton));
    // autonMutex.give();

}