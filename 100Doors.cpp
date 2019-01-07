#include <iostream>

using std::cout;
constexpr uint32_t numDoors = 100;

static void doTheToggles(bool *arr, size_t step)
{
	for (size_t i = step; i < numDoors; i += step)
		arr[i] = !arr[i];
}

static void doTheEntireThing(bool *arr)
{
	for (size_t i = 1; i < numDoors; ++i)
		doTheToggles(arr, i);
}

static void displayDoors(bool *arr)
{
	for (size_t i = 0; i < numDoors; ++i)
	{
		cout << "Door #" << i << " is ";
		if (arr[i])
			cout << "opened";
		else
			cout << "closed";
		cout << '\n';
	}
}

int main()
{
	bool arr[numDoors] = { false };
	
	doTheEntireThing(arr);
	
	displayDoors(arr);
	
}
	