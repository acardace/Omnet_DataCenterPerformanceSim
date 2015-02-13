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

#include "Selector.h"
#include "ResourcePool.h"

namespace sds_project {

Define_Module(Selector);

void Selector::initialize()
{
    federationAvailable = getParentModule()->registerSignal("federationAvailability");
    emit(federationAvailable, 1.0);
    neighbourSize = getParentModule()->gateSize("out");
    if (neighbourSize > 0) {
        neighbour = new cModule* [neighbourSize];
        for (int i=0; i<neighbourSize; i++) {
            cGate *outGate = getParentModule()->gate("out", i); //gate of UploadQueue
            ev << "outGate id=" << outGate->getId() << endl;
            // Iterate 3 times to get:
            // gate of UploadQueue
            // gate of DataCenter
            // gate of neighbour DataCenter
            for (int j=1; j<=2; j++)
                if (outGate)
                    outGate = outGate->getNextGate();
            if (outGate)
                neighbour[i] = outGate->getOwnerModule();
            else
                neighbour[i] = NULL;
        }
    }
    rrCounter = 0;
}

void Selector::handleMessage(cMessage *msg)
{
    bool sent = false;
    for (int i=0; i<neighbourSize; i++) {
        int j = (rrCounter + i) % neighbourSize;
        if (neighbour[j]) {
            queueing::IResourcePool *pool = check_and_cast<queueing::IResourcePool*>(neighbour[j]->getSubmodule("VMs"));
            //queueing::IResourceAllocator *allocator = check_and_cast<queueing::IResourceAllocator*>(neighbour[j]->getSubmodule("resAllocator"));
            if (pool->tryToAllocate(this, 1, 0)) {
                emit(federationAvailable, 1.0);
                send(msg, "out", j);
                sent = true;
                break;
            }
        }
    }
    if (!sent) {
        emit(federationAvailable, 0.0);
        send(msg, "discard");
    }
    if (neighbourSize > 0)
        rrCounter = (rrCounter+1)%neighbourSize;
}

void Selector::resourceGranted(queueing::IResourcePool *provider) {
    //Messages are never enqueued, so there's nothing to do here.
}

}; //namespace
