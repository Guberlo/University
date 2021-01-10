package todo.todo_app.controller.REST;

import java.util.List;
import java.util.Optional;
import java.net.URISyntaxException;
import java.net.URI;

import javax.validation.Valid;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import todo.todo_app.model.Todo;
import todo.todo_app.service.TodoService;

@RestController
@RequestMapping("/api")
public class TodoController {
    
    @Autowired
    private TodoService service;
    
    @GetMapping("/Todo")
    @PreAuthorize("hasRole('ADMIN')")
    public ResponseEntity<List<Todo>> getAllTodos() {
        List<Todo> list = service.getAllTodos();
        return ResponseEntity.ok().body(list);
    }

    @GetMapping("users/Todo")
    @PreAuthorize("hasRole('USER')")
    public ResponseEntity<List<Todo>> getUserTodos() {
        String user = SecurityContextHolder.getContext().getAuthentication().getName();
        List<Todo> list = service.getTodoByUsername(user);
        return ResponseEntity.ok().body(list);
    }

    @GetMapping("users/Todo/{id}")
    @PreAuthorize("hasRole('USER')")
    public ResponseEntity<Optional<Todo>> getUserTodo(@PathVariable Long id) {
        String user = SecurityContextHolder.getContext().getAuthentication().getName();
        List<Todo> list = service.getTodoByUsername(user);

        for (Todo todo : list) {
            if (todo.getId() == id) {
                Optional<Todo> item = service.getTodo(id);
                return ResponseEntity.ok().body(item);
            }
        }
        return ResponseEntity.notFound().build();
    }

    @GetMapping("/Todo/{id}")
    @PreAuthorize("hasRole('ADMIN')")
    public ResponseEntity<Optional<Todo>> getTodo(@PathVariable Long id) {
        Optional<Todo> todo = service.getTodo(id);
        if(todo.isPresent())
            return ResponseEntity.ok().body(todo);
        return ResponseEntity.notFound().build();
    }
    
    @PostMapping("/Todo")
    @PreAuthorize("hasRole('USER')")
    public ResponseEntity<Todo> addTodo(@Valid @RequestBody Todo e) throws URISyntaxException {
        if(e.getId() != null)
            return ResponseEntity.badRequest().build();
        Todo entity = service.addTodo(e);
        return ResponseEntity.created(new URI("/api/users/Todo/" + entity.getId())).body(entity);
    }
    
    // <!-- FIX THIS TO PERMIT ONLY TO USER !-->
    @PutMapping("/Todo")
    @PreAuthorize("hasRole('USER')")
    public ResponseEntity<Todo> updateTodo(@Valid @RequestBody Todo e) {
        if(e.getId() == null)
            return ResponseEntity.badRequest().build();

        String user = SecurityContextHolder.getContext().getAuthentication().getName();
        List<Todo> list = service.getTodoByUsername(user);

        for(Todo todo : list) {
            if(todo.getId() == e.getId()) {
                Todo entity = service.updateTodo(e);
                return ResponseEntity.ok().body(entity);
            }
        }

        return ResponseEntity.notFound().build();
    }
    
    // <!-- FIX THIS TO PERMIT ONLY TO USER !-->
    @DeleteMapping("/Todo/{id}")
    @PreAuthorize("hasRole('USER')")
    public ResponseEntity<Void> deleteTodo(@PathVariable Long id) {
        if(!service.getTodo(id).isPresent())
            return ResponseEntity.badRequest().build();

        String user = SecurityContextHolder.getContext().getAuthentication().getName();
        List<Todo> list = service.getTodoByUsername(user);
    
        for(Todo todo : list) {
            if(todo.getId() == id) {
                service.deleteTodo(id);
                return ResponseEntity.ok().build();
            }
        }
    
        return ResponseEntity.notFound().build();
    }

}