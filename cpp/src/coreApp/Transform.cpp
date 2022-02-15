// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR

#include "Transform.h"

// Helper rotation function.
mat3 Transform::rotate(const float degrees, const vec3& axis) {
    float theta = glm::radians(degrees);
    float x = axis.x, y = axis.y, z = axis.z;
    mat3 M2 = mat3(x * x, x * y, x * z, x * y, y * y, y * z, x * z, y * z, z * z);
    mat3 M3 = mat3(0, z, -1 * y, -1 * z, 0, x, y, -1 * x, 0);

    // Rodriguez formula
    return (
        (cos(theta) * mat3(1.0)) +
        (M2 - cos(theta) * M2) +
        (sin(theta) * M3)
    );
}

void Transform::left(float degrees, vec3& eye, vec3& up) {
    mat3 R = Transform::rotate(-degrees, up);
    eye = eye * R;
    up = up * R;
}

void Transform::up(float degrees, vec3& eye, vec3& up) {
    mat3 R = Transform::rotate(-degrees, glm::normalize(glm::cross(eye, up)));
    eye = eye * R;
    up = up * R;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) {
    vec3 w = glm::normalize(eye),
        u = -glm::normalize(glm::cross(w, up)),
        v = glm::cross(w, u);

    return mat4(
        u.x, v.x, w.x, 0,
        u.y, v.y, w.y, 0,
        u.z, v.z, w.z, 0,
        -glm::dot(u, eye), -glm::dot(v, eye), -glm::dot(w, eye), 1.0
    );
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar) {
    mat4 ret;
    float theta = glm::radians(fovy) / 2;
    float d = 1.0 / tan(theta);
    float A = -((zFar + zNear) / (zFar - zNear));
    float B = -((2*zFar*zNear) / (zFar - zNear));
    ret = mat4(
        d / aspect, 0, 0, 0,
        0, d, 0, 0,
        0, 0, A, -1,
        0, 0, B, 0
    );
    return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) {
    return mat4(
        sx, 0, 0, 0,
        0, sy, 0, 0,
        0, 0, sz, 0,
        0, 0, 0, 1
    );
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) {
    return mat4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        tx, ty, tz, 1
    );
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) {
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform() {

}

Transform::~Transform() {

}
