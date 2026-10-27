package socialnetwork.exceptions;

/** Reports invalid entity data. */
public class ValidationException extends RuntimeException {
    /** Creates a validation error.
     * @param message explanation
     */
    public ValidationException(String message) { super(message); }
}
