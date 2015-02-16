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

#ifndef RESALLOCATOR_H_
#define RESALLOCATOR_H_

#include "Allocate.h"
#include "VirtualMachineImage.h"

namespace sds_project {

/*
 * See NED file for more info
 */

class ResAllocator: public queueing::Allocate {
    private:
        // state
        cQueue queue;

        // parameters
        int capacity;
        bool fifo, availabilityOnDrop, instantService;
        queueing::IResourcePool *resourcePool;
        int resourceAmount;
        int resourcePriority;
        double respLimit;
        int lessThanRespJobs;

        // statistics
        simsignal_t droppedSignal;
        simsignal_t queueLengthSignal;;
        simsignal_t lessThanRespLimitSignal;
        simsignal_t availability_tSignal;
        simsignal_t instantServiceSignal;
    public:
        ResAllocator();
        virtual ~ResAllocator();

        virtual void resourceGranted(queueing::IResourcePool *provider);
        virtual int getLessThanRespJobs();
    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual void enqueueOrForward(VirtualMachineImage *vm);
        virtual bool allocateResource(VirtualMachineImage *vm);
        virtual VirtualMachineImage *vmDequeue();
};

};//namespace

#endif /* RESALLOCATOR_H_ */
