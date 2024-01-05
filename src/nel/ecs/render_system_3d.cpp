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

    auto meshView = activeScene->handle.view<Transform, Mesh>();
    for(auto [entity, transform, mesh]: meshView.each())
    {
      if(!this->resourceManager->hasResource<RenderObject>(mesh.name))
      {
        this->resourceManager->loadRenderObject(mesh.name, mesh.vertices, mesh.indices);
      }

      RenderObject &renderObject = this->resourceManager->getRenderObject(mesh.name);
      renderObject.bind();

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