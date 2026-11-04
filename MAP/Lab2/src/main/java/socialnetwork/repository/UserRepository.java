package socialnetwork.service;

import socialnetwork.domain.User;
import socialnetwork.domain.Friendship;
import socialnetwork.exceptions.RepositoryException;
import socialnetwork.repository.Repository;

import java.util.List;

public interface UserRepository extends Repository<Long, User>{
    void findByName(String name);
}