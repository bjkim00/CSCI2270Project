#include <iostream>
#include <fstream>
#include "json.hpp"
#include "hash.hpp"
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
            HashTable hwyBuckets(550);
        };
        json streamReader(std::string fileName);
        

};

json JSONparser::streamReader(std::string fileName)
{
    std::ifstream hwyStream;
    hwyStream.open(fileName);
    if (hwyStream.is_open())
    {
        std::cout << "Storing " << fileName <<  std::endl;
        json j;
        hwyStream >> j;
        return j;
    }
    else 
    {
        cout << "File open failed" << endl;
        json empty;
        return empty;
    }
}
int main()
{
    JSONparser yeet;
    json hwyJson = yeet.streamReader("hwyQuality.json");
    std::cout << hwyJson << std::endl;
}