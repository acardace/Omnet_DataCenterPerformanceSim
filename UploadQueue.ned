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

import org.omnetpp.queueing.Classifier;
import org.omnetpp.queueing.Deallocate;
import org.omnetpp.queueing.ResourcePool;
import org.omnetpp.queueing.Sink;


module UploadQueue
{
    @display("i=block/network;bgb=535,248");
    gates:
        input in;
        output out[];
    submodules:
        enqueue: ResAllocator {
            @display("p=104,141");
            resourceModuleName = ".queueSize";
        }
        dropped: PacketSink {
            @display("p=244,45");
        }
        selector: Selector {
            @display("p=413,141");
        }
        queueSize: ResourcePool {
            @display("p=104,45");
        }
        deallocate: Deallocate {
            @display("p=413,45");
            resourceModuleName = ".queueSize";
        }
    connections:
        in --> enqueue.in++;
        for i=0..sizeof(out)-1 {
            selector.out[i] --> out[i];
        }
        selector.discard --> deallocate.in++;
        deallocate.out --> dropped.in++;
        enqueue.out --> selector.in;
        enqueue.discard --> dropped.in++;
}
