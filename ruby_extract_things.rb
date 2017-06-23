require 'rubygems'
require 'json'

# Pls don't use me
def regex_it(f = 'hangman_animals.txt')
	contents = File.read(f).split("\n").sort()

	contents.each do |c|
		line = c.scan(/"Word": "[a-zA-Z]*"/).to_s.strip()
		if line.length > 2 
			# puts line.to_s.split(" ")
			puts line[14..-5]
		end
	end
end

def json_parse_it(f = 'hangman_all.json', topic = "Animals")
	file = open(f)
	json = file.read
	
	parsed = JSON.parse(json)
	
	output_array = []
	parsed[topic].each do |a|
		output_array << a["Word"]
	end
	return output_array
end


all = 'hangman_all.json'

h = {
	"Animals" => 'hangman_animals.txt',
	"Movies" => 'hangman_movies.txt',
	"Countries" => 'hangman_countries.txt',
	"Things" => 'hangman_things.txt',
}

# For each item in h, parse the json of that category,
# and write all the words into a file
h.each do |k, v|
	array = json_parse_it(all, k)
	
	# Write array to v
	File.open(v, "w+") do |f|
		puts "Putting " + k + " into " + v
		array.each { |e| f.puts(e) }
	end
end
