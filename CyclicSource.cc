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

#include "CyclicSource.h"

namespace sds_project {

Define_Module(CyclicSource);

void SourceBase::initialize()
{
    createdSignal = registerSignal("created");
    VMCounter = 0;
    WATCH(VMCounter);
    VMName = par("VMName").stringValue();
    if (VMName == "")
        VMName = getName();
}

void SourceBase::finish()
{
    emit(createdSignal, VMCounter);
}

void CyclicSource::initialize()
{
    SourceBase::initialize();
    startTime = par("startTime");
    stopTime = par("stopTime");
    numVMs = par("numVMs");

    // schedule the first message timer for start time
    scheduleAt(startTime, new cMessage("newVMTimer"));
}

cPacket *CyclicSource::createPacket()
{
    char buf[80];
    sprintf(buf, "%.60s-%d", VMName.c_str(), ++VMCounter);
    cPacket *packet = new cPacket(buf, par("VMType"), par("diskSize").longValue());
    return packet;
}

void CyclicSource::handleMessage(cMessage *msg)
{
    ASSERT(msg->isSelfMessage());

    if ((numVMs < 0 || numVMs > VMCounter) && (stopTime < 0 || stopTime > simTime()))
    {
        // reschedule the timer for the next message
        scheduleAt(simTime() + par("interArrivalTime").doubleValue(), msg);

        cPacket *packet = createPacket();
        send(packet, "out");
    }
    else
    {
        // finished
        delete msg;
    }
}

}; //namespace
