package socialnetwork.domain;

import java.util.Objects;

public abstract class Entity<ID> {
    private final ID id;

    protected Entity(ID id) {
        this.id = id;
    }

    /** Returns the ID.
     * @return entity ID
     */
    public ID getId() {
        return id;
    }

    @Override
    public boolean equals(Object object) {
        if (this == object) return true;
        if (object == null || getClass() != object.getClass()) return false;
        Entity<?> other = (Entity<?>) object;
        return Objects.equals(id, other.id);
    }

    @Override
    public int hashCode() {
        return Objects.hashCode(id);
    }
}
