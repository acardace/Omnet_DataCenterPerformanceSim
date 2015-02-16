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

#include "PacketSink.h"
#include <VirtualMachineImage.h>
#include <CyclicSource.h>
#include <ResAllocator.h>

namespace sds_project {

Define_Module(PacketSink);

void PacketSink::initialize()
{
    lifeTimeSignal = registerSignal("lifeTime");
    waitingTimeSignal = registerSignal("waitingTime");
    queuesVisitedSignal = registerSignal("queuesVisited");
    serviceTime = registerSignal("serviceTime");
    totalDelayTimeSignal = registerSignal("totalDelayTime");
    delaysVisitedSignal = registerSignal("delaysVisited");
    generationSignal = registerSignal("generation");
    availabilitySignal = registerSignal("availabilitySignal");
    responsivenessSignal = registerSignal("responsiveness");
    keepJobs = par("keepJobs");
    calcAvailability = par("calcAvailability").boolValue();
    calcServiceTime = par("calcServiceTime").boolValue();
    calcWaitingTime = par("calcWaitingTime").boolValue();
    jobCounter = 0;
}

simsignal_t PacketSink::getServiceTimeSignal(){
    return serviceTime;
}

void PacketSink::handleMessage(cMessage *msg)
{
    VirtualMachineImage *vm = check_and_cast<VirtualMachineImage*>(msg);

    // to calculate availability we have to count dropped jobs
    ++jobCounter;

    // gather statistics
    emit(lifeTimeSignal, simTime()- vm->getCreationTime());
    emit(queuesVisitedSignal, vm->getQueueCount());
    emit(totalDelayTimeSignal, vm->getTotalDelayTime());
    emit(delaysVisitedSignal, vm->getDelayCount());
    emit(generationSignal, vm->getGeneration());

    //could be coming from outer space
    if(calcWaitingTime)
        getModuleByPath(vm->getOwner().c_str())->emit(waitingTimeSignal, vm->getTotalQueueingTime());

    //register ServiceTime
    if( calcServiceTime )
        getModuleByPath(vm->getOwner().c_str())->emit(serviceTime,vm->getServiceTime());

    if (!keepJobs)
        delete msg;
}

void PacketSink::finish()
{
    if (calcAvailability) {
        // Calculate availability
        cModule *parent = getParentModule();
        cModule *parentsparent = parent->getParentModule();
        cModule *circlicSource = parentsparent->getSubmodule("cyclicSource");
        CyclicSource *source = check_and_cast<CyclicSource*>(circlicSource);
        double totalJobs = (double) source->getJobCount();
        double availability = 1.0 - (double)jobCounter / totalJobs;
        emit(availabilitySignal, availability);
    }

   CyclicSource *source = (CyclicSource *) getParentModule()->findObject("cyclicSource",false);
   ResAllocator *allocator = (ResAllocator *) getParentModule()->findObject("resAllocator",false);

   if( source != NULL){
       int createdJobs = source->getJobCount();
       int lessThanRespJobs = allocator->getLessThanRespJobs();
       emit(responsivenessSignal, (double) lessThanRespJobs/createdJobs);
   }
}

}; //namespace

