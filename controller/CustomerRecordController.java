
package controller;

import au.edu.uts.ap.javafx.Controller;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;
import model.Game;
import model.Kiosk;

public class CustomerRecordController extends Controller<Kiosk> {
	@FXML private TextField idTf;
    @FXML private Button selectCustomerBtn;
    @FXML private Text commentTxt;
    @FXML private TableView<Game> rentedGamesTv;
    @FXML private TableView<Game> rentHistoryTv;
    
    public final Kiosk getKiosk() {
        return model;
    }
    
    private int getID() {
        return Integer.parseInt(idTf.getText());
    }
    
    @FXML
    private void handleSelectCustomer(ActionEvent event) {
        try {
            rentedGamesTv.setItems(getKiosk().getCustomer(getID()).currentlyRented());
            rentHistoryTv.setItems(getKiosk().getCustomer(getID()).rentingHistory());
            commentTxt.setText(getKiosk().getCustomer(getID()).toString());
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
