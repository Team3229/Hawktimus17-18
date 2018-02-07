#include <Autonomous.h>

Autonomous::Autonomous()
{
	gyro = new ADXRS450_Gyro();
	chooser = new frc::SendableChooser<int>();
	ultra = new AnalogInput(ULTRA_PORT);
}

Autonomous::~Autonomous()
{
	delete gyro;
	delete chooser;
	delete ultra;
}


void Autonomous::AutoInit(std::string colors)
{
	switchColor = colors[0]; //Get the color of the switch

	ReadStation();
}


void Autonomous::ReadStation()
{
	//Read from smart dashboard, set position, target, and delay.
}

void Autonomous::AutoPeriodic() { /*Runs either exchange, switch, or baseline based on enums*/}
void Autonomous::Exchange() {}
void Autonomous::Switch () {}
void Autonomous::Baseline() {}
