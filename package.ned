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

import ned.DatarateChannel;

//
// TODO documentation
//
network Network
{
    @display("bgb=650,334");
    submodules:
        dataCenter: DataCenter {
            @display("p=105,92");
        }
        dataCenter1: DataCenter {
            @display("p=404,131");
        }
        dataCenter2: DataCenter {
            @display("p=296,288");
        }
    connections:
        dataCenter.out++ --> DatarateChannel --> dataCenter1.in++;
        dataCenter.out++ --> DatarateChannel --> dataCenter2.in++;
        dataCenter1.out++ --> DatarateChannel --> dataCenter2.in++;
}
