#include <string>

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
	   std::array<zmq::const_buffer, 1> getSensorValsRsp_msgs = {
		   zmq::str_buffer("getSensorValsRsp:1,2,3,44,5")   };  //TODO:  insert values from input 
	
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
			   //save obtained pwm values to pwma and pwmb
			   
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