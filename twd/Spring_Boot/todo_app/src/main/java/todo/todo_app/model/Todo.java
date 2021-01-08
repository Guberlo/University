package todo.todo_app.model;

import java.util.Date;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;

import com.fasterxml.jackson.annotation.JsonFormat;

@Entity
public class Todo {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @NotBlank
    private String username;

    @NotBlank
    @Size(min = 10, message = "Enter at least 10 characters...")
    private String description;

    @NotNull
    @JsonFormat(pattern = "dd/MM/yyyy")
    private Date date;

    public Todo() {
    }

    public Todo(@NotBlank String username,
            @NotBlank @Size(min = 10, message = "Enter at least 10 characters...") String description,
            @NotNull Date date) {
        this.username = username;
        this.description = description;
        this.date = date;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    @Override
    public String toString() {
        return "Todo [date=" + date + ", description=" + description + ", id=" + id + ", username=" + username + "]";
    }
}