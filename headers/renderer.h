#pragma once

#include "imgui_user.h"
#include <GLFW/glfw3.h>

class UnitCircleValue {
    public:
        UnitCircleValue() {
            r    = 237.5;
            od.x = c.x + r;
            od.y = c.y;
        }
        // circle angle
        float a{};
        // circle radians
        float ar{};
        // circle radius
        float r;
        // circle diameter
        ImVec2 d{};
        // circle diameter
        ImVec2 od{};
        ImVec2 sd{};
        // circle center
        ImVec2 c{};

        float crd{};

        float artan{};
        float arsin{};
        float arcos{};
        float arcsc{};
        float arsec{};
        float arcot{};

        inline void update(const ImVec2 &center) {
            c    = center;
            od.x = c.x + r;
            od.y = c.y;
        }

        inline void updateNumber(float mouseWheel, const ImVec2 &mousePos) {
            using namespace ImMath;
            setRadius(mouseWheel);

            a     = trueDegree(radiansToDegrees(angleFromPoints(c, mousePos)));
            ar    = degreesToRadians(a);
            artan = tanf(ar);
            arsin = sinf(ar);
            arcos = cosf(ar);
            arcsc = csc(ar);
            arsec = sec(ar);
            arcot = cot(ar);
            d.x   = nudge(c.x, arcos, r);
            d.y   = nudge(c.y, arsin, r);
            sd.x  = arsec * r + c.x;
            sd.y  = arcsc * r + c.y;
            crd   = pointDistance(d, od);
        }

    private:
        inline void setRadius(float mouseWheel) {
            if (mouseWheel != 0.0F) {
                r += mouseWheel * 2.5F;
                if (r > 350) {
                    r = 350;
                } else if (r < 80) {
                    r = 80;
                }

                od.x = c.x + r;
                od.y = c.y;
            }
        }
};

class Renderer {
    public:
        Renderer();

        bool initImGui();
        void loopRender();

    private:
        GLFWwindow  *window;
        ImGuiWindow *imWindow;
        ImFont      *imFont;
        ImGuiIO     *imIo;
        ImGuiStyle  *imStyle;
        MyImRect     availableDisplay{};
        ImVec2       displaySize{}, mousePos{};
        ImVec4       displayBg{ 0.014, 0.092, 0.131, 1.00 };

        UnitCircleValue c{};

        void renderStart();
        void renderEnd(int display_w, int display_h);
        void destroy();

        void drawWindow();
        void drawUnitCircle(ImDrawList *draw);
        void updateMousePos();
};