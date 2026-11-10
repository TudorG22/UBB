package socialnetwork.service;

import socialnetwork.domain.Friendship;
import socialnetwork.domain.User;
import socialnetwork.exceptions.RepositoryException;
import socialnetwork.repository.Repository;

import java.time.LocalDateTime;
import java.util.Comparator;
import java.util.function.Function;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class FriendshipService {
    private final Repository<String, Friendship> friendshipRepository;
    private final UserService userService;

    public FriendshipService(Repository<String, Friendship> friendshipRepository, UserService userService) {
        this.friendshipRepository = friendshipRepository;
        this.userService = userService;
    }

    /** Adds a friendship.
     * @param firstId first user ID
     * @param secondId second user ID
     * @throws socialnetwork.exceptions.ValidationException if users or data are invalid
     * @throws RepositoryException if it exists or storage fails
     */
    public void addFriendship(Long firstId, Long secondId) {
        if (friendshipRepository.save(new Friendship(firstId, secondId, LocalDateTime.now())) != null) {
            throw new RepositoryException("Prietenie existenta.");
        }
    }

    /** Removes a friendship.
     * @param firstId first user ID
     * @param secondId second user ID
     * @throws RepositoryException if absent or storage fails
     */
    public void removeFriendship(Long firstId, Long secondId) {
        if (friendshipRepository.delete(Friendship.createId(firstId, secondId)) == null) {
            throw new RepositoryException("Prietenie inexistenta.");
        }
    }

    /** Lists friendships.
     * @return all friendships
     */
    public List<Friendship> getFriendships() {
        return friendshipRepository.findAll();
    }

    /** Lists the friends of a user. */
    public List<User> getFriends(Long id) {
        return friendsOf(id).stream()
                .map(userService::findUser)
                .flatMap(java.util.Optional::stream)
                .collect(Collectors.toList());
    }

    /** Lists connected communities.
     * @return communities of user IDs
     */
    public List<List<Long>> getCommunities() {
        return communities(allUserIds(), graph());
    }

    /** Counts connected communities.
     * @return number of communities
     */
    public int numberOfCommunities() {
        return (int) getCommunities().stream().count();
    }

    /** Finds the community with the longest shortest path.
     * @return users in that community
     */
    public List<User> mostSociableCommunity() {
        Map<Long, Set<Long>> graph = graph();
        List<Long> selected = communities(allUserIds(), graph).stream()
                .min(Comparator.comparingInt((List<Long> community) -> longestRoad(community, graph))
                        .thenComparingInt(List::size).reversed())
                .orElseGet(java.util.ArrayList::new);
        Map<Long, User> usersById = userService.getUsers().stream()
                .collect(Collectors.toMap(User::getId, Function.identity()));
        return selected.stream().map(usersById::get)
                .collect(Collectors.toList());
    }

    private Set<Long> allUserIds() {
        return userService.getUsers().stream().map(User::getId).collect(Collectors.toSet());
    }

    private Map<Long, Set<Long>> graph() {
        return friendshipRepository.findAll().stream()
                .flatMap(friendship -> Stream.of(
                        Map.entry(friendship.getFirstUserId(), friendship.getSecondUserId()),
                        Map.entry(friendship.getSecondUserId(), friendship.getFirstUserId())))
                .collect(Collectors.groupingBy(Map.Entry::getKey,
                        Collectors.mapping(Map.Entry::getValue, Collectors.toSet())));
    }

    private List<List<Long>> communities(Set<Long> remaining, Map<Long, Set<Long>> graph) {
        if (remaining.isEmpty()) {
            return List.of();
        }
        Long start = remaining.stream().min(Comparator.naturalOrder()).orElseThrow();
        List<Long> community = connected(Set.of(start), Set.of(start), graph).stream()
                .sorted().collect(Collectors.toList());
        Set<Long> rest = remaining.stream().filter(Predicate.not(community::contains))
                .collect(Collectors.toSet());
        return Stream.concat(Stream.of(community), communities(rest, graph).stream())
                .collect(Collectors.toList());
    }

    private Set<Long> connected(Set<Long> frontier, Set<Long> visited, Map<Long, Set<Long>> graph) {
        if (frontier.isEmpty()) {
            return visited;
        }
        Set<Long> next = frontier.stream().flatMap(id -> graph.getOrDefault(id, Set.of()).stream())
                .filter(Predicate.not(visited::contains)).collect(Collectors.toSet());
        Set<Long> allVisited = Stream.concat(visited.stream(), next.stream()).collect(Collectors.toSet());
        return connected(next, allVisited, graph);
    }

    private int longestRoad(List<Long> community, Map<Long, Set<Long>> graph) {
        return community.stream()
                .flatMap(first -> community.stream().map(second -> distance(first, second, graph)))
                .reduce(Integer::max).orElse(0);
    }

    private int distance(Long start, Long finish, Map<Long, Set<Long>> graph) {
        return distance(Set.of(start), Set.of(start), finish, graph, 0);
    }

    private int distance(Set<Long> frontier, Set<Long> visited, Long finish,
                         Map<Long, Set<Long>> graph, int length) {
        if (frontier.stream().anyMatch(finish::equals)) {
            return length;
        }
        if (frontier.isEmpty()) {
            return -1;
        }
        Set<Long> next = frontier.stream().flatMap(id -> graph.getOrDefault(id, Set.of()).stream())
                .filter(Predicate.not(visited::contains)).collect(Collectors.toSet());
        Set<Long> allVisited = Stream.concat(visited.stream(), next.stream()).collect(Collectors.toSet());
        return distance(next, allVisited, finish, graph, length + 1);
    }

    private List<Long> friendsOf(Long id) {
        return friendshipRepository.findAll().stream()
                .filter(friendship -> friendship.getFirstUserId().equals(id)
                        || friendship.getSecondUserId().equals(id))
                .map(friendship -> friendship.getFirstUserId().equals(id)
                        ? friendship.getSecondUserId() : friendship.getFirstUserId())
                .distinct().collect(Collectors.toList());
    }
}
