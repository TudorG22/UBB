package socialnetwork.repository;

import socialnetwork.domain.Entity;
import socialnetwork.exceptions.RepositoryException;
import socialnetwork.exceptions.ValidationException;
import socialnetwork.validation.Validator;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.charset.StandardCharsets;
import java.time.format.DateTimeParseException;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

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

        try (Stream<String> stream = Files.lines(file, StandardCharsets.UTF_8)) {
            List<String> lines = stream.collect(Collectors.toList());
            IntStream.range(0, lines.size()).forEach(index -> {
                try {
                    if (super.save(extractEntity(lines.get(index))) != null) {
                        throw new RepositoryException("Entitate duplicata.");
                    }
                } catch (IllegalArgumentException | DateTimeParseException | ValidationException
                         | RepositoryException exception) {
                    throw new RepositoryException(file + ", linia " + (index + 1) + ": "
                            + exception.getMessage(), exception);
                }
            });
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
            List<String> lines = findAll().stream()
                    .map(this::createEntityAsString)
                    .collect(Collectors.toList());
            Files.write(file, lines, StandardCharsets.UTF_8);
        } catch (IOException exception) {
            throw new RepositoryException("Nu se poate scrie fisierul: " + file, exception);
        }
    }

    protected abstract E extractEntity(String line);

    protected abstract String createEntityAsString(E entity);
}
