package datacenter;

import ned.IUnidirectionalChannel;
import org.omnetpp.queueing.Allocate;
import org.omnetpp.queueing.Deallocate;
import org.omnetpp.queueing.Delay;
import org.omnetpp.queueing.ResourceBasedQueue;
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
        resourceBasedQueue: ResourceBasedQueue {
            @display("p=246,105");
        }
        delay: Delay {
            @display("p=466,184");
        }
    connections:
        in --> resourceBasedQueue.in++;
        resourceBasedQueue.out --> delay.in++;
        delay.out --> out;
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

