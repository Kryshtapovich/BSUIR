package car_rental.model;

import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import javax.persistence.*;


@Entity
@Table(name = "Car")
@NoArgsConstructor
public class Car {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "CarId")
    @Getter
    private Integer id;

    @Getter
    @Column(name = "Company")
    private String company;

    @Getter
    @Column(name = "Model")
    private String model;

    @Getter
    @Column(name = "EngineVolume")
    private Integer volume;

    @Getter
    @Column(name = "EnginePower")
    private Integer power;

    @Getter
    @Column(name = "Price")
    private Integer price;

    @Setter
    @Getter
    @Column(name = "IsFree")
    private Boolean isFree;

    public Car(String company, String model, Integer volume, Integer power, Integer price) throws Exception {
        if(volume != null && volume <= 0) {
            throw new Exception("Engine volume can't be negative");
        }
        if(power != null && power <= 0) {
            throw new Exception("Engine power can't be negative");
        }
        if (price != null && price < 0) {
            throw new Exception("Price can't be negative");
        }

        this.company = company;
        this.model = model;
        this.volume = volume;
        this.power = power;
        this.price = price;
        this.isFree = true;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null || getClass() != obj.getClass()) {
            return false;
        }
        Car car = (Car) obj;
        return company.equals(car.company) &&
                model.equals(car.model) &&
                volume.equals(car.volume) &&
                power.equals(car.power) &&
                price.equals(car.price);
    }

    public void setPrice(Integer price) throws Exception {
        if(price < 0) {
            throw new Exception("Price can't be negative");
        }
        this.price = price;
    }
}
