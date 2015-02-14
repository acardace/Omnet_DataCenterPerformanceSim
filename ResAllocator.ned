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

import org.omnetpp.queueing.Allocate;

simple ResAllocator extends Allocate
{
    parameters:
        @signal[dropped](type="double");
        @signal[lessThanRespLimit](type="bool");
        @statistic[dropped](title="Queue full, job dropped";record=vector?,count,timeavg;interpolationmode=none);
        @statistic[lessThanRespLimit](title="Request accepted within time limit";record=vector?,count;interpolationmode=none);
    	@class(sds_project::ResAllocator);
    	fifo = true;
    	double respLimit @unit(s) = default(60s);
    	bool instantService = default(true);
    	bool availabilityOnDrop = default(true);
   	gates:
   	    output discard;
}
