//
// Created by Joel Schmidt on 6/10/2016.
//

#ifndef ENGINIMUS_RENDER_SYSTEM_H
#define ENGINIMUS_RENDER_SYSTEM_H

#include <vector>

#include <enginimus/render/shader.h>
#include <enginimus/render/camera.hpp>
#include <enginimus/entity/entity_manager.hpp>
#include <enginimus/component/render_component.hpp>
#include <enginimus/component/transform_component.hpp>

class GLFWwindow;

class RenderSystem {
public:
    int init(const int windowWidth, const int windowHeight, const char* title);
    void setCamera(std::unique_ptr<Camera> camera) { this->camera = std::move(camera); }
    GLFWwindow* getWindow() { return window; }
    void inspect() const;
    void render(EntityManager&);

    void renderComponent(RenderComponent&, TransformComponent&);
private:
    GLFWwindow *window;
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Camera> camera;
    int width;

    int height;
    void prepareFrame() const;
    void renderMesh(const Shader&, const Mesh&, const glm::mat4&) const;
};

#endif //ENGINIMUS_RENDER_SYSTEM_H
