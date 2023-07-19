package controller;

import au.edu.uts.ap.javafx.Controller;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.TableView;
import model.Kiosk;
import model.Game;

public class ShowGamesByYearController extends Controller<Kiosk> {
	@FXML private ListView<Integer> yearsLv;
    @FXML private TableView<Game> gamesTv;
    @FXML private Button displayGamesBtn;
    
    public final Kiosk getKiosk() {
        return model;
    }
    
    private int getSelectedYear() {
        return yearsLv.getSelectionModel().getSelectedItem();
    }
    
    @FXML
    private void handleDisplayGames(ActionEvent event) {
        gamesTv.setItems(getKiosk().getCatalogue().getGamesByYear(getSelectedYear()));
    }
    
    @FXML
    private void handleExit(ActionEvent event) {
        stage.close();
    }
}
