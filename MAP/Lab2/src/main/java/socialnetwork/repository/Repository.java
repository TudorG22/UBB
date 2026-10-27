package socialnetwork.repository;

import java.util.List;

/** Defineste operatiile comune ale unui repository. */
public interface Repository<ID, E> {
    void add(E entity);

    void remove(ID id);

    E find(ID id);

    List<E> getAll();
}
