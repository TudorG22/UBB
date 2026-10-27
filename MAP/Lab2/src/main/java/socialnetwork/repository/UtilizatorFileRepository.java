package socialnetwork.repository;

import socialnetwork.domain.User;
import socialnetwork.exceptions.RepositoryException;
import socialnetwork.validation.Validator;

import java.nio.file.Path;

public class UtilizatorFileRepository extends AbstractFileRepository<Long, User> {
    public UtilizatorFileRepository(Path file, Validator<User> validator) {
        super(file, validator);
    }

    @Override
    protected User extractEntity(String line) {
        String[] data = line.split(";", -1);
        if (data.length != 3) {
            throw new RepositoryException("Linie utilizator invalida.");
        }
        return new User(Long.parseLong(data[0]), data[1], data[2]);
    }

    @Override
    protected String createEntityAsString(User user) {
        return user.getId() + ";" + user.getFirstName() + ";" + user.getLastName();
    }
}
