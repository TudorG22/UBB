package socialnetwork.repository;

import socialnetwork.domain.User;
import socialnetwork.validation.Validator;

import java.util.List;

/** Database repository placeholder for Lab 4. */
public class UtilizatorDbRepository implements Repository<Long, User> {
    private final Validator<User> validator;
    private final String url;
    private final String user;
    private final String password;

    /** Saves connection settings for Lab 4.
     * @param validator user validator
     * @param url database URL
     * @param user database user
     * @param password database password
     */
    public UtilizatorDbRepository(Validator<User> validator, String url, String user, String password) {
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    /** {@inheritDoc}
     * @throws UnsupportedOperationException until Lab 4
     */
    @Override
    public User save(User entity) {
        throw new UnsupportedOperationException("lab 4");
    }

    /** {@inheritDoc}
     * @throws UnsupportedOperationException until Lab 4
     */
    @Override
    public User delete(Long id) {
        throw new UnsupportedOperationException("lab 4");
    }

    /** {@inheritDoc}
     * @throws UnsupportedOperationException until Lab 4
     */
    @Override
    public User update(User entity) {
        throw new UnsupportedOperationException("lab 4");
    }

    /** {@inheritDoc}
     * @throws UnsupportedOperationException until Lab 4
     */
    @Override
    public User findOne(Long id) {
        throw new UnsupportedOperationException("lab 4");
    }

    /** {@inheritDoc}
     * @throws UnsupportedOperationException until Lab 4
     */
    @Override
    public List<User> findAll() {
        throw new UnsupportedOperationException("lab 4");
    }
}
