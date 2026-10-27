package socialnetwork.repository;

import socialnetwork.domain.Friendship;
import socialnetwork.exceptions.RepositoryException;
import socialnetwork.validation.Validator;

import java.nio.file.Path;
import java.time.LocalDateTime;

public class PrietenieFileRepository extends AbstractFileRepository<String, Friendship> {
    public PrietenieFileRepository(Path file, Validator<Friendship> validator) {
        super(file, validator);
    }

    @Override
    protected Friendship extractEntity(String line) {
        String[] data = line.split(";", -1);
        if (data.length != 3) {
            throw new RepositoryException("Linie prietenie invalida.");
        }
        return new Friendship(Long.parseLong(data[0]), Long.parseLong(data[1]), LocalDateTime.parse(data[2]));
    }

    @Override
    protected String createEntityAsString(Friendship friendship) {
        return friendship.getFirstUserId() + ";" + friendship.getSecondUserId()
                + ";" + friendship.getFriendshipDate();
    }
}
