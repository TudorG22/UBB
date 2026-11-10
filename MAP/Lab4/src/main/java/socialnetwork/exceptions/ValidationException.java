package socialnetwork.exceptions;

/** Reports invalid entity data. */
public class ValidationException extends RuntimeException {
    public ValidationException(String message) { super(message); }
}
