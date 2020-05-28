#ifndef _WOLF_GLFW_
#define _WOLF_GLFW_

#include <GLFW/glfw3.h>
#include <string>
namespace Wolf {
    namespace OGLUtil{
        struct GLFWInitConfiguration{
            struct {
                unsigned int major{3};
                unsigned int minor{3};
            }mVersion;
            struct {
                unsigned int width{800};
                unsigned int height{600};
            }mSize;
            std::string mWindowTitle{"WolfEngine"};
            GLFWframebuffersizefun mFrameBufferSizeCallBack;
            GLFWcursorposfun mMouseCallBack;
            GLFWscrollfun mScrollCallBack;
        };
        void GLFWTerminate(std::function<void(void)> terminationHandler = [](){});
        GLFWwindow* GLFWInit(const Wolf::OGLUtil::GLFWInitConfiguration& initConfiguration);
    }    
}


#endif

