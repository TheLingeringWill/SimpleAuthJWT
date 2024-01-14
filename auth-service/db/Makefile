SRC_DIR := .
DOCKER_REPO := simple-auth-jwt
TAG := auth-db
DOCKER_ID := thelingeringwill

# Lint the project according to .sqlfluff
lint:
	@sqlfluff lint ${SRC_DIR}

# Parse lint issues
fix:
	@sqlfluff fix ${SRC_DIR}

# Build image as target
docker-build:
	@docker build -t ${DOCKER_ID}/${DOCKER_REPO}:${TAG} ${SRC_DIR} 

# Push on Docker Hub
docker-push:
	@docker push $(DOCKER_ID)/$(DOCKER_REPO):$(TAG);

.PHONY: lint \
	fix 
