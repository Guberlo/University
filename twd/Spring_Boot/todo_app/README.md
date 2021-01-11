# Todo App
This is a project developed for TSDW course at University of Catania. It shows how to build a REST web app using Spring Boot implementing:
* *CRUD operations in mysql*
* *REST controllers*
* *Security using JWT*
* *Very basic front-end using JSP and some Java Script*

### Schema:
- *Users*

| Filed | Type |
| :------- | :------- |
| id | bigint |
| email | varchar(50) |
| name | varchar(50) |
| password | varchar(300) |
| username | varchar(50) |

- *Roles*

| Field | Type |
| :------- | :------- |
| id | bigint |
| role_name | varchar(60) |

- *User_roles*

| Field | Type |
| :------- | :------- |
| user_id | bigint |
| role_id | bigint |

- *Todo*

| Field | Type |
| :------- | :------- |
| id | String |
| date | datetime |
| description | varchar(255) |
| username | varchar(255) |

### Endpoint:
- *Auth:* **/api/auth**

| Enpoint | Method |  Body (Parameters) | Description |  
| :------- | :------- | :------- | :------- | 
| **/signin** | *POST* | username, password  | Log an already registered user |
| **/signup** | *POST* | email, name,  password, username | Register new user |
| **/logout** | *GET* | JwtToken | Log out logged user |  

- *User:* **/api/user**

| Enpoint | Method |  Auth (Parameters) | Description |  
| :------- | :------- | :------- | :------- |
| **/info** | *GET* | JwtToken | Shows info about user, need to have role USER |
| **/list** | *GET* | JwtToken | Shows info about all users, need to have role ADMIN |

- *Todo:* **/api/**

 Enpoint | Method |  Body (Parameters) | Description | 
| :------- | :------- | :------- | :------- |
| **/Todo** | *GET*  | JwtToken | Get all todos, need to have role ADMIN |
| **/Todo/id** | *GET*  | JwtToken, todoID | Get todo by id if exists , need to have role ADMIN |
| **/users/Todo** | *GET*  | JwtToken | Get all logged user todos, need to have role USER |
| **/users/Todo/id** | *GET*  | JwtToken, todoID | Get todo by id if exists in user collection, need to have role USER |
| **/Todo** | *POST* | JwtToken, username, description, date | Add a todo to logged user |
| **/Todo** | *PUT* | JwtToken, id, username, description, date | Update a todo to logged user |
| **/Todo/id** | *DELETE* | JwtToken | Delete todo by id if exists in user collection, need to have role USER |

### Front-End
Realized using both JSP and Java Script

| URL | Description |  
| :------- | :------- |
| **/login** | *Sends a POST request to the auth endpoint to authenticate user* |
| **/signup** | *Sends a POST request to the auth endpoint to register user* |
| **/home** | *Home page containing a redirect to todo-list* |
| **/todo-list** | *Page that shows user todo list (buttons to update and delete not yet developed)* |
| **/todo-add** | *Page to add a todo, sends a POST request to api endpoint to add a todo* |
