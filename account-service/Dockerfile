FROM famyhub/service:vcpkg 

WORKDIR /home/auth-service
COPY . .
RUN cmake -S . -B build -GNinja
RUN cmake --build build
ENTRYPOINT ./bin/AccountService
