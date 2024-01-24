#include "main.h"

//variables
double magnitude;
double angle;

//This function resets the drive sensors do fix something idk i trust jonah
void reset_drive_sensors(){
    leftMotors.tare_position();
    rightMotors.tare_position(); //I changed these to reset all the motors (does this change things?)
}

//Changing the curve functions changes the sens*

// Left curve function
double left_curve_function(double x) {return (powf(2.718, -(3 / 10)) + powf(2.718, (fabs(x) - 127) / 10) * (1 - powf(2.718, -(3 / 10)))) * x;}

// Right curve function
double right_curve_function(double x) {return (powf(2.718, -(3 / 10)) + powf(2.718, (fabs(x) - 127) / 10) * (1 - powf(2.718, -(3 / 10)))) * x;}

//Function to check if the joystick is within the threshold to avoid physical joystick problems
void checkThreshold(int x_dir, int y_dir, int rotation){

    int joystickThreshold = 5;
    
    //If the sticks are above the threshold then the bot is allowed to move
    if (abs(x_dir) > joystickThreshold || abs(y_dir) > joystickThreshold || abs(rotation) > joystickThreshold) {
        drive(x_dir, y_dir, rotation);
        //reset_drive_sensors();
    }

    else{ //This is where things might go wrong bc idk what im doing here
        leftMotors.move_voltage(0);
        rightMotors.move_voltage(0);
        leftMotors.set_brake_modes(E_MOTOR_BRAKE_HOLD);
        rightMotors.set_brake_modes(E_MOTOR_BRAKE_HOLD);
    }
}

//This is where the bot actually moves after everything w field orient
void drive(int x_dir, int y_dir, int rotation){
    magnitude = sqrt(pow(x_dir,2) + pow(y_dir, 2));
    angle = chassis.getPose(true).theta + atan2(y_dir, x_dir);
    x_dir = magnitude * cos(angle);
    y_dir = magnitude * sin(angle); // I don't understand this math

    left_front_motor.move_voltage((y_dir + x_dir + rotation) * (12000.0 / 127.0));  //why this number again?
    left_back_motor.move_voltage((y_dir - x_dir + rotation) * (12000.0 / 127.0)); 
    right_front_motor.move_voltage((-y_dir + x_dir + rotation) * (12000.00 / 127.0));
    right_back_motor.move_voltage((-y_dir - x_dir + rotation) *(12000.00 / 127.0));

    if(master.get_digital_new_press(DIGITAL_A)){
        inertial_sensor.reset();
    }
}

//Main function where everything comes together
void arcade_flipped(){

    while(true){

        int y_dir, x_dir, rotation;

        y_dir = right_curve_function(master.get_analog(ANALOG_RIGHT_Y));
        x_dir = right_curve_function(master.get_analog(ANALOG_RIGHT_X));
        rotation = left_curve_function(master.get_analog(ANALOG_LEFT_X));

        checkThreshold(x_dir, y_dir, rotation);

    }

}

//print pos to screen
void screenPos(){
	while (true){
		lemlib::Pose pose = chassis.getPose();
		pros::screen::print(TEXT_MEDIUM_CENTER, 2, "x: %f", pose.x);
		pros::screen::print(TEXT_MEDIUM_CENTER, 3, "y: %f", pose.y);
		pros::screen::print(TEXT_MEDIUM_CENTER, 4, "angle: %f", pose.theta);
		pros::delay(10);
	}
}
