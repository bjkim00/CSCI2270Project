// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"


using namespace std;
/*
  	Method Name: createNode
  	Purpose: Create a node with data as 'key'
    return: pointer to the new node
  	*/
node* HashTable::createNode(int k, node* next)
{
    node* nw = new node;
    nw->key = k;
    nw->next = next;
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
  	Method Name: insertItem
  	Purpose: inserts a node with data as 'key' into the Hash Table
    return: false if 'key' already exists in the table, otherwise true
  	*/
bool HashTable::insertItem(int key)
{
    if(!searchItem(key))
    {
        // TODO :
        // Use the hash function on the key to get the index/slot,
        // create a new node with the key and insert it in this slot's list
        int index = hashFunction(key);
        node *nextVal = hashTable[index];
        node* newNode = createNode(key, nextVal);
        hashTable[index] = newNode;
        return true;
     }
    else{
        cout<<"duplicate entry: "<<key<<endl;
        return false;
    }

}
/*
  	Method Name: hashFunction
  	Purpose: function to hash "key" into an index
    return: index in the Hash Table
  	*/
unsigned int HashTable::hashFunction(int key)
{
    return key;
    // int hashKey;
    // if (key<0)
    //     hashKey = key*-1;
    // else
    //     hashKey = key;
    // return hashKey;
}

/*
  	Method Name: printTable
  	Purpose: function to display the Hash Table
    return: none
  	*/
void HashTable::printTable()
{
    for (int i = 0; i < tableSize; i++) {
        cout << i <<"|| ";
        //TODO
        node * trav = hashTable[i];
        while(trav != nullptr){
            cout << trav->key << " ";
            trav = trav->next;
        }
        cout << endl;
    }

 }

/*
  	Method Name: searchItem
  	Purpose: function to search for "key" in the Hash Table
    return: node with "key" as it's data if found, otherwise NULL
  	*/
node* HashTable::searchItem(int key)
{
    //Compute the index by using the hash function
    int index = hashFunction(key);

    //TODO: Search the list at that specific index and return the node if found
    node* trav = hashTable[index];
    while (trav != nullptr && trav->key != key)
    {
        trav = trav->next;
    }
    return trav;
}


bool findThreeSum(int arr[], HashTable &ht, int sizeOfArray)
{
    if (sizeOfArray<3)
    {
        return false;
    }
    for (int i=0; i<sizeOfArray; i++)
    {
        for (int j= i+1; j<sizeOfArray; j++)
        {
            if (arr[i]!= arr[j])
            {
                int twoSum = arr[i] + arr[j];
                ht.insertItem(twoSum);
            }
            
        }
    }
    for (int k=0; k<sizeOfArray; k++)
    {
        int searchFor = arr[k]*-1;
        if (ht.searchItem(searchFor) != nullptr)
        {
            node *result = ht.searchItem(searchFor);
            cout << "sum Found-" << result->key << endl;
            return true;
        }
    }
    return false;
}

//  int main ()
//  {
//     HashTable threeSum(36);
//     int array3[6] =  {-4, -5, -1, 0, 35, 27};
//     int array1[3] =  {-1,0, 1};
//     cout << findThreeSum(array3, threeSum, 6) << endl;
//     threeSum.printTable();
    
//  }