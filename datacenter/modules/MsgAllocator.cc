#include "MsgAllocator.h"

Define_Module(MsgAllocator);

void Allocate::handleMessage(cMessage *msg)
{
    Job *job = check_and_cast<Job *>(msg);
    if (queue.isEmpty() && allocateResource(job)){
        job->setKind(ACCEPTED);
        send(job, "out");
    }else{
        job->setKind(REJECTED);
        send(job, "out");
    }
}
