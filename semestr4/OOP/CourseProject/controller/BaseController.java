package car_rental.controllers;

import car_rental.Constants;
import car_rental.repository.Repository;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.effect.Bloom;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import javafx.util.Callback;
import java.io.File;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;


public class BaseController<T> {

    protected Repository<T> repository;
    protected TextField[] textFields;
    protected HashMap<String, Button> buttons;
    protected HashMap<String, Object> data;
    private String[] dataKeys;

    @FXML
    protected TableView<T> table;

    @FXML
    protected AnchorPane form;

    @FXML
    protected Button registerButton;

    @FXML
    protected Button findButton;

    @FXML
    protected TableColumn<T, Void> deleteButtonsColumn;

    public BaseController() {
        repository = new Repository<T>() {
        };
    }

    public void stop() {
        repository.stop();
    }

    public Stage switchStage(String markup, Stage stage) throws IOException {
        Parent root = FXMLLoader.load(getUrl(markup));
        stage.setScene(new Scene(root));
        return stage;
    }

    public void switchStage(String markup, Object node) throws IOException {
        switchStage(markup, (Stage) ((Node) node).getScene().getWindow());
    }

    public URL getUrl(String path) throws MalformedURLException {
        return new File(path).toURI().toURL();
    }

    protected void initialize(TextField[] fields, String[] dataKeys, Repository<T> repository) {
        textFields = fields;
        this.buttons = new HashMap<>();
        this.buttons.put("add", registerButton);
        this.buttons.put("find", findButton);
        this.dataKeys = dataKeys;
        this.repository = repository;
    }

    protected void fillData() {
        data = new HashMap<>();
        for (int i = 0; i < dataKeys.length; i++) {
            if(!textFields[i].isDisable()) {
                data.put(dataKeys[i], textFields[i].getText());
            }
        }
    }

    protected void clearTextFields() {
        for (TextField field : textFields) {
            field.clear();
        }
    }

    protected void showAlert(Alert.AlertType type, String text) throws MalformedURLException {
        String path = type.equals(Alert.AlertType.ERROR) ? Constants.ERROR : Constants.INFO;
        Alert alert = new Alert(type);
        alert.setHeaderText(text);

        DialogPane dialogPane = alert.getDialogPane();
        dialogPane.getStylesheets().add(getUrl(path).toExternalForm());
        Bloom bloom = new Bloom();
        bloom.setThreshold(0.5);
        dialogPane.setEffect(bloom);
        alert.show();
    }

    private void setVisibility(boolean isTable, boolean isForm) {
        if (!isTable) {
            table.getItems().clear();
        }
        table.setVisible(isTable);
        form.setVisible(isForm);
        for (Button button : buttons.values()) {
            button.setVisible(false);
        }
    }

    protected void showTable(ObservableList<T> data) {
        setVisibility(true, false);
        table.setItems(data);
    }

    protected void showForm() {
        setVisibility(false, true);
    }

    protected void showSearchTable(T obj, String items) throws MalformedURLException {
        ArrayList<T> foundItems = repository.getItemsByObjectFields(obj);
        if (foundItems.size() == 0) {
            showAlert(Alert.AlertType.INFORMATION, String.format("No %s found", items));
        }
        else {
            showTable(FXCollections.observableArrayList(foundItems));
            clearTextFields();
        }
    }

    @FXML
    protected void showAllItems() throws MalformedURLException {
        ObservableList<T> res = FXCollections.observableArrayList(repository.getContainer().getItems());
        if (res.size() == 0) {
            table.setVisible(false);
            showAlert(Alert.AlertType.INFORMATION, "No content to display");
        }
        else {
            showTable(res);
        }
    }

    @FXML
    protected void addItem() {
        showForm();
        buttons.get("add").setVisible(true);
    }

    @FXML
    protected void findItems() {
        showForm();
        buttons.get("find").setVisible(true);
    }

    protected void checkDataForEmptiness() throws Exception {
        if (data.containsValue("")) {
            throw new Exception("Text fields can't be empty");
        }
    }

    protected void checkRepositoryContaining(T item, String itemType, boolean isContain) throws Exception {
        if (isContain && repository.contains(item)) {
            throw new Exception(String.format("Such %s already exists", itemType));
        }
        else if (!isContain && !repository.contains(item)) {
            throw new Exception(String.format("Such %s doesn't exist", itemType));
        }
    }

    protected Integer parseIntegerValue(String value, String valueType) throws Exception {
        try {
            if (value.equals("")) {
                return null;
            }
            else {
                return Integer.parseInt(value);
            }
        }
        catch (NumberFormatException ex) {
            throw new Exception(String.format("Wrong %s provided", valueType));
        }
    }

    protected void registerItem(T item, String itemType) throws MalformedURLException {
        repository.add(item);
        showAlert(Alert.AlertType.INFORMATION, String.format("%s added", itemType));
    }

    protected void deleteItem(T item, String itemType) throws MalformedURLException {
        repository.remove(item);
        showAlert(Alert.AlertType.INFORMATION, String.format("%s deleted", itemType));
    }

    protected T createFromData() throws Exception {
        return null;
    }

    protected void setTable() {

    }

    protected Callback<TableColumn<T, Void>, TableCell<T, Void>> getCellRemoveCallback(String itemType) {
        Callback<TableColumn<T, Void>, TableCell<T, Void>> cellFactory = new Callback<TableColumn<T, Void>, TableCell<T, Void>>() {
            @Override
            public TableCell<T, Void> call(final TableColumn<T, Void> param) {
                final TableCell<T, Void> cell = new TableCell<T, Void>() {
                    private Button btn = new Button("Delete");

                    {
                        try {
                            btn.getStylesheets().add(getUrl(Constants.BUTTON).toExternalForm());
                        }
                        catch (MalformedURLException ex) {
                            try {
                                showAlert(Alert.AlertType.ERROR, ex.getMessage());
                            }
                            catch (MalformedURLException e) {
                                e.printStackTrace();
                            }
                        }

                        btn.setOnAction((ActionEvent event) -> {
                            T item = getTableView().getItems().get(getIndex());
                            try {
                                deleteItem(item, itemType);
                                showAllItems();
                            }
                            catch (MalformedURLException ex) {
                                try {
                                    showAlert(Alert.AlertType.ERROR, ex.getMessage());
                                }
                                catch (MalformedURLException e) {
                                    e.printStackTrace();
                                }
                            }
                        });
                    }

                    @Override
                    public void updateItem(Void item, boolean empty) {
                        super.updateItem(item, empty);
                        if (empty) {
                            setGraphic(null);
                        }
                        else {
                            setGraphic(btn);
                        }
                    }
                };
                return cell;
            }
        };
        return cellFactory;
    }
}
