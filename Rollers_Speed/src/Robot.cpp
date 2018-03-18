/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Spark.h>												//Spark Motor Controller include
#include <SpeedControllerGroup.h>								//Speed Controller Group include
#include <Relay.h>

#include <Joystick.h>

#include <iostream>
#include <string>

#include <SmartDashboard/SmartDashboard.h>

class Robot : public frc::IterativeRobot {
public:
void RobotInit() {
	m_chooser.AddDefault(kAutoNameDefault, kAutoNameDefault);
	m_chooser.AddObject(kAutoNameCustom, kAutoNameCustom);
	frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
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
	m_autoSelected = m_chooser.GetSelected();
	// m_autoSelected = SmartDashboard::GetString(
	// 		"Auto Selector", kAutoNameDefault);
	std::cout << "Auto selected: " << m_autoSelected << std::endl;

	if (m_autoSelected == kAutoNameCustom) {
		// Custom Auto goes here
	} else {
		// Default Auto goes here
	}
}

void AutonomousPeriodic() {
	if (m_autoSelected == kAutoNameCustom) {
		// Custom Auto goes here
	} else {
		// Default Auto goes here
	}
}

void TeleopInit() {}

void TeleopPeriodic() {
	while (IsOperatorControl() && IsEnabled()){
		Rollers.Set(cLeft.GetY());

		if (cLeft.GetRawButton(1)){
			Pulley.Set(1);
		}
		else if (cLeft.GetRawButton(2)){
			Pulley.Set(-1);
		}
		else {
			Pulley.Set(0);
		}
	}
}

void TestPeriodic() {}

private:
	frc::LiveWindow& m_lw = *LiveWindow::GetInstance();
	frc::SendableChooser<std::string> m_chooser;
	const std::string kAutoNameDefault = "Default";
	const std::string kAutoNameCustom = "My Auto";
	std::string m_autoSelected;

	frc::Joystick cLeft{1};										//Declare the Left controller joystick
	frc::Spark RollerR{0};										//Declare the Right speed controller for the rollers
	frc::Spark RollerL{1};										//Declare the Left speed controller for the rollers
	frc::SpeedControllerGroup Rollers{RollerL, RollerR};		//Create a speed controller group and assign the left and right roller speed controllers to the group
	frc::Spark Pulley{2};
};

START_ROBOT_CLASS(Robot)
