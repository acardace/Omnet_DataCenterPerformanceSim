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
        @display("bgb=686,305");
    gates:
        input in;
        output out;
    submodules:
        classifier: Classifier {
            @display("p=232,144");
        }
        Job_Completed: Sink {
            @display("p=616,34");
        }
        router: Router {
            @display("p=345,144");
            gates:
                out[phisicalMachines];
        }
        machine[phisicalMachines]: Queue {
            @display("p=492,144");
        }
        Pqueue_in: Allocate {
            @display("p=79,144");
            resourceModuleName = "VMs";
        }
        VMs: ResourcePool {
            @display("p=427,34");
            amount = virtualMachines;
        }
        Pqueue_out: Deallocate {
            @display("p=616,144");
            resourceModuleName = "VMs";
        }
    connections:
        classifier.out++ --> router.in++;
        for i=0..phisicalMachines-1 {
            router.out[i] --> machine[i].in++;
            machine[i].out --> Pqueue_out.in++;
        }
        classifier.rest --> out;
        Pqueue_in.out --> classifier.in++;
        in --> Pqueue_in.in++;
        Pqueue_out.out --> Job_Completed.in++;
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
