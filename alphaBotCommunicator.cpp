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
			   std::vector<zmq::message_t> cont;
			   
			       while (std::getline(ss, token, ':')) {
					cont.push_back(zmq::message_t(token));
					}
					
					std::cout<<"Header:"<<cont[0]<<"Content:"<<cont[1]<<std::endl;
				
			   
			   return true;
		   }
		 
		 return false;
	 }
	 
	 return false;
}


//TODO : unneeded, compile to lib
//int main()
//{
	
	
//}