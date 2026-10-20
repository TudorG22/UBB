package socialnetwork.service;

import socialnetwork.domain.Friendship;
import socialnetwork.domain.User;
import socialnetwork.exceptions.RepositoryException;
import socialnetwork.repository.FriendshipFileRepository;
import socialnetwork.repository.UserFileRepository;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;

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
        verifyUsers(firstId, secondId);
        if (firstId.equals(secondId)) throw new RepositoryException("Un utilizator nu poate fi propriul prieten.");
        friendshipRepository.add(new Friendship(firstId, secondId));
    }

    public void removeFriendship(Long firstId, Long secondId) {
        friendshipRepository.remove(new Friendship(firstId, secondId));
    }

    public int numberOfCommunities() { return communities().size(); }

    public Collection<User> mostSociableCommunity() {
        List<Set<Long>> communities = communities();
        Set<Long> best = new HashSet<>();
        int longestPath = -1;
        for (Set<Long> community : communities) {
            int diameter = diameter(community);
            if (diameter > longestPath) {
                longestPath = diameter;
                best = community;
            }
        }
        List<User> result = new ArrayList<>();
        for (User user : userRepository.getAll()) if (best.contains(user.getId())) result.add(user);
        return result;
    }

    private void verifyUsers(Long firstId, Long secondId) {
        if (!userRepository.exists(firstId) || !userRepository.exists(secondId)) {
            throw new RepositoryException("Utilizator inexistent.");
        }
    }

    private List<Set<Long>> communities() {
        Map<Long, Set<Long>> graph = graph();
        Set<Long> visited = new HashSet<>();
        List<Set<Long>> result = new ArrayList<>();
        for (Long id : graph.keySet()) {
            if (!visited.contains(id)) {
                Set<Long> component = new HashSet<>();
                Queue<Long> queue = new ArrayDeque<>();
                queue.add(id);
                visited.add(id);
                while (!queue.isEmpty()) {
                    Long current = queue.remove();
                    component.add(current);
                    for (Long neighbour : graph.get(current)) if (visited.add(neighbour)) queue.add(neighbour);
                }
                result.add(component);
            }
        }
        return result;
    }

    private int diameter(Set<Long> community) {
        int maximum = 0;
        Map<Long, Set<Long>> graph = graph();
        for (Long start : community) {
            Map<Long, Integer> distances = new HashMap<>();
            Queue<Long> queue = new ArrayDeque<>();
            queue.add(start);
            distances.put(start, 0);
            while (!queue.isEmpty()) {
                Long current = queue.remove();
                for (Long neighbour : graph.get(current)) {
                    if (!distances.containsKey(neighbour)) {
                        distances.put(neighbour, distances.get(current) + 1);
                        queue.add(neighbour);
                    }
                }
            }
            for (Integer distance : distances.values()) maximum = Math.max(maximum, distance);
        }
        return maximum;
    }

    private Map<Long, Set<Long>> graph() {
        Map<Long, Set<Long>> graph = new HashMap<>();
        for (User user : userRepository.getAll()) graph.put(user.getId(), new HashSet<>());
        for (Friendship friendship : friendshipRepository.getAll()) {
            graph.get(friendship.getFirstUserId()).add(friendship.getSecondUserId());
            graph.get(friendship.getSecondUserId()).add(friendship.getFirstUserId());
        }
        return graph;
    }
}
