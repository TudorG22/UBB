package socialnetwork.repository;

import socialnetwork.config.RepositoryType;
import socialnetwork.domain.Friendship;
import socialnetwork.domain.User;
import socialnetwork.validation.Validator;

import java.nio.file.Path;
import java.util.Properties;

public class RepositoryFactory {
    private final Properties properties;

    public RepositoryFactory(Properties properties) {
        this.properties = properties;
    }

    /** Creates a user repository.
     * @param validator user validator
     * @return configured repository
     * @throws IllegalArgumentException if configuration is missing or unknown
     */
    public Repository<Long, User> createUtilizatorRepository(Validator<User> validator) {
        switch (getRepositoryType()) {
            case MEMORY: return new InMemoryRepository<>(validator);
            case FILE: return new UtilizatorFileRepository(Path.of(getRequired("file.utilizatori")), validator);
            case DATABASE: return new UtilizatorDbRepository(validator, getRequired("db.url"),
                    getRequired("db.user"), getRequired("db.password"));
            default: throw new IllegalArgumentException("Tip de repository invalid.");
        }
    }

    /** Creates a friendship repository.
     * @param validator friendship validator
     * @return configured repository
     * @throws IllegalArgumentException if configuration is missing or unknown
     */
    public Repository<String, Friendship> createPrietenieRepository(Validator<Friendship> validator) {
        switch (getRepositoryType()) {
            case MEMORY: return new InMemoryRepository<>(validator);
            case FILE: return new PrietenieFileRepository(Path.of(getRequired("file.prietenii")), validator);
            case DATABASE: return new PrietenieDbRepository(validator, getRequired("db.url"),
                    getRequired("db.user"), getRequired("db.password"));
            default: throw new IllegalArgumentException("Tip de repository invalid.");
        }
    }

    private RepositoryType getRepositoryType() {
        return RepositoryType.fromString(getRequired("repository.type"));
    }

    private String getRequired(String key) {
        String value = properties.getProperty(key);
        if (value == null || value.isBlank()) {
            throw new IllegalArgumentException("Lipseste proprietatea " + key + ".");
        }
        return value.trim();
    }
}
