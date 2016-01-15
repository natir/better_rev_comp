
/* std include */
#include <chrono>
#include <iostream>
#include <algorithm>

std::string switch_transform(std::string seq)
{
  std::transform(seq.rbegin(), seq.rend(), seq.begin(), [](char c) {
      switch(c) {
      case 'A': return 'T';
      case 'C': return 'G';
      case 'G': return 'C';
      case 'T': return 'A';
      default: return 'N';
      }
      return 'N';
    });
  
  return seq;
}

class tab_revert
{
private :
    char nuc2nuc['T' + 1] = {'N'};
    
public:
    
    tab_revert()
	{
	    nuc2nuc['A'] = 'T';
	    nuc2nuc['T'] = 'A';
	    nuc2nuc['C'] = 'G';
	    nuc2nuc['G'] = 'C';
	}

    std::string operator()(std::string seq)
	{
	    auto first = seq.begin(), last = seq.end();

	    while(true)
		if(first == last || first == --last)
		{
		    if(seq.length() % 2)
			*first = nuc2nuc[*first];
		    return seq;
		}
		else
		{
		    *first = nuc2nuc[*first];
		    *last = nuc2nuc[*last];
		    std::iter_swap(first, last);
		    ++first;
		}

	}
};

int main(int argc, char** argv)
{
    /* Init table */
    tab_revert worker;
    
    std::cout<<"switch_transform;tabular_revert"<<std::endl;

    /* Take argument */
    long long replicate = std::stoll(std::string(argv[1]));
    long long repeat = std::stoll(std::string(argv[2]));
    std::string seq(argv[3]);

    for(auto i = 0; i != replicate; i++)
    {
	/* switch_transform call */
	auto begin = std::chrono::high_resolution_clock::now();
	for(auto i = 0; i != repeat; i++)
	{
	    switch_transform(seq);
	}
	auto elapsed = std::chrono::high_resolution_clock::now() - begin;

	std::cout<<std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()<<";";
    
	/* tab and revert */
	begin = std::chrono::high_resolution_clock::now();
	for(auto i = 0; i != repeat; i++)
	{
	    worker(seq);
	}
	elapsed = std::chrono::high_resolution_clock::now() - begin;

	std::cout<<std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()<<std::endl;
    }

    return 0;
}
