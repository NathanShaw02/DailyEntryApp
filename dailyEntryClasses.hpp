#include <String>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include "asciiImages.hpp"

class DailyEntry{
    int rating;
    char soberStatus;
    std::string todaysNotes;
    public:
    DailyEntry(); //constructor for a new entry
    void setRating(int inp);
    int getRating();
    void setSober(char inp);
    char getSoberStatus();
    void print(); //used for printing current objects data to console 
    void printToFile();//used for printing objects data to txt file

};

DailyEntry::DailyEntry(){
    amogus();
    std::cout<<"\n------------------------------------------";
    std::cout<<"\nHow was your mood today?   (1-10)"<<std::endl;
    int userRating;
    //validation here
    std::cin>>userRating;
    std::cout<<"\nWere you sober today?   (y/n)"<<std::endl;
    char isUserSober;
    std::cin>>isUserSober;
    
    //validation here
    std::cout<<"\nAny notes about today you would like to make?\n";
    std::string usersNotesPt1, usersNotesPt2;
    /*using the getline method for the full input was breaking it by not waiting for user input
    fixed this by having a normal input as one variable and storing the rest of the sentence (which is left in the buffer) in a 2nd variable
    then both strings added together to get final product :)
    */
    //std::cin>>usersNotesPt1;
    std::getline(std::cin,usersNotesPt1);
    std::getline(std::cin,usersNotesPt2);
    
    std::cout<<"\n__________________________________________";
    std::cout<<"\n";
    std::string fullUserInput = usersNotesPt1+usersNotesPt2;

    rating = userRating;
    if(isUserSober=='y'){
        soberStatus = 'Y';
    }else{
        soberStatus = 'N';
    }

    todaysNotes = fullUserInput;
}


void DailyEntry::print(){

    std::cout<<"|Todays Rating: "<<rating<<"|Days Sober Status: "<<soberStatus<<"|\nTodays Notes:\n\n"<<(todaysNotes);
    std::cout<<"\n------------------------------------------";
}


void DailyEntry::printToFile(){
    //get todays date
    auto now = std::chrono::system_clock::now(); //returns a "time_point" object  and assigns it to now || using the auto type here as simpler than specifying the exact type which would be std::chrono::time_point<std::chrono::system_clock>
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);//converts the time_point object now into time_t data type
    std::tm* tm_ptr = std::localtime(&now_time);//converting to tm structure to get a formatted date


    std::ofstream myFile("dailyEntryDatabase.txt",std::ios::app);
    myFile<<"\n"<<std::put_time(tm_ptr,"%Y-%m-%d")<<"|"<<rating<<"|"<<soberStatus<<"|"<<todaysNotes;


    myFile.close();
}


