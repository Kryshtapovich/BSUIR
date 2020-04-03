package car_rental.controllers;

import car_rental.Constants;
import car_rental.model.Car;
import car_rental.model.Client;
import car_rental.model.Deal;
import car_rental.repository.CarRepository;
import car_rental.repository.ClientRepository;
import car_rental.repository.DealRepository;
import javafx.beans.property.SimpleObjectProperty;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import java.io.IOException;
import java.net.MalformedURLException;
import java.time.LocalDate;
import java.util.Date;

public class DealController extends BaseController<Deal> {

    private ClientRepository clients;
    private CarRepository cars;

    @FXML
    private TableColumn<Deal, Integer> id;

    @FXML
    private TableColumn<Deal, Date> issueDate;

    @FXML
    private TableColumn<Deal, Date> returnDate;

    @FXML
    private TableColumn<Deal, Integer> clientId;

    @FXML
    private TableColumn<Deal, Integer> carId;

    @FXML
    private TableColumn<Deal, Float> price;

    @FXML
    private TextField clientField;

    @FXML
    private TextField carField;

    @FXML
    private DatePicker issuePicker;

    @FXML
    private DatePicker returnPicker;

    @Override
    protected Deal createFromData() throws Exception {
        Integer clientId = parseIntegerValue(data.get("clientId").toString(), "client id");
        Integer carId = parseIntegerValue(data.get("carId").toString(), "car id");
        LocalDate issueDate = issuePicker.getValue();
        LocalDate returnDate = returnPicker.getValue();
        Client client = clients.getClientBase().getItemById(clientId);
        Car car = cars.getAutoPark().getItemById(carId);
        return new Deal(issueDate, returnDate, client, car);
    }

    @FXML
    private void initialize() {
        issuePicker.getEditor().setDisable(true);
        returnPicker.getEditor().setDisable(true);
        clients = new ClientRepository();
        cars = new CarRepository();
        TextField[] textFields = new TextField[]{clientField, carField};
        String[] dataKeys = new String[]{"clientId", "carId"};
        initialize(textFields, dataKeys, new DealRepository());
        setTable();
    }

    @Override
    protected void setTable() {
        id.setCellValueFactory(new PropertyValueFactory<>("id"));
        issueDate.setCellValueFactory(cellData -> new SimpleObjectProperty(cellData.getValue().getStringIssueDate()));
        returnDate.setCellValueFactory(cellData -> new SimpleObjectProperty(cellData.getValue().getStringReturnDate()));
        clientId.setCellValueFactory(cellData -> new SimpleObjectProperty<>(cellData.getValue().getClient().getId()));
        carId.setCellValueFactory(cellData -> new SimpleObjectProperty<>(cellData.getValue().getCar().getId()));
        price.setCellValueFactory(new PropertyValueFactory<>("price"));
        deleteButtonsColumn.setCellFactory(getCellRemoveCallback("Deal"));
    }

    @FXML
    private void back(ActionEvent event) throws IOException {
        switchStage(Constants.MAIN_MARKUP, event.getSource());
    }

    private void clearForm() {
        clearTextFields();
        issuePicker.setValue(null);
        issuePicker.getEditor().clear();
        returnPicker.setValue(null);
        returnPicker.getEditor().clear();
    }

    private void checkDatePickers() throws Exception {
        if(issuePicker.getValue() == null || returnPicker.getValue() == null){
            throw new Exception("Date pickers can't be empty");
        }
    }

    public void registerDeal() throws Exception {
        fillData();
        try {
            checkDataForEmptiness();
            Deal deal = createFromData();
            checkDatePickers();
            if (deal.getClient() == null) {
                throw new Exception("Such client doesn't exist");
            }
            if (deal.getCar() == null) {
                throw new Exception("Such car doesn't exist");
            }
            if (!deal.getCar().getIsFree()) {
                throw new Exception("This car isn't free");
            }
            deal.calculatePrice();
            checkRepositoryContaining(deal, "deal", true);
            if (deal.checkDateCrossings(repository.getContainer().getItems())) {
                throw new Exception("Choose another date");
            }
            if (deal.getIssueDate().equals(LocalDate.now())) {
                deal.getCar().setIsFree(false);
            }
            cars.update();
            registerItem(deal, "Deal");
        }
        catch (Exception ex) {
            showAlert(Alert.AlertType.ERROR, ex.getMessage());
        }
        finally {
            clearForm();
        }
    }

    public void searchDeal() throws MalformedURLException {
        fillData();
        try {
            Deal deal = createFromData();
            showSearchTable(deal, "deals");
        }
        catch (Exception ex) {
            showAlert(Alert.AlertType.ERROR, ex.getMessage());
        }
        finally {
            clearForm();
        }
    }

    @Override
    protected void deleteItem(Deal item, String itemType) throws MalformedURLException {
        item.getCar().setIsFree(true);
        super.deleteItem(item, itemType);
    }
}
