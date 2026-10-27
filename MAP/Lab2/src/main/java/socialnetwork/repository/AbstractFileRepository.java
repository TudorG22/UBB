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

public abstract class AbstractFileRepository<ID, E extends Entity<ID>>
        extends InMemoryRepository<ID, E> {
    private final Path file;

    protected AbstractFileRepository(Path file, Validator<E> validator) {
        super(validator);
        this.file = file;
        loadData();
    }

    @Override
    public E save(E entity) {
        E result = super.save(entity);
        if (result == null) {
            writeData();
        }
        return result;
    }

    @Override
    public E delete(ID id) {
        E result = super.delete(id);
        if (result != null) {
            writeData();
        }
        return result;
    }

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

    protected abstract E extractEntity(String line);

    protected abstract String createEntityAsString(E entity);
}
