package socialnetwork.repository;

import socialnetwork.domain.Friendship;
import socialnetwork.validation.Validator;

import java.util.List;

/** Database repository placeholder for Lab 4. */
public class PrietenieDbRepository implements Repository<String, Friendship> {
    private final Validator<Friendship> validator;
    private final String url;
    private final String user;
    private final String password;

    /** Saves connection settings for Lab 4.
     * @param validator friendship validator
     * @param url database URL
     * @param user database user
     * @param password database password
     */
    public PrietenieDbRepository(Validator<Friendship> validator, String url, String user, String password) {
        this.validator = validator;
        this.url = url;
        this.user = user;
        this.password = password;
    }

    /** {@inheritDoc}
     * @throws UnsupportedOperationException until Lab 4
     */
    @Override
    public Friendship save(Friendship entity) {
        throw new UnsupportedOperationException("lab 4");
    }

    /** {@inheritDoc}
     * @throws UnsupportedOperationException until Lab 4
     */
    @Override
    public Friendship delete(String id) {
        throw new UnsupportedOperationException("lab 4");
    }

    /** {@inheritDoc}
     * @throws UnsupportedOperationException until Lab 4
     */
    @Override
    public Friendship update(Friendship entity) {
        throw new UnsupportedOperationException("lab 4");
    }

    /** {@inheritDoc}
     * @throws UnsupportedOperationException until Lab 4
     */
    @Override
    public Friendship findOne(String id) {
        throw new UnsupportedOperationException("lab 4");
    }

    /** {@inheritDoc}
     * @throws UnsupportedOperationException until Lab 4
     */
    @Override
    public List<Friendship> findAll() {
        throw new UnsupportedOperationException("lab 4");
    }
}
