# CSCI2270Project 
#### Goal
===== 
Group Members: Vikram Tholakapalli, BJ Kim, Rithwik Mylavarapu
Story:
    Poor road conditions cause billions of dollars in vehicle damage and cause over one-third of all traffic accidents. Additionally, they can substantially slow traffic down causing numerous other externalities such as decreased productivity for workers, higher pollution, increased travel times, etc. the list goes on and on. In fact, according to the American Society of Civil Engineers, bad roads will cost American Businesses estimated $240 billion from 2019 to 2022.
    However, despite large support for infrastructure rebuilding across the aisle, governments still lack adequate funding. Therefore in order to maximize benefits of the funds available to CDOT our project seeks to answer where CDOT should focus its effort. 

Specifically, the goal of our project is to create a visual map that will show the areas that CDOT should prioritize. Our plan is the following:

What we need to do:
* Get Data
    * Determine Data format (geoJSON) and how to extract relevent data
    * HashTable for storing highways
    * Printing pre-set ranges will be a function under the HashTable class that we are implementing (i.e. we can sprint the top-third priority highways, mid-third priority highways, and low-third priority highways.
* Priority Queue
    * It needs a priority queue that takes into account the road quality and traffic volume through the section. It prioritizes the sections of road which have the worst quality and the greatest traffic volume
    * Formula for determining Priority
    * If traffic volume is above a certain point it can also recommend other infrastructure upgrades such as HOV/Toll lane
* Visualization
    * Learn QT
        * Color coded for urgency
        * Indicators for special infrastructure (HOV) 
        * Has multiple check marks that allows you to turn on different options from above struct
    * Overlay Google Maps
        *This is where we use QT to overlay our info on to google maps
