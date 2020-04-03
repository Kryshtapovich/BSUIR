package car_rental.model;

import lombok.Data;
import lombok.Getter;
import lombok.NoArgsConstructor;

import javax.persistence.*;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.temporal.ChronoUnit;
import java.util.ArrayList;


@Data
@Entity
@Table(name = "Deal")
@NoArgsConstructor
public class Deal {

    @Id
    @Column(name = "DealId")
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Getter
    private Integer id;

    @Getter
    @Column(name = "IssueDate")
    private LocalDate issueDate;

    @Getter
    @Column(name = "ReturnDate")
    private LocalDate returnDate;

    @Getter
    @OneToOne
    @JoinColumn(name = "ClientId", referencedColumnName = "ClientId")
    private Client client;

    @Getter
    @OneToOne
    @JoinColumn(name = "CarId", referencedColumnName = "CarId")
    private Car car;

    @Getter
    @Column(name = "Price")
    private Integer price;


    public Deal(LocalDate issueDate, LocalDate returnDate, Client client, Car car) throws Exception {
        this.client = client;
        this.car = car;

        if ((issueDate != null && returnDate != null) &&
                (returnDate.isBefore(issueDate) || issueDate.isBefore(LocalDate.now()))) {
            throw new Exception("Wrong date provided");
        }

        this.issueDate = issueDate;
        this.returnDate = returnDate;
    }

    public void calculatePrice() {
        if (issueDate != null && returnDate != null && car != null) {
            int period = (int) ChronoUnit.DAYS.between(issueDate, returnDate);
            this.price = period == 0 ? car.getPrice() : period * car.getPrice();
        }
    }

    public String getStringIssueDate() {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd-MM-yyyy");
        return issueDate.format(formatter);
    }

    public String getStringReturnDate() {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd-MM-yyyy");
        return returnDate.format(formatter);
    }

    public boolean checkDateCrossings(ArrayList<Deal> deals) {
        for (Deal deal : deals) {
            if (ChronoUnit.DAYS.between(issueDate, deal.returnDate) >= 0 ||
                    ChronoUnit.DAYS.between(deal.issueDate, returnDate) >= 0) {
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null || getClass() != obj.getClass()) {
            return false;
        }
        Deal deal = (Deal) obj;
        return issueDate.equals(deal.issueDate) &&
                returnDate.equals(deal.returnDate) &&
                client.equals(deal.client) &&
                car.equals(deal.car) &&
                price.equals(deal.price);
    }
}
