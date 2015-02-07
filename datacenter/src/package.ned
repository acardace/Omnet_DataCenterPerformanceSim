package datacenter;

import ned.IUnidirectionalChannel;
import org.omnetpp.queueing.Allocate;
import org.omnetpp.queueing.Classifier;
import org.omnetpp.queueing.Deallocate;
import org.omnetpp.queueing.Delay;
import org.omnetpp.queueing.Dot;
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
        output out[];
    types:
    submodules:
        Pres: ResourcePool {
            @display("p=242,277");
        }
        Prun: Delay {
            @display("p=361,144");
        }
        classifier: Classifier {
            @display("p=184,144");
        }
        allocate: Allocate {
            @display("p=88,144");
        }
        deallocate: Deallocate {
            @display("p=497,144");
        }
    connections:
        classifier.out++ --> Prun.in++;
        in --> allocate.in++;
        allocate.out --> classifier.in++;
        Prun.out --> deallocate.in++;
        classifier.out++ --> out++;
        deallocate.out --> out++;
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

