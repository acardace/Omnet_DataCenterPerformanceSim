// This program is free software: you can redistribute it and/or modify

#include "GenericClassifier.h"

namespace sds_project {

Define_Module(GenericClassifier);

void GenericClassifier::initialize()
{
}

void GenericClassifier::handleMessage(cMessage *msg)
{
    int outGateIndex = -1;
    outGateIndex = msg->getKind();
    if (outGateIndex < 0 || outGateIndex >= gateSize("out"))
        send(msg, "rest");
    else
        send(msg, "out", outGateIndex);
}

}; //namespace

