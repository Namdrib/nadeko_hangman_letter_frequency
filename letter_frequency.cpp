#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unistd.h> // getopt
#include <utility>
#include <vector>

using namespace std;

#define all(c) (c).begin(), (c).end()

// Counts the frequency of letters in some text file or stdin if not supplied

// Show usage
void usage(char *programName)
{
	cerr << "Usage: " << programName << " [options]\n"
	     << "\nOptions:\n"
	     << "\tc\t\tTake into account letter casing (default: ignore casing)\n"
	     << "\tf filename\tRead input from `filename`. (default: read from stdin)\n"
		 << "\th\t\tShow this help message and exit program\n"
         << "\tp\t\tTake into account punctuation (default: only process alphanumerics)\n"
         << "\tw\t\tWhether to output the list of words in the given list (default: no output)\n";
}


void parseArgs(int argc, char* argv[], bool &considerCase, 
               string &filename, bool &considerPunctuation, bool &performSort, bool &outputWords)
{
	int c = 0;
	while ((c = getopt(argc, argv, "cf:hps")) != -1)
	{
		switch (c)
		{
			// Take into account case
			case 'c':
			{
				considerCase = true;
				break;
			}
			
			// Store provided filename
			case 'f':
			{
				filename = optarg;
				break;
			}
			
			// Take into account punctuation
			case 'p':
			{
				considerPunctuation = true;
				break;
			}
			
			// Sort the output at the end
			case 's':
			{
				performSort = true;
				break;
			}
			
			// Whether to output the list of words
			case 'w':
			{
				outputWords = true;
				break;
			}
			
			// Show help and exit
			default:
			{
				usage(argv[0]);
				exit(EXIT_SUCCESS);
			}
		}
	}
}

// Reads strings from a filestream (per line)
vector<string> readFileIntoVector(const string &filename)
{
	vector<string> out;
	
	istream *isPtr = nullptr; // Read from this
	ifstream f;
	
	// Open a file if necessary
	if (filename != "")
	{
		f.open(filename.c_str());
		if (!f.is_open())
		{
			cerr << "Error, could not open " << filename << endl;
			exit(EXIT_FAILURE);
		}
		isPtr = &f;
	}
	else
	{
		isPtr = &cin;
	}
	
	// Do the reading
	for (string temp; getline(*isPtr, temp); )
	{
		out.push_back(temp);
	}
	
	if (filename != "")
	{
		f.close();
	}
	
	return out;
}

template <typename T>
ostream& operator << (ostream &os, vector<T> &v)
{
	for (size_t i=0; i<v.size(); i++)
	{
		os << v[i];
		if (i < v.size()-1) os << ", ";
	}
	return os;
}

int main(int argc, char* argv[])
{
	bool considerCase = false;
	bool considerPunctuation = false;
	bool outputWords = false;
	bool performSort = false;
	string filename = ""; // blank means take from stdin
	
	parseArgs(argc, argv, considerCase, filename, considerPunctuation, performSort, outputWords);
	
	// Read words into a vector of strings.
	// If filename is blank, then read from stdin
	vector<string> words = readFileIntoVector(filename);
	
	if (outputWords)
	{
		cout << "Words: " << words << endl;
	}
	
	// Build the letter frequency
	map<char, unsigned long long> letterFrequency;
	for (string s : words)
	{
		for (char c : s)
		{
			if (!considerPunctuation)
			{
				if (!isalnum(c)) continue;
			}
			if (!considerCase)
			{
				if (isalpha(c)) c = tolower(c);
			}
			
			// Add it to the map
			if (letterFrequency.count(c) == 0)
			{
				letterFrequency[c] = 1;
			}
			else
			{
				letterFrequency[c]++;
			}
		}
	}
	
	// Final output
	vector<pair<char, unsigned long long>> vp(all(letterFrequency));
	if (performSort)
	{
		sort(all(vp), 
			[](const pair<char, unsigned long long> &a, const pair<char, unsigned long long> &b)
			{
				return a.second > b.second;
			}
		);
	}
	
	// Store from map into vector<pair>
	for (auto it : vp)
	{
		cout << it.first << " : " << it.second << endl;
	}
}