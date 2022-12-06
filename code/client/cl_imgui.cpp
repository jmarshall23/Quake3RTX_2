// cl_imgui.cpp
//

#include "../qcommon/engine.hpp"

#include <d3d12.h>
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx12.h"

#include <vector>
#include <string>

bool g_ImGuiIsInit = false;

std::vector<std::string> newConLines;

void Imgui_Printf(const char* v)
{
    newConLines.push_back(v);
}

// Map VK_xxx to ImGuiKey_xxx.
static ImGuiKey ImGui_ImplWin32_VirtualKeyToImGuiKey(WPARAM wParam)
{
    switch (wParam)
    {
    case VK_TAB: return ImGuiKey_Tab;
    case VK_LEFT: return ImGuiKey_LeftArrow;
    case VK_RIGHT: return ImGuiKey_RightArrow;
    case VK_UP: return ImGuiKey_UpArrow;
    case VK_DOWN: return ImGuiKey_DownArrow;
    case VK_PRIOR: return ImGuiKey_PageUp;
    case VK_NEXT: return ImGuiKey_PageDown;
    case VK_HOME: return ImGuiKey_Home;
    case VK_END: return ImGuiKey_End;
    case VK_INSERT: return ImGuiKey_Insert;
    case VK_DELETE: return ImGuiKey_Delete;
    case VK_BACK: return ImGuiKey_Backspace;
    case VK_SPACE: return ImGuiKey_Space;
    case VK_RETURN: return ImGuiKey_Enter;
    case VK_ESCAPE: return ImGuiKey_Escape;
    case VK_OEM_7: return ImGuiKey_Apostrophe;
    case VK_OEM_COMMA: return ImGuiKey_Comma;
    case VK_OEM_MINUS: return ImGuiKey_Minus;
    case VK_OEM_PERIOD: return ImGuiKey_Period;
    case VK_OEM_2: return ImGuiKey_Slash;
    case VK_OEM_1: return ImGuiKey_Semicolon;
    case VK_OEM_PLUS: return ImGuiKey_Equal;
    case VK_OEM_4: return ImGuiKey_LeftBracket;
    case VK_OEM_5: return ImGuiKey_Backslash;
    case VK_OEM_6: return ImGuiKey_RightBracket;
    case VK_OEM_3: return ImGuiKey_GraveAccent;
    case VK_CAPITAL: return ImGuiKey_CapsLock;
    case VK_SCROLL: return ImGuiKey_ScrollLock;
    case VK_NUMLOCK: return ImGuiKey_NumLock;
    case VK_SNAPSHOT: return ImGuiKey_PrintScreen;
    case VK_PAUSE: return ImGuiKey_Pause;
    case VK_NUMPAD0: return ImGuiKey_Keypad0;
    case VK_NUMPAD1: return ImGuiKey_Keypad1;
    case VK_NUMPAD2: return ImGuiKey_Keypad2;
    case VK_NUMPAD3: return ImGuiKey_Keypad3;
    case VK_NUMPAD4: return ImGuiKey_Keypad4;
    case VK_NUMPAD5: return ImGuiKey_Keypad5;
    case VK_NUMPAD6: return ImGuiKey_Keypad6;
    case VK_NUMPAD7: return ImGuiKey_Keypad7;
    case VK_NUMPAD8: return ImGuiKey_Keypad8;
    case VK_NUMPAD9: return ImGuiKey_Keypad9;
    case VK_DECIMAL: return ImGuiKey_KeypadDecimal;
    case VK_DIVIDE: return ImGuiKey_KeypadDivide;
    case VK_MULTIPLY: return ImGuiKey_KeypadMultiply;
    case VK_SUBTRACT: return ImGuiKey_KeypadSubtract;
    case VK_ADD: return ImGuiKey_KeypadAdd;
   // case IM_VK_KEYPAD_ENTER: return ImGuiKey_KeypadEnter;
    case VK_LSHIFT: return ImGuiKey_LeftShift;
    case VK_LCONTROL: return ImGuiKey_LeftCtrl;
    case VK_LMENU: return ImGuiKey_LeftAlt;
    case VK_LWIN: return ImGuiKey_LeftSuper;
    case VK_RSHIFT: return ImGuiKey_RightShift;
    case VK_RCONTROL: return ImGuiKey_RightCtrl;
    case VK_RMENU: return ImGuiKey_RightAlt;
    case VK_RWIN: return ImGuiKey_RightSuper;
    case VK_APPS: return ImGuiKey_Menu;
    case '0': return ImGuiKey_0;
    case '1': return ImGuiKey_1;
    case '2': return ImGuiKey_2;
    case '3': return ImGuiKey_3;
    case '4': return ImGuiKey_4;
    case '5': return ImGuiKey_5;
    case '6': return ImGuiKey_6;
    case '7': return ImGuiKey_7;
    case '8': return ImGuiKey_8;
    case '9': return ImGuiKey_9;
    case 'A': return ImGuiKey_A;
    case 'B': return ImGuiKey_B;
    case 'C': return ImGuiKey_C;
    case 'D': return ImGuiKey_D;
    case 'E': return ImGuiKey_E;
    case 'F': return ImGuiKey_F;
    case 'G': return ImGuiKey_G;
    case 'H': return ImGuiKey_H;
    case 'I': return ImGuiKey_I;
    case 'J': return ImGuiKey_J;
    case 'K': return ImGuiKey_K;
    case 'L': return ImGuiKey_L;
    case 'M': return ImGuiKey_M;
    case 'N': return ImGuiKey_N;
    case 'O': return ImGuiKey_O;
    case 'P': return ImGuiKey_P;
    case 'Q': return ImGuiKey_Q;
    case 'R': return ImGuiKey_R;
    case 'S': return ImGuiKey_S;
    case 'T': return ImGuiKey_T;
    case 'U': return ImGuiKey_U;
    case 'V': return ImGuiKey_V;
    case 'W': return ImGuiKey_W;
    case 'X': return ImGuiKey_X;
    case 'Y': return ImGuiKey_Y;
    case 'Z': return ImGuiKey_Z;
    case VK_F1: return ImGuiKey_F1;
    case VK_F2: return ImGuiKey_F2;
    case VK_F3: return ImGuiKey_F3;
    case VK_F4: return ImGuiKey_F4;
    case VK_F5: return ImGuiKey_F5;
    case VK_F6: return ImGuiKey_F6;
    case VK_F7: return ImGuiKey_F7;
    case VK_F8: return ImGuiKey_F8;
    case VK_F9: return ImGuiKey_F9;
    case VK_F10: return ImGuiKey_F10;
    case VK_F11: return ImGuiKey_F11;
    case VK_F12: return ImGuiKey_F12;
    default: return ImGuiKey_None;
    }
}

