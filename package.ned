package sds_project;

@license(LGPL);

import org.omnetpp.queueing.Allocate;
import org.omnetpp.queueing.Classifier;
import org.omnetpp.queueing.Deallocate;
import org.omnetpp.queueing.Dot;
import org.omnetpp.queueing.Queue;
import org.omnetpp.queueing.ResourcePool;
import org.omnetpp.queueing.Router;
import org.omnetpp.queueing.Sink;
import org.omnetpp.queueing.Source;

import ned.DatarateChannel;

//
// TODO documentation
//
network Network
{
    @display("bgb=488,200");
    submodules:
        dataCenter: DataCenter {
            @display("p=215,84");
        }
    connections:
}
