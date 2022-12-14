#include "renderer.h"

using namespace ImMath;

void Renderer::drawWindow() {
    static float const tableColumdWidth[4]{ 55.98, 186.32, 36.80, 100 };
    ImGui::Begin("##IMGUI_UNIT_CIRCLE", nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    imWindow = ImGui::GetCurrentWindow();

    ImGui::ColorEdit3(" Display BG", (float *)&displayBg);

    ImGui::BeginTable("##TABLE_UNIT_CIRCLE1", 4);
    ImGui::TableSetupColumn("##TABLE_UNIT_CIRCLE1_NAME1", ImGuiTableColumnFlags_DefaultHide | ImGuiTableColumnFlags_WidthFixed, tableColumdWidth[0]);
    ImGui::TableSetupColumn("##TABLE_UNIT_CIRCLE1_NAME2", ImGuiTableColumnFlags_DefaultHide | ImGuiTableColumnFlags_WidthFixed, tableColumdWidth[1]);
    ImGui::TableSetupColumn("##TABLE_UNIT_CIRCLE1_NAME3", ImGuiTableColumnFlags_DefaultHide | ImGuiTableColumnFlags_WidthFixed, tableColumdWidth[2]);
    ImGui::TableSetupColumn("##TABLE_UNIT_CIRCLE1_NAME4", ImGuiTableColumnFlags_DefaultHide | ImGuiTableColumnFlags_WidthStretch, tableColumdWidth[3]);

    // RADIUS
    {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Radius");
        ImGui::TableNextColumn();
        ImGui::Text(": %.2f", c.r);
    }
    // RADIANS
    {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Radians");
        ImGui::TableNextColumn();
        ImGui::Text(": %.2f", trueRadian(c.ar));
        ImGui::TableNextColumn();
        ImGui::Text("Signed");
        ImGui::TableNextColumn();
        ImGui::Text(": %.2f", signRadian(c.ar));
    }
    // ANGLE
    {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("Angle");
        ImGui::TableNextColumn();
        ImGui::Text(": %.2f", trueDegree(c.a));
        ImGui::TableNextColumn();
        ImGui::Text("Signed");
        ImGui::TableNextColumn();
        ImGui::Text(": %.2f", signDegree(c.a));
    }

    // CoSin
    {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("coSinXY");
        ImGui::TableNextColumn();
        ImGui::Text(": { x: %.2f, y: %.2f }", c.d.x, c.d.y);
    }

    // Secant
    {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text("SecantXY");
        ImGui::TableNextColumn();
        ImGui::Text(": { x: %.2f, y: %.2f }", c.sd.x, c.sd.y);
    }

    ImGui::EndTable();

    ImGui::BeginTable("##TABLE_UNIT_CIRCLE2", 3, ImGuiTableFlags_Borders);
    ImGui::TableSetupColumn("##TABLE_UNIT_CIRCLE2", ImGuiTableColumnFlags_WidthFixed, tableColumdWidth[0]);
    ImGui::TableSetupColumn("Ratio##TABLE_UNIT_CIRCLE2", ImGuiTableColumnFlags_WidthFixed, tableColumdWidth[1]);
    ImGui::TableSetupColumn("Value##TABLE_UNIT_CIRCLE2", ImGuiTableColumnFlags_WidthStretch, tableColumdWidth[2]);
    ImGui::TableHeadersRow();

    // Sine
    {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::TextColored({ 0, 0.78431, 0.78431, 1 }, "Sine");
        ImGui::TableNextColumn();
        ImGui::TextColored({ 0, 0.78431, 0.78431, 1 }, "%.2f", c.arsin);
        ImGui::TableNextColumn();
        ImGui::TextColored({ 0, 0.78431, 0.78431, 1 }, "%.2f", c.arsin * c.r);
    }

    // CoSin
    {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::TextColored({ 0.78431, 0, 0.78431, 1 }, "CoSin");
        ImGui::TableNextColumn();
        ImGui::TextColored({ 0.78431, 0, 0.78431, 1 }, "%.2f", c.arcos);
        ImGui::TableNextColumn();
        ImGui::TextColored({ 0.78431, 0, 0.78431, 1 }, "%.2f", c.arcos * c.r);
    }

    // Secant
    {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::TextColored({ 0.78431, 0, 0.78431, 0.5 }, "Secant");
        ImGui::TableNextColumn();
        ImGui::TextColored({ 0.78431, 0, 0.78431, 0.5 }, "%.2f", c.arsec);
        ImGui::TableNextColumn();
        ImGui::TextColored({ 0.78431, 0, 0.78431, 0.5 }, "%.2f", c.arsec * c.r);
    }

    // CoSec
    {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::TextColored({ 0, 0.78431, 0.78431, 0.5 }, "CoSec");
        ImGui::TableNextColumn();
        ImGui::TextColored({ 0, 0.78431, 0.78431, 0.5 }, "%.2f", c.arcsc);
        ImGui::TableNextColumn();
        ImGui::TextColored({ 0, 0.78431, 0.78431, 0.5 }, "%.2f", c.arcsc * c.r);
    }

    // CoTan
    {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::TextColored({ 0.78431, 0.78431, 0, 0.5 }, "CoTan");
        ImGui::TableNextColumn();
        ImGui::TextColored({ 0.78431, 0.78431, 0, 0.5 }, "%.2f", c.arcot);
        ImGui::TableNextColumn();
        ImGui::TextColored({ 0.78431, 0.78431, 0, 0.5 }, "%.2f", c.arcot * c.r);
    }

    // Chord
    {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::TextColored({ 0, 0.78431, 0, 1 }, "Chord");
        ImGui::TableNextColumn();
        ImGui::TextColored({ 0, 0.78431, 0, 1 }, "%.2f", c.crd / c.r);
        ImGui::TableNextColumn();
        ImGui::TextColored({ 0, 0.78431, 0, 1 }, "%.2f", c.crd);
    }
    ImGui::EndTable();

    ImGui::End();
}