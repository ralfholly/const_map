ifneq ("$(MAKECMDGOALS)", "clean")
ifeq ("$(GOOGLE_TEST_HOME)", "")
$(error "Please define GOOGLE_TEST_HOME, ie. `make GOOGLE_TEST_HOME=~/googletest-release-1.8.0'")
endif
endif

TARGET := test/test_const_map

GMOCK_INCLUDE_PATH = $(GOOGLE_TEST_HOME)/googlemock
GTEST_INCLUDE_PATH = $(GOOGLE_TEST_HOME)/googletest

GMOCK_LIBRARY_PATH = $(GOOGLE_TEST_HOME)/googlemock
GTEST_LIBRARY_PATH = $(GOOGLE_TEST_HOME)/googlemock/gtest

# 'override' allows you to pass in extra flags when invoking `make', ie.
# make CPPFLAGS=-std=c++14
override CPPFLAGS += -ansi -std=c++11 -W -Wall -g -pthread -I $(GTEST_INCLUDE_PATH)/include -I $(GMOCK_INCLUDE_PATH)/include -I .
override LDFLAGS += -L$(GTEST_LIBRARY_PATH) -L$(GMOCK_LIBRARY_PATH)
override LDLIBS += -lgtest_main -lgtest -lgmock

.PHONY : all clean clang-tidy

all: test

$(TARGET): $(TARGET).cpp const_map.h

test: $(TARGET)
	./$<

lint:
	clang-tidy test/const_map.cpp --checks=bugprone-*,clang-analizer-*,cppcoreguidelines-* --header-filter=.* -- -I .

clean:
	rm -rf *.o $(TARGET)
