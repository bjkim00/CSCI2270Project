#include "PriorityQueue/PriorityQueue.hpp"
#include "DataCollection/hash.hpp"
#include "DataCollection/DataCollection.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <limits.h>

using namespace std;
/* COMPILE INSTRUCTIONS:
g++ DataCollection/DataCollection.cpp PriorityQueue/PriorityQueue.cpp driver.cpp DataCollection/hash.cpp -std=c++11 */

//Main menu that will take in the user input
void displayMenu(){
cout << "============Main Menu============" << endl;
cout << "1. Show the road with the highest priority" << endl;
cout << "2. Remove the road with the highest priority" << endl;
cout<<"3. Print top N"<<endl;
cout << "4. Quit" << endl;
}

int checkValidInput(string l)
{
  if (l.length() > 1 )
    return 0;
  if (l[0] < 49 || l[0] > 52)
    return 0;
  else
  {
    return stoi(l);
  }
  
}

//Function designed to place all items in the queue into an ordered array that is passed into the Function
RoadNode* orderedArr(PriorityQueue &queue, RoadNode v1[]){
  int count=0;
  int count1=0;
  RoadNode temp;
  while(!queue.isEmpty()){
    temp = queue.peek();
    v1[count1] = temp;
    queue.dequeue();
    count++;
    count1++;
  }
  for(int i=0; i<count; i++){
    queue.enqueue(v1[count-i-1].highway, v1[count-i-1].sectionLength, v1[count-i-1].quality, v1[count-i-1].trafficVolume, v1[count-i-1].iri, v1[count-i-1].rut);
  }
  return v1;
}


//Given a RoadNode print all of its properties
void printNode(RoadNode node){
  string cond;
  if(node.quality == 3){
    cond = "Poor";
  }
  else if(node.quality == 2){
    cond = "Fair";
  }
  else{
    cond = "Good";
  }
  cout<<"Highway: " <<node.highway<<endl;
  cout << "Section Length: " << node.sectionLength << endl;
  cout<<"Priority: "<< node.priority<<endl;
  cout << "Road Quality: " << cond << endl;
  cout << "Traffic Volume: "<< node.trafficVolume << endl;
  cout << "Road IRI: "<< node.iri<<endl;
  cout << "Repair RUT: "<< node.rut<<endl;
  
}

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
    //hwyQ.printTable(); //This is printing the table for testing purposes
    PriorityQueue queue(560); //Creating the queue of highways
    RoadNode v[560];//Creating an array of RoadNodes which will be used in the print top N fucntion
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
    queue.calcNormTraffic(); //Normalize all the traffic
    queue.calcNormIRI(); //Normalize iri
    queue.calcNormRUT(); //Normalize rut
    orderedArr(queue, v);

    int input = 0;
    while(input !=4)
    {
      displayMenu();
      string line;
      getline(cin, line); 
      input = checkValidInput(line);
      switch(input){
        case 1:
        {
          cout<<"Top Priorty Road Shown: "<<endl;
          RoadNode temp = queue.peek();
          if(!queue.isEmpty()){
            printNode(temp);
          }
          break;
        }
        case 2:
        {
          if(!queue.isEmpty()){
            cout<<"Top Priority Road Removed: "<<endl;
            printNode(queue.peek());
            queue.dequeue();
          }
          else{
            cout<<"Heap empty, cannot dequeue"<<endl;
          }
          break;
        }
        case 3:
        {
          int count = queue.currentQueueSize;
          string n;
          cout<<"How many roads would you like to print: ";
          cin.clear();
          getline(cin, n);
          orderedArr(queue, v);
          int numRoads = checkValidInput(n);
          for(int i = 0; i<numRoads; i++){
            if(count>0){
              cout<<"Road Section: "<<i+1<<endl;
              printNode(v[i]);
              cout<<endl;
              count--;
            }
            else{
              cout<<"Queue empty no more to print."<<endl;
              break;
            }
          }
          break;
        }
        case 4:
        {
          break;
        }
      }
    }
      

    cout<<"Goodbye!"<<endl;

    return 0;
}
