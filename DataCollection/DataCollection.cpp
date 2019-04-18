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

HashTable JSONparser::storeinHash(json hwyJson, int type)
{
    HashTable hwyHash(560);
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
int main()
{
    JSONparser yeet;
    json hwyQJson = yeet.fileToJson("hwyQuality.json");
    json hwyTJson = yeet.fileToJson("hwyTraffic.json");
    HashTable hwyQuality = yeet.storeinHash(hwyQJson, 0);
    HashTable hwyTraffic = yeet.storeinHash(hwyTJson, 1);
    hwyQuality.printTable();
    hwyTraffic.printTable();
}