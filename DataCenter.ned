//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package sds_project;

import ned.DatarateChannel;
import org.omnetpp.queueing.Classifier;
import org.omnetpp.queueing.Deallocate;
import org.omnetpp.queueing.ResourcePool;
import org.omnetpp.queueing.Sink;
import org.omnetpp.queueing.Source;

module DataCenter
{
    parameters:
        int phisicalMachines;
        int virtualMachines;
        @display("bgb=722,244");
    gates:
        //input in;
        //output out;
    submodules:
        classifier: GenericClassifier {
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
        cyclicSource: CyclicSource {
            @display("p=99,43");
        }
    connections:
        classifier.out++ --> router.in++;
        for i=0..phisicalMachines-1 {
            router.out[i] --> machine[i].in++;
            machine[i].out --> Pqueue_out.in++;
        }
        Pqueue_out.out --> Job_Completed.in++;
        resAllocator.out --> classifier.in++;
        classifier.rest --> Job_Completed.in++;
        cyclicSource.out --> resAllocator.in++;
}
