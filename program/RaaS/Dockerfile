# ============================================
# BUILD STAGE 1: C++ Backend
# ============================================
FROM ubuntu:22.04 AS backend-builder

# Устанавливаем переменные окружения для tzdata
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC

# Устанавливаем зависимости для сборки C++
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libboost-all-dev \
    libssl-dev \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Копируем исходный код
WORKDIR /app
COPY . .

# Создаем директорию для сборки и собираем проект
RUN mkdir -p build && cd build && \
    cmake .. \
        -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_TESTS=OFF \
        -DBUILD_WEB_INTERFACE=ON && \
    make -j$(nproc)

# ============================================
# BUILD STAGE 2: Web Frontend
# ============================================
FROM node:18-alpine AS frontend-builder

# Устанавливаем зависимости для сборки фронтенда
WORKDIR /app/web

# Копируем package.json и package-lock.json
COPY web/package*.json ./

# Устанавливаем зависимости
RUN npm ci --only=production

# Копируем исходники фронтенда
COPY web/ ./

# Собираем фронтенд
RUN npm run build

# ============================================
# FINAL STAGE: Runtime
# ============================================
FROM ubuntu:22.04 AS runtime

# Устанавливаем переменные окружения
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC
ENV APP_USER=netstalker
ENV APP_HOME=/opt/netstalker
ENV NODE_ENV=production
ENV PORT=8080

# Создаем не-root пользователя
RUN useradd -r -s /bin/false ${APP_USER} && \
    mkdir -p ${APP_HOME} && \
    chown -R ${APP_USER}:${APP_USER} ${APP_HOME}

# Устанавливаем только runtime зависимости
RUN apt-get update && apt-get install -y \
    ca-certificates \
    libssl3 \
    libboost-system1.74.0 \
    libboost-thread1.74.0 \
    libboost-program-options1.74.0 \
    curl \
    && rm -rf /var/lib/apt/lists/*

# Копируем скомпилированный бэкенд из первого stage
COPY --from=backend-builder /app/build/bin/netStalker ${APP_HOME}/netStalker

# Копируем собранный фронтенд из второго stage
COPY --from=frontend-builder /app/dist ${APP_HOME}/web

# Копируем конфигурационные файлы
COPY LICENSE.md README.md ${APP_HOME}/

# Настраиваем рабочую директорию и владельца
WORKDIR ${APP_HOME}
RUN chmod +x ${APP_HOME}/netStalker && \
    chown -R ${APP_USER}:${APP_USER} ${APP_HOME}

# Переключаемся на не-root пользователя
USER ${APP_USER}

# Открываем порт для приложения
EXPOSE ${PORT}

# Health check для контейнера
HEALTHCHECK --interval=30s --timeout=3s --start-period=5s --retries=3 \
    CMD curl -f http://localhost:${PORT}/api/health || exit 1

# Команда запуска приложения
CMD ["./netStalker", "--port", "8080", "--web-dir", "./web"]

# ============================================
# ALTERNATIVE STAGE: Development
# ============================================
FROM ubuntu:22.04 AS development

# Устанавливаем переменные окружения для разработки
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC

# Устанавливаем инструменты для разработки
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    gdb \
    valgrind \
    lcov \
    libboost-all-dev \
    libssl-dev \
    pkg-config \
    clang-format \
    curl \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Устанавливаем Node.js для разработки фронтенда
RUN curl -fsSL https://deb.nodesource.com/setup_18.x | bash - && \
    apt-get install -y nodejs

# Копируем исходный код
WORKDIR /app
COPY . .

# Создаем символические ссылки для удобства разработки
RUN ln -sf /app/web /tmp/web-src && \
    ln -sf /app/build /tmp/build-dir

# Устанавливаем зависимости фронтенда
WORKDIR /app/web
RUN npm install

# Возвращаемся в корень
WORKDIR /app

# Команда для запуска в режиме разработки
CMD ["bash", "-c", "mkdir -p build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Debug && make -j$(nproc) && echo 'Development environment ready!' && /bin/bash"]