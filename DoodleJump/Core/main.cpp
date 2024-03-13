#include "DoodleJump.h"
#include <string>

int main(int argc, char* argv[])
{
    DoodleJump* game = new DoodleJump();

    int width = 800;
    int height = 600;
    bool bFullscreen = false;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-window" && i + 1 < argc)
        {
            std::string windowSize = argv[i + 1];
            size_t xPos = windowSize.find('x');
            if (xPos != std::string::npos)
            {
                width = std::stoi(windowSize.substr(0, xPos));
                height = std::stoi(windowSize.substr(xPos + 1));
            }
            i++;
        }
        else if (arg == "-fullscreen")
        {
            bFullscreen = true;
        }
    }

    game->setScreenSize(width, height, bFullscreen);

    return run(game);
}