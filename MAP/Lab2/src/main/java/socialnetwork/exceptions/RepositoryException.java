package socialnetwork.exceptions;

/** Reports a repository or persistence error. */
public class RepositoryException extends RuntimeException {
    public RepositoryException(String message) { super(message); }

    public RepositoryException(String message, Throwable cause) { super(message, cause); }
}
