FROM gcc:11.3.0
COPY /src /app
RUN gcc /app/p1/main.cpp -o /app/a1.out -lstdc++ -lrt 
RUN gcc /app/p2/main.cpp -o /app/a2.out -lstdc++ -lrt 
