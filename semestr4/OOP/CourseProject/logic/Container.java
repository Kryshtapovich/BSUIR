package car_rental.logic;

import lombok.Getter;

import java.util.ArrayList;
import java.util.function.Predicate;
import java.util.stream.Collectors;

public abstract class Container<T> {

    @Getter
    protected ArrayList<T> items;

    public Container(ArrayList<T> items) {
        this.items = items;
    }

    public void addItem(T item) {
        items.add(item);
    }

    public void removeItem(T item) {
        items.remove(item);
    }

    protected ArrayList<T> getItemsByCondition(Predicate<T> condition) {
        return (ArrayList<T>) items.stream().filter(condition).collect(Collectors.toList());
    }

    public abstract T getItemById(Integer id);

    public abstract ArrayList<T> getItemsByObjectFields(T obj);

    public T getItem(T item) {
        return items.get(items.indexOf(item));
    }
}
