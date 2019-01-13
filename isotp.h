#ifndef ISOTP_H
#define ISOTP_H

#include <mutex>
#include <map>
#include <cinttypes>
#include <functional>

#include <isotpsession.h>
#include "can.h"

typedef std::map<uint32_t, IsoTpSession> tSessionMap;


class IsoTp
{
private:
    std::mutex m_sessionMutex;
    tSessionMap m_sessionMap;
    tSharedCan m_pCan;

protected:

    tSessionMap::iterator MakeSession(uint32_t id);
    void SessionTimeout(uint32_t id);
public:
    void IngestFrame(tCanFrame &frame);

    void SessionFinished(tTpMsg msg);

    void SetCan(tSharedCan pCan);
    IsoTp();
};

#endif // ISOTP_H
