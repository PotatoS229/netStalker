.PHONY: help build build-dev run run-dev stop clean test logs shell

# Переменные
IMAGE_NAME = netstalker
CONTAINER_NAME = netstalker-app
DEV_CONTAINER_NAME = netstalker-dev
TAG = latest

help: ## Показать это сообщение
	@echo "Доступные команды:"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2}'

build: ## Собрать production образ
	docker build --target runtime -t $(IMAGE_NAME):$(TAG) .

build-dev: ## Собрать development образ
	docker build --target development -t $(IMAGE_NAME)-dev:$(TAG) .

run: build ## Запустить production контейнер
	docker run -d \
		--name $(CONTAINER_NAME) \
		-p 8080:8080 \
		--restart unless-stopped \
		$(IMAGE_NAME):$(TAG)

run-dev: build-dev ## Запустить development контейнер
	docker run -d \
		--name $(DEV_CONTAINER_NAME) \
		-p 8080:8080 \
		-p 3000:3000 \
		-p 9229:9229 \
		-v $(PWD):/app \
		$(IMAGE_NAME)-dev:$(TAG)

stop: ## Остановить контейнер
	docker stop $(CONTAINER_NAME) || true
	docker rm $(CONTAINER_NAME) || true

stop-dev: ## Остановить development контейнер
	docker stop $(DEV_CONTAINER_NAME) || true
	docker rm $(DEV_CONTAINER_NAME) || true

clean: stop stop-dev ## Очистить все контейнеры и образы
	docker system prune -f

test: ## Запустить тесты в контейнере
	docker run --rm $(IMAGE_NAME)-dev:$(TAG) /app/build/tests/unit/test

logs: ## Показать логи контейнера
	docker logs -f $(CONTAINER_NAME)

logs-dev: ## Показать логи development контейнера
	docker logs -f $(DEV_CONTAINER_NAME)

shell: ## Зайти в shell production контейнера
	docker exec -it $(CONTAINER_NAME) /bin/bash

shell-dev: ## Зайти в shell development контейнера
	docker exec -it $(DEV_CONTAINER_NAME) /bin/bash

compose-up: ## Запустить через docker-compose
	docker-compose up -d

compose-down: ## Остановить docker-compose
	docker-compose down

compose-logs: ## Показать логи docker-compose
	docker-compose logs -f

# Алиасы
up: compose-up
down: compose-down
restart: stop run