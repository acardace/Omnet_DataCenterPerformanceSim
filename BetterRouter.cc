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

#include "PMachine.h"
#include "BetterRouter.h"
#include <limits>

namespace sds_project {

Define_Module(BetterRouter);

void BetterRouter::initialize()
{
    const char *algName = par("routingAlgorithm");

    if (strcmp(algName, "random") == 0) {
        routingAlgorithm = ALG_RANDOM;
    } else if (strcmp(algName, "roundRobin") == 0) {
        routingAlgorithm = ALG_ROUND_ROBIN;
    } else if (strcmp(algName, "minQueueLength") == 0) {
        routingAlgorithm = ALG_MIN_QUEUE_LENGTH;
    } else if (strcmp(algName, "minDelay") == 0) {
        routingAlgorithm = ALG_MIN_DELAY;
    } else if (strcmp(algName, "minServiceTime") == 0) {
        routingAlgorithm = ALG_MIN_SERVICE_TIME;
    } else if (strcmp(algName, "nonFullQueue") == 0) {
        routingAlgorithm = ALG_NON_FULL_QUEUE;
    } else if (strcmp(algName, "nonFullQueue") == 0) {
        routingAlgorithm = ALG_NON_FULL_QUEUE;
    }
    rrCounter = 0;
}

void BetterRouter::handleMessage(cMessage *msg)
{
    int outGateIndex = -1;  // by default we drop the message
    switch (routingAlgorithm)
    {
        case ALG_RANDOM:
            outGateIndex = par("randomGateIndex");
            break;
        case ALG_ROUND_ROBIN:
            outGateIndex = rrCounter;
            rrCounter = (rrCounter + 1) % gateSize("out");
            break;
        case ALG_MIN_QUEUE_LENGTH:
            int min;
            min = std::numeric_limits<int>::max();
            for (int i=0; i < gateSize("out"); i++) {
                cGate *otherGate = gate("out", i)->getNextGate();
                PMachine *pm = check_and_cast<PMachine *>(otherGate->getOwnerModule());
                if (pm->length() < min) {
                    min = pm->length();
                    outGateIndex = i;
                }
            }
            break;
        case ALG_MIN_DELAY:
            // TODO implementation missing
            outGateIndex = -1;
            break;
        case ALG_MIN_SERVICE_TIME:
            // TODO implementation missing
            outGateIndex = -1;
            break;
        case ALG_NON_FULL_QUEUE:
            // TODO implementation missing
            outGateIndex = -1;
            break;
        default:
            outGateIndex = -1;
            break;
    }

    // send out if the index is legal
    if (outGateIndex < 0 || outGateIndex >= gateSize("out"))
        error("Invalid output gate selected during routing");

    send(msg, "out", outGateIndex);
}

}; //namespace
