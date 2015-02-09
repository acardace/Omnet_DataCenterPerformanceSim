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

Define_Module(Selector);

void Selector::initialize()
{
    neighbourSize = getParentModule()->gateSize("out");
    neighbour = new int [neighbourSize];
    for (int i=0; i<neighbourSize; i++) {
        neighbour[i] = getParentModule->gate("out", i)->getNextGate()->getOwnerModule();
    }
    rrCounter = 0;
}

void Selector::handleMessage(cMessage *msg)
{
    bool freeDatacenter = false;
    for (int i=0; i<neighbourSize; i++) {
        int j = (rrCounter + i) % neighbourSize;
        queueing::IResourcePool *pool = check_and_cast<queueing::IResourcePool*>(neighbour[j]->getSubModule("VMs"));
        if (pool->tryToAllocate(this, 1, 0)) {
            send(msg, "out");
            break;
        }
    }
    rrCounter = (rrCounter+1)%neighbourSize;
}
