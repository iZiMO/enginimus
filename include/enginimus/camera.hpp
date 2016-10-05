//
//  camera.hpp
//  gol
//
//  Created by Joel Schmidt on 21/09/2016.
//  Copyright © 2016 Joel Schmidt. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

class Camera {
    
    bool first = true;
    
    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    
    int lastX = 0;
    int lastY = 0;
    GLfloat pitch = 0.f;
    GLfloat yaw = -90.f;
    
public:
    
    void onMouseMoved(int xpos, int ypos) {
        if(first) // this bool variable is initially set to true
        {
            lastX = xpos;
            lastY = ypos;
            first = false;
        }
        
        GLfloat xOffset = xpos - lastX;
        GLfloat yOffset = lastY - ypos;
        
        lastX = xpos;
        lastY = ypos;
        
        GLfloat sensitivity = 0.05f;
        xOffset *= sensitivity;
        yOffset *= sensitivity;
        
        yaw += xOffset;
        pitch += yOffset;
        
        if(pitch > 89.0f) {
            pitch =  89.0f;
        }
        if(pitch < -89.0f) {
            pitch = -89.0f;
        }
        
        glm::vec3 front;
        front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        front.y = sin(glm::radians(pitch));
        front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        cameraFront = glm::normalize(front);
    }
    
    glm::mat4 getView(bool* keys, GLfloat deltaTime) {
        GLfloat cameraSpeed = 5.0f * deltaTime;
        if(keys[GLFW_KEY_W]) {
            cameraPos += cameraSpeed * cameraFront;
        }
        if(keys[GLFW_KEY_S]) {
            cameraPos -= cameraSpeed * cameraFront;
        }
        if(keys[GLFW_KEY_A]) {
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        }
        if(keys[GLFW_KEY_D]) {
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        }
        
        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        return view;
    }
};

#endif /* camera_hpp */
