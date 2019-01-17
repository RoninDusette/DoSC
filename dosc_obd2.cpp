#include "dosc.h"

void DoSC::ProcessOb2Name(tResultStringMap *pMap, tTpMsg msg)
{
    std::string name;

    if (msg.data[1] != 0x0A)
    {
        return;
    }

    for (size_t i = 3; i < msg.data.size(); i++)
    {
        if (msg.data[i] == '\0')
        {
            break;
        }

        name += static_cast<char>(msg.data[i]);
    }

    (*pMap)[msg.id] = name;
}

void DoSC::Obd2GetName(uint32_t id, tResultStringMap &map)
{
    tCanFrame frame;

    tProcCall call = std::bind(&DoSC::ProcessOb2Name, this, &map,
                               std::placeholders::_1);
    RegisterCodeFunc(0x49, call);

    frame.id = id;
    frame.data[0] = 0x02;
    frame.data[1] = 0x09;
    frame.data[2] = 0x0A;
    frame.size = 03;
    m_pCan->SendCanFrame(frame);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    RegisterCodeFunc(0x49, nullptr);
}
