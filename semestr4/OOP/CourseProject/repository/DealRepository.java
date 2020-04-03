package car_rental.repository;

import car_rental.logic.DealBase;
import car_rental.model.Deal;
import java.time.LocalDate;
import java.time.temporal.ChronoUnit;


public class DealRepository extends Repository<Deal> {

    public DealRepository() {
        super();
        container = new DealBase(this.getContentFromTable("Deal"));
        for (Deal deal : getDealBase().getItems()) {
            if (ChronoUnit.DAYS.between(deal.getReturnDate(), LocalDate.now()) <= 0) {
                deal.getCar().setIsFree(true);
            }
            else if(ChronoUnit.DAYS.between(LocalDate.now(), deal.getIssueDate()) <= 0) {
                deal.getCar().setIsFree(false);
            }
        }
    }

    public DealBase getDealBase() {
        return (DealBase) container;
    }
}
