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
    m_isoTp.IngestFrame(frame);
}

void DoSC::SendCanFrame(tCanFrame &frame)
{
    m_pCan->SendCanFrame(frame);
}

int DoSC::StartCan(std::string &interface)
{
    m_pCan->AssignInterface(interface);
    m_pCan->StartCan();

    return DOSC_OK;
}

void DoSC::StopCan()
{
    m_pCan->StopCan();
    m_pCan->UnassignInterface();
}

DoSC::DoSC()
{
    tCanRxCb callback = std::bind(&DoSC::CanRxCb, this, std::placeholders::_1);
    m_pCan = std::make_shared<can>();
    m_pCan->SetRxCb(callback);

    m_isoTp.SetCan(m_pCan);
}

DoSC::~DoSC()
{
    StopCan();
}
