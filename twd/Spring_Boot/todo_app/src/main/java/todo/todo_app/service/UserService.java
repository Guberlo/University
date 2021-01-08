package todo.todo_app.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import todo.todo_app.model.User;
import todo.todo_app.repository.UserRepository;
import todo.todo_app.security.UserPrinciple;


@Service
public class UserService implements UserDetailsService {

    @Autowired
    private UserRepository repository;

    @Override
    @Transactional
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        User user = repository.findByUsername(username).orElseThrow( () -> new UsernameNotFoundException("User " + username +  "not found!"));

        return UserPrinciple.build(user);
    }

}