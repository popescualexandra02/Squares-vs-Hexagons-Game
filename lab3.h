#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Lab3 : public gfxc::SimpleScene
    {
     public:
        Lab3();
        ~Lab3();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void Danger_appear(int type, int j,float line_y, float deltaTime);
        void Star_Appear(glm::vec3 dangerPosition, int type, float deltaTimeSeconds, float line);
        void Star_shoot(int type, int i, float deltaTimeSeconds, glm::vec3 dangerPosition);
        void Soldier_gone(int i, float deltaTimeSeconds);
        void Soldier_killed(glm::vec3 danger1Position, glm::vec3 danger2Position, glm::vec3 danger3Position, glm::vec3 soldierPosition, float line);

     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;

        // TODO(student): If you need any other class variables, define them here.

    };
}   // namespace m1
