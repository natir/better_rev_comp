
/* std include */
#include <chrono>
#include <iostream>
#include <algorithm>

std::string switch_transform(std::string seq)
{
    std::string r(seq);
    std::transform(seq.rbegin(), seq.rend(), r.begin(), [](char c) {
	    switch(c) {
	    case 'A': return 'T';
	    case 'C': return 'G';
	    case 'G': return 'C';
	    case 'T': return 'A';
	    default: return 'N';
	    }
	    return 'N';
	});

    return r;
}

std::string switch_transform_const_ref(const std::string& seq)
{
    std::string r(seq);
    std::transform(seq.rbegin(), seq.rend(), r.begin(), [](char c) {
	    switch(c) {
	    case 'A': return 'T';
	    case 'C': return 'G';
	    case 'G': return 'C';
	    case 'T': return 'A';
	    default: return 'N';
	    }
	    return 'N';
	});

    return r;
}


class tab_revert
{
private :
    char nuc2nuc['T' + 1] = {'N'};

    static tab_revert* m_instance;

private :
    
    tab_revert()
	{
	    nuc2nuc['A'] = 'T';
	    nuc2nuc['T'] = 'A';
	    nuc2nuc['C'] = 'G';
	    nuc2nuc['G'] = 'C';
	}
    
public:

    static tab_revert* get_instance()
	{
	    if(!m_instance)
		m_instance = new tab_revert();

	    return m_instance;
	}

    std::string run(std::string seq)
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

	    return seq;
	}

    std::string run_ref(std::string& seq)
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

	    return seq;
	}
};
tab_revert *tab_revert::m_instance = 0;

int main(int argc, char** argv)
{
    /* Take argument */
    long long replicate = std::stoll(std::string(argv[1]));
    long long repeat = std::stoll(std::string(argv[2]));
    std::string seq(argv[3]);

    /* Init table */
    std::cout<<"switch_transform;switch_transform_const_ref;tabular_revert;tabular_revert_ref"<<std::endl;

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

	/* switch_transform_const_ref call */
	begin = std::chrono::high_resolution_clock::now();
	for(auto i = 0; i != repeat; i++)
	{
	    switch_transform_const_ref(seq);
	}
	elapsed = std::chrono::high_resolution_clock::now() - begin;

	std::cout<<std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()<<";";
    
	/* tab and revert */
	begin = std::chrono::high_resolution_clock::now();
	for(auto i = 0; i != repeat; i++)
	{
	    tab_revert::get_instance()->run(seq);
	}
	elapsed = std::chrono::high_resolution_clock::now() - begin;

	std::cout<<std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()<<";";

	/* tab and revert */
	begin = std::chrono::high_resolution_clock::now();
	for(auto i = 0; i != repeat; i++)
	{
	    tab_revert::get_instance()->run_ref(seq);
	}
	elapsed = std::chrono::high_resolution_clock::now() - begin;

	std::cout<<std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()<<std::endl;
    }

    return 0;
}
