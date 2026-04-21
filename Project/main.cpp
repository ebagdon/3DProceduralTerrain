#define STB_IMAGE_IMPLEMENTATION

#include "GraphicsManager.h"

int main()
{
	// create graphics manager
	GraphicsManager graphicsManager = GraphicsManager();

	// loop while the program is still running
	while (graphicsManager.ProgramRunning())
	{
		// run the graphics manager to handle graphics
		graphicsManager.Run();
	}

	return 0;
}