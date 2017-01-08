#include "Scene.h"
#include "Instance.h"


Scene::Scene() {
    this->camera = new Camera(0, 0);
}

/**
 * Instantiate / add object to the scene.
 *
 * @param Instance instance
 */
void Scene::instantiate(Instance *instance) {
    this->newInstances->push_back(instance);
}

/**
 * Remove object from the scene
 *
 * @param Instance instance
 */
void Scene::destantiate(Instance *instance) {
    instance->trash = true;
}

/**
 * Default scene behavior / logic
 */
void Scene::tickDefault(float delta) {
    this->camera->tick(delta);
    for(std::vector<Instance*>::iterator it = this->instances->begin(); it != this->instances->end();) {
        
        /* Checking if instance should be deleted */
        if ((*it)->trash) {
            std::vector<Instance*>::iterator position = std::find(
                this->instances->begin(),
                this->instances->end(),
                (*it)
            );

            if (position != this->instances->end()) {
                delete (*it);

                /*
                 * Delete instance from list.
                 *
                 * It is very important that we update the current
                 * iterator by assigning the one that std::vector::erase
                 * returns to it.
                 */
                it = this->instances->erase(position);
            }

            continue;
        }

        /* Update the size of the collisionBox */
        (*it)->collisionBox->setSize(
            (*it)->sprite->getCurrentImage()->getWidth(),
            (*it)->sprite->getCurrentImage()->getHeight()
        );

        /* Update instance logic */
        (*it)->tick(delta);

        /* Everything went OK, so let us go to next instance */
        ++it;
    }

    /* Remove objects / instances that are waiting for being removed */
    for(std::vector<Instance*>::iterator it = this->newInstances->begin(); it != this->newInstances->end();) {
        this->instances->push_back((*it));

        ++it;
    }

    this->newInstances->clear();
}

/**
 * Default scene graphics behavior
 */
void Scene::drawDefault(float delta) {
    this->camera->draw(delta);
    for(std::vector<Instance*>::iterator it = this->instances->begin(); it != this->instances->end(); ++it) {
        glPushMatrix();

        if ((*it)->centeredOrigo) {
            glTranslatef((*it)->x - (*it)->sprite->getWidth()/2, (*it)->y - (*it)->sprite->getHeight()/2, 0.0f);
        } else {
            glTranslatef((*it)->x, (*it)->y, 0.0f); 
        }

        if ((*it)->centeredOrigo) {
            glTranslatef(((*it)->sprite->getWidth()/2), ((*it)->sprite->getHeight()/2), 0);
        }

        glRotatef((*it)->rotation, 0.0f, 0.0f, 1.0f);

        if ((*it)->centeredOrigo) {
            glTranslatef(-((*it)->sprite->getWidth()/2), -((*it)->sprite->getHeight()/2), 0);
        }

        (*it)->draw(delta);

        glPopMatrix();
    }
}
