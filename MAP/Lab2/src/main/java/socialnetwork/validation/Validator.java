package socialnetwork.validation;

/** Defineste strategia de validare a unei entitati. */
public interface Validator<T> {
    void validate(T entity);
}
