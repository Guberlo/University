INSERT IGNORE INTO roles(role_name) VALUES ('ROLE_USER'), ('ROLE_ADMIN');

INSERT IGNORE INTO users(name, username, password, email) VALUES ('Admin', 'admin', '$2a$10$CPClv9ShoEM3Fc2PJ2NkLuXcau2jUN8k2g5l5hkB0qgMABc4.1hy.', 'admin@email.com');
INSERT IGNORE INTO user_roles(user_id, role_id) VALUES (1,1), (1,2);