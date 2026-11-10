package socialnetwork.repository;

import socialnetwork.config.RepositoryType;
import socialnetwork.domain.Friendship;
import socialnetwork.domain.User;
import socialnetwork.validation.Validator;

import java.nio.file.Path;
import java.util.Map;
import java.util.Properties;
import java.util.function.Function;
import java.util.function.Supplier;

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
        Function<Validator<User>, Repository<Long, User>> memory = InMemoryRepository::new;
        Map<RepositoryType, Supplier<Repository<Long, User>>> factories = Map.of(
                RepositoryType.MEMORY, () -> memory.apply(validator),
                RepositoryType.FILE, () -> new UtilizatorFileRepository(
                        Path.of(getRequired("file.utilizatori")), validator),
                RepositoryType.DATABASE, () -> new UtilizatorDbRepository(validator,
                        getRequired("db.url"), getRequired("db.user"), getRequired("db.password")));
        return factories.get(getRepositoryType()).get();
    }

    /** Creates a friendship repository.
     * @param validator friendship validator
     * @return configured repository
     * @throws IllegalArgumentException if configuration is missing or unknown
     */
    public Repository<String, Friendship> createPrietenieRepository(Validator<Friendship> validator) {
        Function<Validator<Friendship>, Repository<String, Friendship>> memory = InMemoryRepository::new;
        Map<RepositoryType, Supplier<Repository<String, Friendship>>> factories = Map.of(
                RepositoryType.MEMORY, () -> memory.apply(validator),
                RepositoryType.FILE, () -> new PrietenieFileRepository(
                        Path.of(getRequired("file.prietenii")), validator),
                RepositoryType.DATABASE, () -> new PrietenieDbRepository(validator,
                        getRequired("db.url"), getRequired("db.user"), getRequired("db.password")));
        return factories.get(getRepositoryType()).get();
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
