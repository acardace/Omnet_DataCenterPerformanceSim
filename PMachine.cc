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
    if(msg->isSelfMessage()){
        //the msg has already been serviced
        VMs--;
        emit(assigned_VMs_Signal,VMs);
        endService(msg);
    }else{
        //the message just got here
        VMs++;
        emit(assigned_VMs_Signal,VMs);
        simtime_t serviceTime = startService( msg );
        scheduleAt( simTime()+serviceTime, msg );
    }
}


simtime_t PMachine::startService(cMessage *msg){
    double scheduleTime;
    scheduleTime = par("serviceTime").doubleValue()*pow((1+degradation),VMs-1);
    EV << "Starting service of " << msg->getName() << endl;
    msg->setTimestamp();
    return scheduleTime;
}

void PMachine::endService(cMessage *msg){
   /* EV << "Finishing service of " << msg->getName() << endl;
    simtime_t d = simTime() - msg->getTimestamp();
    msg->setTotalServiceTime(msg->getTotalServiceTime() + d);*/
    send(msg, "out");
}

int PMachine::length(){
    return VMs;
}

}; //namespace
