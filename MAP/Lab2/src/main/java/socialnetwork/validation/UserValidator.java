package socialnetwork.validation;

import socialnetwork.domain.User;
import socialnetwork.exceptions.ValidationException;

/** Validates a user. */
public class UserValidator implements Validator<User> {
    /** {@inheritDoc} */
    @Override
    public void validate(User user) {
        if (user == null || user.getId() == null || user.getId() <= 0
                || user.getFirstName() == null || user.getFirstName().isBlank()
                || user.getLastName() == null || user.getLastName().isBlank()
                || user.getFirstName().contains(";") || user.getLastName().contains(";")
                || user.getFirstName().contains("\n") || user.getLastName().contains("\n")
                || user.getFirstName().contains("\r") || user.getLastName().contains("\r")) {
            throw new ValidationException("Date utilizator invalide.");
        }
    }
}
