#!/bin/sh
echo Open Ingress at http://localhost:80/
kubectl -n istio-system port-forward deployment/istio-ingressgateway 80:8080
