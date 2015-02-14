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

//
// Destroys (or optionally keep) the packets and collects statistics
//
simple PacketSink
{
    parameters:
        @class(sds_project::PacketSink);
        @display("i=block/sink");
        @signal[lifeTime](type="simtime_t");
        @signal[totalQueueingTime](type="simtime_t");
        @signal[totalDelayTime](type="simtime_t");
        @signal[totalServiceTime](type="simtime_t");
        @signal[queuesVisited](type="long");
        @signal[delaysVisited](type="long");
        @signal[generation](type="long");
        @statistic[lifeTime](title="lifetime of arrived jobs";unit=s;record=vector,mean,max;interpolationmode=none);
        @statistic[totalQueueingTime](title="the total time spent in queues by arrived jobs";unit=s;record=vector?,mean,max;interpolationmode=none);
        @statistic[totalDelayTime](title="the total time spent in delay nodes by arrived jobs";unit=s;record=vector?,mean,max;interpolationmode=none);
        @statistic[totalServiceTime](title="the total time spent  by arrived jobs";unit=s;record=vector?,mean,max;interpolationmode=none);
        @statistic[queuesVisited](title="the total number of queues visited by arrived jobs";record=vector?,mean,max;interpolationmode=none);
        @statistic[delaysVisited](title="the total number of delays visited by arrived jobs";record=vector?,mean,max;interpolationmode=none);
        @statistic[generation](title="the generation of the arrived jobs";record=vector?,mean,max;interpolationmode=none);
        bool keepJobs = default(false); // whether to keep the received jobs till the end of simulation
        bool calcAvailability = default(false); // whether to calculate data center availability (only for dropped jobs sink)
    gates:
        input in[];
}
