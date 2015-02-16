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

#ifndef VIRTUALMACHINEIMAGE_H_
#define VIRTUALMACHINEIMAGE_H_

#include <omnetpp.h>

/*
 * Abstraction of a Virtual Machine image
 */

namespace sds_project {

class VirtualMachineImage: public cPacket{
protected:
    int priority_var;
    int queueCount_var;
    int delayCount_var;
    int generation_var;
    simtime_t totalQueueingTime_var;
    simtime_t serviceTime_var;
    simtime_t totalDelayTime_var;
    std::string owner;

public:
    VirtualMachineImage();
    VirtualMachineImage(const char *name=NULL, short kind=0, int64 bitLength=0);
    virtual ~VirtualMachineImage();

    virtual int getPriority() const;
    virtual void setPriority(int priority);

    //statistics related functions
    virtual simtime_t getTotalQueueingTime() const;
    virtual void setTotalQueueingTime(simtime_t totalQueueingTime);
    virtual simtime_t getServiceTime() const;
    virtual void setServiceTime(simtime_t serviceTime);
    virtual simtime_t getTotalDelayTime() const;
    virtual void setTotalDelayTime(simtime_t totalDelayTime);
    virtual int getQueueCount() const;
    virtual void setQueueCount(int queueCount);
    virtual int getDelayCount() const;
    virtual void setDelayCount(int delayCount);
    virtual int getGeneration() const;
    virtual void setGeneration(int generation);
    virtual std::string getOwner();
    virtual void setOwner(std::string moduleOwner);
};

}; //namespace

#endif /* VIRTUALMACHINEIMAGE_H_ */
