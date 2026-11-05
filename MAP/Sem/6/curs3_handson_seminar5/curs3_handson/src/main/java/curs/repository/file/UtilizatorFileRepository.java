package curs.repository.file;

import curs.domain.Utilizator;
import curs.domain.validators.Validator;

/**
 * Text file repository for users; one user per line, with the format id;firstName;lastName
 */
public class UtilizatorFileRepository extends AbstractFileRepository<Long, Utilizator> {

    /**
     *
     * @param validator - the validation strategy for users
     * @param fileName  - the path of the text file
     */
    public UtilizatorFileRepository(Validator<Utilizator> validator, String fileName) {
        super(validator, fileName);
    }

    /**
     *
     * @param line - a line with the format id;firstName;lastName
     * @return the user described by the line
     */
    @Override
    protected Utilizator extractEntity(String line) {
        String[] fields = line.split(";", -1);
        Utilizator u = new Utilizator(fields[1], fields[2]);
        u.setId(Long.parseLong(fields[0]));
        return u;
    }

    /**
     *
     * @param u - the user to be converted
     * @return the line id;firstName;lastName
     */
    @Override
    protected String createEntityAsString(Utilizator u) {
        return u.getId() + ";" + u.getFirstName() + ";" + u.getLastName();
    }
}
