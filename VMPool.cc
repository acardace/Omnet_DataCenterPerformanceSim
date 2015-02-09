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

#include "VMPool.h"

namespace sds_project {

Define_Module(VMPool);

VMPool::VMPool(){};

VMPool::~VMPool(){};

void VMPool::initialize(){
    WATCH(amount);
    amount = par("amount");
    amountSignal = registerSignal("amount");
    emit(amountSignal, amount);
    if (ev.isGUI())
        updateDisplayString();
}

void VMPool::updateDisplayString(){
    char buf[80];
    sprintf(buf, "amount: %ld", amount);
    getDisplayString().setTagArg("t",0, buf);
}

bool VMPool::tryToAllocate(queueing::IResourceAllocator *allocator, long amountToAllocate, int priority){
    Enter_Method("allocate(%ld): %s", amountToAllocate, amount >= amountToAllocate ? "success" : "fail");
    if (amount >= amountToAllocate) {
        amount -= amountToAllocate;
        emit(amountSignal, amount);
        if (ev.isGUI())
            updateDisplayString();
        return true;
    }
    return false;
}

void VMPool::release(long amountToRelease){
    Enter_Method("release(%ld)", amountToRelease);

    amount += amountToRelease;
    emit(amountSignal, amount);
    if (ev.isGUI())
        updateDisplayString();
}

}; //namespace
