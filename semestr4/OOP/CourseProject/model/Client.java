package car_rental.model;

import lombok.Data;
import lombok.Getter;
import lombok.NoArgsConstructor;
import javax.persistence.*;

@Data
@Entity
@Table(name = "Client")
@NoArgsConstructor
public class Client {

    @Id
    @Column(name = "ClientId")
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Getter
    private Integer id;

    @Column(name = "Name")
    private String name;

    @Column(name = "Surname")
    private String surname;

    @Column(name = "Address")
    private String address;

    @Column(name = "PhoneNumber")
    private String phone;

    public Client(String name, String surname, String address, String phone) {
        this.name = name;
        this.surname = surname;
        this.address = address;
        this.phone = phone;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null || getClass() != obj.getClass()) {
            return false;
        }
        Client client = (Client) obj;
        return name.equals(client.name) &&
                surname.equals(client.surname) &&
                address.equals(client.address) &&
                phone.equals(client.phone);
    }
}
