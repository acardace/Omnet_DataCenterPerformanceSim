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

//Resource pool module, it just grants resources on request if they are available
simple VMPool
{
    parameters:
        @class(sds_project::VMPool);
        @signal[amount](type="long");
        @statistic[amount](title="available resource";record=vector?,timeavg,min;interpolationmode=sample-hold);
        @display("i=block/buffer;t=,r,black");
        int amount = default(1);        // the amount of resource units
}
