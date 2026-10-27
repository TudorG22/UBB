package socialnetwork.ui;

import socialnetwork.domain.Friendship;
import socialnetwork.domain.User;
import socialnetwork.exceptions.RepositoryException;
import socialnetwork.exceptions.ValidationException;
import socialnetwork.service.FriendshipService;
import socialnetwork.service.UserService;

import java.util.List;
import java.util.Scanner;

/** Text console for the application. */
public class Console {
    private final UserService userService;
    private final FriendshipService friendshipService;
    private final Scanner scanner = new Scanner(System.in);

    /** Creates the console.
     * @param userService user operations
     * @param friendshipService friendship operations
     */
    public Console(UserService userService, FriendshipService friendshipService) {
        this.userService = userService;
        this.friendshipService = friendshipService;
    }

    /** Reads commands until exit. */
    public void run() {
        while (true) {
            printMenu();
            try {
                String option = scanner.nextLine();
                switch (option) {
                    case "1":
                        addUser();
                        break;
                    case "2":
                        removeUser();
                        break;
                    case "3":
                        addFriendship();
                        break;
                    case "4":
                        removeFriendship();
                        break;
                    case "5":
                        showAll();
                        break;
                    case "6":
                        System.out.println("Numar comunitati: " + friendshipService.numberOfCommunities());
                        break;
                    case "7":
                        showMostSociableCommunity();
                        break;
                    case "0":
                        return;
                    default:
                        System.out.println("Optiune invalida.");
                }
            } catch (ValidationException | RepositoryException | IllegalArgumentException
                     | UnsupportedOperationException exception) {
                System.out.println(exception.getMessage());
            }
        }
    }

    private void printMenu() {
        System.out.println("1. Adauga utilizator\n2. Sterge utilizator\n3. Adauga prietenie\n4. Sterge prietenie\n5. Afiseaza tot\n6. Numar comunitati\n7. Cea mai sociabila comunitate\n0. Iesire");
    }

    private void showAll() {
        System.out.println("Utilizatori:");
        for (User user : userService.getUsers()) System.out.println(user);
        System.out.println("Prieteni:");
        for (Friendship friendship : friendshipService.getFriendships()) System.out.println(friendship);
        System.out.println("Comunitati:");
        for (List<Long> community : friendshipService.getCommunities()) System.out.println(community);
    }

    private void showMostSociableCommunity() {
        for (User user : friendshipService.mostSociableCommunity()) System.out.println(user);
    }

    private void addUser() {
        System.out.print("Id: ");
        Long id = Long.parseLong(scanner.nextLine());
        System.out.print("Prenume: ");
        String firstName = scanner.nextLine();
        System.out.print("Nume: ");
        String lastName = scanner.nextLine();
        userService.addUser(id, firstName, lastName);
    }

    private void removeUser() { userService.removeUser(readId("Id: ")); }

    private void addFriendship() {
        friendshipService.addFriendship(readId("Primul id: "), readId("Al doilea id: "));
    }

    private void removeFriendship() {
        friendshipService.removeFriendship(readId("Primul id: "), readId("Al doilea id: "));
    }

    private Long readId(String message) {
        System.out.print(message);
        return Long.parseLong(scanner.nextLine());
    }
}
