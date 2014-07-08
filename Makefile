# Use g++ otherwise C++ stdlib is not linked in.
CC=g++

ValueMapperTest : ValueMapperTest.o ValueMapper.o

ValueMapper.o : ValueMapper.cpp ValueMapper.h
ValueMapperTest.o : ValueMapperTest.cpp ValueMapper.h

clean:
	rm -rf *.o ValueMapperTest
