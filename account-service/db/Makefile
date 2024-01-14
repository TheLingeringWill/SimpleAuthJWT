SRC_DIR := .
DOCKER_REPO := simple-auth-jwt
TAG := account-db
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

# Build image without using cache
docker-clean-build:
	@docker build --no-cache -t ${DOCKER_ID}/${DOCKER_REPO}:${TAG} ${SRC_DIR};

# Run the container on specific port
docker-run:
	@docker run -p ${PORT}:5432 -e POSTGRES_PASSWORD=${PASSWORD} ${DOCKER_REPO}:${TAG}; 

# Tags the local image with the Docker Hub repository information
docker-tag:
	@docker tag $(DOCKER_REPO):$(TAG) $(DOCKER_ID)/$(DOCKER_REPO):$(TAG);
	
# Login to Docker Hub
docker-login:
	@docker login;

# Push on Docker Hub
docker-push:
	@docker push $(DOCKER_ID)/$(DOCKER_REPO):$(TAG);

# Tag the local image then push
docker-tag-push: docker-tag \
		 docker-push
.PHONY: lint \
	fix 
