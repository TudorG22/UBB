package socialnetwork.repository;

import socialnetwork.domain.Friendship;
import socialnetwork.exceptions.RepositoryException;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.HashSet;
import java.util.Set;

/** Pastreaza prieteniile intr-un fisier text. */
public class FriendshipFileRepository {
    private final Path file;
    private final Set<Friendship> friendships = new HashSet<>();

    public FriendshipFileRepository(Path file) { this.file = file; load(); }

    public void add(Friendship friendship) {
        if (!friendships.add(friendship)) throw new RepositoryException("Prietenie existenta.");
        save();
    }

    public void remove(Friendship friendship) {
        if (!friendships.remove(friendship)) throw new RepositoryException("Prietenie inexistenta.");
        save();
    }

    public Set<Friendship> getAll() { return new HashSet<>(friendships); }

    public void removeForUser(Long id) {
        friendships.removeIf(friendship -> friendship.getFirstUserId().equals(id) || friendship.getSecondUserId().equals(id));
        save();
    }

    private void load() {
        try {
            if (!Files.exists(file)) return;
            for (String line : Files.readAllLines(file)) {
                if (!line.isBlank()) {
                    String[] data = line.split(";");
                    friendships.add(new Friendship(Long.parseLong(data[0]), Long.parseLong(data[1])));
                }
            }
        } catch (IOException | RuntimeException exception) { throw new RepositoryException("Nu se pot citi prieteniile."); }
    }

    private void save() {
        try {
            Files.createDirectories(file.getParent());
            Files.write(file, friendships.stream().map(Friendship::toString).toList());
        } catch (IOException exception) { throw new RepositoryException("Nu se pot salva prieteniile."); }
    }
}
