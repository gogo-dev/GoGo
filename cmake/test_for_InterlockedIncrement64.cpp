#include <windows.h>

int main()
{
	unsigned long long v = 0;
	InterlockedIncrement64(&v);

	return 0;
}
