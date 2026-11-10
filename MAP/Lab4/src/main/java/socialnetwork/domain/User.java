package socialnetwork.domain;

public class User extends Entity<Long> {
    private final String firstName;
    private final String lastName;

    public User(Long id, String firstName, String lastName) {
        super(id);
        this.firstName = firstName;
        this.lastName = lastName;
    }

    /** Returns the first name.
     * @return first name
     */
    public String getFirstName() { return firstName; }
    /** Returns the last name.
     * @return last name
     */
    public String getLastName() { return lastName; }

    @Override
    public String toString() { return getId() + ";" + firstName + ";" + lastName; }
}
