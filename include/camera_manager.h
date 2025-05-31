#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H
#include "glm/vec3.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum PositionKeyType
{
    W, A, S, D
};

class CameraManager
{
public:
    CameraManager(const glm::vec3 position, const glm::vec3 front, const glm::vec3 up, float fov,
                  float viewWidth, float viewHeight): _position(position),
                                                      _front(front), _up(up), _fov(fov), _lastX(viewWidth / 2.0f),
                                                      _lastY(viewHeight / 2.0f)
    {
    }

    ~CameraManager() = default;

    void scrollChangeFov(double yOffset);
    void mouseMoveChangeDirection(double xPosIn, double yPosIn);
    void keyboardInputChangePosition(PositionKeyType type, float speed);

    glm::mat4 getProjectionMatrix(int width, int height) const;
    glm::mat4 getViewMatrix() const;

private:
    glm::vec3 _position;
    glm::vec3 _front;
    glm::vec3 _up;
    float _fov;

    bool firstMouse = true;

    // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    float yaw = -90.0f;
    float pitch = 0.0f;
    float _lastX;
    float _lastY;

    float sensitivity = 0.1f; // change this value to your liking
};


#endif //CAMERA_MANAGER_H
