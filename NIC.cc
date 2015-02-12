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

#include "NIC.h"

Define_Module(NIC);

NIC::~NIC()
{
    cancelAndDelete(transmissionFinishedMsg);
}

void NIC::initialize()
{
    capacity = par("capacity");
    transmissionFinishedMsg = new cMessage("transmission-finished");
    cGate *outGate = gate("out");
    if (outGate) channel = outGate->getNextGate()->getNextGate()->getChannel();
    queue.setName("queue");
}

void NIC::transmissionFinished() {
    if (!queue.empty()) {
        cMessage *msg = (cMessage *) queue.pop();
        send(msg, "out");
        if (!queue.empty())
            scheduleAt(channel->getTransmissionFinishTime(), transmissionFinishedMsg);
    }
}

void NIC::tryToSend(cMessage *msg) {
    if (channel->isBusy()) {
        // check for container capacity
        if (capacity >=0 && queue.length() >= capacity)
        {
            EV << "Capacity full! Message dropped.\n";
            if (ev.isGUI()) bubble("Dropped!");
            delete msg;
            return;
        }
        else {
            queue.insert(msg);
            // reschedule only the first time, because after that transmissionFinished() takes charge
            if (queue.length() == 1)
                scheduleAt(channel->getTransmissionFinishTime(), transmissionFinishedMsg);
        }
    }
    else send(msg, "out");
}

void NIC::handleMessage(cMessage *msg)
{
    if (msg == transmissionFinishedMsg)
        transmissionFinished();
    else {
        if (channel->isTransmissionChannel())
            tryToSend(msg);
        else send(msg, "out");
    }
}
