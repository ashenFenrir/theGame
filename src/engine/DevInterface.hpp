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

    static bool wireframe;

    DevInterface() = default;
    
    static bool init();
    static void update();
    static void render();
    static void processEvent(const SDL_Event *event);
};

