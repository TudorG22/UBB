package curs.repository.factory;

import curs.domain.Utilizator;
import curs.domain.validators.Validator;
import curs.repository.InMemoryRepository;
import curs.repository.Repository;
import curs.repository.db.UtilizatorDbRepository;
import curs.repository.file.UtilizatorFileRepository;

import java.util.Properties;

// RepositoryFactory este singurul loc care cunoaște clasele concrete de repository (Simple Factory).
//• Tipul de stocare și parametrii lui se citesc din config.properties, nu din cod.
public class RepositoryFactory {
    private final Properties properties;

    public RepositoryFactory(Properties prop) {
        this.properties = prop;
    }

    public Repository<Long, Utilizator> createUtilizatorRepository(Validator<Utilizator> validator) {
        String value = properties.getProperty("repository.type");
        if (value == null) {
            throw new IllegalArgumentException("Property nu poate fi null");
        }
        RepositoryType type = RepositoryType.valueOf(value.trim().toUpperCase());
        switch(type) {
            case MEMORY:
                return new InMemoryRepository<Long, Utilizator>(validator);
            case FILE:
                return new UtilizatorFileRepository(validator, properties.getProperty("repository.file.utilizatori"));
            case DATABASE:
                return new UtilizatorDbRepository(validator, properties.getProperty("db.url"),
                        properties.getProperty("db.username"),
                        properties.getProperty("db.password"));

            default:
                throw new IllegalArgumentException("RepositoryType invalid: " + type);
        }
    }
}
