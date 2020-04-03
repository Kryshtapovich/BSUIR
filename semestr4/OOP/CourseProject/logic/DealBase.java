package car_rental.logic;

import car_rental.model.Deal;
import java.util.ArrayList;


public class DealBase extends Container<Deal> {

    public DealBase(ArrayList<Deal> deals) {
        super(deals);
    }

    @Override
    public Deal getItemById(Integer id) {
        ArrayList<Deal> res = getItemsByCondition(x -> x.getId().equals(id));
        if (res.size() == 0) {
            return null;
        }
        else {
            return res.get(0);
        }
    }

    @Override
    public ArrayList<Deal> getItemsByObjectFields(Deal obj) {
        ArrayList<Deal> dealsByIssueDate = getItemsByCondition(x -> x.getStringIssueDate().equals(obj.getIssueDate()));
        ArrayList<Deal> dealsByReturnDate = getItemsByCondition(x -> x.getStringReturnDate().equals(obj.getReturnDate()));
        ArrayList<Deal> dealsByClient = getItemsByCondition(x -> x.getClient().equals(obj.getClient()));
        ArrayList<Deal> dealsByCar = getItemsByCondition(x -> x.getCar().equals(obj.getCar()));
        dealsByClient.addAll(dealsByCar);
        dealsByReturnDate.addAll(dealsByClient);
        dealsByReturnDate.addAll(dealsByIssueDate);
        return dealsByReturnDate;
    }
}
