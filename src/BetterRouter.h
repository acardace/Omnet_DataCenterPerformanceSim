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

#ifndef __DATACENTER_BETTERROUTER_H_
#define __DATACENTER_BETTERROUTER_H_

#include <omnetpp.h>
#include "Router.h"

/**
 * Router with additional policies for:
 * 1) assigning a VM to the least congestioned PM;
 * 2) moving a VM to a free data center.
 */

namespace datacenter {

class BetterRouter : public queueing::Router
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

}; //namespace
#endif
