package car_rental.logic;

import car_rental.model.Client;
import java.util.ArrayList;
import java.util.stream.Collectors;


public class ClientBase extends Container<Client> {

    public ClientBase(ArrayList<Client> clients) {
        super(clients);
    }

    @Override
    public Client getItemById(Integer id) {
        ArrayList<Client> res = getItemsByCondition(x -> x.getId().equals(id));
        if (res.size() == 0){
            return null;
        }else {
            return res.get(0);
        }
    }

    @Override
    public ArrayList<Client> getItemsByObjectFields(Client obj) {
        ArrayList<Client> clientsByName = getItemsByCondition(x -> x.getName().equals(obj.getName()));
        ArrayList<Client> clientsBySurname = getItemsByCondition(x -> x.getSurname().equals(obj.getSurname()));
        ArrayList<Client> clientsByAddress = getItemsByCondition(x -> x.getAddress().equals(obj.getAddress()));
        ArrayList<Client> clientsByPhone = getItemsByCondition(x -> x.getPhone().equals(obj.getPhone()));
        clientsByAddress.addAll(clientsByPhone);
        clientsBySurname.addAll(clientsByAddress);
        clientsByName.addAll(clientsBySurname);
        return (ArrayList<Client>) clientsByName.stream().distinct().collect(Collectors.toList());
    }
}
