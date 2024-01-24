# SimpleAuthJWT
This project serves as an illustrative example of creating a basic authentication application using JWT tokens and one-time passwords (OTP) for enhanced security measures using microservices architecture with the service mesh.

## Prerequisites
## Install Docker and Minikube
https://www.docker.com/get-started/

https://minikube.sigs.k8s.io/docs/start/

Then start the Kubernetes cluster:
```
minikube start --cpus=2 --memory=5000 --driver=docker
```
## Install Istio
https://istio.io/latest/docs/setup/getting-started/
```
cd istio-1.17.0    
export PATH=$PWD/bin:$PATH    
istioctl install --set profile=demo -y
cd ..   
```
Enable auto-injection of the Istio side-cars when the pods are started:
```
kubectl label namespace default istio-injection=enabled
```
Install the Istio addons (Kiali, Prometheus, Jaeger, Grafana):
```
kubectl apply -f samples/addons
```
## 
Enable auto-injection of the Istio side-cars when the pods are started:
```
kubectl label namespace default istio-injection=enabled
```
## Install Helm
https://helm.sh/docs/intro/install/


## Getting Started

These instructions will help you set up and run the project on your local machine.

1. Clone the repository:

    ```bash
    git clone https://github.com/your-username/your-repository.git --recurse-submodules
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
