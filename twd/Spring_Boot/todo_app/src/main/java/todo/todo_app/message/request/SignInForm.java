package todo.todo_app.message.request;

import javax.validation.constraints.NotBlank;
import javax.validation.constraints.Size;

public class SignInForm {
    @NotBlank
    @Size(min = 3, max = 50)
    private String username;

    @NotBlank
    @Size(min = 3, max = 50)
    private String password;

    public SignInForm() {
    }

    public SignInForm(@NotBlank @Size(min = 3, max = 50) String username,
            @NotBlank @Size(min = 3, max = 50) String password) {
        this.username = username;
        this.password = password;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    @Override
    public String toString() {
        return "SignInForm [password=" + password + ", username=" + username + "]";
    }

}
