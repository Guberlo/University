package todo.todo_app.service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import todo.todo_app.model.Todo;
import todo.todo_app.repository.TodoRepository;

@Service
public class TodoService {

    @Autowired
    private TodoRepository repository;

    public Todo addTodo(Todo entity) {
        return repository.save(entity);
    }

    public Optional<Todo> getTodo(Long id) {
        return repository.findById(id);
    }

    public List<Todo> getAllTodos() {
        List<Todo> list = new ArrayList<>();
        repository.findAll().forEach(e -> list.add(e));
        return list;
    }

    public List<Todo> getTodoByUsername(String username) {
        List<Todo> list = new ArrayList<>();
        repository.findByUsername(username).forEach(e -> list.add(e));
        return list;
    }

    public Todo updateTodo(Todo e) {
        return repository.save(e);
    }

    public void deleteTodo(Long id) {
        repository.deleteById(id);
    }

}