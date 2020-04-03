package car_rental.controllers;

import java.io.IOException;
import java.net.MalformedURLException;
import car_rental.Constants;
import car_rental.model.Client;
import car_rental.repository.ClientRepository;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.control.cell.TextFieldTableCell;


public class ClientController extends BaseController<Client> {

    @FXML
    private TableColumn<Client, Integer> id;

    @FXML
    private TableColumn<Client, String> name;

    @FXML
    private TableColumn<Client, String> surname;

    @FXML
    private TableColumn<Client, String> address;

    @FXML
    private TableColumn<Client, String> phone;

    @FXML
    private TextField nameField;

    @FXML
    private TextField surnameField;

    @FXML
    private TextField addressField;

    @FXML
    private TextField phoneField;

    @FXML
    private void back(ActionEvent event) throws IOException {
        switchStage(Constants.MAIN_MARKUP, event.getSource());
    }

    @FXML
    private void registerClient() throws Exception {
        fillData();
        Client client = createFromData();
        try {
            checkDataForEmptiness();
            checkRepositoryContaining(client, "client", true);
            registerItem(client, "Client");
        }
        catch (Exception ex) {
            showAlert(Alert.AlertType.ERROR, ex.getMessage());
        }
        finally {
            clearTextFields();
        }
    }

    @FXML
    private void searchClient() throws MalformedURLException {
        fillData();
        showSearchTable(createFromData(), "clients");
    }

    @FXML
    private void initialize() {
        TextField[] fields = new TextField[]{nameField, surnameField, addressField, phoneField};
        String[] dataKeys = new String[]{"name", "surname", "address", "phone"};
        initialize(fields, dataKeys, new ClientRepository());
        setTable();
    }

    @Override
    protected Client createFromData() {
        String name = data.get("name").toString();
        String surname = data.get("surname").toString();
        String address = data.get("address").toString();
        String phone = data.get("phone").toString();
        return new Client(name, surname, address, phone);
    }

    @Override
    protected void setTable() {
        id.setCellValueFactory(new PropertyValueFactory<>("id"));
        name.setCellValueFactory(new PropertyValueFactory<>("name"));
        name.setCellFactory(TextFieldTableCell.forTableColumn());
        surname.setCellValueFactory(new PropertyValueFactory<>("surname"));
        surname.setCellFactory(TextFieldTableCell.forTableColumn());
        address.setCellValueFactory(new PropertyValueFactory<>("address"));
        address.setCellFactory(TextFieldTableCell.forTableColumn());
        phone.setCellValueFactory(new PropertyValueFactory<>("phone"));
        phone.setCellFactory(TextFieldTableCell.forTableColumn());
        deleteButtonsColumn.setCellFactory(getCellRemoveCallback("Client"));
    }

    public void changeNameHandler(TableColumn.CellEditEvent editedCell) {
        Client selectedClient = table.getSelectionModel().getSelectedItem();
        selectedClient.setName(editedCell.getNewValue().toString());
        repository.update();
    }

    public void changeSurnameHandler(TableColumn.CellEditEvent editedCell) {
        Client selectedClient = table.getSelectionModel().getSelectedItem();
        selectedClient.setSurname(editedCell.getNewValue().toString());
        repository.update();
    }

    public void changeAddressHandler(TableColumn.CellEditEvent editedCell) {
        Client selectedClient = table.getSelectionModel().getSelectedItem();
        selectedClient.setAddress(editedCell.getNewValue().toString());
        repository.update();
    }

    public void changePhoneHandler(TableColumn.CellEditEvent editedCell) {
        Client selectedClient = table.getSelectionModel().getSelectedItem();
        selectedClient.setPhone(editedCell.getNewValue().toString());
        repository.update();
    }
}
