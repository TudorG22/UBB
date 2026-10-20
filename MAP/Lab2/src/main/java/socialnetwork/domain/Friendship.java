package socialnetwork.domain;

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
    public String toString() { return firstUserId + ";" + secondUserId; }
}