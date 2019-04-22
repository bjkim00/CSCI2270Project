#include "PriorityQueue.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <limits>
#include <float.h>

using namespace std;

//Purpose: perform all operations necessary to instantiate a class object
PriorityQueue::PriorityQueue(int queueSize){
    priorityQueue = new RoadNode[queueSize];
    maxQueueSize = queueSize;
    currentQueueSize = 0;
    //We set the max and min data to negatives for max and positve for min
    //so that we are sure they will be adjusted by any inputted data
    maxTraffic = -FLT_MAX;
    minTraffic = FLT_MAX;
    maxIRI = -FLT_MAX;
    minIRI = FLT_MAX;
    maxRUT = -FLT_MAX;
    minRUT = FLT_MAX;
}

// Purpose: free all resources that the object has acquired
PriorityQueue::~PriorityQueue(){
    while(currentQueueSize!=0){
        dequeue();
    }
    delete[] priorityQueue;
}

//Purpose: Calculate priority of highway
float PriorityQueue::calcPriority(int _quality, float _trafficVolume, float _iri, float _rut){
    return ((_trafficVolume * _quality) - _iri - _rut);
}

//Purpose: Normalize the traffic of the highways between 0 and 1
void PriorityQueue::calcNormTraffic(){
    for(int i = 0; i < currentQueueSize; i++){
        priorityQueue[i].trafficVolume = (priorityQueue[i].trafficVolume - minTraffic)/(maxTraffic - minTraffic);
    }
}

//Purpose: Normalize the IRI values between 0 and 1
void PriorityQueue::calcNormIRI(){
    for(int i = 0; i < currentQueueSize; i++){
        priorityQueue[i].iri = (priorityQueue[i].iri - minIRI)/(maxIRI - minIRI);
    }
}

//Purpose: Normalize the RUT values between 0 and 1
void PriorityQueue::calcNormRUT(){
    for(int i = 0; i < currentQueueSize; i++){
        priorityQueue[i].rut = (priorityQueue[i].rut - minRUT)/(maxRUT - minRUT);
    }
}

// Purpose: enqueue new group into priority queue; call the calc priority with the given values
void PriorityQueue::enqueue (string _highway, float _sectionLength, int _quality, float _trafficVolume, float _iri, float _rut){
    if(currentQueueSize == maxQueueSize)
    {
        cout<<"Heap full, cannot enqueue"<<endl;
        return;
    }
    else{
        currentQueueSize++;
        int index = currentQueueSize - 1;
        RoadNode addedGroup;
        addedGroup.highway = _highway;
        addedGroup.sectionLength = _sectionLength;
        addedGroup.quality = _quality;
        addedGroup.trafficVolume = _trafficVolume;
        addedGroup.priority = calcPriority(_quality, _trafficVolume, _iri, _rut);
        addedGroup.iri = _iri;
        addedGroup.rut = _rut;
        //The following if statements just check to see if the new data
        //are either min or max in their respective categories
        if(addedGroup.trafficVolume >= maxTraffic){
            maxTraffic = addedGroup.trafficVolume;
        }
        if(addedGroup.trafficVolume <= minTraffic){
            minTraffic = addedGroup.trafficVolume;
        }
        if(addedGroup.iri >= maxIRI){
            maxIRI = addedGroup.iri;
        }
        if(addedGroup.iri <= minIRI){
            minIRI = addedGroup.iri;
        }
        if(addedGroup.rut >= maxRUT){
            maxRUT = addedGroup.rut;
        }
        if(addedGroup.rut <= minRUT){
            minRUT = addedGroup.rut;
        }
        if(_trafficVolume/_sectionLength >= 150000){ //This ratio for now is subject to change. I am not sure what the ratio
            //should be in order to have a decent number of highways to be recommened to add HOV or Toll lanes
            addedGroup.severity = true;
        }else{
            addedGroup.severity = false;
        }
        priorityQueue[index] = addedGroup;
        if(index>0){
          repairUpward(index);
        }
    }
}

//Purpose: remove the group (allocate the table) at the front of the priority queue from
void PriorityQueue::dequeue(){
    if(isEmpty()){
        return;
    }
    priorityQueue[0] = priorityQueue[currentQueueSize-1];
    currentQueueSize--;
    repairDownward(0);
}

