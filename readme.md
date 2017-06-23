# Goal
Provide an unfair advantage when playing the Hangman game on the [Nadeko bot](https://github.com/Kwoth/NadekoBot)

Do this by finding the most common letters in each possible group of words

# Requirements
- make
- g++ 11
- ruby
- shell (bash)

# Instructions
- `make` to compile the C++ program that counts the letter frequency
- (optional) `./acquire_json.sh` to download the .json file - only required if file `hangman_all.json` is missing or has been modified
- `ruby ruby_extract_things.rb` to extract the words from each category into files (one file for each category, named `hangman_$CATEGORY.txt`
- `./a -f $FILE` to run the C++ program on a file. Provide no argument to take input from stdin
	- there exist options for this program - run `./a -h` to see all options

# The result
- the executable built by `letter_frequency.cpp` will output how often each letter appears in a file
	- this gives an idea of what letters to start with to gain an unfair advantage in hangman