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
#include <VirtualMachineImage.h>

namespace sds_project{

Define_Module(PMachine);

PMachine::PMachine(){};

PMachine::~PMachine(){};

void PMachine::initialize(){
    physicalRes = getParentModule()->par("phisicalMachines");
    logicalRes = getParentModule()->par("virtualMachines");
    VMs = 0;

    if( physicalRes < logicalRes )
        degradation = par("degradation_factor").doubleValue(); //multiplexing allowed
    else
        degradation = 0; //multiplexing not allowed
}

void PMachine::handleMessage(cMessage *msg){
    if(msg->isSelfMessage()){
        //the msg has already been serviced
        VMs--;
        endService(msg);
    }else{
        //the message just got here
        VMs++;
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
    EV << "Finishing service of " << msg->getName() << endl;
    VirtualMachineImage *vm = check_and_cast<VirtualMachineImage*>(msg);
    simtime_t d = simTime() - vm->getTimestamp();
    vm->setTotalServiceTime(vm->getTotalServiceTime() + d);
    send(msg, "out");
}

int PMachine::length(){
    return VMs;
}

}; //namespace
