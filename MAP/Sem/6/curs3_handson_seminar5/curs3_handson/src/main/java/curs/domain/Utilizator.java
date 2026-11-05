package curs.domain;

import java.util.ArrayList;
import java.util.List;

/**
 * User of the social network, identified by an id of type Long
 */
public class Utilizator extends Entity<Long> {
    private String firstName;
    private String lastName;
    private final List<Utilizator> friends = new ArrayList<>();

    /**
     * creates a user with no friends; the id must be set with setId
     *
     * @param firstName - the first name of the user
     * @param lastName  - the last name of the user
     */
    public Utilizator(String firstName, String lastName) {
        this.firstName = firstName;
        this.lastName = lastName;
    }

    /**
     *
     * @return the first name of the user
     */
    public String getFirstName() {
        return firstName;
    }

    /**
     *
     * @param firstName - the new first name of the user
     */
    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    /**
     *
     * @return the last name of the user
     */
    public String getLastName() {
        return lastName;
    }

    /**
     *
     * @param lastName - the new last name of the user
     */
    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    /**
     *
     * @return the list of friends of the user
     * (never null; empty if the user has no friends)
     */
    public List<Utilizator> getFriends() {
        return friends;
    }

    /**
     *
     * @return the string representation of the user (without the friends list)
     */
    @Override
    public String toString() {
        return "Utilizator{id=" + id +
                ", firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                '}';
    }
}
