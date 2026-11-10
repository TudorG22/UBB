package socialnetwork.service;

import socialnetwork.domain.User;
import socialnetwork.domain.Friendship;
import socialnetwork.exceptions.RepositoryException;
import socialnetwork.repository.Repository;

import java.util.List;
import java.util.Optional;
import java.util.Set;
import java.util.Map;
import java.util.Comparator;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class UserService {
    private final Repository<Long, User> userRepository;
    private final Repository<String, Friendship> friendshipRepository;

    public UserService(Repository<Long, User> userRepository, Repository<String, Friendship> friendshipRepository) {
        this.userRepository = userRepository;
        this.friendshipRepository = friendshipRepository;
    }

    /** Adds a user.
     * @param id user ID
     * @param firstName first name
     * @param lastName last name
     * @throws socialnetwork.exceptions.ValidationException if data is invalid
     * @throws RepositoryException if the user exists or storage fails
     */
    public void addUser(Long id, String firstName, String lastName) {
        if (userRepository.save(new User(id, firstName, lastName)) != null) {
            throw new RepositoryException("Utilizator existent.");
        }
    }

    /** Removes a user and their friendships.
     * @param id user ID
     * @throws RepositoryException if the user is absent or storage fails
     */
    public void removeUser(Long id) {
        findUser(id).orElseThrow(() -> new RepositoryException("Utilizator inexistent."));
        List<String> friendshipIds = friendshipRepository.findAll(friendship ->
                        friendship.getFirstUserId().equals(id) || friendship.getSecondUserId().equals(id))
                .stream().map(Friendship::getId).collect(Collectors.toList());
        friendshipIds.forEach(friendshipRepository::delete);
        userRepository.delete(id);
    }

    /** Checks whether a user exists.
     * @param id user ID
     * @return true if present
     */
    public boolean exists(Long id) {
        return findUser(id).isPresent();
    }

    /** Finds a user.
     * @param id user ID
     * @return optional user
     */
    public Optional<User> findUser(Long id) {
        return Optional.ofNullable(userRepository.findOne(id));
    }

    /** Lists users.
     * @return all users
     */
    public List<User> getUsers() {
        return userRepository.findAll();
    }

    /** Searches by name prefix, optionally keeping only users without friends. */
    public List<User> searchUsers(String text, boolean onlyWithoutFriends) {
        Predicate<User> byName = CriteriiUtilizator.prenumeIncepeCu(text)
                .or(CriteriiUtilizator.numeIncepeCu(text));
        Map<Long, Long> friendCounts = friendshipRepository.findAll().stream()
                .flatMap(friendship -> Stream.of(friendship.getFirstUserId(), friendship.getSecondUserId()))
                .collect(Collectors.groupingBy(Function.identity(), Collectors.counting()));
        Set<Long> idsWithFriends = friendCounts.keySet();
        Function<Set<Long>, Predicate<User>> withoutFriends = CriteriiUtilizator::faraPrieteni;
        Predicate<User> withFriends = withoutFriends.apply(idsWithFriends).negate();
        Predicate<User> filter = byName.and(onlyWithoutFriends ? Predicate.not(withFriends) : user -> true);
        return userRepository.findAll(filter).stream()
                .sorted(Comparator.comparing(User::getLastName).thenComparing(User::getFirstName))
                .collect(Collectors.toList());
    }
}
