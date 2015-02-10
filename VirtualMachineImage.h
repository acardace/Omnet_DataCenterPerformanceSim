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

#ifndef VIRTUALMACHINEIMAGE_H_
#define VIRTUALMACHINEIMAGE_H_

#include <cmessage.h>
#include <Job.h>

class VirtualMachineImage: public cPacket {
protected:
    Job *job;
public:
    VirtualMachineImage();
    virtual ~VirtualMachineImage();
    Job *getJob();
    void setJob(Job *job);
};

#endif /* VIRTUALMACHINEIMAGE_H_ */
