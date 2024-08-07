## Protobuf
para compilar o codigo do probuf:

protoc --python_out=. message.proto
protoc --cpp_out=. message.proto

compilar o codigo cpp: 
g++ -o my_program test.cpp message.pb.cc `pkg-config --cflags --libs protobuf`

## Cpu: 
compilar codigo da cpu:
g++ -o cpu cpu.cpp

## Comandos: 

g++ -o  commands comandos.cpp -lboost_system -lboost_filesystem -lpthread

