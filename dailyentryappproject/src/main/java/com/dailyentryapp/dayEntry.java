package com.dailyentryapp;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;


import javafx.scene.control.TextArea;


public class dayEntry {
    String date;
    int moodRating;
    char soberStatus;
    String todaysNotes;
    String todaysDate;

    dayEntry(){
        this.date = null;
        this.moodRating = 0;
        this.soberStatus = 'u';

    }

    dayEntry(String dateInp, int moodRatingInp, char soberStatusInp){
        this.date = dateInp;
        this.moodRating = moodRatingInp;
        this.soberStatus = soberStatusInp;
    }

    public String getDate(){
        return date;
    }
    void setDate(String newDate){
        date = newDate;
    }

    public int getMoodRating(){
        return moodRating;
    }
    void setMoodRating(int newMoodRating){
        moodRating = newMoodRating;
    }

    public char getSoberStatus(){
        return soberStatus;
    }
    void setSoberStatus(char newSoberStatus){
        soberStatus = newSoberStatus;
    }

    void getLatestEntry(TextArea myArea){
        String filePath = "dailyEntryDatabase.txt";
        try(RandomAccessFile myDatabase = new RandomAccessFile(filePath, "r")){//using RandomAccessFile as it allows us to access the file from a custom point (in this instance last entry) which will save us iterating over the whole file
            long length = myDatabase.length();//gets length of file
            if (length == 0){//checks if file is empty
                System.out.println("File empty");
                return;
            }

            //will iterate backwards until \n is found (eg start of the previous line)
            long characterPosition = length-1;
            StringBuilder lastLine = new StringBuilder();//using StringBuilder allows us to easily add the character to the string

            while(characterPosition>=0){
                myDatabase.seek(characterPosition);
                char tempChar = (char) myDatabase.readByte(); //assigns the character at current position to the variable tempChar

                if(tempChar =='\n'){
                    break;
                }else{
                    lastLine.insert(0,tempChar);//inserts tempChar at position 0
                }

                characterPosition--;//moves character position once character back
            }
            String finalLastline = lastLine.toString();
            finalLastline = finalLastline.substring(15,finalLastline.length());
            myArea.setText(finalLastline);
            System.out.println("Last line is: "+finalLastline);

        }catch (IOException e){
            System.out.println("Error with file!\n");
            e.printStackTrace();
        }
    }
    String getLine(int offset){
        ++offset;
        String filePath = "dailyEntryDatabase.txt";
        try(RandomAccessFile myDatabase = new RandomAccessFile(filePath, "r")){//using RandomAccessFile as it allows us to access the file from a custom point (in this instance last entry) which will save us iterating over the whole file
            long length = myDatabase.length();//gets length of file
            if (length == 0){//checks if file is empty
                System.out.println("File empty");
                return "";
            }

            //will iterate backwards until \n is found (eg start of the previous line)
            long characterPosition = length-1;
            StringBuilder lastLine = new StringBuilder();//using StringBuilder allows us to easily add the character to the string
            int numberOfNewLines = 0;
            while(characterPosition>=0){
                myDatabase.seek(characterPosition);
                char tempChar = (char) myDatabase.readByte(); //assigns the character at current position to the variable tempChar

                if(tempChar =='\n'){
                    numberOfNewLines++;
                    if(numberOfNewLines == offset){
                        break;
                    }else{
                        //System.out.println("at this point lastLine is: "+lastLine);
                        lastLine.setLength(0);
                        characterPosition--;
                        continue;
                    }
                }else{
                    lastLine.insert(0,tempChar);//inserts tempChar at position 0
                }

                characterPosition--;//moves character position once character back
            }
            String finalLastline = lastLine.toString();
            setDate(finalLastline.substring(0,10));

            //setting mood rating
            String unfinalisedMoodRating = finalLastline.substring(11,13);
            int characterOffset = 0;//holds the offset for if there is a double digit mood entry
            if(unfinalisedMoodRating.indexOf("|")!=-1){//index of returns -1 if it is not present, therefore if | is in the string it needs to be stripped and the rest of the ALSO COULD HAVE JUST CHECKED IF ITS 10 AS THIS IS THE ONLY CASE IT WILL ALLOW but i guess this way has its merit too
                //strip end character
                unfinalisedMoodRating = unfinalisedMoodRating.substring(0, 1);
                moodRating = Integer.parseInt(unfinalisedMoodRating);
            }else{
                characterOffset++;
            }
            moodRating = Integer.parseInt(unfinalisedMoodRating);

            //setting soberSatus
            soberStatus = (finalLastline.substring(13+characterOffset,14+characterOffset)).charAt(0);//extracts the Y/N value then converts to character
            System.out.println("Sober Status ="+ soberStatus);
            //setting todaysNotes
            finalLastline = finalLastline.substring(15+characterOffset,finalLastline.length());
            todaysNotes = finalLastline;

            //setting todaysDate
            todaysDate = finalLastline.substring(0,10);
            return finalLastline;
        }catch (IOException e){
        System.out.println("Error with file!\n");
        e.printStackTrace();
        return "";
        }
    }

    int getSoberStreak(){
        String prevLineDate = "nothing";
        this.getLine(0);
        System.out.println("Hi hopefully here are todays notes: "+todaysNotes);
        int streak = 0;
        while(soberStatus!='N'&&(prevLineDate.equals(date)==false)){//loops until it finds an instance of not being sober or the end of the file
            streak++;
            prevLineDate = date;
            this.getLine(streak);
        }
        return streak;
    }


}

