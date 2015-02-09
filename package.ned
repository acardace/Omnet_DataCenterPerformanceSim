package sds_project;

@license(LGPL);

import org.omnetpp.queueing.Allocate;
import org.omnetpp.queueing.Classifier;
import org.omnetpp.queueing.Deallocate;
import org.omnetpp.queueing.Queue;
import org.omnetpp.queueing.ResourcePool;
import org.omnetpp.queueing.Router;
import org.omnetpp.queueing.Sink;
import org.omnetpp.queueing.Source;
@license(LGPL);
//
// TODO documentation
//
network DataCenter
{
    parameters:
        int phisicalMachines;
        int virtualMachines;
        @display("bgb=689,236");
    gates:
        //input in;
        //output out;
    submodules:
        classifier: Classifier {
            @display("p=217,162");
        }
        Job_Completed: Sink {
            @display("p=610,43");
        }
        router: BetterRouter {
            @display("p=345,162");
            routingAlgorithm = default("minQueueLength");
            gates:
                out[phisicalMachines];
        }
        machine[phisicalMachines]: Queue {
            @display("p=476,162");
        }
        resAllocator: ResAllocator {
            @display("p=99,162");
            resourceModuleName = ".VMs";
        }
        Pqueue_out: Deallocate {
            @display("p=610,162");
            resourceModuleName = ".VMs";
        }
        source: Source {
            @display("p=99,43");
        }
        VMs: VMPool {
            @display("p=345,43");
            amount = virtualMachines;
        }
    connections:
        classifier.out++ --> router.in++;
        for i=0..phisicalMachines-1 {
            router.out[i] --> machine[i].in++;
            machine[i].out --> Pqueue_out.in++;
        }
        Pqueue_out.out --> Job_Completed.in++;
        resAllocator.out --> classifier.in++;
        source.out --> resAllocator.in++;
        classifier.rest --> Job_Completed.in++;
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
        //source.out --> dataCenter.in;
        //dataCenter.out --> sink.in++;
}
