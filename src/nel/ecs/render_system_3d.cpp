#include "render_system_3d.hpp"

RenderSystem3D::RenderSystem3D(SceneManager *sceneManager, ResourceManager *resourceManager, CameraSystem *cameraSystem)
{
  this->sceneManager = sceneManager;
  this->resourceManager = resourceManager;
  this->cameraSystem = cameraSystem;
}

void RenderSystem3D::render()
{
  Scene *activeScene = this->sceneManager->activeScene;


  if(activeScene)
  {
    Shader &defaultShader = this->resourceManager->getShader("default");
    defaultShader.use();

    auto lightView = activeScene->handle.view<Transform, Light>();
    for(auto [entity, transform, light] : lightView.each())
    {
      if(light.type == Light::DIRECTIONAL)
      {
        glm::mat4 rotated = glm::mat4(1.0f);
        glm::mat4 rotationMatrix = glm::eulerAngleYXZ(glm::radians(transform.rotation.y), glm::radians(transform.rotation.x), glm::radians(transform.rotation.z));
        glm::vec3 direction = glm::vec3(rotationMatrix * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)); // Use the forward vector

        defaultShader.setFloat("light.direction", glm::normalize(direction));
        defaultShader.setFloat("light.ambient", light.ambient);
        defaultShader.setFloat("light.diffuse", light.diffuse);
        defaultShader.setFloat("light.specular", light.specular);
      }
    }

    auto meshView = activeScene->handle.view<Transform, Mesh, Material>();
    for(auto [entity, transform, mesh, material]: meshView.each())
    {
      if(!this->resourceManager->hasResource<RenderObject>(mesh.name))
      {
        this->resourceManager->loadRenderObject(mesh.name, mesh.vertices, mesh.indices);
      }

      RenderObject &renderObject = this->resourceManager->getRenderObject(mesh.name);
      renderObject.bind();

      if(material.diffuseTexture)
      {
        material.diffuseTexture.bind();
        defaultShader.setInt("material.diffuseTexture", 0);
      }
      else
      {
        defaultShader.setFloat("material.diffuseColor", material.diffuseColor);
      }

      defaultShader.setInt("material.hasTexture", material.diffuseTexture);

      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, transform.position);
      // model = glm::toMat4(glm::quat(transform.rotation));
      model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
      model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
      model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
      model = glm::scale(model, transform.scale);

      defaultShader.setMatrix("projectionView", this->cameraSystem->projectionMatrix * this->cameraSystem->viewMatrix);
      defaultShader.setMatrix("model", model);

      renderObject.render(mesh.indices.size());
    }
  }
}