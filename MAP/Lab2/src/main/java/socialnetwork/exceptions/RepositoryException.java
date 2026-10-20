package socialnetwork.exceptions;

/** Semnaleaza o eroare la nivelul persistentei. */
public class RepositoryException extends RuntimeException {
    public RepositoryException(String message) { super(message); }
}
