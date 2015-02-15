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

namespace sds_project {

Define_Module(ResAllocator)

ResAllocator::ResAllocator(){}

ResAllocator::~ResAllocator(){}

void ResAllocator::initialize(){
    droppedSignal = registerSignal("dropped");
    queueLengthSignal = registerSignal("queueLength");
    lessThanRespLimitSignal = registerSignal("lessThanRespLimit");
    availability_tSignal = registerSignal("availability_t");
    instantServiceSignal = registerSignal("instantService");
    emit(queueLengthSignal, 0l);

    lessThanRespJobs = 0;
    fifo = par("fifo");
    capacity = par("capacity");
    queue.setName("queue");
    availabilityOnDrop = par("availabilityOnDrop");
    instantService = par("instantService");
    resourceAmount = par("resourceAmount");
    resourcePriority = par("resourcePriority");
    respLimit = par("respLimit");

    const char *resourceName = par("resourceModuleName");
    cModule *mod = getParentModule()->getModuleByPath(resourceName);
    if (!mod)
        throw cRuntimeError("Cannot find resource pool module `%s'", resourceName);
    resourcePool = check_and_cast<queueing::IResourcePool*>(mod);
}

void ResAllocator::enqueueOrForward(VirtualMachineImage *vm){
    // check for container capacity
    if (capacity >=0 && queue.length() >= capacity)
    {
        EV << "Capacity full! Message dropped.\n";
        if (ev.isGUI()) bubble("Dropped!");
        emit(droppedSignal, 1.0);
        if (availabilityOnDrop)
            emit(availability_tSignal, 0.0);
        send(vm, "discard");
    }
    else
    {
        EV << "Message enqueued.\n";
        vm->setTimestamp();
        queue.insert(vm);
        emit(queueLengthSignal, queue.length());
        emit(droppedSignal, 0.0);
        emit(availability_tSignal, 1.0);
    }
}

bool ResAllocator::allocateResource(VirtualMachineImage *vm){
    return resourcePool->tryToAllocate(this, resourceAmount, resourcePriority);
}

void ResAllocator::handleMessage(cMessage *msg){
    VirtualMachineImage *vm = check_and_cast<VirtualMachineImage*>(msg);
    if (queue.isEmpty() && allocateResource(vm)){
        lessThanRespJobs++;
        emit(lessThanRespLimitSignal, true);
        emit(droppedSignal, 0.0);
        emit(availability_tSignal, 1.0);
        emit(instantServiceSignal, 1.0);
        send(vm, "out");
    } else {
        emit(instantServiceSignal, 0.0);
        enqueueOrForward(vm);
    }
};

VirtualMachineImage *ResAllocator::vmDequeue(){
    VirtualMachineImage *vm;
    vm = (VirtualMachineImage *)queue.pop();
    emit(queueLengthSignal, queue.length());
    simtime_t dt = simTime() - vm->getTimestamp();
    vm->setTotalQueueingTime(vm->getTotalQueueingTime() + dt);
    if (dt < respLimit){
        lessThanRespJobs++;
        emit(lessThanRespLimitSignal, true);
    }

    return vm;
}

void ResAllocator::resourceGranted(queueing::IResourcePool *provider){
    Enter_Method("resourceGranted");

    // send out job for which resource was granted
    ASSERT2(!queue.empty(), "Resource granted while no jobs are waiting");
    VirtualMachineImage *vm = vmDequeue();
    send(vm, "out");

    // try to handle other waiting jobs as well
    while (!queue.isEmpty() && allocateResource( (VirtualMachineImage *) queue.front() ))
    {
        VirtualMachineImage *vm = vmDequeue();
        send(vm, "out");
    }

}

int ResAllocator::getLessThanRespJobs(){
    return lessThanRespJobs;
}

}; //namespace

