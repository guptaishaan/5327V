#include "main.h"


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

double leftJoystick;
double rightJoystick;



void on_center_button() {}

/*void live_telemetry(void* param) {
  while (1) {
    telm_printf(1,"  LDPos=%f, RDPos=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
    telm_printf(2,"  LDVel=%f, RDVel=%f",left_drive_motors.getActualVelocity(),right_drive_motors.getActualVelocity());
    telm_printf(3,"  LDCur=%d, RDCur=%d",left_drive_motors.getCurrentDraw(),right_drive_motors.getCurrentDraw());
    telm_printf(4,"  BMode=%s",right_drive_motors.getBrakeMode() == okapi::AbstractMotor::brakeMode::hold ? "Hold" : "Coast");
    telm_printf(5,"  Left Vel=%3.0f, Right Vel=%3.0f",left_drive_motors.getActualVelocity(),right_drive_motors.getActualVelocity());

    pros::Task::delay(50);
  }
}*/

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::delay(50);
	driveRightBack.tare_position();
	driveLeftBack.tare_position();
	driveRightFront.tare_position();
	driveLeftFront.tare_position();
	gui();

	//pros::Task telm_task (live_telemetry, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "telm");

}

typedef enum motor_brake_mode_e {
  E_MOTOR_BRAKE_BRAKE = 1, // Motor short brakes when stopped
} motor_brake_mode_e_t;
/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void auton1(){

	driveRightBack.move_velocity(-127);
	driveRightFront.move_velocity(-127);
	driveLeftBack.move_velocity(127);
	driveLeftFront.move_velocity(127);	
	
}
void auton2(){

	driveRightBack.move_velocity(127);
	driveRightFront.move_velocity(127);
	driveLeftBack.move_velocity(-127);
	driveLeftFront.move_velocity(-127);	
}

void autonomous(){
}

	//not sure if this does what i want it to do



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

double sensing(int type, int input){
	double a = 1.0;
	double b = pow((128) , (1/127));
	double x = static_cast <double> (input);
	bool negativeval = false;
	if (x < 0)
	{
		x = abs(x);
		negativeval = true;
	}
	
	if (type==1)
	{
		x = (x);
	}
	else if (type==2)
	{
		x = a*pow(b,x) - a;
	}
	else if (type == 3)
	{
		x = (log((x+a)/a))/log(b);
	}
	else
	{
		x = x;
	}
	if (negativeval == true)
	{
		return(x * -1.0);
	}
	else
	{
		return(x);
	}
}


void opcontrol() {
	driveEnabled = false;
	pros::delay(5000);

	controller.rumble("- . -");

	while (true) {
		controller.set_text(1, 9, "Whats up dawg");


		leftJoystick = sensing(1, controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
    	rightJoystick = sensing(1, controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));

		driveRightBack.move(rightJoystick);
    	driveRightFront.move(rightJoystick);
    	driveLeftBack.move(leftJoystick);
    	driveLeftFront.move(leftJoystick);
	
		if ((leftJoystick==0) && (rightJoystick==0)){
			brake();
			}

		
			
		pros::delay(20);
	}
}
