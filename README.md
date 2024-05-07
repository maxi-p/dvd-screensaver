# DVD screensaver

## Installation
1. Set the C++ specification to cpp17 ('-std=c++17' if you use CLI)
2. Download SFML (preferably 2.5.1)
3. Add SFML's include folder to your include directory ('-I/...' if you use CLI)
4. Add SFML's lib folder to your library path ('-L/...' if you use CLI)
5. Link the SFML Graphics, Window, and System libraries ('-lsfml-graphics -lsfml-window -lsfml-system' if you use CLI)
6. Download [ImGui](https://github.com/ocornut/imgui)
7. Download [imgui-sfml](https://github.com/SFML/imgui-sfml)
8. Add the ImGui and imgui-sfml folders to your include directory
9. Add ``imgui.cpp``, ``imgui_widgets.cpp``, ``imgui_draw.cpp``, 
 ``imgui_tables.cpp``, and ``imgui-SFML.cpp`` to your build/project
10. Copy the contents of ``imconfig-SFML.h`` to your ``imconfig.h`` file.
11. Link OpenGL to your build