void CL_ImGuiKeyInput(int keyDown, unsigned int key)
{
    ImGuiIO& io = ImGui::GetIO();

    if (cls.keyCatchers & KEYCATCH_CONSOLE) {
        io.KeyShift = false;
        io.AddKeyEvent(ImGui_ImplWin32_VirtualKeyToImGuiKey(key), keyDown != 0);

        if (keyDown)
        {
            if (key == 191)
            {
                key = '/';
            }
            if (key == 189)
            {
                key = '_';
            }
            io.AddInputCharacter(tolower(key));
        }
    }
}

void CL_ImGuiMouseInput(int buttonDown, int key)
{
    ImGuiIO& io = ImGui::GetIO();

    if (cls.keyCatchers & KEYCATCH_CONSOLE) {
        io.AddMouseButtonEvent(key, buttonDown != 0);
    }
}

/*
=================
CL_InitImGui
=================
*/
void CL_InitImGui(void* window_handle, void* graphicsDevice, void* graphicsDeviceDescriptorHeap) {
    ID3D12DescriptorHeap* g_pd3dSrvDescHeap = (ID3D12DescriptorHeap * )graphicsDeviceDescriptorHeap;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(window_handle);
    ImGui_ImplDX12_Init((ID3D12Device *)graphicsDevice, 3,
        DXGI_FORMAT_R8G8B8A8_UNORM, g_pd3dSrvDescHeap,
        g_pd3dSrvDescHeap->GetCPUDescriptorHandleForHeapStart(),
        g_pd3dSrvDescHeap->GetGPUDescriptorHandleForHeapStart());

    g_ImGuiIsInit = true;
}

void CL_RenderImGuiFrame(void)
{
    if (!g_ImGuiIsInit)
        return;

    // Start the Dear ImGui frame
    ImGui_ImplDX12_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // ImGui rendering happens in here.
    if(com_showfps->integer > 0)
    {
        ImGui::SetNextWindowPos(ImVec2(cls.glconfig.vidWidth - 300, 50));
        ImGui::SetNextWindowSize(ImVec2(200, 100));
        ImGui::Begin("Framerate");
        ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        renderStats_t stats;
        re.R_GetFrameStats(&stats);

        ImGui::Text("NumRenderLights: %d", stats.numRenderLights);
        ImGui::Text("NumRenderedEntities: %d", stats.numRenderedEntities);

        ImGui::End();
    }

    if (cls.keyCatchers & KEYCATCH_CONSOLE) {
        static char console_buffer[4096];

        ImGui::SetNextWindowPos(ImVec2(200, 200));
        ImGui::SetNextWindowSize(ImVec2(800, 600));

        ImGui::Begin("Developer Console");

        const float footerHeightToReserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
        ImGui::BeginChild("ScrollRegion##", ImVec2(0, -footerHeightToReserve), false, 0);

        int startLine = newConLines.size() - 300;
        if (startLine < 0)
            startLine = 0;

        for (int i = startLine; i < newConLines.size(); i++)
        {
            ImGui::PushTextWrapPos();

            ImGui::TextUnformatted(newConLines[i].c_str());

            // Stop wrapping since we are done displaying console items.
            ImGui::PopTextWrapPos();
        }

        ImGui::SetScrollHereY(1.0f);

        ImGui::EndChild();

        ImGui::Separator();

        ImGui::PushItemWidth(-ImGui::GetStyle().ItemSpacing.x * 7);

        ImGui::SetItemDefaultFocus();
        if (ImGui::InputText("Input", &console_buffer[0], sizeof(console_buffer), ImGuiInputTextFlags_EnterReturnsTrue))
        {
            Cbuf_AddText(console_buffer);
            Cbuf_AddText("\n");
            console_buffer[0] = 0;
        }       

        ImGui::End();
    }

    // Rendering
    ImGui::Render();
}

void CL_FinalRenderImGui(void* commandList)
{
    if (!g_ImGuiIsInit)
        return;

    ID3D12GraphicsCommandList* cmdList = (ID3D12GraphicsCommandList *)commandList;

    ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), cmdList);
}