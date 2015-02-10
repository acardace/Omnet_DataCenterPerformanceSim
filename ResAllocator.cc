//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <omnetpp.h>
#include <ResAllocator.h>
#include <Job.h>

namespace sds_project {

Define_Module(ResAllocator)

ResAllocator::ResAllocator(){}

ResAllocator::~ResAllocator(){}

void ResAllocator::initialize(){
    forwardedSignal = registerSignal("forwarded");
    queueingTimeSignal = registerSignal("queueingTime");
    queueLengthSignal = registerSignal("queueLength");
    emit(queueLengthSignal, 0l);

    fifo = par("fifo");
    capacity = par("capacity");
    queue.setName("queue");

    resourceAmount = par("resourceAmount");
    resourcePriority = par("resourcePriority");

    const char *resourceName = par("resourceModuleName");
    cModule *mod = getParentModule()->getModuleByPath(resourceName);
    if (!mod)
        throw cRuntimeError("Cannot find resource pool module `%s'", resourceName);
    resourcePool = check_and_cast<queueing::IResourcePool*>(mod);
}

void ResAllocator::handleMessage(cMessage *msg){
    queueing::Job *job = check_and_cast<queueing::Job *>(msg);
    if (queue.isEmpty() && allocateResource(job)){
        job->setKind(ACCEPTED);
        send(job, "out");
    }else
        enqueueOrForward(job);
}

void ResAllocator::enqueueOrForward(queueing::Job *job){
    // check for container capacity
    if (capacity >=0 && queue.length() >= capacity)
    {
        EV << "Capacity full! Job forwarded.\n";
        if (ev.isGUI()) bubble("Forwarded!");
        emit(forwardedSignal, 1);
        job->setKind(REJECTED);
        send(job, "out");
    }
    else
    {
        EV << "Job enqueued.\n";
        job->setTimestamp();
        queue.insert(job);
        emit(queueLengthSignal, queue.length());
    }
}

bool ResAllocator::allocateResource(queueing::Job *job){
    return resourcePool->tryToAllocate(this, resourceAmount, resourcePriority + job->getPriority());
}

queueing::Job *ResAllocator::dequeue(){
    queueing::Job *job;
    job = (queueing::Job *)queue.pop();
    emit(queueLengthSignal, queue.length());

    simtime_t dt = simTime() - job->getTimestamp();
    job->setTotalQueueingTime(job->getTotalQueueingTime() + dt);
    emit(queueingTimeSignal, dt);

    return job;
}

void ResAllocator::resourceGranted(queueing::IResourcePool *provider){
    Enter_Method("resourceGranted");

    // send out job for which resource was granted
    ASSERT2(!queue.empty(), "Resource granted while no jobs are waiting");
    queueing::Job *job = dequeue();
    job->setKind(ACCEPTED);
    send(job, "out");

    // try to handle other waiting jobs as well
    while (!queue.isEmpty() && allocateResource( (queueing::Job *) queue.front() ))
    {
        queueing::Job *job = dequeue();
        job->setKind(ACCEPTED);
        send(job, "out");
    }
}

}; //namespace

