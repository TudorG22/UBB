package socialnetwork.validation;

/** Checks an entity before it is stored.
 * @param <T> entity type
 */
public interface Validator<T> {
    /** Checks an entity.
     * @param entity entity to check
     * @throws socialnetwork.exceptions.ValidationException if invalid
     */
    void validate(T entity);
}
