package socialnetwork;

import socialnetwork.domain.Friendship;
import socialnetwork.domain.User;
import socialnetwork.exceptions.RepositoryException;
import socialnetwork.repository.Repository;
import socialnetwork.repository.RepositoryFactory;
import socialnetwork.service.FriendshipService;
import socialnetwork.service.UserService;
import socialnetwork.ui.Console;
import socialnetwork.validation.FriendshipValidator;
import socialnetwork.validation.UserValidator;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

/** Starts the application. */
public class Main {
    /** Starts the console application.
     * @param args unused command line arguments
     */
    public static void main(String[] args) {
        try {
            RepositoryFactory factory = new RepositoryFactory(loadConfiguration("/config.properties"));
            Repository<Long, User> users = factory.createUtilizatorRepository(new UserValidator());
            Repository<String, Friendship> friendships = factory.createPrietenieRepository(new FriendshipValidator(users));
            UserService userService = new UserService(users, friendships);
            FriendshipService friendshipService = new FriendshipService(friendships, userService);
            new Console(userService, friendshipService).run();
        } catch (RepositoryException | IllegalArgumentException exception) {
            System.out.println(exception.getMessage());
        }
    }

    private static Properties loadConfiguration(String resource) {
        Properties properties = new Properties();
        try (InputStream input = Main.class.getResourceAsStream(resource)) {
            if (input == null) {
                throw new IllegalArgumentException("Lipseste resursa " + resource + ".");
            }
            properties.load(input);
        } catch (IOException exception) {
            throw new RepositoryException("Nu se poate citi resursa " + resource + ".", exception);
        }
        return properties;
    }
}
