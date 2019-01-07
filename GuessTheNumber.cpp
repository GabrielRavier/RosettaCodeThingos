#include <iostream>
#include <random>
#include <chrono>

using std::cout;
using std::cin;
using std::mt19937;
using std::enable_if;
using std::seed_seq;
using std::uniform_int_distribution;
using std::random_device;

template<class T = mt19937, size_t N = T::state_size>
auto seededRandomEngine() -> typename enable_if<!!N, T>::type
{
	random_device rd;
	if (rd.entropy() != 0)
	{
		seed_seq seeds
		{
			rd(),
			rd(),
			rd(),
			rd(),
			rd(),
			rd(),
			rd(),
			rd(),
		};
		T seededEngine(seeds);
		return seededEngine;
	}
	srand(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
	seed_seq seeds
	{
		static_cast<int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()),
		static_cast<int>(std::chrono::high_resolution_clock::now().time_since_epoch().count() >> 32),
		rand(),
		rand(),
		rand(),
		rand(),
		rand(),
		rand(),
	};
	T seededEngine(seeds);
	return seededEngine;
}

// return random number between mi and ma
int32_t random(int32_t minimum, int32_t maximum)
{
	static thread_local mt19937 engine(seededRandomEngine());

	// Distribution goes from 0 to TYPE_MAX by default
	static uniform_int_distribution<int32_t> distrInt;

	return (minimum + (distrInt(engine) % (maximum - minimum + 1)));
}

int main()
{
	int n = random(1, 10);
	
	cout << "Try to guess a number between 1 and 10\n";

	while (1)
	{
		int guess = 0;
		cin >> guess;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		if (guess == n)
		{
			cout << "Correct !";
			return 0;
		}
		
		cout << "Wrong number. Retry";
	}
}