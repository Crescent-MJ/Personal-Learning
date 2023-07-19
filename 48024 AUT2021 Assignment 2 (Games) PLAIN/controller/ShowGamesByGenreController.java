package controller;

import au.edu.uts.ap.javafx.Controller;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.TableView;
import model.Genre;
import model.Kiosk;
import model.Game;

public class ShowGamesByGenreController extends Controller<Kiosk>{
	@FXML private ListView<Genre> genresLv;
    @FXML private TableView<Game> gamesTv;
    @FXML private Button displayGamesBtn;
    
    public final Kiosk getKiosk() {
        return model;
    }
    
    private Genre getSelectedGenre() {
        return genresLv.getSelectionModel().getSelectedItem();
    }
    
    @FXML
    private void handleDisplayGames(ActionEvent event) {
        gamesTv.setItems(getKiosk().getCatalogue().getGamesInGenre(getSelectedGenre()));
    }
    
    @FXML
    private void handleExit(ActionEvent event) {
        stage.close();
    }
}
