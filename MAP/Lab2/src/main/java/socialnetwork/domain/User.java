package socialnetwork.domain;

import java.util.Objects;

/** Reprezinta un utilizator al retelei de socializare. */
public class User {
    private final Long id;
    private final String firstName;
    private final String lastName;

    public User(Long id, String firstName, String lastName) {
        this.id = id;
        this.firstName = firstName;
        this.lastName = lastName;
    }

    public Long getId() { return id; }
    public String getFirstName() { return firstName; }
    public String getLastName() { return lastName; }

    @Override
    public boolean equals(Object object) {
        if (this == object) return true;
        if (!(object instanceof User user)) return false;
        return Objects.equals(id, user.id);
    }

    @Override
    public int hashCode() { return Objects.hash(id); }

    @Override
    public String toString() { return id + ";" + firstName + ";" + lastName; }
}
