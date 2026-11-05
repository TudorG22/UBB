package curs.domain.validators;

import curs.domain.Utilizator;

/**
 * Stricter validation strategy for Utilizator entities
 * A user is valid if:
 * - the id is not null and positive
 * - the first name and the last name start with an uppercase letter,
 * have at least 2 characters and contain only letters
 */
public class UtilizatorValidatorStrict implements Validator<Utilizator> {

    /**
     * all the errors are reported at once, in a single ValidationException
     *
     * @param u - the user to be validated
     * @throws ValidationException if the user is null or not valid;
     *                             the message contains all the errors found
     */
    @Override
    public void validate(Utilizator u) {
        if (u == null)
            throw new ValidationException("Utilizatorul nu poate fi null!");

        StringBuilder errors = new StringBuilder();

        if (u.getId() == null || u.getId() <= 0)
            errors.append("id invalid; ");
        if (!esteNumeValid(u.getFirstName()))
            errors.append("prenume invalid (strict); ");
        if (!esteNumeValid(u.getLastName()))
            errors.append("nume invalid (strict); ");

        if (!errors.isEmpty())
            throw new ValidationException(errors.toString().trim());
    }

    /**
     *
     * @param s - the name to be checked
     * @return true - if s starts with an uppercase letter, has at least 2 characters
     * and contains only letters, false otherwise
     */
    private static boolean esteNumeValid(String s) {
        if (s == null || s.length() < 2 || !Character.isUpperCase(s.charAt(0)))
            return false;
        for (char c : s.toCharArray())
            if (!Character.isLetter(c))
                return false;
        return true;
    }
}
