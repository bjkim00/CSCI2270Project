#include <iostream>
#include <fstream>
#include "json.hpp"
#include "hash.hpp"
#include "DataCollection.hpp"
using json = nlohmann::json;


//This function creates a json object with the file given
json JSONparser::fileToJson(std::string fileName)
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

HashTable JSONparser::storeinHash(json hwyJson, int type, int hashSize)
{
    HashTable hwyHash(hashSize);
    //loops through all items
    for (auto& it: hwyJson.items())
    {
        int index = stoi(it.key());
        //If the json file is hwy Quality
        if (type == 0)
        {
            string hwyCode = hwyJson[index]["hwy"];
            string strBeginPt = hwyJson[index]["bmp"];
            string dirStr = hwyJson[index]["dir"];
            float beginPt = stof(strBeginPt);
            int dir = stoi(dirStr);
            hwyHash.insertItem(hwyCode, beginPt, 0, hwyJson[index], dir);
        }
        //If the json file is hwy Traffic
        else if (type == 1)
        {
            string hwyCode = hwyJson[index]["route"];
            string strBeginPt = hwyJson[index]["refpt"];
            float beginPt = stof(strBeginPt);
            hwyHash.insertItem(hwyCode, beginPt, 1, hwyJson[index], 0);
        }
       
    }
    return hwyHash;
}

void JSONparser::combineHashTables(HashTable &traffic, HashTable &quality)
{
    int trafficSize = traffic.getTableSize();
    int qualitySize = quality.getTableSize();
    
    node ** qualityArray = quality.gethashTable();
    node ** trafficArray = traffic.gethashTable();
    // Loop through quality
    for (int i = 0; i < trafficSize; i++) {
        // cout << i <<"|| ";
        node * travQ = qualityArray[i];
        node * travT = trafficArray[i];

        // if index is not empty
        if (travT != nullptr)
        {
            int trafficSum = 0;
            float totalLength = 0;
            //Calculate traffic average
            while (travT != nullptr)
            {
                trafficSum += travT->aadt;
                totalLength += travT->lengthTraffic;
                travT = travT->next;
            }
            float tavg = trafficSum/totalLength;
            //Add the traffic avg to quality hashtable
            while (travQ != nullptr)
            {
                travQ->trafficAvg = tavg;
                travQ = travQ->next;
            }
        }

       
    }
    
}

// int main()
// {
//     /* IS a use case, this is how you should use this */
//     JSONparser yeet;
//     //Stores the json files
//     json hwyQJson = yeet.fileToJson("hwyQuality.json");
//     json hwyTJson = yeet.fileToJson("hwyTraffic.json");
    
//     //Stores the values in hashtables
//     HashTable hwyQuality = yeet.storeinHash(hwyQJson, 0, 550);
//     HashTable hwyTraffic = yeet.storeinHash(hwyTJson, 1, 560);
//     // THis is what you want, its the complete hashtable that has all your needs
//     //While traffic ain't important it still helps
//     yeet.combineHashTables(hwyTraffic, hwyQuality);
//     // hwyTraffic.printTable();
//     hwyQuality.printTable();

//     /* Just some testing shite */
    
// }