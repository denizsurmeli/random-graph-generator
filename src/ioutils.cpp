//
// Created by Deniz Surmeli on 29.04.2022.
//

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

//Splits the string by the given delimiter, puts the pieces into a vector.
//Example:
//str:"1 2 3 4 5 6"
//result: std::vector<int>(1,2,3,4,5,6).
void split_string(std::string str, char delimiter, std::deque<int> &in)
{
  std::string temp;

  for(int i = 0 ; i < str.size(); i ++)
  {
	if(str.at(i) == delimiter)
	{
	  in.push_back(std::stoi(temp));
	  temp.clear();
	}
	else
	{
	  temp.push_back(str.at(i));
	}
  }
  //push remaining piece to vector
  if(!temp.empty())
	in.push_back(std::stoi(temp));
}

//Reads the file content, line by line.After parsing the file,
//returns a vector that contains the degree sequence of the future graph.
std::deque<int> read_input(std::string filepath)
{
  std::fstream file;
  std::deque<int> degrees;
  std::string line;

  file.open(filepath, std::ios::in);
  if(file.is_open())
  {
	//skip the first line, we will handle things dynamically
	std::getline(file,line);
	//second line is the one that contains the degree sequence
	while(std::getline(file, line))
	{
	  //capture the line, split by delimiter " ", push them onto vector
	  split_string(line,' ',degrees);
	}
  }
  file.close();
  return degrees;
}