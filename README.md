# SimpleAuthJWT
This project serves as an illustrative example of creating a basic authentication application using JWT tokens and one-time passwords (OTP) for enhanced security measures using microservices architecture with the service mesh.

## Prerequisites

Before you begin, ensure you have met the following requirements:

- [Docker](https://www.docker.com/)

- [Helm](https://helm.sh/)

- [Istio](https://istio.io/)
 
- [Yarn](https://yarnpkg.com/)

## Getting Started

These instructions will help you set up and run the project on your local machine.

1. Clone the repository:

    ```bash
    git clone https://github.com/your-username/your-repository.git --recurse-submodule
    cd your-repository
    ```
2. Deploy the infrastructure and forwarding port
    ```bash
    cd k8s
    helm install infra-deploy .
    sudo -E ./ingress-forward
    ```
3. Build the client app
   ```bash
    cd client
    yarn
    yarn build
    yarn dev
    ```
