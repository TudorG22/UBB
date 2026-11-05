package curs.repository.db;

import curs.domain.Utilizator;
import curs.domain.validators.Validator;
import curs.repository.Repository;

public class UtilizatorDbRepository implements Repository<Long, Utilizator> {
    private Validator<Utilizator> validator;
    private final String url;
    private final String user;
    private final String password;

    public UtilizatorDbRepository(Validator<Utilizator> val, String url, String user, String password) {
        this.validator = val;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    @Override
    public Utilizator findOne(Long aLong) {
        throw new UnsupportedOperationException("findOne() not implemented yet");
    }

    @Override
    public Iterable<Utilizator> findAll() {
        throw new UnsupportedOperationException("findAll() not implemented yet");
    }

    @Override
    public Utilizator save(Utilizator entity) {
        throw new UnsupportedOperationException("save() not implemented yet");
    }

    @Override
    public Utilizator delete(Long aLong) {
        throw new UnsupportedOperationException("delete() not implemented yet");
    }

    @Override
    public Utilizator update(Utilizator entity) {
        throw new UnsupportedOperationException("update() not implemented yet");
    }
}
