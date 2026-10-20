package socialnetwork.domain;

import java.util.Objects;

/** Reprezinta o prietenie intre doi utilizatori. */
public class Friendship {
    private final Long firstUserId;
    private final Long secondUserId;

    public Friendship(Long firstUserId, Long secondUserId) {
        this.firstUserId = firstUserId;
        this.secondUserId = secondUserId;
    }

    public Long getFirstUserId() { return firstUserId; }
    public Long getSecondUserId() { return secondUserId; }

    @Override
    public boolean equals(Object object) {
        if (this == object) return true;
        if (!(object instanceof Friendship friendship)) return false;
        return (Objects.equals(firstUserId, friendship.firstUserId) && Objects.equals(secondUserId, friendship.secondUserId))
                || (Objects.equals(firstUserId, friendship.secondUserId) && Objects.equals(secondUserId, friendship.firstUserId));
    }

    @Override
    public int hashCode() { return Objects.hash(firstUserId) + Objects.hash(secondUserId); }

    @Override
    public String toString() { return firstUserId + ";" + secondUserId; }
}
