package sds_project;

@license(LGPL);

import ned.DatarateChannel;

//
// TODO documentation
//
network Network
{
    @display("bgb=775,348");
    submodules:
        dataCenter0: DataCenter {
            @display("p=105,92");
        }
        dataCenter1: DataCenter {
            @display("p=307,43");
        }
        dataCenter2: DataCenter {
            @display("p=254,190");
        }
        dataCenter3: DataCenter {
            @display("p=523,73");
        }
        dataCenter4: DataCenter {
            @display("p=469,218");
        }
    connections:
        dataCenter0.out++ --> DatarateChannel --> dataCenter1.in++;
        dataCenter0.out++ --> DatarateChannel --> dataCenter2.in++;
        dataCenter1.out++ --> DatarateChannel --> dataCenter0.in++;
        dataCenter3.out++ --> DatarateChannel --> dataCenter2.in++;
        dataCenter4.out++ --> DatarateChannel --> dataCenter1.in++;
        dataCenter1.out++ --> DatarateChannel --> dataCenter3.in++;
        dataCenter3.out++ --> DatarateChannel --> dataCenter4.in++;
        dataCenter4.out++ --> DatarateChannel --> dataCenter2.in++;
        dataCenter1.out++ --> DatarateChannel --> dataCenter4.in++;
}
