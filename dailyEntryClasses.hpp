#include <String>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include "asciiImages.hpp"

std::string singleDigitDateFormatting(int inp){
    std::string newString;
    if(inp>0&&inp<10){
        newString = "0"+std::to_string(inp);
    }else{
        newString = std::to_string(inp);
    }
    return newString;
}

std::string getCurrentDate(){
    time_t now = time(0);//gets current time based on system
    tm* localTime = localtime(&now);//declares a tm pointer that = now which has been converted from a time_t value to a tm struct using localtime()
    std::string currentDate = std::to_string(1900+localTime->tm_year)+"-"+singleDigitDateFormatting(localTime->tm_mon+1)+"-"+singleDigitDateFormatting(localTime->tm_mday);//retrueves the year,month and date and formats it. tm_year stores number of years since 1900, tm_mon holds an int for the month starting at 0
    return currentDate;
}


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
    if(entryDate==getCurrentDate()){
        std::cout<<"\nYou already have an entry logged for today!\nWould you like to add any notes? (y/n)";
        char userInputYN;
        std::cin>>userInputYN;
        userInputYN = std::tolower(userInputYN);
        while(userInputYN!='y'&&userInputYN!='n'){
            std::cout<<"\nPlease enter either Y or N\n"<<std::endl;
            std::cin>>userInputYN;
            userInputYN = std::tolower(userInputYN);
        }
        if(userInputYN == 'y'){
            //add notes to entry
        }else{
            exit(0);//program terminates if you dont want to do anything
        }
    
    }else{
        //do full entry
    }


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
        isUserSober = std::tolower(isUserSober);
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

    std::ofstream myFile("dailyEntryDatabase.txt",std::ios::app);

    std::string todaysDate = getCurrentDate();
    myFile<<"\n"<<todaysDate<<"|"<<rating<<"|"<<soberStatus<<"|"<<todaysNotes;

    myFile.close();
}


