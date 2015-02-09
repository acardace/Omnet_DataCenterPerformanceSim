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

#include "PMachine.h"

namespace sds_project{

Define_Module(PMachine);

PMachine::PMachine(){};

PMachine::~PMachine(){};

void PMachine::initialize(){
    VMs = 0;
    assigned_VMs_Signal = registerSignal("assigned_VMs");
    emit(assigned_VMs_Signal, VMs);
    degradation = par("degradation_factor").doubleValue();
}

void PMachine::handleMessage(cMessage *msg){
    queueing::Job *job = check_and_cast<queueing::Job *>(msg);
    if(job->isSelfMessage()){
        //the job has already been serviced
        VMs--;
        emit(assigned_VMs_Signal,VMs);
        endService(job);
    }else{
        //the message just got here
        VMs++;
        emit(assigned_VMs_Signal,VMs);
        simtime_t serviceTime = startService( job );
        scheduleAt( simTime()+serviceTime, job );
    }
}


simtime_t PMachine::startService(queueing::Job *job){
    double scheduleTime;
    scheduleTime = par("serviceTime").doubleValue()*pow((1+degradation),VMs-1);
    EV << "Starting service of " << job->getName() << endl;
    job->setTimestamp();
    return scheduleTime;
}

void PMachine::endService(queueing::Job *job){
    EV << "Finishing service of " << job->getName() << endl;
    simtime_t d = simTime() - job->getTimestamp();
    job->setTotalServiceTime(job->getTotalServiceTime() + d);
    send(job, "out");
}

int PMachine::length(){
    return VMs;
}

}; //namespace
