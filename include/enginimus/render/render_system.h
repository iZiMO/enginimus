//
// Created by Joel Schmidt on 6/10/2016.
//

#ifndef ENGINIMUS_RENDER_SYSTEM_H
#define ENGINIMUS_RENDER_SYSTEM_H

#include <vector>

#include <enginimus/render/shader.h>
#include <enginimus/camera.hpp>
#include <enginimus/render/render_component.hpp>


class GLFWwindow;

class RenderSystem {
public:
    int init(const int windowWidth, const int windowHeight, const char* title);
    GLFWwindow* getWindow() { return window; }
    void inspect();

    void render(const Camera &camera);

    void registerComponent(RenderComponent component) { components.push_back(component); }

private:
    GLFWwindow *window;
    Shader* shader;
    int width;
    int height;

    vector<RenderComponent> components;

    void prepareFrame(const Camera& camera);
    void renderComponents() const;
    void renderComponent(const Shader&, const RenderComponent&) const;
    void renderMesh(const Shader&, const Mesh&, const glm::mat4&) const;
};

#endif //ENGINIMUS_RENDER_SYSTEM_H
