#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Object.h"
#include "Shader.h"

enum class CameraType
{
    Perspective,
    Orthographic
};

class Camera : public Object
{
private:
    // En : Camera properties (perspective).
    // Tr : Kamera özellikleri (perspektif).

    float fov, pNear, pFar, aspect;

    // En : Camera properties (orthographic).
    // Tr : Kamera özellikleri (ortografik).

    float left, right, bottom, top, oNear, oFar;

public:
    Camera();
    ~Camera();

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetPerspectiveMatrix() const;
    glm::mat4 GetOrthographicMatrix() const;
    glm::mat4 GetModelMatrix() const;
    void SetPerspective(float fov, float aspect, float near, float far);
    void SetOrthographic(float left, float right, float bottom, float top, float near, float far);
    void SetUniforms(Shader *shader, const char *model = "model", const char *view = "view", const char *projection = "projection", CameraType type = CameraType::Perspective);
};
#endif