// return: groupID of the group at the front of the priority queue
RoadNode PriorityQueue::peek(){
    if(isEmpty()){
        cout<<"Heap empty, nothing to peek"<<endl;
    }
    else{
        return priorityQueue[0];
    }
}

//return: true if queue is full, false otherwise
bool PriorityQueue::isFull(){
    if(currentQueueSize == maxQueueSize){
        return true;
    }
    else{
        return false;
    }
}

// return: true if queue is empty, false otherwise
bool PriorityQueue::isEmpty(){
    if(currentQueueSize == 0){
        return true;
    }
    else{
        return false;
    }
}

//The repairUpward and repairDownward just help keep the shape and
//rules of the heap in check

//Ultimately, these two functions are very similar to functions we had written for
//class homework and recitation
void PriorityQueue::repairUpward(int nodeIndex){
    int parent = (nodeIndex-1)/2;
    if (parent >= 0 && priorityQueue[parent].priority < priorityQueue[nodeIndex].priority){
        RoadNode temp;
        temp.highway = priorityQueue[parent].highway;
        temp.sectionLength = priorityQueue[parent].sectionLength;
        temp.quality = priorityQueue[parent].quality;
        temp.trafficVolume = priorityQueue[parent].trafficVolume;
        temp.priority = priorityQueue[parent].priority;
        temp.severity = priorityQueue[parent].severity;
        temp.iri = priorityQueue[parent].iri;
        temp.rut = priorityQueue[parent].rut;
        priorityQueue[parent] = priorityQueue[nodeIndex];
        priorityQueue[nodeIndex] = temp;
        repairUpward(parent);
        return;
    }
    else if(parent>=0 && priorityQueue[parent].priority == priorityQueue[nodeIndex].priority){
        if(priorityQueue[parent].sectionLength < priorityQueue[nodeIndex].sectionLength){
            RoadNode temp;
            temp.highway = priorityQueue[parent].highway;
            temp.sectionLength = priorityQueue[parent].sectionLength;
            temp.quality = priorityQueue[parent].quality;
            temp.trafficVolume = priorityQueue[parent].trafficVolume;
            temp.priority = priorityQueue[parent].priority;
            temp.severity = priorityQueue[parent].severity;
            temp.iri = priorityQueue[parent].iri;
            temp.rut = priorityQueue[parent].rut;
            priorityQueue[parent] = priorityQueue[nodeIndex];
            priorityQueue[nodeIndex] = temp;
            repairUpward(parent);
            return;
        }
    }
    return;
}

void PriorityQueue::repairDownward(int nodeIndex){
    int leftChild = (2*nodeIndex)+1;
    int rightChild = (2*nodeIndex)+2;
    int highestPriority = nodeIndex;
    if (leftChild < currentQueueSize && priorityQueue[leftChild].priority >= priorityQueue[highestPriority].priority){
        if(priorityQueue[leftChild].priority == priorityQueue[highestPriority].priority && priorityQueue[leftChild].sectionLength > priorityQueue[highestPriority].sectionLength){
            highestPriority = leftChild;
        }
        else if(priorityQueue[leftChild].priority > priorityQueue[highestPriority].priority){
            highestPriority = leftChild;
        }
    }
    if (rightChild < currentQueueSize && priorityQueue[rightChild].priority >= priorityQueue[highestPriority].priority){
        if(priorityQueue[rightChild].priority == priorityQueue[highestPriority].priority && priorityQueue[rightChild].sectionLength > priorityQueue[highestPriority].sectionLength){
            highestPriority = rightChild;
        }
        else if(priorityQueue[rightChild].priority > priorityQueue[highestPriority].priority){
            highestPriority = rightChild;
        }
    }

    if(highestPriority!= nodeIndex){
        RoadNode temp;
        temp.highway = priorityQueue[highestPriority].highway;
        temp.sectionLength = priorityQueue[highestPriority].sectionLength;
        temp.quality = priorityQueue[highestPriority].quality;
        temp.trafficVolume = priorityQueue[highestPriority].trafficVolume;
        temp.priority = priorityQueue[highestPriority].priority;
        temp.severity = priorityQueue[highestPriority].severity;
        temp.iri = priorityQueue[highestPriority].iri;
        temp.rut = priorityQueue[highestPriority].rut;
        priorityQueue[highestPriority] = priorityQueue[nodeIndex];
        priorityQueue[nodeIndex] = temp;
        repairDownward(highestPriority);
    }
}
