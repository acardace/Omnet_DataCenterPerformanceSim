package datacenter.src;

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
    parameters:
        int phisicalMachines;
        int virtualMachines;
        @display("bgb=726,248");
    gates:
        input in;
        output out;
    types:
    submodules:
        VMs: ResourcePool {
            @display("p=53,61");
            amount = virtualMachines;
        }
        classifier: Classifier {
            @display("p=184,144");
        }
        allocate: Allocate {
            @display("p=53,144");
            resourceModuleName = "VMs";
        }
        deallocate: Deallocate {
            @display("p=666,144");
            resourceModuleName = "VMs";
        }
        Job_Completed: Sink {
            @display("p=666,35");
        }
        router: Router {
            @display("p=326,144");
            gates:
                out[phisicalMachines];
        }
        machine[phisicalMachines]: Queue {
            @display("p=491,144");
        }
    connections:
        in --> allocate.in++;
        allocate.out --> classifier.in++;
        deallocate.out --> Job_Completed.in++;
        classifier.out++ --> router.in++;
        classifier.out++ --> out;
        for i=0..phisicalMachines-1 {
            router.out[i] --> machine[i].in++;
            machine[i].out --> deallocate.in++;
        }
}

//
// TODO documentation
//
network Network
{
    @display("bgb=488,200");
    submodules:
        sink: Sink {
            @display("p=380,84");
        }
        source: Source {
            @display("p=56,84");
            interArrivalTime = exponential(3s);
        }
        dataCenter: DataCenter {
            @display("p=232,84");
        }
    connections:
        source.out --> dataCenter.in;
        dataCenter.out --> sink.in++;
}

