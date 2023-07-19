package controller;

import au.edu.uts.ap.javafx.Controller;
import au.edu.uts.ap.javafx.ViewLoader;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.stage.Stage;
import model.Kiosk;

public class AdminController extends Controller<Kiosk> {
    public final Kiosk getKiosk() {
    	return model;
    }
    
    @FXML
    private void handleViewAllCustomers(ActionEvent event) throws Exception {
        ViewLoader.showStage(getKiosk(), "/view/ShowAllCustomers.fxml", "Show All Customers", new Stage());
    }
    
    @FXML
    private void handleViewAllGames(ActionEvent event) throws Exception {
        ViewLoader.showStage(getKiosk(), "/view/ShowAllGames.fxml", "Show All Games", new Stage());
    }
    
    @FXML
    private void handleViewAddCustomer(ActionEvent event) throws Exception {
        ViewLoader.showStage(getKiosk(), "/view/AddCustomer.fxml", "Add Customer", new Stage());
    }
    
    @FXML
    private void handleViewAddGame(ActionEvent event) throws Exception {
        ViewLoader.showStage(getKiosk(), "/view/AddGame.fxml", "Add Game", new Stage());
    }
    
    @FXML
    private void handleViewRemoveCustomer(ActionEvent event) throws Exception {
        ViewLoader.showStage(getKiosk(), "/view/RemoveCustomer.fxml", "Remove Customer", new Stage());
    }
    
    @FXML
    private void handleViewRemoveGame(ActionEvent event) throws Exception {
        ViewLoader.showStage(getKiosk(), "/view/RemoveGame.fxml", "Remove Game", new Stage());
    }
    
    @FXML
    private void handleExit(ActionEvent event) {
        stage.close();
    }
}
