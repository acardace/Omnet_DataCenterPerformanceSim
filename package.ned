package sds_project;

@license(LGPL);

import ned.DatarateChannel;


network Cloud
{
    @display("bgb=1061,388");
    submodules:
        dataCenter: DataCenter {
            @display("p=83,45");
        }
        dataCenter1: DataCenter {
            @display("p=373,45");
        }
    connections:
        dataCenter.out --> DatarateChannel --> dataCenter1.in;
}
