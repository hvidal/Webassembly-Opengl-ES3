#ifndef _WINDOW_H
#define _WINDOW_H

#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#include <functional>
#include "Log.h"

class Window {
    struct GLFWWindowDeleter {
        void operator()(GLFWwindow* w) {
            glfwDestroyWindow(w);
            glfwTerminate();
        }
    };

    std::unique_ptr<GLFWwindow, GLFWWindowDeleter> window;

    static void error(int error, const char* msg) {
        Log::error("Error: %s", msg);
    }

public:
    Window(uint32_t width, uint32_t height, const char* title) {
        glfwSetErrorCallback(Window::error);

        if (!glfwInit()) {
            Log::error("Faileid to initialize GLFW");
            emscripten_force_exit(EXIT_FAILURE);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        GLFWwindow* w = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!w) {
            Log::error("Failed to create GLFW window");
            glfwTerminate();
            emscripten_force_exit(EXIT_FAILURE);
        }
        window.reset(w);
        glfwMakeContextCurrent(window.get());
    }

    void update() const {
        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }

    std::pair<uint32_t, uint32_t> getSize() const {
        int w, h;
        glfwGetFramebufferSize(window.get(), &w, &h);
        return { w, h };
    }

    float getAspectRatio() const {
        auto [width, height] = getSize();
        return width / static_cast<float>(height);
    }
};


#endif