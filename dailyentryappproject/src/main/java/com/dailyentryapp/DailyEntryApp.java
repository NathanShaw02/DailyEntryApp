package com.dailyentryapp;

import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.event.ActionEvent;
import javafx.scene.Scene;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.geometry.HPos;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.geometry.VPos;
import javafx.scene.layout.HBox;
import javafx.scene.layout.RowConstraints;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.scene.control.Label;
import javafx.scene.control.Button;
import javafx.scene.control.DatePicker;
import javafx.scene.control.TextArea;
import com.dailyentryapp.dayEntry;



import java.io.IOException;

/**
 * JavaFX App
 */


public class DailyEntryApp extends Application {//creates a class called "DailyEntryApp" which is a derived class of the applicaiton class

    @Override
    public void start(Stage myApp){//starts the applicaiton with the stage titled myApp
        //----------------------------------------HOME SCREEN---------------------------------------------
        GridPane root = new GridPane();//declares a GridPane
        Scene homeScene = new Scene(root,1600,1000);//declares the home page screen with a gridPane root 

        //root gridpane config
        root.setPadding(new Insets(10));//adds a padding seperating the content from the edge

        root.setHgap(10);//sets a horizontal gap between each element 
        root.setVgap(10);//sets a Verticle gap between each element 

        //root gridpane rows and columns || setting constraints

        ColumnConstraints col0 = new ColumnConstraints();
        col0.setPercentWidth(50);
        col0.setHalignment(HPos.CENTER);
        ColumnConstraints col1 = new ColumnConstraints();
        col1.setPercentWidth(50);
        col1.setHalignment(HPos.CENTER);



        RowConstraints row0 = new RowConstraints();
        row0.setPercentHeight(10);
        row0.setValignment(VPos.CENTER);
        RowConstraints row1 = new RowConstraints();
        row1.setPercentHeight(80);
        row1.setValignment(VPos.CENTER);
        RowConstraints row2 = new RowConstraints();
        row2.setPercentHeight(10);
        row2.setValignment(VPos.CENTER);

        root.getColumnConstraints().addAll(col0,col1);

        root.getRowConstraints().addAll(row0,row1,row2);


        //what we are putting on the screen
        myApp.setTitle("MyDailyEntryTracker");//gives window a title

        Label usernameLabel = new Label("My Username");
        root.add(usernameLabel, 0, 0);
        Label experienceLabel = new Label("XP: 0/0");
        root.add(experienceLabel, 1, 0);

        DatePicker moodCalendar = new DatePicker();
        root.add(moodCalendar,0,1);
        
        //sober streak vbox
        Label soberStreakTitle = new Label("Current Sober Streak:");
        Label soberStreak = new Label("0");
        VBox soberStreakVbox = new VBox(10,soberStreakTitle,soberStreak);
        soberStreakVbox.setPadding(new Insets(10));
        soberStreakVbox.setAlignment(Pos.CENTER);
        root.add(soberStreakVbox, 1,1);


        //-----------------------------------------------------DIARY PAGE --------------------------
        GridPane diaryPagePane = new GridPane();

        //diary page config

        //root gridpane config
        diaryPagePane.setPadding(new Insets(10));//adds a padding seperating the content from the edge

        diaryPagePane.setHgap(10);//sets a horizontal gap between each element 
        diaryPagePane.setVgap(10);//sets a Verticle gap between each element 

        //root gridpane rows and columns || setting constraints

        ColumnConstraints diaryColumn = new ColumnConstraints();
        diaryColumn.setPercentWidth(100);
        diaryColumn.setHalignment(HPos.CENTER);
        diaryPagePane.getColumnConstraints().add(diaryColumn);
        diaryPagePane.getRowConstraints().addAll(row0,row1,row2);

        Button prevDateButton = new Button(" < ");
        Button nextDateButton = new Button(" > ");
        Label displayDateLabel = new Label("todays Date");
        HBox diaryDateHBox = new HBox();
        diaryDateHBox.getChildren().addAll(prevDateButton,displayDateLabel,nextDateButton);
        diaryPagePane.add(diaryDateHBox,0,0);
        diaryDateHBox.setAlignment(Pos.CENTER);
        TextArea todaysText = new TextArea();
        diaryPagePane.add(todaysText,0,1);
        Button homeButton = new Button("Home");
        homeButton.setOnAction(new EventHandler<ActionEvent>(){
            @Override
            public void handle(ActionEvent event){
                homeScene.setRoot(root);
            }
        });

        diaryPagePane.add(homeButton,0,2);




        Button diaryPageButton = new Button("Diary Page");
        diaryPageButton.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event){
                System.out.println("goto Diary Button Pressed :D");
                //get last line of file
                dayEntry newEntry = new dayEntry();
                newEntry.getLatestEntry(todaysText);
                System.out.println();
                homeScene.setRoot(diaryPagePane);
            }
        });
        root.add(diaryPageButton,1,2);

        
        //assigning the scene and showing it
        myApp.setScene(homeScene);//sets the scene on the stage
        myApp.show();//Reveals the curtain to the stage and shows the first scene
    }

    public static void main(String[] args){//defines main which launches the applicaiton 
        launch(args);//initialises the javafx applicaiton
    }

    
}