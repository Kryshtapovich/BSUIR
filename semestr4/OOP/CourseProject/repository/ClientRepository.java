package car_rental.repository;

import car_rental.model.Client;
import car_rental.logic.ClientBase;


public class ClientRepository extends Repository<Client> {

    public ClientRepository() {
        super();
        container = new ClientBase(this.getContentFromTable("Client"));
    }

    public ClientBase getClientBase() {
        return (ClientBase) container;
    }
}
