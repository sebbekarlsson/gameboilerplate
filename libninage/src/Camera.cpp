#include "includes/Ninage.h"
#include "includes/Camera.h"


/**
 * Constructor
 */
Camera::Camera(float x, float y) : Entity(x, y) {
    this->zoomPoint = new glm::vec2(0.1f, 0.1f); 
    this->zoom = 1.0f;
}

/**
 * Update logic for camera
 */
void Camera::tick(float delta) {
    this->updatePhysics(delta);
}

/**
 * This function is suppost to be used to draw
 * GUI
 */
void Camera::draw(float delta) {
    Color * col = new Color(255.0f, 255.0f, 255.0f, 100.0f);

    glPushMatrix();
    glTranslatef(16.0f, 16.0f, 0.0f);
    game->drawText("FPS: " + std::to_string(game->getFPS()), "/usr/local/share/ninage/assets/font/bits.ttf", 16, col);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16.0f, 32.0f + 8.0f, 0.0f);
    game->drawText("DELTA: " + std::to_string(delta), "/usr/local/share/ninage/assets/font/bits.ttf", 16, col);
    glPopMatrix();

    delete col;
}

/**
 * Change the x and y value of the zoom point.
 *
 * @param float x
 * @param float y
 */
void Camera::setZoomPoint(float x, float y) {
    this->zoomPoint->x = x;
    this->zoomPoint->y = y;
}

/**
 * Get the reference of the zoom point
 *
 * @return glm::vec2&
 */
glm::vec2& Camera::getZoomPoint() {
    return *this->zoomPoint;
}

void Camera::scene(float delta, Instance * instance) {}