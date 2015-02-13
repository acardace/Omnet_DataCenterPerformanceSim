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
        int vmDiskSize = default(100KiB) @unit(B);
        int mainQueueCapacity = default(-1);
        int uploadQueueCapacity = default(-1);
        @signal[utilization](type="double");
    	@statistic[utilization](title="utilization ratio";record=vector,mean,min,max,timeavg;interpolationmode=none);
        @display("bgb=722,417;i=device/mainframe;tt=A data center network, which includes a group of servers and generates its own VMs.");

    gates:
        input in[];
        output out[];
    submodules:
        Job_Completed: PacketSink {
            @display("p=654,43");
        }
        router: BetterRouter {
            @display("p=269,221");
            routingAlgorithm = default("minQueueLength");
            gates:
                out[phisicalMachines];
        }
        machine[phisicalMachines]: PMachine {
            @display("p=476,221");
        }
        resAllocator: ResAllocator {
            @display("p=89,221");
            resourceModuleName = ".VMs";
            capacity = mainQueueCapacity;
        }
        Pqueue_out: Deallocate {
            @display("p=654,221");
            resourceModuleName = ".VMs";
        }
        cyclicSource: CyclicSource {
            @display("p=89,43");
            jobName = default("VM");
            diskSize = vmDiskSize;
        }
        uploadQueue: UploadQueue {
            @display("p=210,100");
            capacity = uploadQueueCapacity;
        }
        VMs: ResourcePool {
            @display("p=446,100");
            amount = virtualMachines;
        }
        remoteDeallocate: RemoteDeallocate {
            @display("p=269,322");
            resourceModuleName = "queueSize";
        }
    connections:
        for i=0..phisicalMachines-1 {
            router.out[i] --> machine[i].in++;
            machine[i].out --> Pqueue_out.in++;
        }
        Pqueue_out.out --> Job_Completed.in++;
        cyclicSource.out --> resAllocator.in++;
        for i=0..sizeof(out)-1 {
            uploadQueue.out++ --> out[i];
        }
        for i=0..sizeof(in)-1 {
            in[i] --> remoteDeallocate.in++;
        }
        resAllocator.out --> router.in++;
        resAllocator.discard --> uploadQueue.in;
        remoteDeallocate.out --> router.in++;
}
