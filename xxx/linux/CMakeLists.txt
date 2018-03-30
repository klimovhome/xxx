cmake_minimum_required (VERSION 2.6) 
 
add_definitions(-D __XXX_LINUX__)
add_definitions(-std=c++11)
 
set (PROJECT linxxx) 
 
project (${PROJECT}) 
 
set (HEADERS )
 
set (SOURCES ../src/xxx.cpp ../src/recv_transport.cpp ../src/send_transport.cpp ../src/sender.cpp ../src/receiver.cpp ../src/assembler.cpp ../src/disassembler.cpp ../src/formater.cpp) 
 
add_executable (${PROJECT} ${HEADERS} ${SOURCES})