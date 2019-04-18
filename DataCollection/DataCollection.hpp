#ifndef DATACOLLECTION_HPP
#define DATACOLLECTION_HPP

#include <iostream>
#include <fstream>
#include "json.hpp"
#include "hash.hpp"
using namespace std;
using json = nlohmann::json;
/* Goal of this program: Parse hwyQuality.json and hwyTraffic.json and Relevant data are as follows:
QUALITY:
    Hwy: Highway
    Bmp, emp: Beginning mile point and end mile point
    Length: of section
    Cond: Condition of road
    Iri: International roughness index or otherwise ride quality
    Rut: Remaining service life for rutting  
TRAFFIC:
`   Hwy: Highway
    LENGTH_: The Centerline Segment Length or Segment Distance (in Miles) to the Thousandth of a Mile.
    AADT: Annual average daily traffic count

 */

/* How its going to do that:
    1. Use a file stream in order to access the json data
    2. Create a Json object with the installed library after using getline
    3. Create a class/struct using the data give
    4. All this should be done with a class that can be included in other files*/
//Compilation: g++ DataCollection.cpp hash.cpp -std=c++11
class JSONparser
{
    private:
        // HashTable hwyBuckets;
    public:
        JSONparser() { 
        };
        //This function creates a json object with the file given
        json fileToJson(std::string fileName);
        //This function creates a hash table of hwy structs and stores given hwy quality info in it
        HashTable storeinHash(json hwyJson, int type);
};

#endif