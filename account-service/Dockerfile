FROM thelingeringwill/vcpkg:1 

WORKDIR /home/auth-service
COPY . .
RUN cmake -S . -B build
RUN cmake --build build
ENTRYPOINT ./bin/AccountService
