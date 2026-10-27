package socialnetwork.service;

import socialnetwork.domain.User;
import socialnetwork.repository.FriendshipFileRepository;
import socialnetwork.repository.UserFileRepository;

import java.util.List;

/** Contine operatiile specifice utilizatorilor. */
public class UserService {
    private final UserFileRepository userRepository;
    private final FriendshipFileRepository friendshipRepository;

    public UserService(UserFileRepository userRepository, FriendshipFileRepository friendshipRepository) {
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

    public boolean exists(Long id) {
        return userRepository.exists(id);
    }

    public User findUser(Long id) {
        return userRepository.find(id);
    }

    public List<User> getUsers() {
        return userRepository.getAll();
    }
}
