-- Сохраните как: database_setup.sql
-- Этот файл будет содержать всю структуру вашей БД

-- Убедитесь, что используем правильную базу данных
USE myApp_db;

-- 1. Создание таблицы пользователей
CREATE TABLE users (
    id INT PRIMARY KEY AUTO_INCREMENT,          -- Уникальный ID, автоматически увеличивается
    username VARCHAR(50) UNIQUE NOT NULL,       -- Уникальное имя пользователя
    email VARCHAR(100) UNIQUE NOT NULL,         -- Уникальный email
    password_hash VARCHAR(255) NOT NULL,        -- Хэш пароля (никогда не храните пароли в чистом виде!)
    full_name VARCHAR(100),                     -- Полное имя
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, -- Дата создания (автоматически)
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP -- Дата обновления
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 2. Создание таблицы продуктов
CREATE TABLE products (
    id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    description TEXT,
    price DECIMAL(10, 2) NOT NULL CHECK (price >= 0), -- Цена с 2 знаками после запятой, не отрицательная
    stock_quantity INT DEFAULT 0 CHECK (stock_quantity >= 0),
    category_id INT,
    is_active BOOLEAN DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 3. Создание таблицы заказов
CREATE TABLE orders (
    id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT NOT NULL,
    total_amount DECIMAL(10, 2) NOT NULL,
    status ENUM('pending', 'processing', 'shipped', 'delivered', 'cancelled') DEFAULT 'pending',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE -- Внешний ключ, каскадное удаление
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 4. Создание таблицы элементов заказа
CREATE TABLE order_items (
    order_id INT NOT NULL,
    product_id INT NOT NULL,
    quantity INT NOT NULL CHECK (quantity > 0),
    price_at_time DECIMAL(10, 2) NOT NULL, -- Цена на момент покупки
    PRIMARY KEY (order_id, product_id),    -- Составной первичный ключ
    FOREIGN KEY (order_id) REFERENCES orders(id) ON DELETE CASCADE,
    FOREIGN KEY (product_id) REFERENCES products(id) ON DELETE RESTRICT
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

