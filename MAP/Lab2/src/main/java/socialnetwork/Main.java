package socialnetwork;

import socialnetwork.repository.FriendshipFileRepository;
import socialnetwork.repository.UserFileRepository;
import socialnetwork.service.NetworkService;
import socialnetwork.ui.Console;
import socialnetwork.validation.UserValidator;

import java.nio.file.Path;

/** Porneste aplicatia. */
public class Main {
    public static void main(String[] args) {
        UserFileRepository users = new UserFileRepository(Path.of("data", "users.txt"), new UserValidator());
        FriendshipFileRepository friendships = new FriendshipFileRepository(Path.of("data", "friendships.txt"));
        new Console(new NetworkService(users, friendships)).run();
    }
}
