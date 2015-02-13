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

#ifndef __SDS_PROJECT_PMACHINE_H_
#define __SDS_PROJECT_PMACHINE_H_

#include <omnetpp.h>
#include <Job.h>

namespace sds_project{

class PMachine : public cSimpleModule
{
  private:
    simsignal_t serviceTime;
    double degradation;
    int VMs;

  protected:
    int logicalRes;
    int physicalRes;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual simtime_t startService(cMessage *job);
    virtual void endService(cMessage *job);

  public:

    PMachine();
    virtual ~PMachine();
    int length();

};

}; //namespace

#endif
