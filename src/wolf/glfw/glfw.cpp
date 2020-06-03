#include <functional>
#include <glad/glad.h>
#include <wolf/glfw/glfw.hpp>

namespace Wolf {
    namespace OGLUtil {

        void GLFWTerminate(std::function<void(void)> terminationHandler){
            terminationHandler();
            glfwTerminate();
        }

        void GLFWInit(const Wolf::OGLUtil::GLFWInitConfiguration& initConfiguration){

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
        GLFWwindow* GLFWCreateWindow(const Wolf::OGLUtil::GLFWWindowConfiguration& windowConfiguration){
            


            // glfw window creation
            // --------------------
            GLFWwindow* pWindow = glfwCreateWindow(
                windowConfiguration.mSize.width, 
                windowConfiguration.mSize.height, 
                windowConfiguration.mWindowTitle.c_str(), 
                nullptr, 
                nullptr);

            if (pWindow == nullptr)
            {
                //std::cout << "Failed to create GLFW window" << std::endl;
                Wolf::OGLUtil::GLFWTerminate();
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
                Wolf::OGLUtil::GLFWTerminate();
                return nullptr;
            }


            return pWindow;
        }
    }
}
