#ifndef DOSC_H
#define DOSC_H

#include <string>

#include "dosc_global.h"

#include "can.h"

#define DOSC_OK 0

class DOSCSHARED_EXPORT DoSC
{
private:
    can m_can;

protected:

public:
    int StartCan(std::string &interface);
    void StopCan();

    void CanRxCb(tCanFrame &frame);
    void SendCanFrame(tCanFrame &frame);

    DoSC();
    ~DoSC();
};

#endif // DOSC_H