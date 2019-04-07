#include "PriorityQueue.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

void displayMenu(){
cout << "============Main Menu============" << endl;
cout << "1. Get group information from file" << endl;
cout << "2. Add a group to Priority Queue" << endl;
cout << "3. Show next group in the queue" << endl;
cout << "4. Serve Next group" << endl;
cout << "5. Serve Entire Queue" << endl;
cout << "6. Quit" << endl;
}

int main(int argc, char* argv[]){
  PriorityQueue myQueue(stoi(argv[1]));
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
        string priority;
        string severity;    // we need checks to make sure the input is valid

        cout << "Enter Section Length (in meters):" << endl; //Idk what units
        cin>>sectionLength;

        cout << "Enter Road Quality (0-100):" << endl;
        cin>>quality;

        cout << "Enter Traffic Volume (0-100):" << endl;
        cin>>trafficVolume;

        cout <<"Enter Road Priority (0-100):"<<endl;
        cin>>priority;

        cout<<"Enter Road Severity (Severe, Moderate, or Minor):"<<endl;
        cin>>severity;

        myQueue.enqueue(stof(sectionLength), stof(quality), stof(trafficVolume), stof(priority), severity);
        break;
      }
      case 3:
      {
        cout << "Section Length:" << myQueue.peek().sectionLength << endl;
        cout << "Road Quality:" << myQueue.peek().quality << endl;
        cout << "Traffic Volume:"<< myQueue.peek().trafficVolume << endl;
        cout << "Road Priority:"<<myQueue.peek().priority<<endl;
        cout << "Repair Severity: "<<myQueue.peek().severity<<endl;
        break;
      }
      case 4:
      {
        if(!myQueue.isEmpty()){
          cout << "Section Length: " << myQueue.peek().sectionLength<< " , Priority: "<< myQueue.peek().priority << " , Traffic Volume: "<<myQueue.peek().trafficVolume<<" , Severity: " <<myQueue.peek().severity<<endl;
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
          break;
      }
    }
  }while(input !=6);

  cout<<"Goodbye!"<<endl;
  return 0;
}
