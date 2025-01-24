#ifndef CAMERA_CPP
#define CAMERA_CPP
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
namespace geo
{
#pragma region Constructors and Destructors
    Camera::Camera()
    {
        fov = 45.0f;
        pNear = 0.1f;
        pFar = 100.0f;
        aspect = 1.0f;

        left = -1.0f;
        right = 1.0f;
        bottom = -1.0f;
        top = 1.0f;
        oNear = 0.1f;
        oFar = 100.0f;

        up = glm::vec3(0, 1, 0);
    }
    Camera::~Camera()
    {
    }
#pragma endregion
#pragma region Getters and Setters
    // En : Returns the view matrix.
    // Tr : Görünüm matrisini döndürür.
    glm::mat4 Camera::GetViewMatrix() const
    {

        return glm::lookAt(position, position + GetFront(), GetUp());
    }
    // En : Returns the perspective matrix.
    // Tr : Perspektif matrisini döndürür.
    glm::mat4 Camera::GetPerspectiveMatrix() const
    {
        return glm::perspective(glm::radians(fov), aspect, pNear, pFar);
    }
    // En : Returns the orthographic matrix.
    // Tr : Ortografik matrisini döndürür.
    glm::mat4 Camera::GetOrthographicMatrix() const
    {
        return glm::ortho(left, right, bottom, top, oNear, oFar);
    }
    // En : Returns the model matrix.
    // Tr : Model matrisini döndürür.
    glm::mat4 Camera::GetModelMatrix() const
    {
        return glm::mat4(1.0f);
    }
    // En : Sets the perspective properties.
    // `fov` : Field of view.
    // `aspect` : Aspect ratio.
    // `near` : Near plane, the closest point to the camera.
    // `far` : Far plane, the farthest point to the camera.
    // Tr : Perspektif özelliklerini ayarlar.
    // `fov` : Görüş alanı.
    // `aspect` : en boy oranı.
    // `near` : Yakın düzlem, kameraya en yakın nokta.
    // `far` : Uzak düzlem, kameraya en uzak nokta.
    void Camera::SetPerspective(float fov, float aspect, float near, float far)
    {
        this->fov = fov;
        this->aspect = aspect;
        pNear = near;
        pFar = far;
    }
    // En : Sets the orthographic properties.
    // `left` : Left plane.
    // `right` : Right plane.
    // `bottom` : Bottom plane.
    // `top` : Top plane.
    // `near` : Near plane, the closest point to the camera.
    // `far` : Far plane, the farthest point to the camera.
    // Tr : Ortografik özellikleri ayarlar.
    // `left` : Sol düzlem.
    // `right` : Sağ düzlem.
    // `bottom` : Alt düzlem.
    // `top` : Üst düzlem.
    // `near` : Yakın düzlem, kameraya en yakın nokta.
    // `far` : Uzak düzlem, kameraya en uzak nokta.
    void Camera::SetOrthographic(float left, float right, float bottom, float top, float near, float far)
    {
        this->left = left;
        this->right = right;
        this->bottom = bottom;
        this->top = top;
        oNear = near;
        oFar = far;
    }
    // En : Sets the uniforms of the camera.
    // `shader` : Shader object.
    // `model` : Model matrix uniform name.
    // `view` : View matrix uniform name.
    // `projection` : Projection matrix uniform name.
    // `type` : Camera type.
    // Tr : Kameranın uniformlarını ayarlar.
    // `shader` : Shader nesnesi.
    // `model` : Model matrisi uniform ismi.
    // `view` : Görünüm matrisi uniform ismi.
    // `projection` : Projeksiyon matrisi uniform ismi.
    // `type` : Kamera tipi.
    void Camera::SetUniforms(Shader *shader, const char *model, const char *view, const char *projection, CameraType type)
    {
        shader->Set(model, GetModelMatrix());
        shader->Set(view, GetViewMatrix());
        switch (type)
        {
        case CameraType::Perspective:
            shader->Set(projection, GetPerspectiveMatrix());
            break;
        case CameraType::Orthographic:
            shader->Set(projection, GetOrthographicMatrix());
            break;
        }
    }
#pragma endregion
}
#endif