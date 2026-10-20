package socialnetwork.ui;

import socialnetwork.domain.Friendship;
import socialnetwork.domain.User;
import socialnetwork.service.NetworkService;

import java.util.List;
import java.util.Scanner;

/** Reprezinta interfata utilizator de tip consola. */
public class Console {
    private final NetworkService service;
    private final Scanner scanner = new Scanner(System.in);

    public Console(NetworkService service) {
        this.service = service;
    }

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
                        System.out.println("Numar comunitati: " + service.numberOfCommunities());
                        break;
                    case "7":
                        showMostSociableCommunity();
                        break;
                    case "0":
                        return;
                    default:
                        System.out.println("Optiune invalida.");
                }
            } catch (RuntimeException exception) {
                System.out.println(exception.getMessage());
            }
        }
    }

    private void printMenu() {
        System.out.println("1. Adauga utilizator\n2. Sterge utilizator\n3. Adauga prietenie\n4. Sterge prietenie\n5. Afiseaza tot\n6. Numar comunitati\n7. Cea mai sociabila comunitate\n0. Iesire");
    }

    private void showAll() {
        System.out.println("Utilizatori:");
        for (User user : service.getUsers()) System.out.println(user);
        System.out.println("Prieteni:");
        for (Friendship friendship : service.getFriendships()) System.out.println(friendship);
        System.out.println("Comunitati:");
        for (List<Long> community : service.getCommunities()) System.out.println(community);
    }

    private void showMostSociableCommunity() {
        for (User user : service.mostSociableCommunity()) System.out.println(user);
    }

    private void addUser() {
        System.out.print("Id: ");
        Long id = Long.parseLong(scanner.nextLine());
        System.out.print("Prenume: ");
        String firstName = scanner.nextLine();
        System.out.print("Nume: ");
        String lastName = scanner.nextLine();
        service.addUser(id, firstName, lastName);
    }

    private void removeUser() { service.removeUser(readId("Id: ")); }

    private void addFriendship() {
        service.addFriendship(readId("Primul id: "), readId("Al doilea id: "));
    }

    private void removeFriendship() {
        service.removeFriendship(readId("Primul id: "), readId("Al doilea id: "));
    }

    private Long readId(String message) {
        System.out.print(message);
        return Long.parseLong(scanner.nextLine());
    }
}