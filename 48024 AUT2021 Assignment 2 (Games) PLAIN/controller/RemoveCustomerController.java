package controller;

import au.edu.uts.ap.javafx.Controller;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TableView;
import model.Customer;
import model.Kiosk;

public class RemoveCustomerController extends Controller<Kiosk> {
	@FXML private TableView<Customer> customersTv;
    @FXML private Button removeCustomerBtn;
    
    public final Kiosk getKiosk() {
        return model;
    }
    
    private Customer getSelectedCustomer() {
        return customersTv.getSelectionModel().getSelectedItem();
    }
    
    @FXML
    private void handleRemoveCustomer(ActionEvent event) {
        getKiosk().removeCustomer(getSelectedCustomer());
    }
    
    @FXML
    private void handleExit(ActionEvent event) {
        stage.close();
    }

}
