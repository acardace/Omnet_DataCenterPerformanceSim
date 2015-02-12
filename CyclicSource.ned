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

import org.omnetpp.queueing.Source;
package sds_project;

//
// TODO auto-generated module
//
simple CyclicSource
{
    parameters:
        @signal[created](type="long");
        @statistic[created](title="the number of jobs created";record=last;interpolationmode=none);
        @display("i=block/source");
        @class(sds_project::CyclicSource);
        int numJobs = default(-1);               // number of jobs to be generated (-1 means no limit)
        // time between generated jobs
		volatile double interArrivalTime1 @unit(s);
		volatile double interArrivalTime2 @unit(s) = default(-1s);
		volatile double interArrivalTime3 @unit(s) = default(-1s);
		volatile double interArrivalTime4 @unit(s) = default(-1s);
		volatile double interArrivalTime5 @unit(s) = default(-1s);
		volatile double interArrivalTimeDuration1 @unit(s) = default(0s);
		volatile double interArrivalTimeDuration2 @unit(s) = default(0s);
		volatile double interArrivalTimeDuration3 @unit(s) = default(0s);
		volatile double interArrivalTimeDuration4 @unit(s) = default(0s);
		volatile double interArrivalTimeDuration5 @unit(s) = default(0s);
        volatile int diskSize @unit(b);
        string jobName = default("job");         // the base name of the generated job (will be the module name if left empty)
        volatile int jobType = default(0);       // the type attribute of the created job (used by classifers and other modules)
        volatile int jobPriority = default(0);   // priority of the job
        double startTime @unit(s) = default(interArrivalTime1); // when the module sends out the first job
        double stopTime @unit(s) = default(-1s); // when the module stops the job generation (-1 means no limit)
    gates:
        output out;
}
