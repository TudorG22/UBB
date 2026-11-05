package curs;

import curs.domain.CriteriiUtilizator;
import curs.domain.Utilizator;
import curs.domain.validators.UtilizatorValidator;
import curs.domain.validators.UtilizatorValidatorStrict;
import curs.domain.validators.ValidationException;
import curs.domain.validators.Validator;
import curs.ex.functional.Arie;
import curs.ex.functional.Cerc;
import curs.ex.functional.Patrat;
import curs.repository.InMemoryRepository;
import curs.repository.Repository;
import curs.repository.factory.RepositoryFactory;
import curs.repository.file.UtilizatorFileRepository;

import java.io.IOException;
import java.io.InputStream;
import java.util.List;
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
        //cerinta4();
        //listArii();
        //cerinta7();
        cerinta8();
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
        Properties prop = incarcaConfiguratie("/config.properties");
        RepositoryFactory repoFactory = new RepositoryFactory(prop);
        Repository<Long, Utilizator> repo = repoFactory.createUtilizatorRepository(new UtilizatorValidator());
        System.out.println("Repository creat: " + repo.getClass().getSimpleName());
        System.out.println("findAll: " + repo.findAll());
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
        //throw new UnsupportedOperationException("utilizatorDinText nu este implementata");

        String[] name = linie.split(";", -1);
        try{
            Utilizator u_new = new Utilizator(name[1], name[2]);
            u_new.setId(Long.parseLong(name[0]));
            return u_new;
        } catch(NumberFormatException n) {
            throw new ValidationException("Numele nu e corect");
        }
    };

    static Properties incarcaConfiguratie(String resursa) {
        Properties properties = new Properties();
        try {
            InputStream inputStream = Main.class.getResourceAsStream(resursa);
            if(inputStream == null) {
                throw new RuntimeException("Fisierul de configuratie " + resursa + " nu exista!");
            }
            properties.load(inputStream);
        } catch (IOException e) {
            throw new RuntimeException("Eroare la citirea resursei " + resursa, e);
        }
        return properties;
    }

    static <E> void printArie(List<E> figuri, Arie<E> arie) {
        for(E figura: figuri) {
            System.out.println("Aria figurii " + figura +
                    " este " + arie.calculeaza(figura));
        }
    }
    static void listArii() {
        List<Cerc> cercuri = List.of(new Cerc(1), new Cerc(2), new Cerc(3));
        // lista imutabila, nu se pot adauga/elimina elemente
        List<Patrat> patrate = List.of(new Patrat(1), new Patrat(2), new Patrat(3));
        Arie<Cerc> arieCercAnonim = new Arie<Cerc>() {
            @Override
            public double calculeaza(Cerc c) {
                return Math.PI * (c.getRaza() * c.getRaza());
            };
        };
        printArie(cercuri, arieCercAnonim);

        Arie<Cerc> lambdaCerc = abcd -> Math.PI * (abcd.getRaza() * abcd.getRaza());
        System.out.println("Acum afisez aria cu LAMBDA: ");
        printArie(cercuri, lambdaCerc);

        Arie<Cerc> arieCercReference = Cerc::arie;
        System.out.println("Acum afisez aria cu REFERENCE: ");
        printArie(cercuri, arieCercReference);
    }

    static void cerinta7() {
        Validator<Utilizator> utilizatorAnonim = new Validator<Utilizator>() {
            @Override
            public void validate(Utilizator u) {
                if(u.getFirstName() == null || u.getFirstName().isBlank()
                        || u.getLastName() == null || u.getLastName().isBlank()) {
                    throw new ValidationException("Prenumele sau numele nu exista");
                }
            }
        };

        Validator<Utilizator> utilizatorLambda = u -> {
            if(u.getFirstName() == null || u.getFirstName().isBlank()
                    || u.getLastName() == null || u.getLastName().isBlank())
                throw new ValidationException("Pt exresia lambda prenumele si numele nu sunt corecte");
        };

        Validator<Utilizator> utilizatorReference = Main::verificaPrenume;

        //Utilizator u = utilizatorDinText("7;;Pop");
//        try {
//            utilizatorAnonim.validate(u);
//            utilizatorLambda.validate(u);
//            utilizatorReference.validate(u);
//        }
//        catch(Exception e) {
//            System.err.println("Eroare la validarea utilizatorului: " + e.getMessage());
//        }

        int lung_max = 10;
        Validator<Utilizator> validator = ut -> {
            if(ut.getLastName().length() > lung_max || ut.getFirstName().length() > lung_max) {
                throw new ValidationException("Prenumele sau numele au mai mult de "
                        + lung_max + " caractere");
            }
        };

        Validator<Utilizator> validatorCompus = new UtilizatorValidator().andThen(validator);

        Repository<Long, Utilizator> repoInjectat = new InMemoryRepository<>(validatorCompus);
        try {
            repoInjectat.save(utilizatorDinText("1;Ana;Pop"));
            //repoInjectat.save(utilizatorDinText("2;Maximilian-Alexandru;Pop"));
            repoInjectat.save(utilizatorDinText("3;Ana;Pop"));
        }
        catch (Exception e) {
            System.out.println("Eroare la salvarea utilizatorului: " + e.getMessage());
        }
    }

    static void verificaPrenume(Utilizator u) {
        if(u.getFirstName() == null || u.getFirstName().isBlank()
                || u.getLastName() == null || u.getLastName().isBlank()) {
            throw new IllegalArgumentException("Prenumele sau numele nu exista");
        }
    }

    static void cerinta8() {
        Repository<Long, Utilizator> retea = reteaDemo();
        System.out.println("Numele Pop");
        retea.findAll(CriteriiUtilizator.areNumele("Pop")).forEach(System.out::println);
//        retea.findAll(CriteriiUtilizator.areNumele("Pop"));
//        List<Utilizator> list_utilizator = retea.findAll(CriteriiUtilizator.areNumele("Pop"));
//        for(Utilizator u: list_utilizator) {
//
//        }
        retea.findAll(CriteriiUtilizator.areCelPutinPrieteni(2)).forEach(System.out::println);

        retea.findAll(x -> x.getLastName() != "Pop" && x.getFirstName() == "Matei").forEach(System.out::println);
    }

    static Repository<Long, Utilizator> reteaDemo() {
        Repository<Long, Utilizator> retea = new InMemoryRepository<>(new UtilizatorValidator());
        String[] utilizatori = {"1;Ana;Pop", "2;Nelu;Abcd", "3;Ion;Pop", "4;Matei;Andrasi"
                , "5;Seby;Ionescu"};
        for(String user: utilizatori) {
            retea.save(utilizatorDinText(user));
        }
        long[][] prietenii = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
        for(long[] prieteni: prietenii) {
            Utilizator a = retea.findOne(prieteni[0]);
            Utilizator b = retea.findOne(prieteni[1]);
            a.getFriends().add(b);
            b.getFriends().add(a);
        }
        return retea;
    }
}
