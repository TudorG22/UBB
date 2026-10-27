package socialnetwork.repository;

import socialnetwork.domain.Entity;

import java.util.List;

/** Stores entities indexed by their IDs.
 * @param <ID> ID type
 * @param <E> entity type
 */
public interface Repository<ID, E extends Entity<ID>> {
    /** Saves a valid entity.
     * @param entity entity to save
     * @return null on success, or the entity if its ID exists
     * @throws IllegalArgumentException if entity is null
     * @throws socialnetwork.exceptions.ValidationException if entity is invalid
     * @throws socialnetwork.exceptions.RepositoryException if persistence fails
     */
    E save(E entity);

    /** Removes an entity.
     * @param id ID to remove
     * @return removed entity, or null if absent
     * @throws IllegalArgumentException if id is null
     * @throws socialnetwork.exceptions.RepositoryException if persistence fails
     */
    E delete(ID id);

    /** Replaces an existing entity.
     * @param entity new entity
     * @return null on success, or the entity if its ID is absent
     * @throws IllegalArgumentException if entity is null
     * @throws socialnetwork.exceptions.ValidationException if entity is invalid
     * @throws socialnetwork.exceptions.RepositoryException if persistence fails
     */
    E update(E entity);

    /** Finds an entity.
     * @param id ID to find
     * @return entity, or null if absent
     * @throws IllegalArgumentException if id is null
     */
    E findOne(ID id);

    /** Lists stored entities.
     * @return all entities
     */
    List<E> findAll();
}
