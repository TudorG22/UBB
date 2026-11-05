package curs.domain;

import java.util.function.Predicate;

public final class CriteriiUtilizator {

    public CriteriiUtilizator() {}

    public static Predicate<Utilizator> prenumeleIncepeCu(String prefix){
        return p -> p.getFirstName().startsWith(prefix);
    }

    public static Predicate<Utilizator>  areNumele(String nume) {
        return p -> p.getLastName().equals(nume);
    }

    public static Predicate<Utilizator> areCelPutinPrieteni(int n){
        return p -> p.getFriends().size() >= n;
    }

    public static boolean faraPrieteni(Utilizator u) {
        return u.getFriends().isEmpty();
    }
}
