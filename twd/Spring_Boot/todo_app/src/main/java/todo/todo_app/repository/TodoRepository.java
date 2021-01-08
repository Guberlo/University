package todo.todo_app.repository;

import java.util.List;

import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

import todo.todo_app.model.Todo;

@Repository
public interface TodoRepository extends CrudRepository<Todo, Long>{
    List<Todo> findByUsername(String username);
}