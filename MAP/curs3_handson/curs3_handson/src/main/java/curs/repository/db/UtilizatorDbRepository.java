package curs.repository.db;

import curs.domain.Utilizator;
import curs.domain.validators.Validator;
import curs.repository.Repository;
import jdk.jshell.execution.Util;

public class UtilizatorDbRepository implements Repository<Long, Utilizator> {
    private final Validator<Utilizator> validator;
    private final String url;
    private final String user;
    private final String password;

    public UtilizatorDbRepository(Validator<Utilizator> validator, String url, String user, String password) {
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    @Override
    public Utilizator findOne(Long aLong) {
        throw new UnsupportedOperationException("findOne() nu e implementat inca!");
    }

    @Override
    public Iterable<Utilizator> findAll() {
        throw new UnsupportedOperationException("findAll() nu e implementat inca!");
    }

    @Override
    public Utilizator save(Utilizator entity) {
        throw new UnsupportedOperationException("save() nu e implementat inca!");
    }

    @Override
    public Utilizator delete(Long aLong) {
        throw new UnsupportedOperationException("delete() nu e implementat inca!");
    }

    @Override
    public Utilizator update(Utilizator entity) {
        throw new UnsupportedOperationException("update() nu e implementat inca!");
    }
}
