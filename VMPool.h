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

#ifndef __SDS_PROJECT_VMPOOL_H_
#define __SDS_PROJECT_VMPOOL_H_

#include <omnetpp.h>
#include <ResourcePool.h>


class VMPool : public queueing::ResourcePool
{
  private:
    simsignal_t amountSignal;
    long amount;          // the amount of resource currently available

    void updateDisplayString();

  protected:
    virtual void initialize();

  public:
    VMPool();
    virtual ~VMPool();
    virtual bool tryToAllocate(queueing::IResourceAllocator *allocator, long amountToAllocate, int priority);
    virtual void release(long amountToRelease);
};

#endif
