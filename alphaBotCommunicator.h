#include <zmq.hpp>
#include <zmq_addon.hpp>

class alphaBotCommunicator
{
	
	zmq::context_t ctx;
	zmq::socket_t sock;
	
	public:
	
	alphaBotCommunicator();
	
	bool connect();
	
	bool listenForGetSensorValsReq();
	
	bool sendSensorValsToAlphaBot(int* vals);  // can be vector
	
	bool listenForPwmUpdate(int& pwma, int& pwmb);
	
	
};