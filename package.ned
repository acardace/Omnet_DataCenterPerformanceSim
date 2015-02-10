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
    @display("bgb=517,206");
    gates:
        input in;
        output out;
    submodules:
        deallocate: Deallocate {
            @display("p=400,110");
            resourceModuleName = ".uploadQueueSize";
        }
        allocate: Allocate {
            @display("p=127,110");
            resourceModuleName = ".uploadQueueSize";
        }
        selector: Selector {
            @display("p=259,110");
        }
        drop: Sink {
            @display("p=399,20");
        }
        uploadQueueSize: ResourcePool {
            @display("p=127,20");
        }
    connections:
        deallocate.out --> out;
        in --> allocate.in++;
        allocate.out --> selector.in;
        selector.out --> deallocate.in++;
}

//
// TODO documentation
//
network DataCenter
{
    parameters:
        int phisicalMachines;
        int virtualMachines;
        @display("bgb=1214,246");
    gates:
        //input in;
        //output out;
    submodules:
        classifier: Classifier {
            @display("p=238,162");
        }
        Job_Completed: Sink {
            @display("p=853,34");
        }
        router: BetterRouter {
            @display("p=384,162");
            routingAlgorithm = default("minQueueLength");
            gates:
                out[phisicalMachines];
        }
        machine[phisicalMachines]: PMachine {
            @display("p=667,162");
        }
        resAllocator: ResAllocator {
            @display("p=99,162");
            resourceModuleName = ".VMs";
        }
        Pqueue_out: Deallocate {
            @display("p=1042,162");
            resourceModuleName = ".VMs";
        }
        source: Source {
            @display("p=99,43");
        }
        VMs: ResourcePool {
            @display("p=325,34");
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
        dataCenter: DataCenter {
            @display("p=83,45");
        }
    connections:
        //source.out --> dataCenter.in;
        //dataCenter.out --> sink.in++;
}
