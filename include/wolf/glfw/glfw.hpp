#ifndef __WOLF_GLFW__
#define __WOLF_GLFW__

#include <GLFW/glfw3.h>
#include <string>
namespace Wolf {
    namespace GLFW{
        static GLFWwindow* pWindow{nullptr};
        struct GLFWInitConfiguration{
            struct {
                unsigned int major{3};
                unsigned int minor{3};
            }mVersion;
        };
        struct GLFWWindowConfiguration{
            struct {
                unsigned int width{800};
                unsigned int height{600};
            }mSize;
            std::string mWindowTitle{"WolfEngine - GLFW Powered"};
            GLFWframebuffersizefun mFrameBufferSizeCallBack;
            GLFWcursorposfun mMouseCallBack;
            GLFWscrollfun mScrollCallBack;
        };
        void GLFWTerminate(std::function<void(void)> terminationHandler = [](){});
        GLFWwindow* GLFWCreateWindow(const Wolf::GLFW::GLFWWindowConfiguration& windowConfiguration);
        void GLFWInit(const Wolf::GLFW::GLFWInitConfiguration& initConfiguration);
        
        //Default Callbacks
        void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
        void processInput(GLFWwindow *window);

    }    
}


#endif

