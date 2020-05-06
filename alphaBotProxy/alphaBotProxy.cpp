#include "alphaBotProxy.h"

alphaBotProxy::alphaBotProxy()
{
    //ctor
}

alphaBotProxy::~alphaBotProxy()
{
    //dtor
}

std::string alphaBotProxy::process_getSensorVals(std::string msg)
{

std::string rsp = "getSensorValsRsp:";
rsp+="1,2,3,44,5";

return rsp;
}

void alphaBotProxy::process_updatePWM()
{

}
