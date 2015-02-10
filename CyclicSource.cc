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
    jobCounter = 0;
    WATCH(jobCounter);
    jobName = par("jobName").stringValue();
    if (jobName == "")
        jobName = getName();
}

queueing::Job *SourceBase::createJob()
{
    char buf[80];
    sprintf(buf, "%.60s-%d", jobName.c_str(), ++jobCounter);
    queueing::Job *job = new queueing::Job(buf);
    job->setKind(par("jobType"));
    job->setPriority(par("jobPriority"));
    return job;
}

void SourceBase::finish()
{
    emit(createdSignal, jobCounter);
}

void CyclicSource::initialize()
{
    SourceBase::initialize();
    startTime = par("startTime");
    stopTime = par("stopTime");
    numJobs = par("numJobs");

    // schedule the first message timer for start time
    scheduleAt(startTime, new cMessage("newjobTimer"));
}

VirtualMachineImage *CyclicSource::createImage()
{
    char buf[80];
    sprintf(buf, "%.60s-%d", jobName.c_str(), ++jobCounter);
    VirtualMachineImage *image = new VirtualMachineImage(buf, par("jobType"), par("diskSize").longValue());
    image->setJob(SourceBase::createJob());
    return image;
}

void CyclicSource::handleMessage(cMessage *msg)
{
    ASSERT(msg->isSelfMessage());

    if ((numJobs < 0 || numJobs > jobCounter) && (stopTime < 0 || stopTime > simTime()))
    {
        // reschedule the timer for the next message
        scheduleAt(simTime() + par("interArrivalTime").doubleValue(), msg);

        VirtualMachineImage *image = createImage();
        send(image, "out");
    }
    else
    {
        // finished
        delete msg;
    }
}

}; //namespace
