
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

public class ReturnGameController extends Controller<Kiosk> {
	@FXML private TextField idTf;
    @FXML private Button selectCustomerBtn;
    @FXML private TableView<Game> gamesTv;
    @FXML private Button returnGameBtn;
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
        try {
            gamesTv.setItems(getKiosk().getCustomer(getID()).currentlyRented());
            commentTxt.setText("");
        }
        catch (Exception e) {
        	commentTxt.setText("Invalid Customer ID.");
        }
    }
    
    @FXML
    private void handleReturnGame(ActionEvent event) {
        try {
            getKiosk().getCatalogue().returnGameFromCustomer(
                    getSelectedGame(), getKiosk().getCustomer(getID()));
            commentTxt.setText("Game Returned.");
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
                (o, oldGame, newGame) -> returnGameBtn.setDisable(getSelectedGame() == null));
    }
    
    @FXML
    private void handleExit(ActionEvent event) {
        stage.close();
    }
}
