package todo.todo_app.controller.FrontEnd;

import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping("/home")
public class HomeController {
    @GetMapping
    public String home(ModelMap model) {
        String username = SecurityContextHolder.getContext().getAuthentication().getName();
        model.put("username", username);
        
        return "home";
    }
}
