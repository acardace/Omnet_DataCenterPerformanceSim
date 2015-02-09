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
@license(LGPL);
module UploadQueue
{
    @display("bgb=615,251");
    gates:
        input in;
        output out;
    submodules:
        selector: Selector {
            @display("p=60,176");
        }
        resAllocator: ResAllocator {
            @display("p=220,176");
        }
        deallocate: Deallocate {
            @display("p=532,176");
        }
        classifier: Classifier {
            @display("p=381,176");
        }
        uploadQueueSize: VMPool {
            @display("p=220,64");
        }
        discarded: Sink {
            @display("p=381,64");
        }
    connections:
        in --> selector.in;
        selector.out --> resAllocator.in++;
        resAllocator.out --> classifier.in++;
        classifier.out++ --> deallocate.in++;
        deallocate.out --> out;
        classifier.rest --> discarded.in++;
}

//
// TODO documentation
//
network DataCenter
{
    parameters:
        int phisicalMachines;
        int virtualMachines;
        @display("bgb=722,246");
    gates:
        //input in;
        //output out;
    submodules:
        classifier: Classifier {
            @display("p=238,162");
        }
        Job_Completed: Sink {
            @display("p=605,43");
        }
        router: BetterRouter {
            @display("p=345,162");
            routingAlgorithm = default("minQueueLength");
            gates:
                out[phisicalMachines];
        }
        machine[phisicalMachines]: PMachine {
            @display("p=478,162");
        }
        resAllocator: ResAllocator {
            @display("p=99,162");
            resourceModuleName = ".VMs";
        }
        Pqueue_out: Deallocate {
            @display("p=605,162");
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
