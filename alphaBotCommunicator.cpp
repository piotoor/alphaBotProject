#include <string>
#include <iostream>
#include <vector>

#include "alphaBotCommunicator.h"


alphaBotCommunicator::alphaBotCommunicator():sock(ctx, zmq::socket_type::rep)
{

}

bool alphaBotCommunicator::connect()
{

	sock.bind("tcp://*:5555");

	return true;   //TODO check bind()   return value
}

bool alphaBotCommunicator::listenForGetSensorValsReq()
{
 std::vector<zmq::message_t> recv_msgs;

 const auto ret = zmq::recv_multipart(sock, std::back_inserter(recv_msgs));

	int message_received_count = 0;

	 if(*ret > 0)
	 {
		 std::string msg = recv_msgs.at(message_received_count).to_string();
		   	message_received_count++;

			if(msg.compare("getSensorVals") == 0)
		   {
			   return true;
		   }

		 return false;
	 }

	 return false;
}

bool alphaBotCommunicator::sendSensorValsToAlphaBot(int* vals)
{
		//std::string msgString = "getSensorValsRsp:1,2,3,44,5";  //TODO:  insert values from input

	std::string msgString = "getSensorValsRsp:";

	for(int i =0; i<5;i++)
	{


		msgString.append(std::to_string(vals[i]));

		if(i<4)
		{
			msgString.append(",");
		}
	}

	std::cout<<"sendSensorValsToAlphaBot. Msg- "<<msgString<<std::endl;

	//std::wstring widestr = std::wstring(msgString.begin(), msgString.end());

	const std::string message = msgString;

	   std::array<zmq::const_buffer, 1> getSensorValsRsp_msgs = {
		   zmq::buffer(msgString)   };

	zmq::send_multipart(sock, getSensorValsRsp_msgs);

	return true;   //TODO check for errors
}


bool alphaBotCommunicator::listenForPwmUpdate(int& pwma, int& pwmb)
{
 std::vector<zmq::message_t> recv_msgs;

 const auto ret = zmq::recv_multipart(sock, std::back_inserter(recv_msgs));

	int message_received_count = 0;

	 if(*ret > 0)
	 {
		 std::string msg = recv_msgs.at(message_received_count).to_string();
		   	message_received_count++;

			if(msg.find("updatePWM") != std::string::npos)
		   {
			   std::cout<<"listenForPwmUpdate.  Received msg - "<<msg<<std::endl;

			   //save obtained pwm values to pwma and pwmb

			     std::stringstream ss(msg);
				std::string token;
			   //std::vector<zmq::message_t> cont;
			   std::vector<std::string> cont;

			       while (std::getline(ss, token, ':')) {
					   std::cout<<"in loop: "<<token<<std::endl;
					//cont.push_back(zmq::message_t(token));
					cont.push_back(token);
					}

					std::cout<<"Header:"<<cont[0]<<" PWM:"<<cont[1]<<" Val:"<<cont[2]<<std::endl;

				if(cont[1].compare("A") != 0)
				{
					pwma = std::stoi(cont[2]);
				}
				else if(cont[1].compare("B") != 0)
				{
					pwmb = std::stoi(cont[2]);
				}

std::cout<<"2"<<std::endl;

	const std::string rspMessage = "updatePwmRsp";

	   std::array<zmq::const_buffer, 1> getSensorValsRsp_msgs = {
		   zmq::buffer(rspMessage)   };

	zmq::send_multipart(sock, getSensorValsRsp_msgs);

			   return true;
		   }

		 //std::cout<<"3"<<std::endl;
		 std::cout<<"listenForPwmUpdate.  Received msg - "<<msg<<std::endl;

		 return false;
	 }

	 std::cout<<"4"<<std::endl;
	 return false;
}


//TODO : unneeded, compile to lib
//int main()
//{


//}
