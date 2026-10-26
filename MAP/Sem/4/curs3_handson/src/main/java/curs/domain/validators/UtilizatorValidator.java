package curs.domain.validators;

import curs.domain.Utilizator;

/**
 * Validator for Utilizator entities
 * A user is valid if:
 * - the id is not null and positive
 * - the first name and the last name are not blank and start with an uppercase letter
 */
public class UtilizatorValidator implements Validator<Utilizator> {

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
            errors.append("prenume invalid; ");
        if (!esteNumeValid(u.getLastName()))
            errors.append("nume invalid; ");

        if (!errors.isEmpty())
            throw new ValidationException(errors.toString().trim());
    }

    /**
     *
     * @param s - the name to be checked
     * @return true - if s is not null, not blank and starts with an uppercase letter,
     * false otherwise
     */
    private static boolean esteNumeValid(String s) {
        return s != null && !s.isBlank() && Character.isUpperCase(s.charAt(0));
    }
}
