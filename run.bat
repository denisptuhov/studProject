docker build . -t studproject
docker run --name studproject -d -i -t studproject /bin/sh
docker start studproject
docker exec studproject gcc /app/p1/main.cpp -o /app/a1.out -lstdc++ -lrt 
docker exec studproject gcc /app/p2/main.cpp -o /app/a2.out -lstdc++ -lrt
docker exec -it studproject /bin/sh -c "/app/a1.out | /app/a2.out"
docker rm -f studproject