#include "renderer.h"

void Renderer::drawUnitCircle(ImDrawList *draw) {
    c.updateNumber(imIo->MouseWheel, mousePos);

    {
        draw->AddLine({ availableDisplay.Min.x, c.c.y }, { availableDisplay.Max.x, c.c.y }, IM_COL32_WHITE, 2.5);
        draw->AddLine({ c.c.x, 0 }, { c.c.x, availableDisplay.Max.y }, IM_COL32_WHITE, 2.5);
        draw->AddCircle(c.c, c.r, IM_COL32_WHITE, 100, 2.5);
        draw->AddText({ c.c.x + c.r + 5, c.c.y + 5 }, IM_COL32_WHITE, "1");
        draw->AddText({ c.c.x - (c.r + 15), c.c.y - 10 - (imFont->FontSize / 2) }, IM_COL32_WHITE, "-1");
        draw->AddText({ c.c.x - 10, c.c.y + (c.r + 5) }, IM_COL32_WHITE, "1");
        draw->AddText({ c.c.x + 5, c.c.y - (c.r + imFont->FontSize) }, IM_COL32_WHITE, "-1");
    }

    // Chord
    draw->AddLine(c.d, c.od, IM_COL32(0, 200, 0, 64), 2.5);
    // Secant
    draw->AddLine({ c.sd.x, c.c.y }, c.c, IM_COL32(200, 0, 200, 150), 2.5);
    // CoSecant
    draw->AddLine({ c.c.x, c.sd.y }, c.c, IM_COL32(0, 200, 200, 190), 2.5);
    // CoTangent
    draw->AddLine({ c.c.x, c.sd.y }, c.d, IM_COL32(200, 200, 0, 150), 2.5);
    // Tangent
    draw->AddLine({ c.sd.x, c.c.y }, c.d, IM_COL32(200, 200, 0, 150), 2.5);
    // Cosine
    draw->AddLine({ c.c.x, c.d.y }, c.d, IM_COL32(200, 0, 200, 150), 2.5);
    // Sine
    draw->AddLine({ c.d.x, c.c.y }, c.d, IM_COL32(0, 200, 200, 150), 2.5);
    // Radius
    draw->AddLine(c.c, c.d, IM_COL32_WHITE, 2.5);

    if (ImMath::pointDistance(c.c, mousePos) > c.r) draw->AddLine(c.d, mousePos, IM_COL32(0, 200, 0, 150), 2.5);

    // Radius Dot
    draw->AddCircleFilled(c.d, 4, IM_COL32(255, 0, 0, 150), 100);
    // Center Dot
    draw->AddCircleFilled(c.c, 4, IM_COL32(255, 0, 0, 150), 100);
    // Sine Dot
    draw->AddCircleFilled({ c.d.x, c.c.y }, 4, IM_COL32(0, 200, 200, 150), 100);
    // Secant Dot
    draw->AddCircleFilled({ c.sd.x, c.c.y }, 4, IM_COL32(200, 200, 0, 150), 100);
    // Cosine Dot
    draw->AddCircleFilled({ c.c.x, c.d.y }, 4, IM_COL32(200, 0, 200, 150), 100);
    // CoTangent Dot
    draw->AddCircleFilled({ c.c.x, c.sd.y }, 4, IM_COL32(200, 200, 0, 150), 100);
}