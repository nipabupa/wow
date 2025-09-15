#include "imgui.h"
#include "style.h"

// Our state
bool show_demo_window = true;
bool show_another_window = false;


void Draw() {
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("我很好");

    ImGui::Title("你好");
    ImGui::Checkbox("Demo Window", &show_demo_window);
    ImGui::Checkbox("Another Window", &show_another_window);
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    if (ImGui::Button("Button1")) {
        counter++;
    }
    if (ImGui::PrimaryButton("Button2")) {
        counter++;
    }
    if (ImGui::DangerButton("Button3")) {
        counter++;
    }
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);
    ImGui::End();
 
    if(show_demo_window) {
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }
}
