#include <stdio.h>

#include "dosc.h"

void PrintCanFrame(tCanFrame &frame)
{
    printf("%x [%d] ", frame.id, frame.size);
    for (size_t i = 0; i < frame.size; i++)
    {
        printf("%x ", frame.data[i]);
    }
    printf("\n");
}

void DoSC::CanRxCb(tCanFrame &frame)
{
    PrintCanFrame(frame);
}

void DoSC::SendCanFrame(tCanFrame &frame)
{
    m_can.SendCanFrame(frame);
}

int DoSC::StartCan(std::string &interface)
{
    m_can.AssignInterface(interface);
    m_can.StartCan();

    return DOSC_OK;
}

void DoSC::StopCan()
{
    m_can.StopCan();
    m_can.UnassignInterface();
}

DoSC::DoSC()
{
    tCanRxCb callback = std::bind(&DoSC::CanRxCb, this, std::placeholders::_1);
    m_can.SetRxCb(callback);
}

DoSC::~DoSC()
{
    StopCan();
}
