package socialnetwork.service;

import socialnetwork.domain.User;
import socialnetwork.domain.Friendship;
import socialnetwork.exceptions.RepositoryException;
import socialnetwork.repository.Repository;

import java.util.List;

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
        if (userRepository.findOne(id) == null) {
            throw new RepositoryException("Utilizator inexistent.");
        }
        for (Friendship friendship : friendshipRepository.findAll()) {
            if (friendship.getFirstUserId().equals(id) || friendship.getSecondUserId().equals(id)) {
                friendshipRepository.delete(friendship.getId());
            }
        }
        userRepository.delete(id);
    }

    /** Checks whether a user exists.
     * @param id user ID
     * @return true if present
     */
    public boolean exists(Long id) {
        return userRepository.findOne(id) != null;
    }

    /** Finds a user.
     * @param id user ID
     * @return user, or null if absent
     */
    public User findUser(Long id) {
        return userRepository.findOne(id);
    }

    /** Lists users.
     * @return all users
     */
    public List<User> getUsers() {
        return userRepository.findAll();
    }
}
