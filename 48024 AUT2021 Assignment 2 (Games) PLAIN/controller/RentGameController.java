package controller;

import au.edu.uts.ap.javafx.Controller;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;
import model.Kiosk;
import model.Game;

public class RentGameController extends Controller<Kiosk> {
	@FXML private TextField idTf;
    @FXML private Button selectCustomerBtn;
    @FXML private TableView<Game> gamesTv;
    @FXML private Button rentGameBtn;
    @FXML private Text commentTxt;
    
    public final Kiosk getKiosk() {
        return model;
    }
    
    private int getID() {
        return Integer.parseInt(idTf.getText());
    }
    
    private Game getSelectedGame() {
        return gamesTv.getSelectionModel().getSelectedItem();
    }
    
    @FXML
    private void handleSelectCustomer(ActionEvent event) {
        if (getKiosk().getCustomer(getID()) != null) {
            gamesTv.setItems(getKiosk().getCatalogue().getAvailableGames());
            commentTxt.setText("");
        }
        else {
        	commentTxt.setText("Invalid Customer ID.");
        }
    }
    
    @FXML
    private void handleRentGame(ActionEvent event) {
        try {
            if (getKiosk().getCatalogue().rentGameToCustomer(
                    getSelectedGame(), getKiosk().getCustomer(getID()))) {
            	commentTxt.setText("Game Rented.");
            }
            else {
            	commentTxt.setText("Not Enough Money");
            }
        }
        catch (Exception e) {
        	commentTxt.setText("Invalid Customer ID.");
        }
    }
    
    @FXML 
    private void initialize() {
        idTf.textProperty().addListener((o, oldID, newID) ->
                selectCustomerBtn.setDisable(!idTf.getText().matches("[0-9]+")));
        gamesTv.getSelectionModel().selectedItemProperty().addListener(
                (o, oldGame, newGame) -> rentGameBtn.setDisable(getSelectedGame() == null));
    }
    
    @FXML
    private void handleExit(ActionEvent event) {
        stage.close();
    }
}
