#ifndef ALPHABOTPROXY_H
#define ALPHABOTPROXY_H

#include <string>

class alphaBotProxy
{
    public:
        alphaBotProxy();
        virtual ~alphaBotProxy();

        std::string process_getSensorVals(std::string msg);
        void process_updatePWM();

    protected:

    private:
};

#endif // ALPHABOTPROXY_H
