
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

public class FavouriteGamesController extends Controller<Kiosk> {
	@FXML private TextField idTf;
    @FXML private Button selectCustomerBtn;
    @FXML private Text commentTxt;
    @FXML private TableView<Game> favGameTv;
    
    public final Kiosk getKiosk() {
        return model;
    }
    
    private int getID() {
        return Integer.parseInt(idTf.getText());
    }
    
    @FXML
    private void handleSelectCustomer(ActionEvent event) {
        try {
            favGameTv.setItems(getKiosk().getCustomer(getID()).favouriteGames());
            commentTxt.setText("");
        }
        catch (Exception e) {
        	commentTxt.setText("Invalid Customer ID.");
        }
    }
    
    @FXML
    private void handleExit(ActionEvent event) {
        stage.close();
    }

}
