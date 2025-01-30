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
    void print(); //used for printing current objects data to console 
    void printToFile();//used for printing objects data to txt file

};

DailyEntry::DailyEntry(){
    amogus();
    std::cout<<"\n------------------------------------------";

    //-----Finding last line
    std::ifstream myFileR("dailyEntryDatabase.txt", std::ios::binary);
    myFileR.seekg(0,std::ios::end);//move  pointer to last character in file
    std::streamoff fileSize = myFileR.tellg();//gets the position EG the size of file since it is the last line
    std::string lastLine;//declares a string that will hold the last line of the file

    for(std::streamoff i = fileSize - 1; i >= 0; i--){//will iterate through whole file unless it finds a line break
        myFileR.seekg(i,std::ios::beg);//moves pointer to current position
        char ch;
        myFileR.get(ch);//retireves character from current position
        if(ch=='\n'){//if its a new line, we have finished extraction
            break;
        }
        lastLine = ch+lastLine;//concatonates string
    }
    myFileR.close();//closes file
    std::cout<<"Last line: "<<lastLine;
    //extracting date
    std::string entryDate;
    for(int i = 0; i < 10; i++){//std date format so we know how long it will be
        entryDate = entryDate+lastLine[i];
    }
    std::cout<<"Date = "<<entryDate;
    //comparing if date matches todays


    //IF LINE FROM TODAY DOES NOT EXIST DO THIS // IF NOT JUST NOTES AND APPEND LAST LINE
    int userRating = 0;
    std::cout<<"\nHow was your mood today?   (1-10)"<<std::endl;
    std::cin>>userRating;
    while(userRating<1||userRating>10){
        std::cout<<"\nPlease enter a whole number between 1 and 10   (1-10)\n"<<std::endl;
        std::cin>>userRating;
    }
    char isUserSober;
    std::cout<<"\nWere you sober today?   (y/n)"<<std::endl;
    std::cin>>isUserSober;
    isUserSober = std::tolower(isUserSober);
    while(isUserSober!='y'&&isUserSober!='n'){
        std::cout<<"\nPlease enter either Y or N\n"<<std::endl;
        std::cin>>isUserSober;
    }
    
    std::cout<<"\nAny notes about today you would like to make?\n";
    std::string usersNotesPt1, usersNotesPt2;

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


