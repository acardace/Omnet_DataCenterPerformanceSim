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

#include <VMPool.h>

namespace sds_project {

Define_Module(VMPool);

VMPool::VMPool(){};

VMPool::~VMPool(){};

std::ostream& operator << (std::ostream& out, const VMPool::AllocationRequest& req)
{
    out << req.allocator->getFullPath() << " amount: " << req.amountToAllocate << " priority: " << req.priority;
    return out;
}

void VMPool::initialize(){
    WATCH_LIST(allocatorList);
    WATCH(amount);
    amount = par("amount");
    physRes = getParentModule()->par("phisicalMachines");
    logRes = par("amount");
    utilization = registerSignal("utilization");
    emit(utilization, (logRes-amount)/physRes);
    if (ev.isGUI())
        updateDisplayString();
}

bool VMPool::tryToAllocate(queueing::IResourceAllocator *allocator, long amountToAllocate, int priority)
{
    Enter_Method("allocate(%ld): %s", amountToAllocate, amount >= amountToAllocate ? "success" : "fail");
    if (amount >= amountToAllocate) {
        amount -= amountToAllocate;
        emit(utilization, (logRes-amount)/physRes);
        if (ev.isGUI())
            updateDisplayString();
        return true;
    }
    else {
        // register the allocator for later notification
        AllocationRequest req;
        req.priority = priority;
        req.amountToAllocate = amountToAllocate;
        req.allocator = allocator;
        add(req);
        if (ev.isGUI())
            updateDisplayString();
        return false;
    }
}

void VMPool::release(long amountToRelease)
{
    Enter_Method("release(%ld)", amountToRelease);

    amount += amountToRelease;
    AllocationRequestList::iterator firstIt = allocatorList.begin();
    if (!allocatorList.empty() && firstIt->amountToAllocate <= amount) {
        amount -= firstIt->amountToAllocate;
        firstIt->allocator->resourceGranted(this);
        allocatorList.pop_front();
    }
    emit(utilization, (logRes-amount)/physRes);
    if (ev.isGUI())
        updateDisplayString();
}

void VMPool::add(AllocationRequest& request)
{
    // insert request into list, observing priority.
    // start from the back and look for the first request where priority is <= than ours,
    // and insert the new request after that one.
    for (AllocationRequestList::reverse_iterator i = allocatorList.rbegin(); i != allocatorList.rend(); i++) {
        if (i->priority <= request.priority) {
            allocatorList.insert(i.base(), request);
            return;
        }
    }

    // if not found, insert at the beginning
    allocatorList.push_front(request);
}

void VMPool::updateDisplayString()
{
    char buf[80];
    sprintf(buf, "amount: %ld\nrequests: %d", amount, (int)allocatorList.size());
    getDisplayString().setTagArg("t",0, buf);
}

};//namespace
