#include <functional>
#include <glad/glad.h>

#include <wolf/gui/gui.hpp>
#include <wolf/glfw/glfw.hpp>

namespace Wolf::GLFW{

    void GLFWTerminate(std::function<void(void)> terminationHandler){
        terminationHandler();
        glfwTerminate();
    }

    void GLFWInit(const Wolf::GLFW::GLFWInitConfiguration& initConfiguration){

        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, initConfiguration.mVersion.major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, initConfiguration.mVersion.minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
    #endif

    }
    
    GLFWwindow* GLFWCreateWindow(const Wolf::GLFW::GLFWWindowConfiguration& windowConfiguration){

            // glfw window creation
            // --------------------
        Wolf::GLFW::pWindow = glfwCreateWindow(
            windowConfiguration.mSize.width, 
            windowConfiguration.mSize.height, 
            windowConfiguration.mWindowTitle.c_str(), 
            nullptr, 
            nullptr);

        if (pWindow == nullptr)
        {
            //std::cout << "Failed to create GLFW window" << std::endl;
            Wolf::GLFW::GLFWTerminate();
            return nullptr;
        }

        glfwMakeContextCurrent(pWindow);
        glfwSetFramebufferSizeCallback(pWindow, windowConfiguration.mFrameBufferSizeCallBack);
        glfwSetCursorPosCallback(pWindow, windowConfiguration.mMouseCallBack);
        glfwSetScrollCallback(pWindow, windowConfiguration.mScrollCallBack);

        // tell GLFW to capture our mouse
        glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            //std::cout << "Failed to initialize GLAD" << std::endl;
            Wolf::GLFW::GLFWTerminate();
            return nullptr;
        }

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Setup Dear ImGui Context: tell whos the window (GLFW) and what's the GLSL version.
        Wolf::GUIUtil::setupGuiContext(pWindow, "#version 330");

        return pWindow;
    }

    void processInput(GLFWwindow *window)
    {

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        /*if (!guiMode){

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                camera.ProcessKeyboard(FORWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                camera.ProcessKeyboard(BACKWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                camera.ProcessKeyboard(LEFT, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                camera.ProcessKeyboard(RIGHT, deltaTime);
        }

        if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && !blinnKeyPressed) 
        {
            blinn = !blinn;
            blinnKeyPressed = true;
            guiText = blinn ? blinnString.data() : phongString.data();

        }
        if (glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE) 
        {
            blinnKeyPressed = false;
        }
        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS && !guiModeKeyPressed) 
        {
            guiMode = !guiMode;
            guiModeKeyPressed = true;
        // tell GLFW to capture our mouse
            glfwSetInputMode(window, GLFW_CURSOR, guiMode ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

        }
        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_RELEASE) 
        {
            guiModeKeyPressed = false;
        }

        glfwGetCursorPos(window, &cursorPos[0], &cursorPos[1]);   
        */
    }

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
    void framebuffer_size_callback(GLFWwindow* , int width, int height)
    {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
        /*window_size[0] = width;
        window_size[1] = height;*/
    //glViewport(0, 0, width, height);
    }

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
    void mouse_callback(GLFWwindow*, double xpos, double ypos)
    {
        /*if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;

        if (!guiMode){
            camera.ProcessMouseMovement(xoffset, yoffset);
        }*/
    }

    // glfw: whenever the mouse scroll wheel scrolls, this callback is called
    // ----------------------------------------------------------------------
    void scroll_callback(GLFWwindow*, double, double yoffset)
    {
        //camera.ProcessMouseScroll(yoffset);
    }

}

