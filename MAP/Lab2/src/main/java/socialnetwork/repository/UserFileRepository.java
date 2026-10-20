package socialnetwork.repository;

import socialnetwork.domain.User;
import socialnetwork.exceptions.RepositoryException;
import socialnetwork.validation.Validator;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

/** Pastreaza utilizatorii intr-un fisier text. */
public class UserFileRepository {
    private final Path file;
    private final Validator<User> validator;
    private final Map<Long, User> users = new HashMap<>();

    public UserFileRepository(Path file, Validator<User> validator) {
        this.file = file;
        this.validator = validator;
        load();
    }

    public void add(User user) {
        validator.validate(user);
        if (users.putIfAbsent(user.getId(), user) != null) throw new RepositoryException("Utilizator existent.");
        save();
    }

    public void remove(Long id) {
        if (users.remove(id) == null) throw new RepositoryException("Utilizator inexistent.");
        save();
    }

    public boolean exists(Long id) { return users.containsKey(id); }
    public Collection<User> getAll() { return users.values(); }

    private void load() {
        try {
            if (!Files.exists(file)) return;
            for (String line : Files.readAllLines(file)) {
                if (!line.isBlank()) {
                    String[] data = line.split(";", -1);
                    users.put(Long.parseLong(data[0]), new User(Long.parseLong(data[0]), data[1], data[2]));
                }
            }
        } catch (IOException | RuntimeException exception) { throw new RepositoryException("Nu se pot citi utilizatorii."); }
    }

    private void save() {
        try {
            Files.createDirectories(file.getParent());
            Files.write(file, users.values().stream().map(User::toString).toList());
        } catch (IOException exception) { throw new RepositoryException("Nu se pot salva utilizatorii."); }
    }
}
