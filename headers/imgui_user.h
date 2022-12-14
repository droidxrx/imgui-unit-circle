// clang-format off

#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS

#include <imgui.h>
#include <imgui_internal.h>
#include <cmath>

#ifndef IM_PI
#define IM_PI 3.14159265358979323846F
#endif

#define IM_PI_2    6.283185307179586F
#define IM_DEG2RAD 0.017453292519943295F
#define IM_RAD2DEG 57.29577951308232F


static inline ImVec2 ImClampVec2(const ImVec2& v, const ImVec2& mn, const ImVec2& mx)     { return {(v.x < mn.x) ? mn.x : (v.x > mx.x) ? mx.x : v.x, (v.y < mn.y) ? mn.y : (v.y > mx.y) ? mx.y : v.y}; }


static inline ImVec2 operator+(const ImVec2 &lhs, float rhs) { return { lhs.x + rhs, lhs.y + rhs }; }
static inline ImVec2 operator-(const ImVec2 &lhs, float rhs) { return { lhs.x - rhs, lhs.y - rhs }; }

static inline float  csc(float x)  { return 1 / sinf(x); }
static inline double csc(double x) { return 1 / sin(x); }
static inline float  sec(float x)  { return 1 / cosf(x); }
static inline double sec(double x) { return 1 / cos(x); }
static inline float  cot(float x)  { return 1 / tanf(x); }
static inline double cot(double x) { return 1 / tan(x); }

// Math Helper Functions
namespace ImMath {
    static inline float circumFerence(float r)                                  { return IM_PI_2 * r; }
    // Turn degrees into Radians, necessary for circle math
    static inline float degreesToRadians(float a)                               { return a * IM_DEG2RAD; }     
    // Turn Radians into Degrees, necessary for circle math                                         
    static inline float radiansToDegrees(float a)                               { return a * IM_RAD2DEG; }   
    // Returns the angle from two points                                           
    static inline float angleFromPoints(const ImVec2 &a, const ImVec2 &b)       { return atan2f(b.y - a.y, b.x - a.x); }    
    // Returns the angle from two points                       
    static inline float angleFromPoints(float x1, float y1, float x2, float y2) { return atan2f(y2 - y1, x2 - x1); }                      
    // Will return the angle opposite of the B side         
    static inline float angleFromSides(float a, float b, float c)               { return acos(acos((c * c + a * a - b * b) / (2 * c * a))); }    
    // This function is basic ratio math. curries a ratio and then multiplies that by another number
    static inline float ratio(float n, float min, float max)                    { return n * min / max; }                                               
    // Nudge a number a certain percentage of a distance using a starting offset
    static inline float nudge(float s, float p, float d)                        { return p * d + s; }                                                   
    // Make sure a number does not passbelow a min or above a max
    static inline float clamp(float n, float min, float max)                    { return n > max ? max : n < min ? min : n; }                           
    // Given a curried max value, attempts to bring negative numbers to positive range of loop
    static inline float trueNumber(float max, float n)                          { return n < 0 ? n + max : n; }                                         
    static inline float trueRadian(float n)                                     { return trueNumber(IM_PI_2, n); }
    static inline float trueHalfRadian(float n)                                 { return trueNumber(IM_PI, n); }
    static inline float trueDegree(float n)                                     { return trueNumber(360, n); }
    // Given a curried max value, attempts to wrap a number over half into a negative number of loop
    static inline float signNumber(float max, float n)                          { return n > max * 0.5 ? fmodf(n, max) - max : n; }                
    static inline float signRadian(float n)                                     { return signNumber(IM_PI_2, n); }
    static inline float signHalfRadian(float n)                                 { return signNumber(IM_PI, n); }
    static inline float signDegree(float n)                                     { return signNumber(360, n); }
    // The distance between two points
    static inline float pointDistance(const ImVec2 &a, const ImVec2 &b)         { return hypot(a.x - b.x,a.y - b.y); }                           
    // The distance between two points
    static inline float pointDistance(float x1, float y1, float x2, float y2)   { return hypot(x1 - x2,y1 - y2); }                            
} // namespace ImMath


struct MyImRect : public ImRect {
    ImVec2          Center;

    void            Update(float left, float top, float right, float bottom)    { Min.x = left; Min.y = top; Max.x = right; Max.y = bottom; Center.x = (left + right) * 0.5f; Center.y = (top + bottom) * 0.5f; }
    void            Update(const ImVec2& min, const ImVec2& max)                { Min = min; Max = max; Center.x = (min.x + max.x) * 0.5f; Center.y = (min.y + max.y) * 0.5f; }
    void            Update()                                                    { Center.x = (Min.x + Max.x) * 0.5f; Center.y = (Min.y + Max.y) * 0.5f; }
    
    [[nodiscard]]   float GetCenterWidth() const                                { return (Min.x + Max.x) * 0.5f; }
    [[nodiscard]]   float GetCenterHeight() const                               { return (Min.y + Max.y) * 0.5f; }
};
// clang-format on