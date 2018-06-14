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
void usage(char *program_name)
{
	cerr << "Usage: " << program_name << " [options]\n"
	     << "\nOptions:\n"
	     << "  -c\t\tTake into account letter casing (default: ignore casing)\n"
	     << "  -f filename\tRead input from `filename`. (default: read from stdin)\n"
		 << "  -h\t\tShow this help message and exit program\n"
         << "  -p\t\tTake into account punctuation (default: only alphanumerics)\n"
	     << "  -s\t\tSort the output by frequency (default: no sorting)\n"
         << "  -w\t\tOutput the words (default: no output)\n";
}

class config
{
public:
	bool consider_case;
	bool consider_punctuation;
	bool perform_sort;
	bool output_words;
	string filename;

	config()
	{
		consider_case = false;
		consider_punctuation = false;
		output_words = false;
		perform_sort = false;
		filename = ""; // blank means take from stdin
	}
};

bool parse_args(int argc, char* argv[], config &c)
{
	int ch = 0;
	while ((ch = getopt(argc, argv, "cf:hps")) != -1)
	{
		switch (ch)
		{
			// Take into account case
			case 'c':
			{
				c.consider_case = true;
				break;
			}
			
			// Store provided filename
			case 'f':
			{
				c.filename = optarg;
				break;
			}
			
			// Take into account punctuation
			case 'p':
			{
				c.consider_punctuation = true;
				break;
			}
			
			// Sort the output at the end
			case 's':
			{
				c.perform_sort = true;
				break;
			}
			
			// Whether to output the list of words
			case 'w':
			{
				c.output_words = true;
				break;
			}
			
			// Show help and exit
			default:
			{
				usage(argv[0]);
				return false;
			}
		}
	}
	return true;
}

// Reads strings from a filestream (per line)
vector<string> read_file_into_string_vector(const string &filename)
{
	vector<string> out;
	
	istream *is_ptr = nullptr; // Read from this
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
		is_ptr = &f;
	}
	else
	{
		is_ptr = &cin;
	}
	
	// Do the reading
	for (string temp; getline(*is_ptr, temp); )
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
	config c;
	
	if (!parse_args(argc, argv, c))
	{
		return 0;
	}
	
	// Read words into a vector of strings.
	// If filename is blank, then read from stdin
	vector<string> words = read_file_into_string_vector(c.filename);
	
	if (c.output_words)
	{
		cout << "Words: " << words << endl;
	}
	
	// Build the letter frequency
	map<char, unsigned long long> letter_freq;
	for (string s : words)
	{
		for (char ch : s)
		{
			if (!c.consider_punctuation)
			{
				if (!isalnum(ch)) continue;
			}
			if (!c.consider_case)
			{
				if (isalpha(ch)) ch = tolower(ch);
			}
			
			// Add it to the map
			if (letter_freq.count(ch) == 0)
			{
				letter_freq[ch] = 1;
			}
			else
			{
				letter_freq[ch]++;
			}
		}
	}
	
	// Final output
	vector<pair<char, unsigned long long>> vp(all(letter_freq));
	if (c.perform_sort)
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
