package todo.todo_app.repository;

import java.util.Optional;

import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

import todo.todo_app.model.Role;
import todo.todo_app.model.RoleName;

@Repository
public interface RoleRepository extends CrudRepository<Role, Long>{
    Optional<Role> findByRoleName(RoleName roleName);
}