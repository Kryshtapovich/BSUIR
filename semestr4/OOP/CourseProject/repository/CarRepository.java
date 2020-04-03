package car_rental.repository;

import car_rental.model.Car;
import car_rental.logic.AutoPark;

public class CarRepository extends Repository<Car> {

    public CarRepository() {
        super();
        container = new AutoPark(this.getContentFromTable("Car"));
    }

    public AutoPark getAutoPark() {
        return (AutoPark) container;
    }
}
