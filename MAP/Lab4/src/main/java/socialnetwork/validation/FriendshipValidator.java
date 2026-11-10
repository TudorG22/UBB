package socialnetwork.validation;

import socialnetwork.domain.Friendship;
import socialnetwork.domain.User;
import socialnetwork.exceptions.ValidationException;
import socialnetwork.repository.Repository;

public class FriendshipValidator implements Validator<Friendship> {
    private final Repository<Long, User> userRepository;

    public FriendshipValidator(Repository<Long, User> userRepository) {
        this.userRepository = userRepository;
    }

    @Override
    public void validate(Friendship friendship) {
        if (friendship == null || friendship.getFirstUserId() == null || friendship.getSecondUserId() == null
                || friendship.getFriendshipDate() == null || friendship.getFirstUserId().equals(friendship.getSecondUserId())) {
            throw new ValidationException("Date prietenie invalide.");
        }
        if (userRepository.findOne(friendship.getFirstUserId()) == null
                || userRepository.findOne(friendship.getSecondUserId()) == null) {
            throw new ValidationException("Utilizator inexistent.");
        }
    }
}
