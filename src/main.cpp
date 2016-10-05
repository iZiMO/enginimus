//
//  main.cpp
//  gol
//
//  Created by Joel Schmidt on 30/08/2016.
//  Copyright © 2016 Joel Schmidt. All rights reserved.
//

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

// Matrix / vector maths library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Image loader
#include <SOIL.h>

#include <iostream>
#include <fstream>

#include <enginimus/shader.h>
#include <enginimus/camera.hpp>
#include <enginimus/model.hpp>

const uint WINDOW_WIDTH = 800;
const uint WINDOW_HEIGHT = 600;

bool toggle = true;
int rotX = 0;
int rotY = 0;

bool keys[1024];
double deltaTime = 0.0f;
double lastFrame = 0.0f;

Camera camera;

// Is called whenever a key is pressed/released via GLFW
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (action == GLFW_PRESS) {
        keys[key] = true;
    } else if (action == GLFW_RELEASE) {
        keys[key] = false;
    }
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key == GLFW_KEY_T && action == GLFW_PRESS) {
        toggle = !toggle;
    }
    
}

// controls the cube, other controls delegated to Camera
void doMovement() {
    
    if (keys[GLFW_KEY_UP]) {
        rotX += 1;
    }
    if (keys[GLFW_KEY_DOWN]) {
        rotX -= 1;
    }
    if (keys[GLFW_KEY_LEFT]) {
        rotY -= 1;
    }
    if (keys[GLFW_KEY_RIGHT]) {
        rotY += 1;
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    camera.onMouseMoved(xpos, ypos);
}


void inspectGl() {
    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
}

int main()
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Create window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GOL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Init GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    
    inspectGl();
    
    // Show window
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    glEnable(GL_DEPTH_TEST);
    
    // Set the required callback functions
    glfwSetKeyCallback(window, keyCallback);
    
    // Capture mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    
    // create shaders
    Shader shader ("shaders/default.vert",
                   "shaders/default.frag");

    Model box ("assets/Crate/Crate1.obj");
    box.model = glm::translate(box.model, glm::vec3(-5.0f, 0.0f, 0.0f));
    Model dude ("assets/nanosuit.obj");
    
    // Game loop
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        doMovement();
        
        glClearColor(0.1f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shader.use();
        
        //std::cout << glfwGetTime() << std::endl;
        // Transforms Vclip = Mprojection * Mview * Mmodel * Mlocal
//        glm::mat4 model;
//        model = glm::rotate(model, glm::radians(-5.f * rotX), glm::vec3(1.f, 0.f, 0.f));
//        model = glm::rotate(model, glm::radians(5.f * rotY), glm::vec3(0.f, 1.f, 0.f));
        glm::mat4 view = camera.getView(keys, deltaTime);
        glm::mat4 projection = glm::perspectiveFov(glm::radians(45.f), (float)width, (float)height, 0.1f, 100.f);
        
        glUniform1i(glGetUniformLocation(shader.program, "toggle"), toggle);
        glUniformMatrix4fv(glGetUniformLocation(shader.program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        dude.draw(shader);
        box.draw(shader);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
