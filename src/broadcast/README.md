To create a network bridge: `docker network create network_name`

To create a container with a network connection: 
```
docker create --name container_name \
  --network network_name \
  --publish 8080:80 \
  nginx:latest
```

Or to connect a container to a network `docker network connect network_name container_name`

ref: https://docs.docker.com/network/bridge/