package socialnetwork.exceptions;

/** Reports a repository or persistence error. */
public class RepositoryException extends RuntimeException {
    /** Creates an error.
     * @param message explanation
     */
    public RepositoryException(String message) { super(message); }

    /** Creates an error while preserving its cause.
     * @param message explanation
     * @param cause original error
     */
    public RepositoryException(String message, Throwable cause) { super(message, cause); }
}
