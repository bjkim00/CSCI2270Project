// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;
/*
  	Method Name: createNode
  	Purpose: Create a node with data as 'key'
    return: pointer to the new node
  	*/
node* HashTable::createNode(string hwy)
{
    node* nw = new node;
    nw->highway = hwy;
    nw->next = nullptr;
    return nw;
}
/*
    constructor
    Purpose: perform all operations necessary to instantiate a class object
    Param: Size of the Hash Table
    return: none
    */
HashTable::HashTable(int bsize)
{
    this->tableSize= bsize;
    hashTable = new node*[tableSize];
    for(int i=0;i<bsize;i++)
        hashTable[i] = nullptr;
}
 /*
    destructor
    Purpose: perform all operations necessary to destroy class object
    return: none
    */
HashTable::~HashTable()
{
    for (int i=0; i<tableSize; i++)
    {
        node *traverser = hashTable[i];
        while (traverser!= nullptr)
        {
            node *temp = traverser;
            traverser = traverser->next;
            delete temp;
        }
    }
    delete[] hashTable;
}

/*
  	Method Name: searchItem
  	Purpose: function to search for "key" in the Hash Table
    return: node with "key" as it's data if found, otherwise NULL
  	*/
node* HashTable::searchItem(string hwy, float beginPt, int type, int direction)
{
    //Compute the index by using the hash function
    int index = hashFunction(hwy);

    //Find the index where it is
    node* trav = hashTable[index];
    //If its type 0 => only quality data
    if (type == 0)
    {
        //traverse through the whole link
        while (trav != nullptr)
        {
            //If you find that bmp + hwy already exist: break out
            if (trav->bmp == beginPt && trav->highway == hwy)
                break;
            trav = trav->next;
        }
        /* Make sure we can add both directions so: 
            1. If it has the same code
            2. Has the same bmp
        Then Check to make sure the direction is the same
            if not make trav = nullptr so we can add it*/
        if (trav!= nullptr && trav->bmp == beginPt && trav->highway == hwy)
        {
            if (trav->dir != direction)
                trav = nullptr;
        }
    }
    //If its type 1 => only traffic data
    else if (type == 1)
    {
        //Same idea as above
        while (trav != nullptr)
        {
            //If you find that refpt + hwy already exist: break out
            if (trav->refpt == beginPt && trav->highway == hwy)
                break;
            //otherwise keep traversing
            trav = trav->next;
        }
    }
    /* TODO: Implement case for type== 2 */

    
    return trav;
}

/*
  	Method Name: insertItem
  	Purpose: creates a node from given json data 
    return: node created or nullptr if node was not created
  	*/
node* HashTable::insertItem(string hwy, float beginPt, int type, json hwyJson, int direction)
{
    node* found = searchItem(hwy, beginPt, type, direction);
    if(found == nullptr)
    {
        int index = hashFunction(hwy);
        node *currNode = hashTable[index];
        node *prevVal = currNode;
        node* createdNode = createNode(hwy);
        //If a value already exists in the hash Index
        if (prevVal != nullptr)
        {
            //Add to the linked list in order of BMP
            if (type == 0)
            {
                while(currNode != nullptr && currNode->bmp < beginPt)
                {
                    prevVal = currNode;
                    currNode = currNode->next;
                }
            }
            //Add to linked list in order of refpt
            else if (type == 1)
            {
                while(currNode != nullptr && currNode->refpt < beginPt)
                {
                    prevVal = currNode;
                    currNode = currNode->next;
                }
            }
            //If it needs to replace the first index
            if (currNode == hashTable[index])
            {
                hashTable[index] = createdNode;
                createdNode->next = currNode;
            }
            else
            {
                prevVal->next = createdNode;
                createdNode->next = currNode;
            }
           
        }
        //If hash is empty
        else
            hashTable[index] = createdNode;
        
        
        if (type == 0)
        {
            createdNode->highway = hwyJson["hwy"];

            string placeHolder = hwyJson["length"]; //Created because for some reason I can't use stof directly 
            createdNode->lengthQuality = stof(placeHolder);

            placeHolder = hwyJson["bmp"]; 
            createdNode->bmp = stof(placeHolder); //Beginning mile point

            createdNode->cond = hwyJson["cond"]; //Condition
            createdNode->county = hwyJson["county"]; 

            placeHolder = hwyJson["dir"];
            createdNode->dir = stoi(placeHolder); //Direction

            placeHolder = hwyJson["emp"]; 
            createdNode->emp = stof(placeHolder); //ending mile point
            
            placeHolder = hwyJson["iri"];
            createdNode->iri = stoi(placeHolder); //International roughness index (IRI) correlates to perceived ride quality 
            
            placeHolder = hwyJson["rut"];
            createdNode->rut = stoi(placeHolder); 
            
            placeHolder = hwyJson["year"];
            createdNode->year = stoi(placeHolder);
            createdNode->type = 0;
        }
        //If the json file is highway traffic 
        else if (type == 1)
        {

            string placeHolder = hwyJson["aadt"]; //Again have to do this because it can't convert directly
            createdNode->aadt = stoi(placeHolder);  //Traffic volume

            placeHolder = hwyJson["length_"];
            createdNode->lengthTraffic = stof(placeHolder);

            placeHolder = hwyJson["refpt"];
            createdNode->refpt = stof(placeHolder); //Like bmp

            placeHolder = hwyJson["endrefpt"];
            createdNode->endrefpt = stof(placeHolder); //Like emp

            createdNode->route = hwyJson["route"]; //Same as hwy code
            createdNode->type = 1;
        }
        return createdNode;
     }
    else{
        cout<<"duplicate entry of: "<<found->highway<< " BMP/REFPT: " << found->refpt << endl;
        cout << "   " <<hwy<< " BMP/REFPT: " << beginPt << endl;
    }
    return nullptr;

}
/*
  	Method Name: hashFunction
  	Purpose: function to hash "key" into an index
    return: index in the Hash Table
  	*/
unsigned int HashTable::hashFunction(string hwy)
{
    string numbers = hwy.substr(0,3);
    // int letter = hwy[3];
    // letter -= 64;
    int key = stoi(numbers)/* *letter */;
    return key;
    
}

/*
  	Method Name: printTable
  	Purpose: function to display the Hash Table
    return: none
  	*/
void HashTable::printTable()
{
    for (int i = 0; i < tableSize; i++) {
        cout << i <<"|| \n";
        node * trav = hashTable[i];
        while(trav != nullptr){
            if (trav->type == 0)
            {
                cout << "       HWY:" <<trav->highway <<" Segment:" <<trav->bmp <<"-" << trav->emp << " Traffic Avg:"<<trav->trafficAvg << " -> \n";
            }
            else if (trav->type == 1)
            {
                cout << "       HWY:" <<trav->highway <<" Segment:" <<trav->refpt << "-" <<trav->endrefpt << "Traffic:"<<trav->aadt <<" -> \n";
            }
            
            trav = trav->next;
        }
        cout << endl;
    }

 }




//  int main ()
//  {
//     HashTable threeSum(36);
//     int array3[6] =  {-4, -5, -1, 0, 35, 27};
//     int array1[3] =  {-1,0, 1};
//     cout << findThreeSum(array3, threeSum, 6) << endl;
//     threeSum.printTable();
    
//  }