package car_rental.logic;

import car_rental.model.Car;
import java.util.ArrayList;
import java.util.stream.Collectors;


public class AutoPark extends Container<Car> {

    public AutoPark(ArrayList<Car> cars) {
        super(cars);
    }

    @Override
    public Car getItemById(Integer id) {
        ArrayList<Car> res = getItemsByCondition(x -> x.getId().equals(id));
        if (res.size() == 0){
            return null;
        }else {
            return res.get(0);
        }
    }

    @Override
    public ArrayList<Car> getItemsByObjectFields(Car obj) {
        ArrayList<Car> carsByCompany = getItemsByCondition(x -> x.getCompany().equals(obj.getCompany()));
        ArrayList<Car> carsByModel = getItemsByCondition(x -> x.getCompany().equals(obj.getModel()));
        ArrayList<Car> carsByVolume = getItemsByCondition(x -> x.getCompany().equals(obj.getVolume()));
        ArrayList<Car> carsByPower = getItemsByCondition(x -> x.getCompany().equals(obj.getPower()));
        ArrayList<Car> carsByPrice = getItemsByCondition(x -> x.getCompany().equals(obj.getPrice()));
        ArrayList<Car> freeOrRentedCars = new ArrayList<>();
        Boolean flag = obj.getIsFree();
        if (flag != null) {
            freeOrRentedCars = flag ? getItemsByCondition(x -> x.getIsFree()) : getItemsByCondition(x -> !x.getIsFree());
        }
        carsByPrice.addAll(freeOrRentedCars);
        carsByPower.addAll(carsByPrice);
        carsByVolume.addAll(carsByPower);
        carsByModel.addAll(carsByVolume);
        carsByCompany.addAll(carsByModel);
        return (ArrayList<Car>) carsByCompany.stream().distinct().collect(Collectors.toList());
    }
}
