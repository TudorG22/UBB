package socialnetwork.service;

import socialnetwork.domain.User;

import java.util.Set;
import java.util.function.Predicate;

public class CriteriiUtilizator {
    public static Predicate<User> prenumeIncepeCu(String text) {
        return user -> user.getFirstName().startsWith(text);
    }

    public static Predicate<User> numeIncepeCu(String text) {
        return user -> user.getLastName().startsWith(text);
    }

    public static Predicate<User> faraPrieteni(Set<Long> idsWithFriends) {
        return user -> !idsWithFriends.contains(user.getId());
    }
}
