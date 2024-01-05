#include "render_system_3d.hpp"

RenderSystem3D::RenderSystem3D(SceneManager *sceneManager, ResourceManager *resourceManager)
{
  this->sceneManager = sceneManager;
  this->resourceManager = resourceManager;
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
      renderObject.render(mesh.indices.size());
    }
  }
}