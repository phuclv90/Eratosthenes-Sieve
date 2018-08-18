#include <iostream>
#include <vector>
#include <string.h>
#include <iomanip>

enum {
    INVALID_ARGCOUNT = 1,
    INVALID_INPUT = 2
};

void print_usage_and_exit(int exitcode, char* execname)
{
    std::cout <<
        "SIEVE OF ERATOSTHENES - Generate all primes up to the specified limit\n"
        "Usage (with <limit> not less than 2):\n    " <<
        execname << " <limit> [breakat]\nwill print all primes up to <limit>"
                    " with a line break after every <breakat> elements\nCall with `breakat = 0` for no line break (default = 10)\n";
    exit(exitcode);
}

/*
    We'll use a vector of booleans to mark the odd composites. No need to deal with even numbers
    That'll cut the memory requirement in half
    
    The vector will store the prime status of 3, 5, 7, 9, 11...
    i.e. index 0 is for 3, index 1 for 5, etc.
    
    As a result we can calculate the value that an index represents and vice versa
    with the following helper functions
*/
constexpr unsigned indexToPrime(unsigned index) 
{
    return index*2 + 3;
}

constexpr unsigned primeToIndex(unsigned prime)
{
    return (prime - 3)/2;
}

/*
The main sieve
Receives an empty vector and mark composite elements as true
*/
void sieve(std::vector<bool>& isComposite)
{
    unsigned firstprimeidx = primeToIndex(3);
    while (firstprimeidx < isComposite.size())  // loop until we've marked all the elements
    {
        for (unsigned step = indexToPrime(firstprimeidx), value = 2*step;
                value < indexToPrime(isComposite.size()); value += step)
        {
            if (value % 2 == 0) continue;               // no need to mark even numbers as composite
            isComposite[primeToIndex(value)] = true;    // since we only store odd numbers
        }

        do {    // find the next prime
            firstprimeidx++;
        } while (isComposite[firstprimeidx]);
    }
}

/*
Main function
Process command line arguments and print the sieved result
*/
int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3)
        print_usage_and_exit(INVALID_ARGCOUNT, argv[0]);

    int max_prime;  // the upper limit read from command line
    int width = 0;  // width of each column while printing
    int break_at = 10;
    try {
        max_prime = std::stoi(argv[1]);
        width     = strlen(argv[1]);
        if (argc == 3)
        {
            break_at = std::stoi(argv[2]);
            if (break_at < 0)
                max_prime = -1;
            else if (break_at == 0)
                width = 0;
        }
    } catch (...) {
        max_prime = -1;
    }
    
    if (max_prime < 2)
    {
        std::cout << "Invalid input!\n";
        print_usage_and_exit(INVALID_INPUT, argv[0]);
    }
    else if (max_prime == 2)
    {
        std::cout << "2\n";
        return 0;
    }
    else
    {
        std::vector<bool> isComposite(primeToIndex(max_prime) + 1);
        sieve(isComposite);

        std::cout << std::setw(width + 1) << "2 " << (break_at == 1 ? "\n" : "");
        
        unsigned count = 1;
        for (unsigned i = 0; i < isComposite.size(); i++)
        {
            if (!isComposite[i])
            {
                std::cout << std::setw(width) << indexToPrime(i) << ' ';
                if (break_at && (++count >= break_at))
                {
                    count = 0;
                    std::cout << '\n';
                }
            }
        }

        std::cout << '\n';
    }
    
    return 0;
}
