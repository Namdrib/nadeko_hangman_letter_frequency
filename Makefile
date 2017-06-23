# Makefile for Nadeko Hangman Hax0rs

CFLAGS = -std=gnu++11 -Wall -O2

default: the_cpp

all: the_bash the_ruby the_cpp
	
	
the_bash:
	chmod +x acquire_json.sh
	./acquire_json.sh
	
the_cpp:
	g++ -o a letter_frequency.cpp $(CFLAGS)
	
the_ruby:
	ruby ruby_extract_things.rb
	
clean:
	rm -f *.exe* *.txt
	
spotless: clean
	rm -f *.txt *.json 