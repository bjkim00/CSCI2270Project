/*
Starter HPP File for Hash Tables.
DISCLAIMER: We recommend everyone to at least have these functions implemented properly.

For the exams the variable type might change form int to char / any other custom type.
You will also have extra functions which will be the main exam problems. These will just be added to this hpp file and it will be given to you during your exam
*/



#ifndef HASH_HPP
#define HASH_HPP

#include <string>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;
// Struct for a linked list node that stores all json tags
struct node
{
  int type; 
  /* type can be 1 of 3 values:
      0 => Indicates the node is just quality data
      1 => Indicates the node is just traffic data
      2 => Indicates the node is a combination of both */

  /* FROM hwyQuality.json */
  string highway; // hwy name
  struct node* next; // pointer to the next node
  float bmp; //Beginning mile point
  string cond; //Condition
  string county; 
  int dir; //Direction
  float emp; //ending mile point
  int iri; //International roughness index (IRI) correlates to perceived ride quality 
  float lengthQuality; 
  int rut; 
  //RUT: A value between 0 and 100 that is used to calculate Remaining Service Life for 
  //rutting A value of 100 indicates .15 inch or less rutting. A value of 50 is the 
  // threshold that indicates no more remaining service life.
  int year;

  /* FROM hwyTraffic.json */
  int aadt; //Traffic volume
  float lengthTraffic;
  float refpt; //Like bmp
  float endrefpt; //Like emp
  string route; //Same as hwy code

  float trafficAvg;

};

class HashTable
{
    // No. of buckets (Size of the Hash Table)
    int tableSize;

    // Pointer to an array containing buckets (the Hash Table)
    node **hashTable;

  	/*
  	Method Name: createNode
  	Purpose: Create a node with data as 'key'
    return: pointer to the new node
  	*/
    node* createNode(string hwy);

    public:

    /*
    constructor
    Purpose: perform all operations necessary to instantiate a class object
    Param: Size of the Hash Table
    return: none
    */
    HashTable(int bsize);

    /*
    destructor
    Purpose: perform all operations necessary to destroy class object
    return: none
    */
    ~HashTable();

  	/*
  	Method Name: insertItem
  	Purpose: inserts a node with data as 'key' into the Hash Table
    return: false if 'key' already exists in the table, otherwise true
  	*/
    node* insertItem(string hwy, float beginPt, int type, json hwyJson,  int direction);

    /*
  	Method Name: hashFunction
  	Purpose: function to hash "key" into an index
    return: index in the Hash Table
  	*/
    unsigned int hashFunction(string hwy);

    /*
  	Method Name: printTable
  	Purpose: function to display the Hash Table
    return: none
  	*/
    void printTable();

    /*
  	Method Name: searchItem
  	Purpose: function to search for "key" in the Hash Table
    return: node with "key" as it's data if found, otherwise NULL
  	*/
    node* searchItem(string hwy, float beginPt, int type, int direction);
    
    /* Getter for table size */
    int getTableSize()
    {
      return tableSize;
    }
    /* Getter for tableArray */
     node ** gethashTable()
     {
        return hashTable;
     }
};

#endif
