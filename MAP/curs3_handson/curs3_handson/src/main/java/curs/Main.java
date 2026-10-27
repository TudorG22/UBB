package curs;

import curs.domain.Utilizator;
import curs.domain.validators.UtilizatorValidator;
import curs.domain.validators.UtilizatorValidatorStrict;
import curs.domain.validators.ValidationException;
import curs.domain.validators.Validator;
import curs.repository.InMemoryRepository;
import curs.repository.Repository;
import curs.repository.factory.RepositoryFactory;
import curs.repository.file.UtilizatorFileRepository;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Properties;

public class Main {

    /**
     *
     * @param args - command line arguments (not used)
     */
    public static void main(String[] args) {
//        cerinta1();
//        cerinta2();
//        cerinta3();
        cerinta4();
    }

    // ---------------- Cerinta 3. Repository in fisier text ----------------

    /**
     * loads the users from a text file, saves new users (the valid ones reach
     * the file) and reopens the file with a new repository to show that the
     * data persisted
     */
    static void cerinta3() {
        System.out.println("\n=== Cerinta 3 ===");
        String fisier = "data/utilizatori.txt";


    }

    // ---------------- Cerinta 2. Repository in memorie ----------------

    /**
     * saves the same users in two repositories that use different validation
     * strategies; the exceptions thrown by the validator propagate through
     * the repository and are handled here, in the caller
     */
    static void cerinta2() {
        System.out.println("\n=== Cerinta 2 ===");
        // Strategy: acelasi Context (InMemoryRepository), strategii diferite

        //System.out.println("findAll: " + repo.findAll());
    }

    /**
     * saves an entity and reports the result; ValidationException (thrown by
     * the validator) and IllegalArgumentException (thrown by the repository)
     * propagate from the repository and are caught here
     *
     * @param repo   - the repository where the user is saved
     * @param entity - the user to be saved (may be null)
     */
    static void salveaza(Repository<Long, Utilizator> repo, Utilizator entity) {

    }

    // ---------------- Cerinta 1. Utilizator valid ----------------

    /**
     * builds users from text lines (id;firstName;lastName), validates them
     * and prints the result; invalid data does not stop the program
     */
    static void cerinta1() {
        System.out.println("=== Cerinta 1 ===");
        Validator<Utilizator> validator = new UtilizatorValidator();

        // datele vin ca text, ca dintr-un fisier: id;prenume;nume
        String[] linii = {
                "1;Ana;Pop",
                "-2;;ionescu",     // 3 erori de validare
                "12b;Mihai;Pop",   // id nenumeric -> NumberFormatException
                "3;Ion;"           // nume lipsa la final -> vezi split(";", -1)
        };


        System.out.println("Programul continua dupa validare.");
    }

    static void cerinta4() {
        Properties properties = incarcaConfiguratie("/config.properties");
        RepositoryFactory repositoryFactory = new RepositoryFactory(properties);
        Repository<Long, Utilizator> repo = repositoryFactory.createUtilizatorRepository(new UtilizatorValidator());
        System.out.println("Repository creat" + repo.getClass().getSimpleName());
        System.out.println("Find all: " + repo.findAll());
    }

    /**
     * creates a user from a text line; the NumberFormatException thrown by
     * Long.parseLong is translated into a ValidationException, keeping the
     * original exception as cause (exception chaining)
     *
     * @param linie - text line with the format id;firstName;lastName
     * @return the user created from the given line (not validated yet)
     * @throws ValidationException if the id is not numeric
     */
    static Utilizator utilizatorDinText(String linie) {
        /// todo: implement this method
        throw new UnsupportedOperationException("utilizatorDinText nu este implementata");
    }

    static Properties incarcaConfiguratie(String resursa) {
        Properties properties = new Properties();
        try {
            InputStream inputStream = Main.class.getResourceAsStream(resursa);
            if(inputStream == null) {
                throw new RuntimeException("Resursa nu poate fi null!");
            }
            properties.load(inputStream);
        } catch (IOException e) {
            throw new RuntimeException("Eroare la citirea resursei" + resursa, e);
        }
        return properties;
    }
}
