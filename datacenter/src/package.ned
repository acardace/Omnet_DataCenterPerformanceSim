package datacenter;

import ned.IUnidirectionalChannel;
import org.omnetpp.queueing.Allocate;
import org.omnetpp.queueing.Deallocate;
import org.omnetpp.queueing.Delay;
import org.omnetpp.queueing.Queue;
import org.omnetpp.queueing.ResourceBasedQueue;
import org.omnetpp.queueing.ResourcePool;
import org.omnetpp.queueing.Router;
import org.omnetpp.queueing.Sink;
import org.omnetpp.queueing.Source;


@license(LGPL);
//
// TODO documentation
//
module DataCenter
{
    @display("bgb=626,341");
    gates:
        input in;
        output out;
    types:
    submodules:
        Pres: ResourcePool {
            @display("p=182,269");
        }
        Pqueue: ResourceBasedQueue {
            @display("p=84,140");
            resourceModuleName = default("Pres");
        }
        Prun: Queue {
            @display("p=306,140");
        }
    connections:
        in --> Pqueue.in++;
        Pqueue.out --> Prun.in++;
}

//
// TODO documentation
//
network Network
{
    @display("bgb=488,200");
    submodules:
        sink: Sink {
            @display("p=383,103");
        }
        source: Source {
            @display("p=56,84");
        }
        dataCenter: DataCenter {
            @display("p=231,94");
        }
    connections:
        source.out --> dataCenter.in;
        dataCenter.out --> sink.in++;
}

