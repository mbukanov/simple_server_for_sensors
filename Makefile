PROGRAM=home_sensors_server
INCLUDE=-I./src/transport
LIBS=-lpthread -lsqlite3 -ljsoncpp
FILES = ./src/*.cpp ./src/transport/*.cpp ./src/DB/*.cpp

FILES += ./src/cli/*.cpp

COMPILER=g++
all:
	${COMPILER} ${FILES} -o ${PROGRAM} ${LIBS} ${INCLUDE}


clean:
	rm -f ./src/*.o ${PROGRAM}
