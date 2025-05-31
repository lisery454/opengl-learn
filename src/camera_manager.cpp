#include "camera_manager.h"

#include <stdexcept>

#include "glm/glm.hpp"


void CameraManager::scrollChangeFov(const double yOffset)
{
    _fov -= static_cast<float>(yOffset);
    if (_fov < 1.0f)
        _fov = 1.0f;
    if (_fov > 45.0f)
        _fov = 45.0f;
}

void CameraManager::mouseMoveChangeDirection(const double xPosIn, const double yPosIn)
{
    const auto xPos = static_cast<float>(xPosIn);
    const auto yPos = static_cast<float>(yPosIn);

    if (firstMouse)
    {
        _lastX = xPos;
        _lastY = yPos;
        firstMouse = false;
    }

    float xOffset = xPos - _lastX;
    float yOffset = _lastY - yPos; // reversed since y-coordinates go from bottom to top
    _lastX = xPos;
    _lastY = yPos;


    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = static_cast<float>(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
    front.y = static_cast<float>(sin(glm::radians(pitch)));
    front.z = static_cast<float>(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
    _front = glm::normalize(front);
}

void CameraManager::keyboardInputChangePosition(const PositionKeyType type, const float speed)
{
    switch (type)
    {
    case W:
        _position += speed * _front;
        break;
    case S:
        _position -= speed * _front;
        break;
    case A:
        _position -= glm::normalize(glm::cross(_front, _up)) * speed;
        break;
    case D:
        _position += glm::normalize(glm::cross(_front, _up)) * speed;
        break;
    default: throw std::runtime_error("Key not recognized");
    }
}

glm::mat4 CameraManager::getProjectionMatrix(const int width, const int height) const
{
    return glm::perspective(glm::radians(_fov), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);
}

glm::mat4 CameraManager::getViewMatrix() const
{
    return glm::lookAt(_position, _position + _front, _up);
}
