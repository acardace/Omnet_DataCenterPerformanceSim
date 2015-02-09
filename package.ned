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
        @display("bgb=708,232");
    gates:
        //input in;
        //output out;
    submodules:
        classifier: Classifier {
            @display("p=192,144");
        }
        Job_Completed: Sink {
            @display("p=635,43");
        }
        router: Router {
            @display("p=317,144");
            gates:
                out[phisicalMachines];
        }
        machine[phisicalMachines]: Queue {
            @display("p=466,144");
        }
        VMs: ResourcePool {
            @display("p=368,43");
            amount = virtualMachines;
        }
        resAllocator: ResAllocator {
            @display("p=60,144");
            resourceModuleName = ".VMs";
            resourceAmount = virtualMachines;
        }
        Pqueue_out: Deallocate {
            @display("p=635,144");
            resourceModuleName = ".VMs";
            resourceAmount = virtualMachines;
        }
        source: Source {
            @display("p=60,43");
        }
        sink: Sink {
            @display("p=191,51");
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
        classifier.rest --> sink.in++;
}
