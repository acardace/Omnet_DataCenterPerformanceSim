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

#include "RemoteDeallocate.h"
#include "VirtualMachineImage.h"

namespace sds_project {

Define_Module(RemoteDeallocate);

void RemoteDeallocate::initialize()
{
    waitingTimeSignal = registerSignal("waitingTime");
    resourceAmount = par("resourceAmount");
    resourceName = par("resourceModuleName");
}

void RemoteDeallocate::handleMessage(cMessage *msg)
{
    cModule *remoteSelector = msg->getSenderModule();
    cModule *pool = NULL;
    queueing::IResourcePool *resourcePool = NULL;
    pool = remoteSelector->getParentModule()->getSubmodule(resourceName);
    if (pool) resourcePool = check_and_cast<queueing::IResourcePool*>(pool);
    if (resourcePool) {
        resourcePool->release(resourceAmount);
        VirtualMachineImage *vm = check_and_cast<VirtualMachineImage*>(msg);
        simtime_t waitingTime = vm->getTimestamp()+simTime();
        getModuleByPath(vm->getOwner().c_str())->emit(waitingTimeSignal, waitingTime);
    }
    else throw cRuntimeError("Cannot find resource pool module `%s' in remote DataCenter", resourceName);
    send(msg, "out");
}

}; //namespace
