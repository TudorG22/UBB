package socialnetwork.repository;

import socialnetwork.domain.Entity;
import socialnetwork.validation.Validator;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    private final Map<ID, E> entities = new LinkedHashMap<>();
    private final Validator<E> validator;

    public InMemoryRepository(Validator<E> validator) {
        this.validator = validator;
    }

    @Override
    public E save(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entitatea nu poate fi null.");
        }
        validator.validate(entity);
        if (entities.containsKey(entity.getId())) {
            return entity;
        }
        entities.put(entity.getId(), entity);
        return null;
    }

    @Override
    public E delete(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("Id-ul nu poate fi null.");
        }
        return entities.remove(id);
    }

    @Override
    public E update(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entitatea nu poate fi null.");
        }
        validator.validate(entity);
        if (!entities.containsKey(entity.getId())) {
            return entity;
        }
        entities.put(entity.getId(), entity);
        return null;
    }

    @Override
    public E findOne(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("Id-ul nu poate fi null.");
        }
        return entities.get(id);
    }

    @Override
    public List<E> findAll() {
        return new ArrayList<>(entities.values());
    }
}
