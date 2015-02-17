package sds_project;

@license(LGPL);

import ned.DatarateChannel;

//
// TODO documentation
//
network Network
{
    @display("bgb=512,244");
    submodules:
        localDataCenter: DataCenter {
            @display("p=105,92");
        }
        remoteDataCenter[10]: DataCenter {
            @display("p=345,131");
        }
    connections:
        for i=0..9 {
            localDataCenter.out++ --> DatarateChannel --> remoteDataCenter[i].in++;
        }
}
