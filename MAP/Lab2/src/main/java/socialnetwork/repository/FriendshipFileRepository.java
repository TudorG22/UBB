package socialnetwork.repository;

import socialnetwork.domain.Friendship;
import socialnetwork.exceptions.RepositoryException;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;

/** Pastreaza prieteniile intr-un fisier text. */
public class FriendshipFileRepository { // facut interfete
    private final Path file;
    private final List<Friendship> friendships = new ArrayList<>();

    public FriendshipFileRepository(Path file) {
        this.file = file;
        load();
    }

    public void add(Friendship friendship) {
        if (find(friendship) != null) throw new RepositoryException("Prietenie existenta.");
        friendships.add(friendship);
        save();
    }

    public void remove(Friendship friendship) {
        Friendship existing = find(friendship);
        if (existing == null) throw new RepositoryException("Prietenie inexistenta.");
        friendships.remove(existing);
        save();
    }

    public List<Friendship> getAll() { return new ArrayList<>(friendships); }

    public void removeForUser(Long id) {
        for (int i = friendships.size() - 1; i >= 0; i--) {
            Friendship friendship = friendships.get(i);
            if (friendship.getFirstUserId().equals(id) || friendship.getSecondUserId().equals(id)) {
                friendships.remove(i);
            }
        }
        save();
    }

    private Friendship find(Friendship friendship) {
        for (Friendship current : friendships) {
            boolean sameOrder = current.getFirstUserId().equals(friendship.getFirstUserId())
                    && current.getSecondUserId().equals(friendship.getSecondUserId());
            boolean reverseOrder = current.getFirstUserId().equals(friendship.getSecondUserId())
                    && current.getSecondUserId().equals(friendship.getFirstUserId());
            if (sameOrder || reverseOrder) return current;
        }
        return null;
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
        } catch (IOException | RuntimeException exception) {
            throw new RepositoryException("Nu se pot citi prieteniile.");
        }
    }

    private void save() {
        try {
            Files.createDirectories(file.getParent());
            List<String> lines = new ArrayList<>();
            for (Friendship friendship : friendships) lines.add(friendship.toString());
            Files.write(file, lines);
        } catch (IOException exception) {
            throw new RepositoryException("Nu se pot salva prieteniile.");
        }
    }
}