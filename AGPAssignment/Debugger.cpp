#include "Debugger.h"

#include <iostream>

namespace Debugging
{
	void OpenConsole()
	{
		if (AllocConsole())
		{
			// redirecting input, output and errors to allocated console
			FILE* fp = nullptr;
			freopen_s(&fp, "CONIN$", "r", stdin);
			freopen_s(&fp, "CONOUT$", "w", stdout);
			freopen_s(&fp, "CONOUT$", "w", stderr);
			std::ios::sync_with_stdio(true);

			std::cout << "Hello Console!" << std::endl;
		}
	}
}
