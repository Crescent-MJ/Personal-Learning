
package controller;

import au.edu.uts.ap.javafx.Controller;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;
import model.Kiosk;

public class AddGameController extends Controller<Kiosk> {
	@FXML private TextField titleTf;
    @FXML private TextField yearTf;
    @FXML private TextField genreTf;
    @FXML private TextField priceTf;
    @FXML private Text commentTxt;
    @FXML private Button addGameBtn;
    
    public final Kiosk getKiosk() {
        return model;
    }
    
    private String getTitle() {
        return titleTf.getText();
    }
    
    private int getYear() {
        return Integer.parseInt(yearTf.getText());
    }
    
    private String getGenre() {
        return genreTf.getText();
    }
    
    private int getPrice() {
        return Integer.parseInt(priceTf.getText());
    }
    
    @FXML
    private void handleAddGame(ActionEvent event) {
        try {
            if (!getKiosk().getCatalogue().hasGame(getTitle(), getYear())) {
                getKiosk().getCatalogue().addGame(getTitle(), getYear(), getGenre(), getPrice());
                commentTxt.setText("Game added to Catalogue.");
            }
            else {
            	commentTxt.setText("Game already exists.");
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
