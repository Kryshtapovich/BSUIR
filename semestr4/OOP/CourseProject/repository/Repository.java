package car_rental.repository;

import car_rental.logic.Container;
import lombok.Getter;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.cfg.Configuration;
import java.util.ArrayList;


public abstract class Repository<T> {

    @Getter
    protected Container<T> container;

    protected SessionFactory sessionFactory;

    public Repository() {
        Configuration configuration = new Configuration().configure("hibernate.cfg.xml");
        sessionFactory = configuration.buildSessionFactory();
    }

    public void stop() {
        sessionFactory.close();
    }

    public void add(T item) {
        Session session = sessionFactory.openSession();
        if (!contains(item)) {
            container.addItem(item);
            session.beginTransaction();
            session.persist(item);
            session.getTransaction().commit();
        }
        session.close();
    }

    public void remove(T item) {
        Session session = sessionFactory.openSession().getSession();
        container.removeItem(item);
        session.beginTransaction();
        session.delete(item);
        session.getTransaction().commit();
        session.close();
    }

    public void update() {
        Session session = sessionFactory.openSession();
        session.beginTransaction();
        for (T item : container.getItems()) {
            session.update(item);
        }
        session.getTransaction().commit();
        session.close();
    }

    protected ArrayList<T> getContentFromTable(String tableName) {
        Session session = sessionFactory.openSession();
        ArrayList<T> res = (ArrayList<T>) session.createQuery(String.format("from %s", tableName)).getResultList();
        session.close();
        return res;
    }

    public T getItem(T item) {
        return container.getItem(item);
    }

    public ArrayList<T> getItemsByObjectFields(T obj) {
        return container.getItemsByObjectFields(obj);
    }

    public boolean contains(T item) {
        return container.getItems().contains(item);
    }
}
