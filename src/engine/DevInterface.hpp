#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>

class Window;


class DevInterface
{
private:
public:
    static ImGuiIO* io;
    
    static bool show_demo_window;
    static bool show_another_window;

    DevInterface() = default;
    
    static bool init();
    static void update();
    static void render();
};

