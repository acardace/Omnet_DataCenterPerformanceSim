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
module DataCenter
{
    parameters:
        int phisicalMachines;
        int virtualMachines;
        @display("bgb=1177,305");
    gates:
        input in;
        output out;
    submodules:
        VMs: ResourcePool {
            @display("p=484,35");
            amount = virtualMachines;
        }
        classifier: Classifier {
            @display("p=232,144");
        }
        Job_Completed: Sink {
            @display("p=907,43");
        }
        router: Router {
            @display("p=345,144");
            gates:
                out[phisicalMachines];
        }
        machine[phisicalMachines]: Queue {
            @display("p=585,144");
        }
        resAllocator: ResAllocator {
            @display("p=90,144");
        }
        deallocate: Deallocate {
            @display("p=868,144");
        }
    connections:
        classifier.out++ --> router.in++;
        for i=0..phisicalMachines-1 {
            router.out[i] --> machine[i].in++;
        }
        classifier.rest --> out;
        resAllocator.out --> classifier.in++;
        in --> resAllocator.in++;
        machine[0].out --> deallocate.in++;
        deallocate.out --> Job_Completed.in++;
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
