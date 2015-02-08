#ifndef __MSG_ALLOCATOR_H__
#define __MSG_ALLOCATOR_H__

#include "Allocate.h"

//define kinds of messages
#define ACCEPTED 0
#define REJECTED 1

/**
 * Msg_Allocator module
 */
class MsgAllocator : public queueing::Allocate
{
  protected:
    virtual void handleMessage(cMessage *msg);
};

#endif
