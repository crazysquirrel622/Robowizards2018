/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/


/* Team #: 522
 * Game Year: 2018
 * Authors: Kevin Sheridan
 *
 *Hardware List:
 * -8 Spark Motor Controllers
 * -1 Servo
 * -2 Limit Switches
 * -4 Joysticks(Driver Station)
*/







#include <iostream>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <DriverStation.h>

#include <Drive/DifferentialDrive.h>															//Differential Drive include
#include <Spark.h>																				//Spark Motor Controller include
#include <SpeedControllerGroup.h>																//Speed Controller Group include

#include <Joystick.h>																			//Joystick commands include
#include <Servo.h>																				//Servo commands include
#include <DigitalInput.h>																		//Digital Inputs (limit switch) include
#include <Timer.h>																				//Timer and Wait include

class Robot : public frc::IterativeRobot {
public:
void RobotInit() {
	m_chooser.AddDefault(kAutoNameDefault, kAutoNameDefault);									//Create the default autonomous for the Dashboard
	m_chooser.AddObject(kDSRight, kDSRight);													//Create the Right DS autonomous for the Dahboard
	m_chooser.AddObject(kDSLeft, kDSLeft);														//Create the Left DS autonomous for the Dahboard
	m_chooser.AddObject(kDSCenter, kDSCenter);													//Create the Center DS autonomous for the Dahboard
	frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
	myDrive.SetExpiration(0.1);
	Timer.Start();
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void AutonomousInit() {
	m_autoSelected = m_chooser.GetSelected();													//Read what autonomous is selected
	m_autoSelected = SmartDashboard::GetString("Auto Selector", kAutoNameDefault);
	std::cout << "Auto selected: " << m_autoSelected << std::endl;
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();						//Check which side of the scales is for the robot's alliance (field feeds the info in the form of a string of 3 characters eg LRL)
	Timer.Reset();																				//Reset the timer
	Timer.Start();																				//Start the timer
}

void AutonomousPeriodic() {
	if (Timer.Get()<2.0){																		//The Timer allows autonmous code to only execute once instead of looping

				if((m_autoSelected != kAutoNameDefault)){										//Are we on Blue Alliance? and is any non default autonomous selected?
					if (m_autoSelected == kDSRight){											//Code for right side driver station autom
						if (gameData[1] == 'R'){												//Is the scoring platform of the center scale on the right for the alliance?
							//desired goal is to put a power cube in the center scale if the alliance side of the scale is on the right
						}
						else if (gameData[0] == 'R'){											//Is the scoring platform of the alliance scale on the right for the alliance?
							//if the center scale does not have the alliance side on the right check the alliance scale to see if the alliance side is on the right side and place a power cube
						}
						else{
							//if neither of the above are correct pick up a power cube and be the in center between the center scale and alliance scale.
						}
					}
					else if (m_autoSelected == kDSLeft){										//code for left side driver station autom
						if (gameData[1] == 'L') {
							//same as above if but for the left side
						}
						else if (gameData[0] == 'L'){
							//same as above else if but for the left side
						}
						else{
							//same as above else
						}
					}
					else if (m_autoSelected == kDSCenter){										//code for center driver station autom
						if (gameData[0] == 'L'){
							//if the scoring platform for the alliance scale is on the left place a power cube on it
						}
						else{
							//else we put a power cube on the right side of the alliance scale (as the scoring platform for the alliance has to be on the right)
						}
					}
				}

				else{																			//This is default autom. if any of the others are selected run this.
								//Example Autom code: (to be moved)
								//most likely the goal of the default is going to be to raise the pulley to drop the rollers and then drop the pulley down to the ground so a cube can be picked up.
								myDrive.TankDrive(0.75,0.75);									//Start driving forward at 75% (values are on a scale from 0 to 1, with 1 being full speed) speed
								frc::Wait(0.25);												//Wait X seconds before going to the next command

								Pulley.Set(1);													//Turn on the pulley
								frc::Wait(1.0);
								Pulley.Set(0);													//Stop Pulley
								frc::Wait(1.5);
								myDrive.TankDrive(0,0);											//Stop moving
								}
			}
			Timer.Stop();
}

void TeleopInit() {}

void TeleopPeriodic() {
	while (IsOperatorControl() && IsEnabled()){													//Command 1 checks if teleop is enabled command 2 checks if robot is enabled (both must return true)
			myDrive.TankDrive(dLeft.GetY(), dRight.GetY()); 									//Get the Y values from both driver sticks and feed the values to move the robot as tank drive (ie LEft stick controls left side, right stick controls right side)

			if (cLeft.GetRawButton(1) && (pulleyUpper.Get())){ 									//Get the Y value from controller stick and check if the upper limit switch is not active (high if open, low if closed)
				Pulley.Set(1);																	//Command the Pully to operate in the forward direction
			}
			else if (cLeft.GetRawButton(2) && (pulleyLower.Get())){

				Pulley.Set(-1);																	//Command the Pulley to operate in the reverse direction
			}
			else {
				Pulley.Set(0);																	//Turn Pulley off
			}

			Rollers.Set(cLeft.GetY());
			SmartDashboard::PutNumber("Rollers Speed", cLeft.GetY());

			if (cRight.GetY()>0.05){
				Whinch.Set(1);
			}
			else if (cRight.GetY()< -0.05){
				Whinch.Set(-1);
			}
			else {
				Whinch.Set(0.0);
			}

			}

			if (cRight.GetRawButton(1)){
				Hang.Set(1);
			}
			else {
				Hang.Set(0);
			}
}

void TestPeriodic() {}

private:
	frc::LiveWindow& m_lw = *LiveWindow::GetInstance();
	frc::SendableChooser<std::string> m_chooser;
	const std::string kAutoNameDefault = "Default";
	const std::string kDSRight = "Right Driver Station";
	const std::string kDSLeft = "Left Driver Station";
	const std::string kDSCenter = "Middle Driver Station";
	std::string m_autoSelected;
	std::string gameData;

	frc::Spark frontLeft{0};   																	//Front Left Drive Spark Controller Decleration
	frc::Spark frontRight{1};  																	//Front Right Drive Spark Controller Decleration
	frc::Spark backLeft{2};    																	//Back Left Drive Spark Controller Decleration
	frc::Spark backRight{3};   																	//Back Right Drive Spark Controller Decleration
	frc::Joystick dLeft{0};    																	//Left Driver Joystick Decleration
	frc::Joystick dRight{1};   																	//Right Driver Joystick Decleration
	frc::Joystick cLeft{2};    																	//Left Controller Joystick Decleration
	frc::Joystick cRight{3};   																	//Right Controller Joystick Decleration
	frc::SpeedControllerGroup Left{frontLeft, backLeft};										//Declare the Controller Group Left and bind the two left side Sparks to it
	frc::SpeedControllerGroup Right{frontRight, backRight};										//Declare the Controller Group Right and bind the two right side Sparks to it
	frc::DifferentialDrive myDrive{Left, Right};												//Declare the Differential Drive and use the Left and Right Motor Controller Groups
	frc::Spark Pulley{6};																		//Declare the Relay Controlling the Pulley
	frc::Spark RollerR{4};																		//Declare the Right Spark Controller of the Rollers
	frc::Spark RollerL{5};																		//Declare the Left Spark Controller of the Rollers
	frc::SpeedControllerGroup Rollers{RollerL, RollerR};										//Declare the Controller Group for the Rollers and assign the left and right rollor Sparks to the group
	frc::Servo Hang{2};																			//Declare the Servo Controlling the locking mechanism for hanging
	frc::Spark Whinch{7};																		//Declare the Relay that locks thhe Hoist mechanism
	frc::DigitalInput pulleyLower{0};															//Declare the limit switch used as the upper limit on the pulley system
	frc::DigitalInput pulleyUpper{1};															//Declare the limit switch used as the lower limit on the pulley system
	frc::Timer Timer;																			//Declare the timer used for autonomous

};

START_ROBOT_CLASS(Robot)
