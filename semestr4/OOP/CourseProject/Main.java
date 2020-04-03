package car_rental;

import car_rental.controllers.BaseController;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.scene.image.Image;
import javafx.stage.Stage;
import java.io.IOException;
import java.net.URL;

public class Main extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws IOException {

        BaseController controller = new BaseController();
        URL icon = controller.getUrl(Constants.MAIN_ICON);
        primaryStage.getIcons().add(new Image(String.valueOf(icon)));
        primaryStage.setTitle(Constants.TITLE);
        controller.switchStage(Constants.MAIN_MARKUP, primaryStage).show();
        primaryStage.setOnCloseRequest(event -> {
            controller.stop();
            Platform.exit();
            System.exit(0);
        });
    }
}
