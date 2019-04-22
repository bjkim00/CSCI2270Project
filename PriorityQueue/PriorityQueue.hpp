#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <string>
#include <cstring>
using namespace std;
// a struct to store customers group information
struct RoadNode
{
    string highway; //Hwy name
    float sectionLength; //Length of the section that we are looking at
    int quality; //This should be the condition of the road converted to int
    float iri; //International roughness index (1-100)
    float rut; //RUT value between (0-100)
    float trafficVolume; //Traffic average
    float priority; //Priority of each individual section, this will be calculated
    //In calcPriority
    float normPriority; //This is the normalized priority
    bool severity;
};


class PriorityQueue
{
    public:

    //Purpose: perform all operations necessary to instantiate a class object
    PriorityQueue(int queueSize);

    // Purpose: free all resources that the object has acquired
    ~PriorityQueue();

    // Purpose: Determine the priority of the highway
    float calcPriority(int _quality, float _trafficVolume, float _iri, float _rut);

    // Purpose: Normalize the traffic of the highways
    void calcNormTraffic();

    // Purpose: Normalize the iri of the highways
    void calcNormIRI();

    // Purpose: Normalize the rut of the highways
    void calcNormRUT();

    // Purpose: enqueue new group into priority queue; call other
    void enqueue (string _highway, float _sectionLength, int _quality, float _trafficVolume, float _iri, float _rut);

    //Purpose: remove the group (allocate the table) at the front of the priority queue from
    void dequeue();

    // return: groupID of the group at the front of the priority queue
    RoadNode peek();

    //return: true if queue is full, false otherwise  *****Do we need this????
    bool isFull();

    // return: true if queue is empty, false otherwise
    bool isEmpty();

    int currentQueueSize; //number of group currently in the priority queue
    //In public so that it can be accessed for the print top N function
    private:
    //Purpose: maintain heap properties by swapping node with parent if necessary
    void repairUpward(int nodeIndex);

    // Purpose: maintain heap properties by swapping node with child if necessary
    void repairDownward(int nodeIndex);

    RoadNode* priorityQueue; //pointer to the array used to implement priority queue
    int maxQueueSize; //maximum capacity of priority queue
    //Purpose: All of these min and max values will be used to normalize the data
    float maxTraffic; //maximum priority (no normalization)
    float minTraffic; //min priority (no normalization)
    float minIRI; //max iri (no normalization)
    float maxIRI; //min iri (no normalization)
    float minRUT; //max rut (no normalization)
    float maxRUT; //min rut (no normalization)
};

#endif
