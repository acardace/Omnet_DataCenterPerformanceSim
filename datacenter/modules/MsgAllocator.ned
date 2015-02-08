package datacenter.modules;

import org.omnetpp.queueing.Allocate;

//
// A module that defines an "accepted" or "rejected" message according to the available resources
//
simple MsgAllocator extends Allocate
{
    @class(MsgAllocator); 
}