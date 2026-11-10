package socialnetwork.ui;

import socialnetwork.exceptions.RepositoryException;
import socialnetwork.exceptions.ValidationException;
import socialnetwork.service.FriendshipService;
import socialnetwork.service.UserService;

import java.util.Scanner;
import java.util.stream.Collectors;

public class Console {
    private final UserService userService;
    private final FriendshipService friendshipService;
    private final Scanner scanner = new Scanner(System.in);

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
                    case "8":
                        searchUsers();
                        break;
                    case "9":
                        friendshipService.getFriends(readId("Id: ")).forEach(System.out::println);
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
        System.out.println("1. Adauga utilizator\n2. Sterge utilizator\n3. Adauga prietenie\n4. Sterge prietenie\n5. Afiseaza tot\n6. Numar comunitati\n7. Cea mai sociabila comunitate\n8. Cauta utilizatori\n9. Prietenii unui utilizator\n0. Iesire");
    }

    private void showAll() {
        System.out.println("Utilizatori:");
        userService.getUsers().forEach(System.out::println);
        System.out.println("Prieteni:");
        friendshipService.getFriendships().forEach(System.out::println);
        System.out.println("Comunitati:");
        System.out.println(friendshipService.getCommunities().stream()
                .map(Object::toString).collect(Collectors.joining("\n")));
    }

    private void showMostSociableCommunity() {
        friendshipService.mostSociableCommunity().forEach(System.out::println);
    }

    private void searchUsers() {
        System.out.print("Prefix prenume sau nume: ");
        String text = scanner.nextLine();
        System.out.print("Doar fara prieteni? (da/nu): ");
        boolean onlyWithoutFriends = scanner.nextLine().equalsIgnoreCase("da");
        userService.searchUsers(text, onlyWithoutFriends).forEach(System.out::println);
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
