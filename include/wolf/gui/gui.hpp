#ifndef _WOLF_GUI_
#define _WOLF_GUI_

#include <string>
#include <GLFW/glfw3.h>

namespace Wolf::GUIUtil {
    void setupGuiContext(GLFWwindow* pWind, const std::string glsl_version);
    void drawGui();
    void drawGuiExtended(
        char* guiText,
        bool* pUseLight,
        float* pClearColor,
        int* pColSelector,
        int* pRowSelector,
        double* pCursorPos,
        int* pWindowSize);
    void renderGui();
    void renderGuiOpenGL();
}

#endif //_WOLF_GUI_