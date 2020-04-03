package car_rental.controllers;

import java.io.IOException;

import car_rental.Constants;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;

public class HomeController extends BaseController<Object> {

    @FXML
    void manipulateCars(ActionEvent event) throws IOException {
        switchStage(Constants.CARS_MARKUP, event.getSource());
    }

    @FXML
    void manipulateClients(ActionEvent event) throws IOException {
        switchStage(Constants.CLIENTS_MARKUP, event.getSource());
    }

    @FXML
    void manipulateDeals(ActionEvent event) throws IOException {
        switchStage(Constants.DEALS_MARKUP, event.getSource());
    }

    @FXML
    void initialize() {

    }
}


