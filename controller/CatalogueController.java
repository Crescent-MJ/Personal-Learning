
package controller;

import au.edu.uts.ap.javafx.Controller;
import au.edu.uts.ap.javafx.ViewLoader;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.stage.Stage;
import model.Kiosk;

public class CatalogueController extends Controller<Kiosk> {
	public final Kiosk getKiosk() {
        return model;
    }
    
    @FXML
    private void handleViewAllGames(ActionEvent event) throws Exception {
        ViewLoader.showStage(getKiosk(), "/view/ShowAllGames.fxml", "All Games", new Stage());
    }
    
    @FXML
    private void handleViewAvailableGames(ActionEvent event) throws Exception {
        ViewLoader.showStage(getKiosk(), "/view/ShowAvailableGames.fxml", "Available Games", new Stage());
    }
    
    @FXML
    private void handleViewGamesByGenre(ActionEvent event) throws Exception {
        ViewLoader.showStage(getKiosk(), "/view/ShowGamesByGenre.fxml", "Games by Genre", new Stage());
    }
    
    @FXML
    private void handleViewGamesByYear(ActionEvent event) throws Exception {
        ViewLoader.showStage(getKiosk(), "/view/ShowGamesByYear.fxml", "Games by Year", new Stage());
    }
    
    @FXML
    private void handleViewRentGame(ActionEvent event) throws Exception {
        ViewLoader.showStage(getKiosk(), "/view/RentGame.fxml", "Rent a Game", new Stage());
    }
    
    @FXML
    private void handleViewReturnGame(ActionEvent event) throws Exception {
        ViewLoader.showStage(getKiosk(), "/view/ReturnGame.fxml", "Return a Game", new Stage());
    }
    
    @FXML
    private void handleExit(ActionEvent event) {
        stage.close();
    }
}
