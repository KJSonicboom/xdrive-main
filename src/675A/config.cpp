#include "main.h"
using namespace pros;

Controller master (E_CONTROLLER_MASTER);

Motor left_front_motor(4, E_MOTOR_GEARSET_18, false);
Motor left_back_motor (12, E_MOTOR_GEARSET_18, false);
Motor right_front_motor (9, E_MOTOR_GEARSET_18, false);
Motor right_back_motor (20, E_MOTOR_GEARSET_18, false);

Motor_Group leftMotors({left_front_motor, left_back_motor}); 
Motor_Group rightMotors({right_front_motor, right_back_motor});

Motor_Group frontMotors({left_front_motor, right_front_motor});
Motor_Group backMotors({left_back_motor, right_back_motor});

IMU inertial_sensor(18);


lemlib::Drivetrain_t drivetrain {
    &leftMotors,
    &rightMotors,
    6.5,
    3.25,
    200
};

lemlib::OdomSensors_t sensors {
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    &inertial_sensor
};

// forward/backward PID
lemlib::ChassisController_t lateralController {
    10, // kP
    30, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    4, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    40 // slew rate
};
 
 
// create the chassis
lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);