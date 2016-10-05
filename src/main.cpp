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

int rotX = 0;
int rotY = 0;

GLfloat vertices[] = {
    // position         // color            // texture
    -1.0f, -1.0f, 0.f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // bottom left
    1.0f, -1.0f, 0.f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    1.0f, 1.0f, 0.f,    0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // top right
    -1.0f, 1.0f, 0.f,   0.5f, 0.2f, 0.1f,   0.0f, 1.0f  // top left
};

const uint STRIDE_SIZE = 5 * sizeof(GL_FLOAT);
GLfloat cube[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};


GLuint indices[] = {
    0, 1, 2,
    2, 3, 0
};

bool keys[1024];
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

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
    
    // Create VBO and VAO
    GLuint VBO, EBO, VAO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    
    // load texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// default wrapping method
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unsigned char* image = SOIL_load_image("textures/noise.png", &width, &height, 0, SOIL_LOAD_RGB);
    std::cout << width << " x " << height << std::endl;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // 1. Bind VAO
    glBindVertexArray(VAO);
    // 2. Copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
    // 3. Then set the vertex attributes pointers
    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE_SIZE, (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // color
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE_SIZE, (GLvoid*)(3 * sizeof(GL_FLOAT)));
//    glEnableVertexAttribArray(1);
    // texture coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, STRIDE_SIZE, (GLvoid*)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);
    // 4. Copy indices into EBO
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 5. Unbind VAO
    glBindVertexArray(0);
    
    // Wireframe mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    Model dude ("assets/nanosuit.obj");
    
    // Game loop
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        doMovement();
        
        glClearColor(0.1f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glBindTexture(GL_TEXTURE_2D, texture);
        
        shader.use();
        
        //std::cout << glfwGetTime() << std::endl;
        // Transforms Vclip = Mprojection * Mview * Mmodel * Mlocal
        glm::mat4 model;
        model = glm::rotate(model, glm::radians(-5.f * rotX), glm::vec3(1.f, 0.f, 0.f));
        model = glm::rotate(model, glm::radians(5.f * rotY), glm::vec3(0.f, 1.f, 0.f));
        
        glm::mat4 view = camera.getView(keys, deltaTime);
        
        glm::mat4 projection;
        projection = glm::perspectiveFov(glm::radians(45.f), (float)width, (float)height, 0.1f, 100.f);
        
        
        GLuint modelLoc = glGetUniformLocation(shader.program, "model");
        GLuint viewLoc = glGetUniformLocation(shader.program, "view");
        GLuint projectionLoc = glGetUniformLocation(shader.program, "projection");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        dude.draw(shader);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }
    
    // clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}
