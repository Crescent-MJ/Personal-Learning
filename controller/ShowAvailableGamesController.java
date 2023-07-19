package controller;

import au.edu.uts.ap.javafx.Controller;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import model.Kiosk;

public class ShowAvailableGamesController extends Controller<Kiosk> {

	public final Kiosk getKiosk() {
        return model;
    }
    
    @FXML
    private void handleExit(ActionEvent event) {
        stage.close();
    }
}
