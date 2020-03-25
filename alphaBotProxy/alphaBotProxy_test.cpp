#include <iostream>
#include <string>

#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

#include "./alphaBotProxy.h"

void splitVals(std::string &valsString, std::vector<int> &vals)
{
    std::stringstream ss(valsString);
    std::string token;
    while (std::getline(ss, token, ',')) {
        vals.push_back(std::stoi(token));
    }
}

void splitMsgIntoHeaderAndContent(std::string &msg, std::string &header, std::string &content)
{
    std::size_t delimPosition;
    delimPosition = msg.find(":");

    header = msg.substr(0, delimPosition);
    content = msg.substr(delimPosition+1, msg.length());
}

bool test_process_getSensorVals()
{
    alphaBotProxy alphaBot;

    std::string inputMsg = "getSensorVals";

    std::string rsp = alphaBot.process_getSensorVals(inputMsg);

    std::string rspHeader = "";
    std::string rspContent = "";

    splitMsgIntoHeaderAndContent(rsp, rspHeader, rspContent);

    if(rspHeader != "getSensorValsRsp")
    {
        return false;
    }

    std::vector<int> vals;
    splitVals(rspContent, vals);

    if(vals.size() != 5)
    {
        std::cout<<"Size: "<<vals.size()<<std::endl;
        return false;
    }

    return true;
}

bool test_process_updatePWM()
{

    alphaBotProxy alphaBot;

    alphaBot.process_updatePWM();

    return false;
}

int main()
{

std::cout<<"Server test"<<std::endl;

bool result = true;

if(!test_process_getSensorVals())
{
    std::cout<<"test_process_getSensorVals: FAIL"<<std::endl;

    result = false;
}

if(!test_process_updatePWM())
{
    std::cout<<"test_process_updatePWM: FAIL"<<std::endl;

    result = false;
}

std::cout<<"Server test - end"<<std::endl;

std::cout<<"Server test RESULT: ";

if(result)
{
    std::cout<<"PASS";
}
else
{
    std::cout<<"FAIL";
}

std::cout<<std::endl;


return 0;
}
