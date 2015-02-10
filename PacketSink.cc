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

#include "Sink.h"
#include <VirtualMachineImage.h>

namespace queueing {

Define_Module(Sink);

void Sink::initialize()
{
    lifeTimeSignal = registerSignal("lifeTime");
    totalQueueingTimeSignal = registerSignal("totalQueueingTime");
    queuesVisitedSignal = registerSignal("queuesVisited");
    totalServiceTimeSignal = registerSignal("totalServiceTime");
    totalDelayTimeSignal = registerSignal("totalDelayTime");
    delaysVisitedSignal = registerSignal("delaysVisited");
    generationSignal = registerSignal("generation");
    keepJobs = par("keepJobs");
}

void Sink::handleMessage(cMessage *msg)
{
    sds_project::VirtualMachineImage *vm = check_and_cast<sds_project::VirtualMachineImage*>(msg);
    queueing::Job *job = vm->getJob();
    // gather statistics
    emit(lifeTimeSignal, simTime()- job->getCreationTime());
    emit(totalQueueingTimeSignal, job->getTotalQueueingTime());
    emit(queuesVisitedSignal, job->getQueueCount());
    emit(totalServiceTimeSignal, job->getTotalServiceTime());
    emit(totalDelayTimeSignal, job->getTotalDelayTime());
    emit(delaysVisitedSignal, job->getDelayCount());
    emit(generationSignal, job->getGeneration());

    if (!keepJobs)
        delete msg;
}

void Sink::finish()
{
    // TODO missing scalar statistics
}

}; //namespace

