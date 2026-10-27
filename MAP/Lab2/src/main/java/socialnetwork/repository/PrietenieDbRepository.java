package socialnetwork.repository;

import socialnetwork.domain.Friendship;
import socialnetwork.validation.Validator;

import java.util.List;

public class PrietenieDbRepository implements Repository<String, Friendship> {
    private final Validator<Friendship> validator;
    private final String url;
    private final String user;
    private final String password;

    public PrietenieDbRepository(Validator<Friendship> validator, String url, String user, String password) {
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    @Override
    public Friendship save(Friendship entity) {
        throw new UnsupportedOperationException("lab 4");
    }

    @Override
    public Friendship delete(String id) {
        throw new UnsupportedOperationException("lab 4");
    }

    @Override
    public Friendship update(Friendship entity) {
        throw new UnsupportedOperationException("lab 4");
    }

    @Override
    public Friendship findOne(String id) {
        throw new UnsupportedOperationException("lab 4");
    }

    @Override
    public List<Friendship> findAll() {
        throw new UnsupportedOperationException("lab 4");
    }
}
