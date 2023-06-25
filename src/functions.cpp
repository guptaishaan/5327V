#include "main.h"


pros::Controller controller (CONTROLLER_MASTER);
pros::Motor driveRightBack (2, true);
pros::Motor driveLeftBack (1);
pros::Motor driveRightFront (20, true);
pros::Motor driveLeftFront (11);

bool driveEnabled = true;

void brake()
{
	driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	driveRightBack.move_velocity(0);
	driveLeftBack.move_velocity(0);
	driveRightFront.move_velocity(0);
	driveLeftFront.move_velocity(0);
}

//SECTION 1: settings and variables
int currentX = 0;
int currentY = 0;
//constants
float kP = 0.021;
float kI = 0;
float kD = 0;

float tkP = 2.0;
float tkI = 2.0;
float tkD = 2.0;

float current_distance;
float total_distance;

float desired_turn;

//error LATERAL
float error;
float prev_error = 0.0;
float derivative;
float integral;

//error TURNING

float terror;
float tprev_error = 0.0;
float tderivative;
float tintegral;




int drive(float finalX, float finalY, float angle){


    while(driveEnabled){
        //position of motors
        int LFMotor = driveLeftFront.get_position();
        int LBMotor = driveLeftBack.get_position();
        int RFMotor = driveRightFront.get_position();
        int RBMotor = driveRightBack.get_position();
        //current positoin of motors
        int avepos = (LFMotor + LBMotor + RFMotor + RBMotor)/4;

        ///////////////////////////////////////
        //LATERAL MOVEMENT PID
        //////////////////////////////////////
        //bot designed location
        float total_distance = sqrtf(pow(finalX, 2) + pow(finalY, 2));
        //error values
        float error = total_distance - avepos; //may not be correct way of tracking error??? mainly confused on Motor posoitions and average position and error calc
        //testing if we have reached the location
        if (error == 0){
            driveEnabled = false;
        }
        else if (error > 1){
            integral = 0;
        }

        float derivative = error - prev_error;
        float integral = integral + error;        

        //adding it all up
        float power = (error*kP) + (integral*kI) + (derivative*kD);

        ///////////////////////////////////////
        //TURNING MOVEMENT PID
        //////////////////////////////////////

        //error values
        float terror = angle*(3.141592/180) - avepos; //may not be correct way of tracking error??? mainly confused on Motor posoitions and average position and error calc
        //testing if we have reached the location
        if (terror == 0){
            tintegral = 0;
        }

        float tderivative = terror - tprev_error;
        float tintegral = tintegral + terror;        

        //adding it all up
        float tpower = (terror*tkP) + (tintegral*tkI) + (tderivative*tkD);
        ///////////////////////////////////////////////////////////////////

        driveRightBack.move_velocity(power);
	    driveLeftBack.move_velocity(power);
	    driveRightFront.move_velocity(power);
	    driveLeftFront.move_velocity(power);


        prev_error = error;
        tprev_error = terror;
        pros::delay(15);
    }
    return 1;

}