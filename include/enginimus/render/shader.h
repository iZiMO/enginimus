//
//  shader.h
//  gol
//
//  Created by Joel Schmidt on 3/09/2016.
//  Copyright © 2016 Joel Schmidt. All rights reserved.
//

#ifndef ENGINIMUS_SHADER_H
#define ENGINIMUS_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h> // Include glew to get all the required OpenGL headers

class Shader
{
public:
    // The program ID
    GLuint program;
    
    void compileShader(GLuint shaderId, const char* shaderSource, const char* shaderDesc) {
        glShaderSource(shaderId, 1, &shaderSource, NULL);
        glCompileShader(shaderId);
        
        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::" << shaderDesc << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }
    
    void createProgram(GLuint vertexShader, GLuint fragmentShader) {
        this->program = glCreateProgram();
        glAttachShader(this->program, vertexShader);
        glAttachShader(this->program, fragmentShader);
        glLinkProgram(this->program);
        // Print linking errors if any
        GLint success;
        GLchar infoLog[512];
        glGetProgramiv(this->program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(this->program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }
    
    // Constructor reads and builds the shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
    {
        // 1. Retrieve the vertex/fragment source code from filePath
        std::string vertexCode, fragmentCode;
        std::ifstream vShaderFile, fShaderFile;
        // ensures ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::badbit);
        try
        {
            // Open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // Read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // Convert stream into GLchar array
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch(std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const GLchar* vShaderCode = vertexCode.c_str();
        const GLchar* fShaderCode = fragmentCode.c_str();
        
        // vertex shader
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        compileShader(vertexShader, vShaderCode, "VERTEX");
        
        // fragment shader
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        compileShader(fragmentShader, fShaderCode, "FRAGMENT");
        
        // Shader Program
        createProgram(vertexShader, fragmentShader);
        
        // Delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    
    // Use the program
    void use() {
        glUseProgram(this->program);
    }
};

#endif /* ENGINIMUS_SHADER_H */
