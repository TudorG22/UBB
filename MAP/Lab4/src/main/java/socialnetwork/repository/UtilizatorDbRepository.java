package socialnetwork.repository;

import socialnetwork.domain.User;
import socialnetwork.validation.Validator;

import java.util.List;

public class UtilizatorDbRepository implements Repository<Long, User> {
    private final Validator<User> validator;
    private final String url;
    private final String user;
    private final String password;

    public UtilizatorDbRepository(Validator<User> validator, String url, String user, String password) {
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    @Override
    public User save(User entity) {
        throw new UnsupportedOperationException("lab 4");
    }

    @Override
    public User delete(Long id) {
        throw new UnsupportedOperationException("lab 4");
    }

    @Override
    public User update(User entity) {
        throw new UnsupportedOperationException("lab 4");
    }

    @Override
    public User findOne(Long id) {
        throw new UnsupportedOperationException("lab 4");
    }

    @Override
    public List<User> findAll() {
        throw new UnsupportedOperationException("lab 4");
    }
}
