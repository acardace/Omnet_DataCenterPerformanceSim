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
    cycle = par("cycle");

    //init distributions length
    distribution_length[0] = par("first_distribution").doubleValue();
    distribution_length[1] = par("second_distribution").doubleValue() + distribution_length[0];
    tot_dist_length = distribution_length[2] = par("third_distribution").doubleValue() + distribution_length[1];


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

double CyclicSource::generateInterArrivalTime(){
    double currTime = fmod(simTime().dbl(),tot_dist_length);
    double interArrTime;
    int i;

    for(i=0; i<DIST_SIZE; i++)
        if( currTime <= distribution_length[i] )
            break;

    switch( i ){
        case 0:
            interArrTime = par("first_distribution");
            break;
        case 1:
            interArrTime = par("second_distribution");
            break;
        case 2:
            interArrTime = par("third_distribution");
            break;
    }

    return interArrTime;
}

void CyclicSource::handleMessage(cMessage *msg)
{
    ASSERT(msg->isSelfMessage());

    if ((numJobs < 0 || numJobs > jobCounter) && (stopTime < 0 || stopTime > simTime()))
    {
        // reschedule the timer for the next message
        if( cycle )
            scheduleAt(simTime() + generateInterArrivalTime(), msg);
        else
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
