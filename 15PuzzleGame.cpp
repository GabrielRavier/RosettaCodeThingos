#include <iostream>
#include <string>
#include <cstdint>
#include <array>
#include <random>
#include <chrono>

using std::cout;
using std::cin;
using std::array;
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

constexpr uint32_t nRows = 4;
constexpr uint32_t nColumns = 4;
constexpr uint32_t nShuffles = 100;

enum class Moves
{
	up = 0,
	down = 1,
	left = 2,
	right = 3,
	min = 0,
	max = 3,
};

class Game
{
public:
	Game()
	{
		this->setup();
	}

	bool update(Moves move)
	{
		int32_t i = m_holeRow;
		int32_t j = m_holeColumn;
		
		switch (move)
		{
		case Moves::up:
			--i;
			break;
			
		case Moves::down:
			++i;
			break;
			
		case Moves::left:
			--j;
			break;
			
		case Moves::right:
			++j;
			break;
		}	
		
		if ((size_t)i < m_cells.size() && (size_t)j < m_cells.size())
		{
			m_cells[m_holeRow][m_holeColumn] = m_cells[i][j];
			m_cells[i][j] = 0;
			
			m_holeRow = i;
			m_holeColumn = j;
			return true;
		}
		return false;
	}
	
	void setup()
	{
		for (size_t i = 0; i < m_cells.size(); ++i)
			for (size_t j = 0; j < m_cells.size(); ++j)
				m_cells[i][j] = i * m_cells[0].size() + j + 1;
		
		m_cells[m_cells.size() - 1][m_cells[0].size() - 1] = 0;
		m_holeRow = m_cells.size() - 1;
		m_holeColumn = m_cells[0].size() - 1;
		
		uint32_t k = 0;
		while (k < nShuffles)
			k += this->update((Moves)random((int32_t)Moves::min, (int32_t)Moves::max));
	}
	
	bool isFinished()
	{
		size_t k = 1;
		for (size_t i = 0; i < m_cells.size(); ++i)
			for (size_t j = 0; j < m_cells[0].size(); ++j)
				if ((k < m_cells.size() * m_cells[0].size()) && (m_cells[i][j] != k++))
					return false;
		return true;
	}
	
	void showBoard()
	{
		cout << "\n\n";
		
		for (uint32_t i = 0; i < m_cells.size(); ++i)
		{
			cout << '+';
			for (uint32_t j = 0; j < m_cells[0].size(); ++j)
				cout << "----+";
			cout << '\n';
			
			for (uint32_t j = 0; j < m_cells[0].size(); ++j)
			{
				auto tmp = m_cells[i][j];
				cout << "| ";
				if (tmp < 10)
					cout << ' ';
				if (!tmp)
					cout << "  ";
				else
					cout << tmp << ' ';
			}
			cout << "|\n";
		}
		cout << '+';
		for (uint32_t i = 0; i < m_cells[0].size(); ++i)
			cout << "----+";
		cout << '\n';
	}
	
private:
	uint32_t m_holeRow;
	uint32_t m_holeColumn;
	std::array<std::array<uint32_t, nColumns>, nRows> m_cells;
};

Moves getMove()
{
	char c;
	
	for (;;)
	{
		cout << "Enter U/D/L/R : ";
		cin >> c;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		switch (c)
		{
		case 'd':
		case 'D':
			return Moves::up;
			
		case 'u':
		case 'U':
			return Moves::down;
			
		case 'r':
		case 'R':
			return Moves::left;
			
		case 'l':
		case 'L':
			return Moves::right;
		}
	}
}

void pause()
{
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin.get();
}

int main(int /*argc*/, char * /*argv*/[])
{
	Game game;
	
	while (game.isFinished())
		game.setup();
	
	game.showBoard();
	
	while (!game.isFinished())
	{
		game.update(getMove());
		game.showBoard();
	}

	cout << "\nYou Win\n";
	pause();
	
	return EXIT_SUCCESS;
}