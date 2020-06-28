#include <emscripten/emscripten.h>

#include <GLES3/gl3.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory>

#include "Utils/Window.h"
#include "LinearMath/Matrix4x4.h"
#include "Render/Shader.h"
#include "Scene/Triangle.h"

std::unique_ptr<Window> window = std::make_unique<Window>(1024, 768, "Webgl");

Matrix4x4 model, view, mvp;

std::unique_ptr<Triangle> triangle = std::make_unique<Triangle>();

static void generate_frame() {
    auto [width, height] = window->getSize();
    float ratio = width / static_cast<float>(height);

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    // float angle = static_cast<float>(glfwGetTime());
    view.lookAt({0, 0, -15}, {0,0,0}, {0,1,0});
    mvp.perspective(50.f, ratio, 1.f, 1000.f);
    mvp.multiplyRight(view);

    triangle->render(mvp);

    window->update();
}

int main() {
    Log::debug("GL_VERSION %s", glGetString(GL_VERSION));

    emscripten_set_main_loop(generate_frame, 0, 0);
}
