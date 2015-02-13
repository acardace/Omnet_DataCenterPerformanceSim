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

#include <VirtualMachineImage.h>

namespace sds_project {

VirtualMachineImage::VirtualMachineImage() {
    // TODO Auto-generated constructor stub
}

VirtualMachineImage::VirtualMachineImage(const char *name, short kind, int64 bitLength)
:cPacket(name, kind, bitLength) {
}

VirtualMachineImage::~VirtualMachineImage() {

}

int VirtualMachineImage::getPriority() const
{
    return priority_var;
}

void VirtualMachineImage::setPriority(int priority)
{
    this->priority_var = priority;
}

simtime_t VirtualMachineImage::getTotalQueueingTime() const
{
    return totalQueueingTime_var;
}

void VirtualMachineImage::setTotalQueueingTime(simtime_t totalQueueingTime)
{
    this->totalQueueingTime_var = totalQueueingTime;
}

simtime_t VirtualMachineImage::getServiceTime() const
{
    return serviceTime_var;
}

void VirtualMachineImage::setServiceTime(simtime_t serviceTime)
{
    this->serviceTime_var = serviceTime;
}


simtime_t VirtualMachineImage::getTotalDelayTime() const
{
    return totalDelayTime_var;
}

void VirtualMachineImage::setTotalDelayTime(simtime_t totalDelayTime)
{
    this->totalDelayTime_var = totalDelayTime;
}

int VirtualMachineImage::getQueueCount() const
{
    return queueCount_var;
}

void VirtualMachineImage::setQueueCount(int queueCount)
{
    this->queueCount_var = queueCount;
}

int VirtualMachineImage::getDelayCount() const
{
    return delayCount_var;
}

void VirtualMachineImage::setDelayCount(int delayCount)
{
    this->delayCount_var = delayCount;
}

int VirtualMachineImage::getGeneration() const
{
    return generation_var;
}

void VirtualMachineImage::setGeneration(int generation)
{
    this->generation_var = generation;
}

std::string VirtualMachineImage::getOwner(){
    return owner;
}

void VirtualMachineImage::setOwner(std::string moduleOwner){
    owner = moduleOwner;
}

}; //namespace
