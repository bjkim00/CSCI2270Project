#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <string>
#include <cstring>
using namespace std;
// a struct to store customers group information
struct RoadNode
{
    float sectionLength;
    int quality;
    int iri;
    int rut;
    int trafficVolume;
    float priority;
    string severity;
};


class PriorityQueue
{
    public:

    //Purpose: perform all operations necessary to instantiate a class object
    PriorityQueue(int queueSize);

    // Purpose: free all resources that the object has acquired
    ~PriorityQueue();

    // Purpose: Determine the priority of the highway
    float calcPriority(int _quality, int _trafficVolume, int _iri, int _rut);

    // Purpose: enqueue new group into priority queue; call other
    void enqueue (float _sectionLength, int _quality, int _trafficVolume, string _severity, int _iri, int _rut);

    //Purpose: remove the group (allocate the table) at the front of the priority queue from
    void dequeue();

    // return: groupID of the group at the front of the priority queue
    RoadNode peek();

    //return: true if queue is full, false otherwise  *****Do we need this????
    bool isFull();

    // return: true if queue is empty, false otherwise
    bool isEmpty();

    private:
    //Purpose: maintain heap properties by swapping node with parent if necessary
    void repairUpward(int nodeIndex);

    // Purpose: maintain heap properties by swapping node with child if necessary
    void repairDownward(int nodeIndex);

    RoadNode* priorityQueue; //pointer to the array used to implement priority queue
    int currentQueueSize; //number of group currently in the priority queue
    int maxQueueSize; //maximum capacity of priority queue
};

#endif
