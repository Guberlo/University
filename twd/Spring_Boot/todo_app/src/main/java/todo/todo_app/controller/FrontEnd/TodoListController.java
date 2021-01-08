package todo.todo_app.controller.FrontEnd;

import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.GetMapping;

@Controller
public class TodoListController {

    @GetMapping("/todo-list")
    public String showTodoList(ModelMap model) {
        String username = SecurityContextHolder.getContext().getAuthentication().getName();
        model.put("username", username);

        return "todo-list";
    }

    @GetMapping("/todo-add")
    public String addTodo(ModelMap model) {
        String username = SecurityContextHolder.getContext().getAuthentication().getName();
        model.put("username", username);

        return "todo-add";
    }
}
