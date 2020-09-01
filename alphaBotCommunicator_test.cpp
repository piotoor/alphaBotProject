#include "alphaBotCommunicator.h"

#include <iostream>

int main()
{
	alphaBotCommunicator communicator;
	
	std::cout<<"Connect..."<<std::endl;
	
	communicator.connect();
	
	std::cout<<"listenForGetSensorValsReq..."<<std::endl;

	
	communicator.listenForGetSensorValsReq();
	
	std::cout<<"sendSensorValsToAlphaBot..."<<std::endl;
	
	int* vals = new int[5];
	vals[0] = 100;
	vals[1] = 200;
	vals[2] = 300;
	vals[3] = 400;
	vals[4] = 500;
	
	communicator.sendSensorValsToAlphaBot(vals);

	std::cout<<"sendSensorValsToAlphaBot..."<<std::endl;

	int pwma = 0;
	int pwmb = 0;

	communicator.listenForPwmUpdate(pwma, pwmb);
	communicator.listenForPwmUpdate(pwma, pwmb);
	
	std::cout<<"Pwma:"<<pwma<<"Pwmb:"<<pwmb<<std::endl;
	
	std::cout<<"End"<<std::endl;

}