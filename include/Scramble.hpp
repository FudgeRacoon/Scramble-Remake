#ifndef SCRAMBLE_HPP
#define SCRAMBLE_HPP

#include "Graphics/OpenGL/Debug/OpenGLDebugger.hpp"
#include "Graphics/OpenGL/OpenGLIndexBuffer.hpp"
#include "Graphics/OpenGL/OpenGLShader.hpp"
#include "Graphics/OpenGL/OpenGLTexture.hpp"
#include "Graphics/OpenGL/OpenGLVertexArray.hpp"
#include "Graphics/OpenGL/OpenGLVertexBuffer.hpp"

#include "Graphics/GraphicsContext.hpp"
#include "Graphics/RenderCommand.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/RendererContext.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Sprite.hpp"
#include "Graphics/Texture.hpp"

#include "Events/ApplicationEvent.hpp"
#include "Events/MouseEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/Event.hpp"
#include "Events/EventDispatcher.hpp"
#include "Events/EventHandler.hpp"

#include "Input/InputManager.hpp"
#include "Input/KeyCodes.hpp"
#include "Input/KeyListener.hpp"
#include "Input/MouseCodes.hpp"
#include "Input/MouseListener.hpp"

#include "Physics/BodyType.hpp"
#include "Physics/Bounds.hpp"
#include "Physics/PhysicsSystem.hpp"

#include "Utils/SpriteUtils.hpp"
#include "Utils/Utility.hpp"

#include "Scene/Components/Tag.hpp"
#include "Scene/Components/Transform.hpp"
#include "Scene/Components/SpriteRenderer.hpp"
#include "Scene/Components/RigidBody.hpp"
#include "Scene/Components/BoxCollider.hpp"
#include "Scene/Components/AnimationSystem.hpp"

#include "Scene/Camera.hpp"
#include "SCene/Component.hpp"
#include "Scene/Entity.hpp"
#include "Scene/Registry.hpp"
#include "Scene/RuntimeScene.hpp"
#include "Scene/RuntimeSceneManager.hpp"

#include "Core/ScrambleCore.hpp"

#endif