//
// Created by Joel Schmidt on 6/10/2016.
//

#include <enginimus/render_system.h>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Matrix / vector maths library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <enginimus/render_component.hpp>

using namespace std;

int RenderSystem::init(const int windowWidth, const int windowHeight, const char *title) {
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create window
    window = glfwCreateWindow(windowWidth, windowHeight, title, nullptr, nullptr);
    if (window == nullptr) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Init GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "Failed to initialize GLEW" << endl;
        return -1;
    }

    // Show window
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    // create shaders
    shader = new Shader("shaders/default.vert",
            "shaders/default.frag");
}

void RenderSystem::inspect() {
    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    cout << "Maximum nr of vertex attributes supported: " << nrAttributes << endl;

    // etc..
}

void RenderSystem::render(const Camera &camera) {
    prepareFrame(camera);
    renderComponents();
    glfwSwapBuffers(window);
}

void RenderSystem::prepareFrame(const Camera& camera) {
    glClearColor(0.1f, 0.3f, 0.3f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 view = camera.getView();
    glm::mat4 projection = camera.getProjection(width, height);

    shader->use();
    //glUniform1i(glGetUniformLocation(shader->program, "toggle"), toggle);
    glUniformMatrix4fv(glGetUniformLocation(shader->program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader->program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

void RenderSystem::renderComponents() {
    Shader s = *shader;
    for(vector<RenderComponent>::iterator it = components.begin(); it != components.end(); ++it) {
        it->render(s);
    }
}