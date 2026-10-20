package socialnetwork.domain;

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
    public String toString() { return id + ";" + firstName + ";" + lastName; }
}