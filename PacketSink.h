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

#ifndef __SDS_PROJECT_PACKETSINK_H_
#define __SDS_PROJECT_PACKETSINK_H_

#include "QueueingDefs.h"

namespace sds_project {

/**
 * see NED file for more info
 */
class PacketSink : public cSimpleModule
{
  protected:
    simsignal_t lifeTimeSignal;
    simsignal_t waitingTimeSignal;
    simsignal_t queuesVisitedSignal;
    simsignal_t totalServiceTimeSignal;
    simsignal_t totalDelayTimeSignal;
    simsignal_t delaysVisitedSignal;
    simsignal_t generationSignal;
    simsignal_t serviceTime;
    simsignal_t availabilitySignal;
    simsignal_t responsivenessSignal;
    bool keepJobs, calcAvailability, calcServiceTime, calcWaitingTime;
    int jobCounter;

  public:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

    virtual simsignal_t getServiceTimeSignal();
};

}; //namespace

#endif

