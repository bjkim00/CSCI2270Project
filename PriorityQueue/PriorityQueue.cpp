#include "PriorityQueue.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

//Purpose: perform all operations necessary to instantiate a class object
PriorityQueue::PriorityQueue(int queueSize){
    priorityQueue = new RoadNode[queueSize];
    maxQueueSize = queueSize;
    currentQueueSize = 0;
}

// Purpose: free all resources that the object has acquired
PriorityQueue::~PriorityQueue(){
    while(currentQueueSize!=0){
        dequeue();
    }
    delete[] priorityQueue;
}

//Purpose: Calculate priority of highway
float PriorityQueue::calcPriority(int _quality, int _trafficVolume, int _iri, int _rut){
    return ((_trafficVolume * _quality) + _iri + _rut)/1000000;
}

// Purpose: enqueue new group into priority queue; call other
void PriorityQueue::enqueue (float _sectionLength, int _quality, int _trafficVolume, string _severity, int _iri, int _rut){
    if(currentQueueSize == maxQueueSize)
    {
        cout<<"Heap full, cannot enqueue"<<endl;
        return;
    }
    else{
        currentQueueSize++;
        int index = currentQueueSize - 1;
        RoadNode addedGroup;
        addedGroup.sectionLength = _sectionLength;
        addedGroup.quality = _quality;
        addedGroup.trafficVolume = _trafficVolume;
        addedGroup.priority = calcPriority(_quality, _trafficVolume, _iri, _rut);
        addedGroup.iri = _iri;
        addedGroup.rut = _rut;
        addedGroup.severity = _severity;
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

void PriorityQueue::repairUpward(int nodeIndex){
    int parent = (nodeIndex-1)/2;
    if (parent >= 0 && priorityQueue[parent].priority < priorityQueue[nodeIndex].priority){ //would parent point to NULL ever?
        RoadNode temp;
        temp.sectionLength = priorityQueue[parent].sectionLength;
        temp.quality = priorityQueue[parent].quality;
        temp.trafficVolume = priorityQueue[parent].trafficVolume;
        temp.priority = priorityQueue[parent].priority;
        temp.severity = priorityQueue[parent].severity;
        priorityQueue[parent] = priorityQueue[nodeIndex];
        priorityQueue[nodeIndex] = temp;
        repairUpward(parent);
        return;
    }
    else if(parent>=0 && priorityQueue[parent].priority == priorityQueue[nodeIndex].priority){
        if(priorityQueue[parent].sectionLength < priorityQueue[nodeIndex].sectionLength){
            RoadNode temp;
            temp.sectionLength = priorityQueue[parent].sectionLength;
            temp.quality = priorityQueue[parent].quality;
            temp.trafficVolume = priorityQueue[parent].trafficVolume;
            temp.priority = priorityQueue[parent].priority;
            temp.severity = priorityQueue[parent].severity;
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
        temp.sectionLength = priorityQueue[highestPriority].sectionLength;
        temp.quality = priorityQueue[highestPriority].quality;
        temp.trafficVolume = priorityQueue[highestPriority].trafficVolume;
        temp.priority = priorityQueue[highestPriority].priority;
        temp.severity = priorityQueue[highestPriority].severity;
        priorityQueue[highestPriority] = priorityQueue[nodeIndex];
        priorityQueue[nodeIndex] = temp;
    }
}
