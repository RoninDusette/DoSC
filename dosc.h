#ifndef DOSC_H
#define DOSC_H

#include <string>

#include "dosc_global.h"

#include "can.h"
#include "isotp.h"

#define DOSC_OK 0

typedef std::map<uint32_t, std::vector<std::string>> tResultStringMap;

typedef std::function<void(tTpMsg &)> tProcCall;
typedef std::map<uint8_t, tProcCall> tCodeProcMap;

class DOSCSHARED_EXPORT DoSC
{
private:
    tSharedCan m_pCan;
    IsoTp m_isoTp;

    std::mutex m_codeFuncMutex;
    tCodeProcMap m_codeFunc;

protected:
    void ProcessOb2Name(tResultStringMap *pMap, tTpMsg msg);
    void ProcessObd2Faults(tResultStringMap *pMap, tTpMsg msg);

    void RegisterCodeFunc(uint8_t code, tProcCall call);
    void CallCodeFunc(uint8_t code, tTpMsg &msg);

    void IsoTpFinishedCb(tTpMsg &msg);
public:
    DoSC();
    ~DoSC();

    int StartCan(std::string &interface);
    void StopCan();

    void CanRxCb(tCanFrame &frame);
    void SendCanFrame(tCanFrame &frame);

    void Obd2GetName(uint32_t id, tResultStringMap &map);
    void Obd2GetFaults(uint32_t id, tResultStringMap &map);
    void Obd2ClearFaults(uint32_t id, tResultStringMap &map);
};

#endif // DOSC_H
