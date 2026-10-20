package socialnetwork.exceptions;

/** Semnaleaza date invalide. */
public class ValidationException extends RuntimeException {
    public ValidationException(String message) { super(message); }
}
