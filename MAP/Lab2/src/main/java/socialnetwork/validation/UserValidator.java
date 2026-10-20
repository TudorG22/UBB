package socialnetwork.validation;

import socialnetwork.domain.User;
import socialnetwork.exceptions.ValidationException;

/** Valideaza datele unui utilizator. */
public class UserValidator implements Validator<User> {
    @Override
    public void validate(User user) {
        if (user == null || user.getId() == null || user.getId() <= 0
                || user.getFirstName() == null || user.getFirstName().isBlank()
                || user.getLastName() == null || user.getLastName().isBlank()) {
            throw new ValidationException("Date utilizator invalide.");
        }
    }
}
