#include <iostream>
#include <ctime>
#include <string>


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

int main(){

    std::cout<<"Todays Date: "<<getCurrentDate();
    return 0;
}