package socialnetwork.service;

import socialnetwork.domain.Friendship;
import socialnetwork.domain.User;
import socialnetwork.exceptions.RepositoryException;
import socialnetwork.repository.FriendshipFileRepository;
import socialnetwork.repository.UserFileRepository;

import java.util.ArrayList;
import java.util.List;

/** Contine operatiile specifice retelei de socializare. */
public class NetworkService {
    private final UserFileRepository userRepository;
    private final FriendshipFileRepository friendshipRepository;

    public NetworkService(UserFileRepository userRepository, FriendshipFileRepository friendshipRepository) {
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
    }

    public void addUser(Long id, String firstName, String lastName) {
        userRepository.add(new User(id, firstName, lastName));
    }

    public void removeUser(Long id) {
        userRepository.remove(id);
        friendshipRepository.removeForUser(id);
    }

    public void addFriendship(Long firstId, Long secondId) {
        if (!userRepository.exists(firstId) || !userRepository.exists(secondId)) {
            throw new RepositoryException("Utilizator inexistent.");
        }
        if (firstId.equals(secondId)) {
            throw new RepositoryException("Un utilizator nu poate fi propriul prieten.");
        }
        friendshipRepository.add(new Friendship(firstId, secondId));
    }

    public void removeFriendship(Long firstId, Long secondId) {
        friendshipRepository.remove(new Friendship(firstId, secondId));
    }

    public List<User> getUsers() { return userRepository.getAll(); }

    public List<Friendship> getFriendships() { return friendshipRepository.getAll(); }

    public List<List<Long>> getCommunities() { return communities(); }

    public int numberOfCommunities() { return communities().size(); }

    public List<User> mostSociableCommunity() {
        List<List<Long>> allCommunities = communities();
        List<Long> mostSociable = new ArrayList<>();
        int longestRoad = -1;

        for (List<Long> community : allCommunities) {
            int road = longestRoad(community);
            if (road > longestRoad) {
                longestRoad = road;
                mostSociable = community;
            }
        }

        List<User> result = new ArrayList<>();
        for (Long id : mostSociable) result.add(userRepository.find(id));
        return result;
    }

    private List<List<Long>> communities() {
        List<List<Long>> result = new ArrayList<>();
        List<Long> visited = new ArrayList<>();

        for (User user : userRepository.getAll()) {
            if (!visited.contains(user.getId())) {
                List<Long> community = new ArrayList<>();
                visit(user.getId(), visited, community);
                result.add(community);
            }
        }
        return result;
    }

    private void visit(Long id, List<Long> visited, List<Long> community) {
        visited.add(id);
        community.add(id);
        for (Long friendId : friendsOf(id)) {
            if (!visited.contains(friendId)) visit(friendId, visited, community);
        }
    }

    private int longestRoad(List<Long> community) {
        int maximum = 0;
        for (Long firstId : community) {
            for (Long secondId : community) {
                int distance = distance(firstId, secondId);
                if (distance > maximum) maximum = distance;
            }
        }
        return maximum;
    }

    private int distance(Long start, Long finish) {
        List<Long> queue = new ArrayList<>();
        List<Integer> distances = new ArrayList<>();
        List<Long> visited = new ArrayList<>();
        int position = 0;

        queue.add(start);
        distances.add(0);
        visited.add(start);

        while (position < queue.size()) {
            Long current = queue.get(position);
            int currentDistance = distances.get(position);
            if (current.equals(finish)) return currentDistance;

            for (Long friendId : friendsOf(current)) {
                if (!visited.contains(friendId)) {
                    visited.add(friendId);
                    queue.add(friendId);
                    distances.add(currentDistance + 1);
                }
            }
            position++;
        }
        return -1;
    }

    private List<Long> friendsOf(Long id) {
        List<Long> result = new ArrayList<>();
        for (Friendship friendship : friendshipRepository.getAll()) {
            if (friendship.getFirstUserId().equals(id)) result.add(friendship.getSecondUserId());
            if (friendship.getSecondUserId().equals(id)) result.add(friendship.getFirstUserId());
        }
        return result;
    }
}