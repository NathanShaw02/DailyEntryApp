#include "dailyEntryClasses.hpp"

int main(){

    DailyEntry myEntry;

    if(myEntry.getProcessedToday()==false){
        myEntry.printToFile();
    }
    return 0;
}