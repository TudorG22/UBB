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
import socialnetwork.validation.Validator;
import socialnetwork.exceptions.ValidationException;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class Main {
    /** Starts the console application.
     * @param args unused command line arguments
     */
    public static void main(String[] args) {
        try {
            RepositoryFactory factory = new RepositoryFactory(loadConfiguration("/config.properties"));
            Validator<User> userValidator = new UserValidator().andThen(user -> {
                if (user.getFirstName().length() > 50 || user.getLastName().length() > 50) {
                    throw new ValidationException("Numele poate avea cel mult 50 de caractere.");
                }
            });
            Repository<Long, User> users = factory.createUtilizatorRepository(userValidator);
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
