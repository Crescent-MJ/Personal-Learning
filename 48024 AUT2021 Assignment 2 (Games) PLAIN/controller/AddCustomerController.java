
package controller;

import au.edu.uts.ap.javafx.Controller;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;
import model.Kiosk;

public class AddCustomerController extends Controller<Kiosk> {
	@FXML private TextField idTf;
    @FXML private TextField nameTf;
    @FXML private TextField balanceTf;
    @FXML private Text commentTxt;
    @FXML private Button addCustomerBtn;
    
    public final Kiosk getKiosk() {
        return model;
    }
    
    private int getID() {
        return Integer.parseInt(idTf.getText());
    }
    
    private String getName() {
        return nameTf.getText();
    }
    
    private int getBalance() {
        return Integer.parseInt(balanceTf.getText());
    }
    
    @FXML
    private void handleAddCustomer(ActionEvent event) {
        try {
            if (getKiosk().getCustomer(getID()) == null) {
                getKiosk().addCustomer(getID(), getName(), getBalance());
                commentTxt.setText("Customer added to Kiosk.");
            }
            else {
            	commentTxt.setText("Customer ID already exists.");
            }
        }
        catch (Exception e) {
        	commentTxt.setText("Invalid Inputs.");
        }
    }
    
    @FXML
    private void handleExit(ActionEvent event) {
        stage.close();
    }
}
