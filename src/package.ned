package datacenter.src;

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
<<<<<<< HEAD
            @display("p=326,144");
=======
            @display("p=345,144");
>>>>>>> 482120f28fb0b62cb7b78fddd6ead901fdd7ee24
            gates:
                out[phisicalMachines];
        }
        machine[phisicalMachines]: Queue {
            @display("p=585,144");
        }
        Pqueue_in: MsgAllocator {
            @display("p=79,144");
            resourceModuleName = "VMs";
        }
        Pqueue_out: Deallocate {
            @display("p=888,144");
            resourceModuleName = "VMs";
        }
    connections:
        Pqueue_out.out --> Job_Completed.in++;
        classifier.out++ --> router.in++;
        for i=0..phisicalMachines-1 {
            router.out[i] --> machine[i].in++;
            machine[i].out --> Pqueue_out.in++;
        }
        in --> Pqueue_in.in++;
        Pqueue_in.out --> classifier.in++;
        classifier.rest --> out;
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

