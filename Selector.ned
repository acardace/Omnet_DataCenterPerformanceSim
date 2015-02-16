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
// Selector with additional features which allow to pre-allocate a resource from a remote DataCenter module
//
simple Selector
{
    parameters:
        @class(sds_project::Selector);
        @signal[federationAvailability](type="double");
  		@statistic[federationAvailability](record=vector,timeavg,mean,count);
  		@display("i=block/dispatch");
    gates:
        input in;
        output out[];
        output discard;
}
