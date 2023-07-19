package controller;

import au.edu.uts.ap.javafx.Controller;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;
import model.Kiosk;

public class TopUpAccountController extends Controller<Kiosk> {
	@FXML private Text commentTxt;
    @FXML private TextField idTf;
    @FXML private TextField amountTf;
    @FXML private Button topUpBtn;
    
    public final Kiosk getKiosk() {
        return model;
    }
    
    private int getID() {
        return Integer.parseInt(idTf.getText());
    }
    
    private int getAmount() {
        return Integer.parseInt(amountTf.getText());
    }
    
    @FXML
    private void handleTopUp(ActionEvent event) {
        try {
            getKiosk().topUpAccount(getKiosk().getCustomer(getID()), getAmount());
            commentTxt.setText("Transaction Complete.");
        }
        catch (NullPointerException e) {
        	commentTxt.setText("Invalid Customer ID.");
        }
        catch (NumberFormatException e) {
        	commentTxt.setText("Invalid Amount.");
        }
    }
    
    @FXML
    private void handleExit(ActionEvent event) {
        stage.close();
    }
}
