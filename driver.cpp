#include "PriorityQueue/PriorityQueue.hpp"
#include "DataCollection/hash.hpp"
#include "DataCollection/DataCollection.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;
/* COMPILE INSTRUCTIONS: 
g++ DataCollection/DataCollection.cpp PriorityQueue/PriorityQueue.cpp driver.cpp DataCollection/hash.cpp -std=c++11 */
int main(int argc, char *argv[]){
    JSONparser highways; //This will create the JSONparser object that will
    //be used to read the data
    json quality = highways.fileToJson("DataCollection/hwyQuality.json"); //Json file that holds
    //quality data
    json traffic = highways.fileToJson("DataCollection/hwyTraffic.json"); //Json file that holds
    //traffic data
    HashTable hwyQ = highways.storeinHash(quality, 0, 560); //HashTable holding
    //quality data
    HashTable hwyT = highways.storeinHash(traffic, 1, 560); //HashTable holding
    //traffic data
    highways.combineHashTables(hwyT, hwyQ); //Combine to one hash table
    hwyQ.printTable(); //This is printing the table for testing purposes
    PriorityQueue queue(560); //Creating the queue of highways
    for(int i = 0; i < hwyQ.getTableSize(); i++){ //Going through the hashtable and
        //adding the nodes to the priority queue
        node *trav = hwyQ.gethashTable()[i]; //This helps to traverse the hashtable
        int condition = 0; //The integer value of condition of the road
        if (trav == nullptr)
        {
            continue;
        }
        if(trav->cond == "LOW"){
            condition = 3;
        }else if(trav->cond == "MODERATE"){
            condition = 2;
        }else{
            condition = 1;
        }
        queue.enqueue(trav->highway, trav->lengthQuality, condition, trav->trafficAvg, trav->iri, trav->rut); //Enqueue every hightway
        // into the priority queue
    }
    queue.calcNormPriority(); //Normalize all the priority

    return 0;
}
