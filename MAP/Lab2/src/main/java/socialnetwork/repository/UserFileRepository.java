package socialnetwork.repository;

import socialnetwork.domain.User;
import socialnetwork.exceptions.RepositoryException;
import socialnetwork.validation.Validator;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;

/** Pastreaza utilizatorii intr-un fisier text. */
public class UserFileRepository implements FileRepository<Long, User> {
    private final Path file;
    private final Validator<User> validator;
    private final List<User> users = new ArrayList<>();

    public UserFileRepository(Path file, Validator<User> validator) {
        this.file = file;
        this.validator = validator;
        load();
    }

    public void add(User user) {
        validator.validate(user);
        if (find(user.getId()) != null) throw new RepositoryException("Utilizator existent.");
        users.add(user);
        save();
    }

    public void remove(Long id) {
        User user = find(id);
        if (user == null) throw new RepositoryException("Utilizator inexistent.");
        users.remove(user);
        save();
    }

    public boolean exists(Long id) { return find(id) != null; }

    public User find(Long id) {
        for (User user : users) {
            if (user.getId().equals(id)) return user;
        }
        return null;
    }

    public List<User> getAll() { return new ArrayList<>(users); }

    private void load() {
        try {
            if (!Files.exists(file)) return;
            for (String line : Files.readAllLines(file)) {
                if (!line.isBlank()) {
                    String[] data = line.split(";");
                    users.add(new User(Long.parseLong(data[0]), data[1], data[2]));
                }
            }
        } catch (IOException | RuntimeException exception) {
            throw new RepositoryException("Nu se pot citi utilizatorii.");
        }
    }

    private void save() {
        try {
            Files.createDirectories(file.getParent());
            List<String> lines = new ArrayList<>();
            for (User user : users) lines.add(user.toString());
            Files.write(file, lines);
        } catch (IOException exception) {
            throw new RepositoryException("Nu se pot salva utilizatorii.");
        }
    }
}
