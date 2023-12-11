#include "headerfiles/camera.h"

MainCamera::MainCamera(float zoom, float rotation) {
    setOffset(static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2));
    setZoom(zoom);
    setRotation(rotation);
}

MainCamera::~MainCamera() {

}

void MainCamera::update() {

}

void MainCamera::draw() {

}

//----------------------------Setter----------------------------------

void MainCamera::setTarget(Vector2 target) {
    this->mainCamera.target = target;
}

void MainCamera::setOffset(Vector2 offset) {
    this->mainCamera.offset = offset;
}

void MainCamera::setOffset(float x, float y) {
    this->mainCamera.offset.x = x;
    this->mainCamera.offset.y = y;
}

void MainCamera::setZoom(float zoom) {
    this->mainCamera.zoom = zoom;
}

void MainCamera::setRotation(float rotation) {
    this->mainCamera.rotation = rotation;
}

//----------------------------Getter----------------------------------

Camera2D MainCamera::getMainCamera() {
    return this->mainCamera;
}