//
// Created by Deniz Surmeli on 29.04.2022.
//

#include <deque>
#include <algorithm>

bool is_all_zero(std::deque<int> sequence)
{
  return std::all_of(sequence.begin(),sequence.end(),[](int i){return i == 0;});
}

bool havel_hakimi(std::deque<int> sequence)
{
  if(sequence.size() < 1 || is_all_zero(sequence))
	return true;
  std::sort(sequence.begin(),sequence.end(),std::greater<int>());
  int highest_degree = sequence.front();
  if(highest_degree > sequence.size() - 1)
	return false;
  sequence.pop_front();
  for(int i = 0; i < highest_degree ; i++)
  {
	if(sequence.at(i) > 0)
	  sequence.at(i)--;
	else
	  return false;
  }

  return havel_hakimi(std::move(sequence));
}
