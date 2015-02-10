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
        @statistic[created](title="the number of VMs created";record=last;interpolationmode=none);
        @display("i=block/source");
        @class(sds_project::CyclicSource);
        int numVMs = default(-1);               // number of VMs to be generated (-1 means no limit)
        volatile double interArrivalTime @unit(s); // time between generated VMs
        volatile int diskSize @unit(b);
        string VMName = default("VM");         // the base name of the generated VM (will be the module name if left empty)
        volatile int VMType = default(0);       // the type attribute of the created VM (used by classifers and other modules)
        volatile int VMPriority = default(0);   // priority of the VM
        double startTime @unit(s) = default(interArrivalTime); // when the module sends out the first VM
        double stopTime @unit(s) = default(-1s); // when the module stops the VM generation (-1 means no limit)
    gates:
        output out;
}
