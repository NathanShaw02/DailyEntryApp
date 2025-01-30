module com.dailyentryapp {
    requires javafx.controls;
    requires javafx.fxml;

    opens com.dailyentryapp to javafx.fxml;
    exports com.dailyentryapp;
}
