#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Camera.h"


class Instance;

class Scene {
    public:
        Scene();

        std::vector<Instance*> *instances = new std::vector<Instance*>();
        std::vector<Instance*> *newInstances = new std::vector<Instance*>();
        Camera * camera;

        bool initialized;

        void instantiate(Instance *instance);
        void destantiate(Instance *instance);
        void tickDefault(float delta);
        void drawDefault(float delta);
        void initialize(float delta);

        /**
         * Update logic for scene
         *
         * @param float delta
         */
        virtual void tick(float delta) = 0;

        /**
         * Draw scene graphics
         *
         * @param float delta
         */
        virtual void draw(float detla) = 0;

        /**
         * Initialize scene, place out game objects etc..
         *
         * @param float delta
         */
        virtual void init(float delta) = 0;
};

#endif
