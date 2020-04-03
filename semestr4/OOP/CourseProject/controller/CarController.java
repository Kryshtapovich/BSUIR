package car_rental.controllers;

import java.io.IOException;
import java.net.MalformedURLException;
import car_rental.Constants;
import car_rental.model.Car;
import car_rental.repository.CarRepository;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.control.cell.TextFieldTableCell;
import javafx.util.converter.IntegerStringConverter;


public class CarController extends BaseController<Car> {

    @FXML
    private TableColumn<Car, Integer> id;

    @FXML
    private TableColumn<Car, String> company;

    @FXML
    private TableColumn<Car, String> model;

    @FXML
    private TableColumn<Car, Integer> volume;

    @FXML
    private TableColumn<Car, Integer> power;

    @FXML
    private TableColumn<Car, Integer> price;

    @FXML
    private TableColumn<Car, Boolean> isFree;

    @FXML
    private TextField companyField;

    @FXML
    private TextField modelField;

    @FXML
    private TextField volumeField;

    @FXML
    private TextField powerField;

    @FXML
    private TextField priceField;

    @FXML
    private TextField isFreeField;

    @FXML
    private Label isFreeLabel;

    @FXML
    private void back(ActionEvent event) throws IOException {
        switchStage(Constants.MAIN_MARKUP, event.getSource());
    }

    @Override
    protected void addItem() {
        super.addItem();
        isFreeLabel.setDisable(true);
        isFreeField.setDisable(true);
    }

    @Override
    protected void findItems() {
        super.findItems();
        isFreeLabel.setDisable(false);
        isFreeField.setDisable(false);
    }

    @FXML
    private void registerCar() throws MalformedURLException {
        fillData();
        try {
            checkDataForEmptiness();
            registerItem(createFromData(), "Car");
        }
        catch (Exception ex) {
            showAlert(Alert.AlertType.ERROR, ex.getMessage());
        }
        finally {
            clearTextFields();
        }
    }

    @FXML
    private void searchCar() throws MalformedURLException {
        fillData();
        try {
            Car car = createFromData();
            String buffer = data.get("isFree").toString();
            Boolean isFree = buffer.equals("") ? null : Boolean.parseBoolean(buffer);
            car.setIsFree(isFree);
            showSearchTable(car, "cars");
        }
        catch (Exception ex) {
            showAlert(Alert.AlertType.ERROR, ex.getMessage());
        }
    }

    @FXML
    private void initialize() {
        TextField[] fields = new TextField[]{companyField, modelField, volumeField, powerField, priceField, isFreeField};
        String[] dataKeys = new String[]{"company", "model", "volume", "power", "price", "isFree"};
        initialize(fields, dataKeys, new CarRepository());
        setTable();
    }

    @Override
    protected void setTable() {
        id.setCellValueFactory(new PropertyValueFactory<>("id"));
        company.setCellValueFactory(new PropertyValueFactory<>("company"));
        model.setCellValueFactory(new PropertyValueFactory<>("model"));
        volume.setCellValueFactory(new PropertyValueFactory<>("volume"));
        power.setCellValueFactory(new PropertyValueFactory<>("power"));
        price.setCellValueFactory(new PropertyValueFactory<>("price"));
        price.setCellFactory(TextFieldTableCell.forTableColumn(new IntegerStringConverter()));
        isFree.setCellValueFactory(new PropertyValueFactory<>("isFree"));
        deleteButtonsColumn.setCellFactory(getCellRemoveCallback("Car"));
    }

    @Override
    protected Car createFromData() throws Exception {
        String company = data.get("company").toString();
        String model = data.get("model").toString();
        Integer volume = parseIntegerValue(data.get("volume").toString(), "engine volume");
        Integer power = parseIntegerValue(data.get("power").toString(), "engine power");
        Integer price = parseIntegerValue(data.get("price").toString(), "price");
        return new Car(company, model, volume, power, price);
    }

    public void changePriceHandler(TableColumn.CellEditEvent editedCell) throws MalformedURLException {
        try {
            Car selectedCar = table.getSelectionModel().getSelectedItem();
            selectedCar.setPrice(parseIntegerValue(editedCell.getNewValue().toString(), "price"));
            repository.update();
        }
        catch (Exception ex) {
            showAlert(Alert.AlertType.ERROR, ex.getMessage());
        }
    }
}
