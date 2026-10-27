package socialnetwork.repository;

import socialnetwork.domain.Entity;
import socialnetwork.exceptions.RepositoryException;
import socialnetwork.exceptions.ValidationException;
import socialnetwork.validation.Validator;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.charset.StandardCharsets;
import java.time.format.DateTimeParseException;

/** Stores entities in memory and a UTF-8 text file.
 * @param <ID> ID type
 * @param <E> entity type
 */
public abstract class AbstractFileRepository<ID, E extends Entity<ID>>
        extends InMemoryRepository<ID, E> {
    private final Path file;

    /** Loads existing data from a file.
     * @param file text file path
     * @param validator entity validator
     * @throws RepositoryException if a line is invalid or reading fails
     */
    protected AbstractFileRepository(Path file, Validator<E> validator) {
        super(validator);
        this.file = file;
        loadData();
    }

    /** {@inheritDoc} */
    @Override
    public E save(E entity) {
        E result = super.save(entity);
        if (result == null) {
            writeData();
        }
        return result;
    }

    /** {@inheritDoc} */
    @Override
    public E delete(ID id) {
        E result = super.delete(id);
        if (result != null) {
            writeData();
        }
        return result;
    }

    /** {@inheritDoc} */
    @Override
    public E update(E entity) {
        E result = super.update(entity);
        if (result == null) {
            writeData();
        }
        return result;
    }

    private void loadData() {
        if (!Files.exists(file)) {
            return;
        }

        try (BufferedReader reader = Files.newBufferedReader(file, StandardCharsets.UTF_8)) {
            String line;
            int lineNumber = 0;
            while ((line = reader.readLine()) != null) {
                lineNumber++;
                try {
                    if (super.save(extractEntity(line)) != null) {
                        throw new RepositoryException("Entitate duplicata.");
                    }
                } catch (IllegalArgumentException | DateTimeParseException | ValidationException
                         | RepositoryException exception) {
                    throw new RepositoryException(file + ", linia " + lineNumber + ": "
                            + exception.getMessage(), exception);
                }
            }
        } catch (IOException exception) {
            throw new RepositoryException("Nu se poate citi fisierul: " + file, exception);
        }
    }

    private void writeData() {
        try {
            Path parent = file.getParent();
            if (parent != null) {
                Files.createDirectories(parent);
            }
            try (BufferedWriter writer = Files.newBufferedWriter(file, StandardCharsets.UTF_8)) {
                for (E entity : findAll()) {
                    writer.write(createEntityAsString(entity));
                    writer.newLine();
                }
            }
        } catch (IOException exception) {
            throw new RepositoryException("Nu se poate scrie fisierul: " + file, exception);
        }
    }

    /** Converts one line to an entity.
     * @param line text line
     * @return parsed entity
     */
    protected abstract E extractEntity(String line);

    /** Converts an entity to one line.
     * @param entity entity to write
     * @return text line
     */
    protected abstract String createEntityAsString(E entity);
}
