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
#include <sstream>
#include <string>

namespace sds_project {

void SourceBase::initialize()
{
    createdSignal = registerSignal("created");
    jobCounter = 0;
    WATCH(jobCounter);
    jobName = par("jobName").stringValue();
    if (jobName == "")
        jobName = getName();
}

void SourceBase::finish()
{
    emit(createdSignal, jobCounter);
}

//----
Define_Module(CyclicSource);

void CyclicSource::initialize()
{
    SourceBase::initialize();
    startTime = par("startTime");
    stopTime = par("stopTime");
    numJobs = par("numJobs");
    previousTotalDuration = 0;
    // decide to cycle only if more than one interArrivalTime was given
    /*int counter;
    for (int i=1; i<DIST_SIZE; i++) {
        std::ostringstream strs;
        strs << (i+1);
        const char *num = ("interArrivalTimeDuration"+(strs.str())).c_str();
        double duration = par(num).doubleValue();
        if (duration >= 0) counter++;
    }
    cycle = counter > 1;*/
    // schedule the first message timer for start time
    scheduleAt(startTime, new cMessage("newjobTimer"));
}

VirtualMachineImage *CyclicSource::createImage()
{
    char buf[80];
    sprintf(buf, "%.60s-%d", jobName.c_str(), ++jobCounter);
    VirtualMachineImage *image = new VirtualMachineImage(buf, par("jobType"), par("diskSize").longValue()*8);
    return image;
}

void CyclicSource::generateDistributionLength() {
    //generate inter-arrival time duration
    double duration = par("interArrivalTimeDuration1").doubleValue();
    distribution_length[0] = duration > 0 ? duration : 1;
    for (int i=1; i<DIST_SIZE; i++) {
        std::ostringstream strs;
        strs << (i+1);
        const char *num = ("interArrivalTimeDuration"+(strs.str())).c_str();
        duration = par(num).doubleValue();
        distribution_length[i] = distribution_length[i-1];
        distribution_length[i] += duration > 0 ? duration : 0;
    }
    tot_dist_length = distribution_length[DIST_SIZE-1];
}

double CyclicSource::generateInterArrivalTime(){
    simtime_t simulationTime = simTime();
    if (simulationTime > previousTotalDuration) {
        generateDistributionLength();
        previousTotalDuration += tot_dist_length;
    }
    double currTime = fmod(simulationTime.dbl(),tot_dist_length);
    double interArrTime;
    std::ostringstream strs;
    const char *num;
    int i;

    for(i=0; i<DIST_SIZE; i++)
        if( currTime <= distribution_length[i] )
            break;

    strs << (i+1);
    num = ("interArrivalTime"+(strs.str())).c_str();
    interArrTime = par(num);
    return interArrTime;
}

void CyclicSource::handleMessage(cMessage *msg)
{
    ASSERT(msg->isSelfMessage());

    if ((numJobs < 0 || numJobs > jobCounter) && (stopTime < 0 || stopTime > simTime()))
    {
        // reschedule the timer for the next message
        scheduleAt(simTime() + generateInterArrivalTime(), msg);

        VirtualMachineImage *image = createImage();
        last = image;
        send(image, "out");
    }
    else
    {
        // finished
        delete msg;
    }
}

}; //namespace
