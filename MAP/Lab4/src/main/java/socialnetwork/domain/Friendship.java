package socialnetwork.domain;

import java.time.LocalDateTime;

public class Friendship extends Entity<String> {
    private final Long firstUserId;
    private final Long secondUserId;
    private final LocalDateTime friendshipDate;

    public Friendship(Long firstUserId, Long secondUserId, LocalDateTime friendshipDate) {
        super(createId(firstUserId, secondUserId));
        this.firstUserId = firstUserId;
        this.secondUserId = secondUserId;
        this.friendshipDate = friendshipDate;
    }

    /** Returns the first user ID.
     * @return first user ID
     */
    public Long getFirstUserId() { return firstUserId; }
    /** Returns the second user ID.
     * @return second user ID
     */
    public Long getSecondUserId() { return secondUserId; }
    /** Returns the creation date.
     * @return creation date
     */
    public LocalDateTime getFriendshipDate() { return friendshipDate; }

    /** Returns the same ID for either order of users.
     * @param firstUserId first user ID
     * @param secondUserId second user ID
     * @return normalized friendship ID
     */
    public static String createId(Long firstUserId, Long secondUserId) {
        if (firstUserId == null || secondUserId == null) {
            return "";
        }
        return firstUserId <= secondUserId
                ? firstUserId + ";" + secondUserId
                : secondUserId + ";" + firstUserId;
    }

    @Override
    public String toString() { return firstUserId + ";" + secondUserId + ";" + friendshipDate; }
}
