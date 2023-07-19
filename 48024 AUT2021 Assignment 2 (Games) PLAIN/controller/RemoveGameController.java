package controller;

import au.edu.uts.ap.javafx.Controller;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TableView;
import model.Kiosk;
import model.Game;

public class RemoveGameController extends Controller<Kiosk> {
	@FXML private TableView<Game> gamesTv;
    @FXML private Button removeGameBtn;
    
    public final Kiosk getKiosk() {
        return model;
    }
    
    private Game getSelectedGame() {
        return gamesTv.getSelectionModel().getSelectedItem();
    }
    
    @FXML private void initialize() {
        gamesTv.setItems(getKiosk().getCatalogue().getAllGames());
    }
    
    @FXML
    private void handleRemoveGame(ActionEvent event) {
        getKiosk().getCatalogue().removeGame(getSelectedGame());
        gamesTv.setItems(getKiosk().getCatalogue().getAllGames());
    }
    
    @FXML
    private void handleExit(ActionEvent event) {
        stage.close();
    }

}
