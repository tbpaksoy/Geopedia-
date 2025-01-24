#ifndef OBJECT_CPP
#define OBJECT_CPP
#include "Object.h"
namespace geo
{
#pragma region En : Constructors and Destructor Tr : Yapıcılar ve Yıkıcı
    Object::Object(glm::vec3 position, glm::quat rotation, glm::vec3 scale, glm::vec3 up)
    {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
        this->up = up;
    }
    Object::~Object()
    {
    }
#pragma endregion
#pragma region En : Transform functions Tr : Dönüşüm fonksiyonları
    // En: Translates the object by the given vector.
    //`translation` is the vector to translate the object.
    // Tr: Nesneyi verilen vektör ile öteler.
    // `translation` nesneyi öteleme vektörüdür.
    void Object::Translate(glm::vec3 translation)
    {
        position += translation;
    }
    // En: Rotates the object by the given quaternion.
    // `rotation` is the quaternion to rotate the object.
    // Tr: Nesneyi verilen kuartyon ile döndürür.
    // `rotation` nesneyi döndürmek için kullanılacak kuartyondur.
    void Object::Rotate(glm::quat rotation)
    {
        this->rotation = glm::normalize(rotation * this->rotation);
    }
    // En: Scales the object by the given vector.
    // `scale` is the vector to scale the object.
    // Tr: Nesneyi verilen vektör ile ölçeklendirir.
    // `scale` nesneyi ölçeklendirmek için kullanılacak vektördür.
    void Object::Scale(glm::vec3 scale)
    {
        this->scale *= scale;
    }
    // En : Rotates the object to look at the target.
    // `target` is the position to look at.
    // Tr : Nesneyi hedefe bakacak şekilde döndürür.
    // `target` bakılacak konumdur.
    void Object::LookAt(glm::vec3 target)
    {
        rotation = glm::quatLookAt(glm::normalize(target - position), up);
    }
    // En : Sets the position of the object.
    // `position` is the position to set.
    // Tr : Nesnenin konumunu ayarlar.
    // `position` ayarlanacak konumdur.
    void Object::SetPosition(glm::vec3 position)
    {
        this->position = position;
    }
    // En : Sets the rotation of the object.
    // `rotation` is the rotation to set.
    // Tr : Nesnenin dönüşünü ayarlar.
    // `rotation` ayarlanacak dönüştür.
    void Object::SetRotation(glm::quat rotation)
    {
        this->rotation = rotation;
    }
    // En : Sets the scale of the object.
    // `scale` is the scale to set.
    // Tr : Nesnenin ölçeğini ayarlar.
    // `scale` ayarlanacak ölçektir.
    void Object::SetScale(glm::vec3 scale)
    {
        this->scale = scale;
    }
    // En : Do transformations here after setting position, rotation and scale.
    // Should be overridden by derived classes.
    // Tr : Pozisyon, dönüş ve ölçekleri ayarladıktan sonra burada dönüşümleri yapın.
    // Türetilmiş sınıflar tarafından geçersiz kılınmalıdır.
    void Object::DoTransformations()
    {
    }
#pragma endregion
#pragma region En : Getters Tr : Alıcılar
    // En : Gives the position of the object.
    // Tr : Nesnenin konumunu verir.
    glm::vec3 Object::GetPosition() const
    {
        return position;
    }
    // En : Gives the rotation of the object.
    // Tr : Nesnenin dönüşünü verir.
    glm::quat Object::GetRotation() const
    {
        return rotation;
    }
    // En : Gives the scale of the object.
    // Tr : Nesnenin ölçeğini verir.
    glm::vec3 Object::GetScale() const
    {
        return scale;
    }
    // En : Gives the up vector of the object.
    // Tr : Nesnenin yukarı vektörünü verir.
    glm::vec3 Object::GetUp() const
    {
        return up;
    }
    // En : Gives the front vector of the object.
    // Tr : Nesnenin ön vektörünü verir.
    glm::vec3 Object::GetFront() const
    {
        return glm::normalize(rotation * glm::vec3(0, 0, -1));
    }
    // En : Gives the right vector of the object.
    // Tr : Nesnenin sağ vektörünü verir.
    glm::vec3 Object::GetRight() const
    {
        return glm::normalize(rotation * glm::vec3(1, 0, 0));
    }
#pragma endregion
}
#endif