#include "PriorityQueue.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

void displayMenu(){
cout << "============Main Menu============" << endl;
cout << "1. Get group information from file" << endl;
cout << "2. Add a group to Priority Queue" << endl;
cout << "3. Show next group in the queue" << endl;
cout << "4. Serve Next group" << endl;
cout << "5. Serve Entire Queue" << endl;
cout<<"6. Print top N"<<endl;
cout << "7. Quit" << endl;
}

RoadNode* orderedArr(PriorityQueue &queue, RoadNode v1[]){
  //PriorityQueue queue1(size);
  int count=0;
  int count1=0;
  //RoadNode v1[4000];
  RoadNode temp;
  while(!queue.isEmpty()){
    temp = queue.peek();
    v1[count1] = temp;
    queue.dequeue();
    count++;
    count1++;
    //queue1.enqueue(temp.sectionLength, temp.quality, temp.trafficVolume, temp.iri, temp.rut);
  }
  for(int i=0; i<count; i++){
    queue.enqueue(v1[count-i-1].sectionLength, v1[count-i-1].quality, v1[count-i-1].trafficVolume, v1[count-i-1].iri, v1[count-i-1].rut);
  }
  return v1;
}

void printNode(RoadNode node){
  cout << "Section Length:" << node.sectionLength << endl;
  cout << "Road Quality:" << node.quality << endl;
  cout << "Traffic Volume:"<< node.trafficVolume << endl;
  cout << "Road IRI:"<< node.iri<<endl;
  cout << "Repair RUT: "<< node.rut<<endl;
}

int main(int argc, char* argv[]){
  int queueSize = stoi(argv[1]);
  PriorityQueue myQueue(queueSize);
  RoadNode v[4000];
  int input;
  do{
    displayMenu();
    cin>>input; // need checks to make sure input is valid
    switch(input){
			case 1:
      {
        /*cout<<"Enter filename:"<<endl;
        string inputFile;
        cin.ignore();
        getline(cin, inputFile);
        ifstream myFile(inputFile);
        if(myFile.is_open()){
          string line;
          while(getline(myFile, line) && !myQueue.isFull()){
            stringstream ss;
            ss<<line;
            string name;
            string size;
            string time;
            getline(ss, name, ' ');
            getline(ss, size, ' ');
            getline(ss, time);
            myQueue.enqueue(name, stoi(size), stoi(time));
          }
          cout<<"Heap full, cannot enqueue"<<endl;
        }
        else{
          cout<<"error, file did not open correctly"<<endl;
        }*/
        break;
      }
			case 2:
      {
        string sectionLength;
        string quality;
        string trafficVolume;
        string _iri;
        string _rut;    // we need checks to make sure the input is valid

        cout << "Enter Section Length (in meters):" << endl; //Idk what units
        cin>>sectionLength;

        cout << "Enter Road Quality (0-100):" << endl;
        cin>>quality;

        cout << "Enter Traffic Volume (0-100):" << endl;
        cin>>trafficVolume;

        cout <<"Enter IRI (0-100):"<<endl;
        cin>>_iri;

        cout<<"Enter RUT (0-100):"<<endl;
        cin>>_rut;

        myQueue.enqueue(stof(sectionLength), stoi(quality), stoi(trafficVolume), stoi(_iri), stoi(_rut));
        break;
      }
      case 3:
      {
        RoadNode temp = myQueue.peek();
        if(!myQueue.isEmpty()){
          printNode(temp);
        }
        break;
      }
      case 4:
      {
        if(!myQueue.isEmpty()){
          cout << "Section Length: " << myQueue.peek().sectionLength<< " , IRI: "<< myQueue.peek().iri << " , Traffic Volume: "<<myQueue.peek().trafficVolume<<" , RUT: " <<myQueue.peek().rut<<endl;
          myQueue.dequeue();
        }
        else{
          cout<<"Heap empty, cannot dequeue"<<endl;
        }
        break;
      }
      case 5:
      {/*
        while(!myQueue.isEmpty()){
          totalCookTime = totalCookTime + myQueue.peek().cookingTime;
          cout << "Group Name: " << myQueue.peek().groupName<< " - Total Cook Time for the Group: "<< totalCookTime << endl;
          myQueue.dequeue();
        }
        cout<<"Heap empty, cannot dequeue"<<endl;*/
        break;
      }
      case 6:
      {
        int count = myQueue.currentQueueSize;
        string n;
        cout<<"How many roads would you like to print: ";
        cin.ignore();
        getline(cin, n);
        orderedArr(myQueue, v);
        for(int i = 0; i<stoi(n); i++){
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
      case 7:
      {
        break;
      }
    }
  }while(input !=7);

  cout<<"Goodbye!"<<endl;
  return 0;
}
