#define TRUSSC_SHOW_CONSOLE 1
#include "TrussC.h"
#include "tcxHapPlayer.h"
#include "tcxOsc.h"
#include "tcxObj.h"
#include "tcxGltf.h"

#include "JlTrussC.h"

#include "jlcxx/jlcxx.hpp"
#include "jlcxx/stl.hpp"

#include "trussc_generated.h"

using namespace std;
using namespace tc;

static void *setupFnPtr = nullptr;
static void *updateFnPtr = nullptr;
static void *drawFnPtr = nullptr;
static void *keyPressedFnPtr = nullptr;
static void *keyReleasedFnPtr = nullptr;
static void *mousePressedFnPtr = nullptr;
static void *mouseReleasedFnPtr = nullptr;
static void *mouseMovedFnPtr = nullptr;
static void *mouseDraggedFnPtr = nullptr;
static void *mouseScrolledFnPtr = nullptr;
static void *windowResizedFnPtr = nullptr;
static void *filesDroppedFnPtr = nullptr;
static void *exitFnPtr = nullptr;

class TestApp : public App {
    void draw() override {
        clear(0.12f);

        // Rotating box
        noFill();
        translate(getWindowWidth() / 2, getWindowHeight() / 2);
        rotate(getElapsedTimef() *0.1f, getElapsedTimef() *0.15f, 0);
        drawBox(200.0f);
    }
};

void runTrusscTestApp(int width=960, int height=600, const std::string& title="TrussC") {
    WindowSettings settings;
    settings.setSize(width, height);
    settings.setTitle(title);
    runApp<TestApp>(settings);
}

void setSetupFn(jl_value_t *fn){
    setupFnPtr = jl_unbox_voidpointer(fn);
}

void setUpdateFn(jl_value_t *fn){
    updateFnPtr = jl_unbox_voidpointer(fn);
}

void setDrawFn(jl_value_t *fn){
    drawFnPtr = jl_unbox_voidpointer(fn);
}

void setKeyPressedFn(jl_value_t *fn){
    keyPressedFnPtr = jl_unbox_voidpointer(fn);
}

void setKeyReleasedFn(jl_value_t *fn){
    keyReleasedFnPtr = jl_unbox_voidpointer(fn);
}

void setMousePressedFn(jl_value_t *fn){
    mousePressedFnPtr = jl_unbox_voidpointer(fn);
}

void setMouseReleasedFn(jl_value_t *fn){
    mouseReleasedFnPtr = jl_unbox_voidpointer(fn);
}

void setMouseMovedFn(jl_value_t *fn){
    mouseMovedFnPtr = jl_unbox_voidpointer(fn);
}

void setMouseScrolledFn(jl_value_t *fn){
    mouseScrolledFnPtr = jl_unbox_voidpointer(fn);
}

void setMouseDraggedFn(jl_value_t *fn){
    mouseDraggedFnPtr = jl_unbox_voidpointer(fn);
}

void setWindowResizedFn(jl_value_t *fn){
    windowResizedFnPtr = jl_unbox_voidpointer(fn);
}

void setFilesDroppedFn(jl_value_t *fn){
    filesDroppedFnPtr = jl_unbox_voidpointer(fn);
}

void setExitFn(jl_value_t *fn){
    exitFnPtr = jl_unbox_voidpointer(fn);
}

void callFnPtr(void* ptr){
    if(ptr != nullptr){
        typedef void (*CppPtr)();
        CppPtr rePtr = reinterpret_cast<CppPtr>(ptr);
        rePtr();
    }
}

void callKeyFnPtr(void* ptr, int key){
    if(ptr != nullptr){
        typedef void (*CppPtr)(int key);
        CppPtr rePtr = reinterpret_cast<CppPtr>(ptr);
        rePtr(key);
    }
}

void callMouseFnPtr(void* ptr, Vec2 pos, int button){
    if(ptr != nullptr){
        typedef void (*CppPtr)(Vec2& pos, int button);
        CppPtr rePtr = reinterpret_cast<CppPtr>(ptr);
        rePtr(pos, button);
    }
}

void callMouseMovedFnPtr(void* ptr, Vec2 pos){
    if(ptr != nullptr){
        typedef void (*CppPtr)(Vec2& pos);
        CppPtr rePtr = reinterpret_cast<CppPtr>(ptr);
        rePtr(pos);
    }
}

void callWindowResizedFnPtr(void* ptr, int w, int h){
    if(ptr != nullptr){
        typedef void (*CppPtr)(int w, int h);
        CppPtr rePtr = reinterpret_cast<CppPtr>(ptr);
        rePtr(w, h);
    }
}

void callFilesDroppedFnPtr(void* ptr, const vector<string>& files){
    if(ptr != nullptr){
        typedef void (*CppPtr)(vector<string>& files);
        CppPtr rePtr = reinterpret_cast<CppPtr>(ptr);
        rePtr(const_cast<vector<string>&>(files));
    }
}

void callSetupFn(){
    callFnPtr(setupFnPtr);
}

void callUpdateFn(){
    callFnPtr(updateFnPtr);
}

void callDrawFn(){
    callFnPtr(drawFnPtr);
}

void callKeyPressedFn(int key){
    callKeyFnPtr(keyPressedFnPtr, key);
}

void callKeyReleasedFn(int key){
    callKeyFnPtr(keyReleasedFnPtr, key);
}

void callMousePressedFn(Vec2 pos, int button){
    callMouseFnPtr(mousePressedFnPtr, pos, button);
}

void callMouseReleasedFn(Vec2 pos, int button){
    callMouseFnPtr(mouseReleasedFnPtr, pos, button);
}

void callMouseMovedFn(Vec2 pos){
    callMouseMovedFnPtr(mouseMovedFnPtr, pos);
}

void callMouseScrolledFn(Vec2 delta){
    callMouseMovedFnPtr(mouseScrolledFnPtr, delta);
}

void callMouseDraggedFn(Vec2 pos, int button){
    callMouseFnPtr(mouseDraggedFnPtr, pos, button);
}

void callWindowResizedFn(int w, int h){
    callWindowResizedFnPtr(windowResizedFnPtr, w, h);
}

void callFilesDroppedFn(const vector<string>& files){
    callFilesDroppedFnPtr(filesDroppedFnPtr, files);
}

void callExitFn(){
    callFnPtr(exitFnPtr);
}

class MyApp : public App {
public:

    void setup() override {
        callSetupFn();
    }

    void update() override {
        callUpdateFn();
    }

    void draw() override {
        callDrawFn();
    }

    void keyPressed(int key) override {
        callKeyPressedFn(key);
    }

    void keyReleased(int key) override {
        callKeyReleasedFn(key);
    }

    void mousePressed(Vec2 pos, int button) override {
        callMousePressedFn(pos, button);
    }

    void mouseReleased(Vec2 pos, int button) override {
        callMouseReleasedFn(pos, button);
    }

    void mouseMoved(Vec2 pos) override {
        callMouseMovedFn(pos);

    }

    void mouseDragged(Vec2 pos, int button) override {
        callMouseDraggedFn(pos, button);

    }

    void mouseScrolled(Vec2 delta) override {
        callMouseScrolledFn(delta);
    }

    void windowResized(int width, int height) override {
        callWindowResizedFn(width, height);

    }

    void filesDropped(const vector<string>& files) override {
        callFilesDroppedFn(files);
    }

    void exit() override {
        callExitFn();
    }
};

void runTrusscApp(int width=960, int height=600, const std::string& title="TrussC") {
    WindowSettings settings;
    settings.setSize(width, height);
    settings.setTitle(title);
    runApp<MyApp>(settings);
}

std::string greet()
{
   return "Hello from JlTrussC C++!!";
}

namespace jlcxx
{
  template<> struct IsMirroredType<FpsSettings> : std::false_type { };
  template<> struct IsMirroredType<IesProfile> : std::false_type { };
  template<> struct IsMirroredType<sg_image> : std::false_type { };
  template<> struct IsMirroredType<sg_view> : std::false_type { };
  template<> struct IsMirroredType<sg_sampler> : std::false_type { };
  template<> struct IsMirroredType<sg_shader_desc> : std::false_type { };
  template<> struct IsMirroredType<ShaderVertex> : std::false_type { };
  template<> struct IsMirroredType<pugi::xml_document> : std::false_type { };
}

JLCXX_MODULE define_julia_module(jlcxx::Module& mod)
{
  mod.method("greet", &greet);
  mod.method("runTrusscTestApp", &runTrusscTestApp);
  mod.method("runTrusscTestApp", [](){ runTrusscTestApp(); });
  mod.method("runTrusscTestApp", [](int w, int h){ runTrusscTestApp(w, h); });
  mod.method("runTrusscApp", &runTrusscApp);
  mod.method("runTrusscApp", [](){ runTrusscApp(); });
  mod.method("runTrusscApp", [](int w, int h){ runTrusscApp(w, h); });
  mod.method("setSetupFn", &setSetupFn);
  mod.method("setUpdateFn", &setUpdateFn);
  mod.method("setDrawFn", &setDrawFn);
  mod.method("setKeyPressedFn", &setKeyPressedFn);
  mod.method("setKeyReleasedFn", &setKeyReleasedFn);
  mod.method("setMousePressedFn", &setMousePressedFn);
  mod.method("setMouseReleasedFn", &setMouseReleasedFn);
  mod.method("setMouseMovedFn", &setMouseMovedFn);
  mod.method("setMouseScrolledFn", &setMouseScrolledFn);
  mod.method("setMouseDraggedFn", &setMouseDraggedFn);
  mod.method("setWindowResizedFn", &setWindowResizedFn);
  mod.method("setFilesDroppedFn", &setFilesDroppedFn);
  mod.method("setExitFn", &setExitFn);

  mod.method("getElapsedTimef", &getElapsedTime);

  mod.add_type<Vec2>("Vec2")
    .constructor<>()
    .constructor<float, float>()
    .constructor<const Vec2&>()
    .method("x", [](Vec2& v){ return v.x; })
    .method("y", [](Vec2& v){ return v.y; })
    .method("x!", [](Vec2& v, float p){ v.x = p; })
    .method("y!", [](Vec2& v, float p){ v.y = p; })
    .method("set", [](Vec2& v, const Vec2& a){ return v.set(a); })
    .method("set", [](Vec2& v, float a, float b){ return v.set(a,b); })
    .method("set!", [](Vec2& v, const Vec2& a){ return v.set(a); })
    .method("set!", [](Vec2& v, float a, float b){ return v.set(a,b); })
    .method("add", [](Vec2& v, const Vec2& p){ return v + p; })
    .method("mul", [](Vec2& v, const Vec2& p){ return v * p; })
    .method("div", [](Vec2& v, const Vec2& p){ return v / p; })
    .method("sub", [](Vec2& v, const Vec2& p){ return v - p; })
    .method("add", [](Vec2& v, float p){ return v + p; })
    .method("mul", [](Vec2& v, float p){ return v * p; })
    .method("div", [](Vec2& v, float p){ return v / p; })
    .method("sub", [](Vec2& v, float p){ return v - p; })
    .method("add", [](Vec2& v, int p){ return v + p; })
    .method("mul", [](Vec2& v, int p){ return v * p; })
    .method("div", [](Vec2& v, int p){ return v / p; })
    .method("sub", [](Vec2& v, int p){ return v - p; })
    .method("add", [](Vec2& v, double p){ return v + p; })
    .method("mul", [](Vec2& v, double p){ return v * p; })
    .method("div", [](Vec2& v, double p){ return v / p; })
    .method("sub", [](Vec2& v, double p){ return v - p; })
    .method("eq", [](Vec2& v, const Vec2& p){ return v == p; })
    .method("length", &Vec2::length)
    .method("lengthSquared", &Vec2::lengthSquared)
    .method("normalized", &Vec2::normalized)
    .method("normalize", &Vec2::normalize)
    .method("limit", &Vec2::limit)
    .method("dot", &Vec2::dot)
    .method("cross", &Vec2::cross)
    .method("distance", &Vec2::distance)
    .method("distanceSquared", &Vec2::distanceSquared)
    .method("angle", [](Vec2& p){ return p.angle(); })
    .method("angle", [](Vec2& p, const Vec2& v){ return p.angle(v); })
    .method("rotated", &Vec2::rotated)
    .method("rotate", &Vec2::rotate)
    .method("lerp", &Vec2::lerp)
    .method("perpendicular", &Vec2::perpendicular)
    .method("reflected", &Vec2::reflected)
    .method("fromAngle", [](float a, float b){ return Vec2::fromAngle(a, b); })
    .method("fromAngle", [](float a){ return Vec2::fromAngle(a); })
    ;

  mod.add_type<Vec3>("Vec3")
    .constructor<>()
    .constructor<float, float, float>()
    .constructor<const Vec2&>()
    .constructor<const Vec3&>()
    .method("x", [](Vec3& v){ return v.x; })
    .method("y", [](Vec3& v){ return v.y; })
    .method("z", [](Vec3& v){ return v.z; })
    .method("x!", [](Vec3& v, float p){ v.x = p; })
    .method("y!", [](Vec3& v, float p){ v.y = p; })
    .method("z!", [](Vec3& v, float p){ v.z = p; })
    .method("set", [](Vec3& v, const Vec3& a){ return v.set(a); })
    .method("set", [](Vec3& v, float a, float b, float c){ return v.set(a,b,c); })
    .method("set!", [](Vec3& v, const Vec3& a){ return v.set(a); })
    .method("set!", [](Vec3& v, float a, float b, float c){ return v.set(a,b,c); })
    .method("add", [](Vec3& v, const Vec3& p){ return v + p; })
    .method("mul", [](Vec3& v, const Vec3& p){ return v * p; })
    .method("div", [](Vec3& v, const Vec3& p){ return v / p; })
    .method("sub", [](Vec3& v, const Vec3& p){ return v - p; })
    .method("add", [](Vec3& v, float p){ return v + p; })
    .method("mul", [](Vec3& v, float p){ return v * p; })
    .method("div", [](Vec3& v, float p){ return v / p; })
    .method("sub", [](Vec3& v, float p){ return v - p; })
    .method("add", [](Vec3& v, int p){ return v + p; })
    .method("mul", [](Vec3& v, int p){ return v * p; })
    .method("div", [](Vec3& v, int p){ return v / p; })
    .method("sub", [](Vec3& v, int p){ return v - p; })
    .method("add", [](Vec3& v, double p){ return v + p; })
    .method("mul", [](Vec3& v, double p){ return v * p; })
    .method("div", [](Vec3& v, double p){ return v / p; })
    .method("sub", [](Vec3& v, double p){ return v - p; })
    .method("eq", [](Vec3& v, const Vec3& p){ return v == p; })
    .method("length", &Vec3::length)
    .method("lengthSquared", &Vec3::lengthSquared)
    .method("normalized", &Vec3::normalized)
    .method("normalize", &Vec3::normalize)
    .method("limit", &Vec3::limit)
    .method("dot", &Vec3::dot)
    .method("cross", &Vec3::cross)
    .method("distance", &Vec3::distance)
    .method("distanceSquared", &Vec3::distanceSquared)
    .method("lerp", &Vec3::lerp)
    .method("reflected", &Vec3::reflected)
    .method("xy", &Vec3::xy)
    ;

  mod.add_type<IVec2>("IVec2")
    .constructor<>()
    .constructor<int, int>()
    .constructor<const IVec2&>()
    .method("x", [](IVec2& v){ return v.x; })
    .method("y", [](IVec2& v){ return v.y; })
    .method("x!", [](IVec2& v, int p){ v.x = p; })
    .method("y!", [](IVec2& v, int p){ v.y = p; })
    .method("add", [](IVec2& v, const IVec2& p){ return v + p; })
    .method("sub", [](IVec2& v, const IVec2& p){ return v - p; })
    .method("add", [](IVec2& v, int p){ return v + p; })
    .method("mul", [](IVec2& v, int p){ return v * p; })
    .method("sub", [](IVec2& v, int p){ return v - p; })
    .method("eq", [](IVec2& v, const IVec2& p){ return v == p; })
    .method("toVec2", &IVec2::toVec2)
    ;

  mod.add_type<IVec3>("IVec3")
    .constructor<>()
    .constructor<int, int, int>()
    .constructor<const IVec3&>()
    .method("x", [](IVec3& v){ return v.x; })
    .method("y", [](IVec3& v){ return v.y; })
    .method("z", [](IVec3& v){ return v.z; })
    .method("x!", [](IVec3& v, int p){ v.x = p; })
    .method("y!", [](IVec3& v, int p){ v.y = p; })
    .method("z!", [](IVec3& v, int p){ v.z = p; })
    .method("add", [](IVec3& v, const IVec3& p){ return v + p; })
    .method("sub", [](IVec3& v, const IVec3& p){ return v - p; })
    .method("add", [](IVec3& v, int p){ return v + p; })
    .method("mul", [](IVec3& v, int p){ return v * p; })
    .method("sub", [](IVec3& v, int p){ return v - p; })
    .method("eq", [](IVec3& v, const IVec3& p){ return v == p; })
    .method("toVec3", &IVec3::toVec3)
    ;

  mod.add_type<Vec4>("Vec4")
    .constructor<>()
    .constructor<float, float, float, float>()
    .constructor<const Vec4&>()
    .method("x", [](Vec4& v){ return v.x; })
    .method("y", [](Vec4& v){ return v.y; })
    .method("z", [](Vec4& v){ return v.z; })
    .method("w", [](Vec4& v){ return v.w; })
    .method("x!", [](Vec4& v, float p){ v.x = p; })
    .method("y!", [](Vec4& v, float p){ v.y = p; })
    .method("z!", [](Vec4& v, float p){ v.z = p; })
    .method("w!", [](Vec4& v, float p){ v.w = p; })
    .method("set", [](Vec4& v, const Vec4& a){ return v.set(a); })
    .method("set", [](Vec4& v, float a, float b, float c, float d){ return v.set(a,b,c,d); })
    .method("set!", [](Vec4& v, const Vec4& a){ return v.set(a); })
    .method("set!", [](Vec4& v, float a, float b, float c, float d){ return v.set(a,b,c,d); })
    .method("add", [](Vec4& v, const Vec4& p){ return v + p; })
    .method("sub", [](Vec4& v, const Vec4& p){ return v - p; })
    .method("add", [](Vec4& v, float p){ return v + p; })
    .method("mul", [](Vec4& v, float p){ return v * p; })
    .method("div", [](Vec4& v, float p){ return v / p; })
    .method("sub", [](Vec4& v, float p){ return v - p; })
    .method("add", [](Vec4& v, int p){ return v + p; })
    .method("mul", [](Vec4& v, int p){ return v * p; })
    .method("div", [](Vec4& v, int p){ return v / p; })
    .method("sub", [](Vec4& v, int p){ return v - p; })
    .method("add", [](Vec4& v, double p){ return v + p; })
    .method("mul", [](Vec4& v, double p){ return v * p; })
    .method("div", [](Vec4& v, double p){ return v / p; })
    .method("sub", [](Vec4& v, double p){ return v - p; })
    .method("eq", [](Vec4& v, const Vec4& p){ return v == p; })
    .method("length", &Vec4::length)
    .method("lengthSquared", &Vec4::lengthSquared)
    .method("normalized", &Vec4::normalized)
    .method("normalize", &Vec4::normalize)
    .method("dot", &Vec4::dot)
    .method("lerp", &Vec4::lerp)
    .method("xy", &Vec4::xy)
    ;

  auto quat_type = mod.add_type<Quaternion>("Quaternion")
    .constructor<>()
    .constructor<float, float, float, float>()
    .constructor<const Quaternion&>()
    .method("w", [](Quaternion& v){ return v.w; })
    .method("x", [](Quaternion& v){ return v.x; })
    .method("y", [](Quaternion& v){ return v.y; })
    .method("z", [](Quaternion& v){ return v.z; })
    .method("w!", [](Quaternion& v, float p){ v.w = p; })
    .method("x!", [](Quaternion& v, float p){ v.x = p; })
    .method("y!", [](Quaternion& v, float p){ v.y = p; })
    .method("z!", [](Quaternion& v, float p){ v.z = p; })
    .method("eq", [](Quaternion& v, const Quaternion& p){ return v == p; })
    // .method("identity", [](){ return Quaternion::identity(); })
    .method("toEuler", &Quaternion::toEuler)
    .method("length", &Quaternion::length)
    .method("lengthSquared", &Quaternion::lengthSquared)
    .method("normalized", &Quaternion::normalized)
    .method("normalize", &Quaternion::normalize)
    .method("conjugate", &Quaternion::conjugate)
    .method("rotate", &Quaternion::rotate)
    ;

  // WORKAROUND
  mod.method("Quaternion_identity", [](){ return Quaternion::identity(); });
  mod.method("Quaternion_fromAxisAngle", [](const Vec3& a, float b){ return Quaternion::fromAxisAngle(a, b); });
  mod.method("Quaternion_fromEuler", [](float pitch, float yaw, float roll){ return Quaternion::fromEuler(pitch, yaw, roll); });
  mod.method("Quaternion_fromEuler", [](const Vec3& euler){ return Quaternion::fromEuler(euler); });
  mod.method("Quaternion_slerp", [](const Quaternion& a, const Quaternion& b, float t) { return Quaternion::slerp(a, b, t); });
    ;

  auto mat4_type = mod.add_type<Mat4>("Mat4")
    .constructor<>()
    .constructor<
        float, float, float, float,
        float, float, float, float,
        float, float, float, float,
        float, float, float, float>()
    .constructor<const Mat4&>()
    .method("at", [](Mat4& m, int raw, int col) { return m.at(raw, col); })
    .method("set", [](Mat4& m, int raw, int col, int v){ m.at(raw, col) = v; })
    .method("set!", [](Mat4& m, int raw, int col, int v){ m.at(raw, col) = v; })
    .method("mul", [](Mat4& v, const Mat4& p){ return v * p; })
    .method("mul", [](Mat4& v, const Vec4& p){ return v * p; })
    .method("mul", [](Mat4& v, const Vec3& p){ return v * p; })
    // .method("identity", [](){ return Mat4::identity(); })
    .method("transposed", &Mat4::transposed)
    .method("inverted", &Mat4::inverted)
    ;

  // WORKAROUND
  mod.method("Mat4_identity", [](){ return Mat4::identity(); });
  mod.method("Mat4_translate", [](float tx, float ty, float tz){ return Mat4::translate(tx, ty, tz); });
  mod.method("Mat4_translate", [](const Vec3& t){ return Mat4::translate(t); });
  mod.method("Mat4_rotateX", [](float r){ return Mat4::rotateX(r); });
  mod.method("Mat4_rotateY", [](float r){ return Mat4::rotateY(r); });
  mod.method("Mat4_rotateZ", [](float r){ return Mat4::rotateZ(r); });
  mod.method("Mat4_rotate", [](float r, const Vec3& a){ return Mat4::rotate(r, a); });
  mod.method("Mat4_scale", [](float s){ return Mat4::scale(s); });
  mod.method("Mat4_scale", [](float sx, float sy, float sz){ return Mat4::scale(sx, sy, sz); });
  mod.method("Mat4_scale", [](const Vec3& s){ return Mat4::scale(s); });
  mod.method("Mat4_lookAt", [](const Vec3& eye, const Vec3& target, const Vec3& up){ return Mat4::lookAt(eye, target, up); });
  mod.method("Mat4_ortho", [](float a, float b, float c, float d, float e, float f){ return Mat4::ortho(a,b,c,d,e,f); });
  mod.method("Mat4_perspective", [](float a, float b, float c, float d){ return Mat4::perspective(a,b,c,d); });
  mod.method("Mat4_frustum", [](float a, float b, float c, float d, float e, float f){ return Mat4::frustum(a,b,c,d,e,f); });

  // WORKAROUND
  quat_type.method("toMatrix", &Quaternion::toMatrix);

  mod.add_type<Mat3>("Mat3")
    .constructor<>()
    .constructor<
        float, float, float,
        float, float, float,
        float, float, float>()
    .constructor<const Mat3&>()
    .method("at", [](Mat3& m, int raw, int col) { return m.at(raw, col); })
    .method("set", [](Mat3& m, int raw, int col, int v){ m.at(raw, col) = v; })
    .method("set!", [](Mat3& m, int raw, int col, int v){ m.at(raw, col) = v; })
    .method("mul", [](Mat3& v, const Mat3& p){ return v * p; })
    .method("mul", [](Mat3& v, const Vec3& p){ return v * p; })
    .method("mul", [](Mat3& v, const Vec2& p){ return v * p; })
    // .method("identity", [](){ return Mat3::identity(); })
    .method("determinant", &Mat3::determinant)
    .method("transposed", &Mat3::transposed)
    .method("inverted", &Mat3::inverted)
    ;

  // WORKAROUND
  mod.method("Mat3_identity", [](){ return Mat3::identity(); });
  mod.method("Mat3_getHomography", [](const Vec2 src[4], const Vec2 dst[4]){ return Mat3::getHomography(src, dst); });
  mod.method("Mat3_rotate", [](float r){ return Mat3::rotate(r); });
  mod.method("Mat3_scale", [](float s){ return Mat3::scale(s); });
  mod.method("Mat3_scale", [](float sx, float sy){ return Mat3::scale(sx, sy); });
  mod.method("Mat3_scale", [](const Vec2& s){ return Mat3::scale(s); });
  mod.method("Mat3_translate", [](float tx, float ty){ return Mat3::translate(tx, ty); });
  mod.method("Mat3_translate", [](const Vec2& t){ return Mat3::translate(t); });

  // WORKAROUND
  mod.method("Mat4_fromHomography", [](const Mat3& h){ return Mat4::fromHomography(h); });

  mod.add_type<Rect>("Rect")
    .constructor<>()
    .constructor<float, float, float, float>()
    .constructor<float, float, float, float, float>()
    .constructor<const Vec2&, float, float>()
    .constructor<const Vec3&, float, float>()
    .constructor<const Rect&>()
    .method("x", [](Rect& v){ return v.x; })
    .method("y", [](Rect& v){ return v.y; })
    .method("width", [](Rect& v){ return v.width; })
    .method("height", [](Rect& v){ return v.height; })
    .method("x!", [](Rect& v, float p){ v.x = p; })
    .method("y!", [](Rect& v, float p){ v.y = p; })
    .method("width!", [](Rect& v, float p){ v.width = p; })
    .method("height!", [](Rect& v, float p){ v.height = p; })
    .method("set", [](Rect& v, const Vec2& a, float c, float d){ return v.set(a,c,d); })
    .method("set", [](Rect& v, float a, float b, float c, float d){ return v.set(a,b,c,d); })
    .method("set!", [](Rect& v, const Vec2& a, float c, float d){ return v.set(a,c,d); })
    .method("set!", [](Rect& v, float a, float b, float c, float d){ return v.set(a,b,c,d); })
    .method("getRight", &Rect::getRight)
    .method("getBottom", &Rect::getBottom)
    .method("getCenter", &Rect::getCenter)
    .method("getCenterX", &Rect::getCenterX)
    .method("getCenterY", &Rect::getCenterY)
    .method("contains", &Rect::contains)
    .method("intersects", &Rect::intersects)
    ;

  mod.add_type<ColorLinear>("ColorLinear");
  mod.add_type<ColorHSB>("ColorHSB");
  mod.add_type<ColorOKLab>("ColorOKLab");
  mod.add_type<ColorOKLCH>("ColorOKLCH");

  mod.add_type<Color>("Color")
    .constructor<>()
    .constructor<float>()
    .constructor<float, float>()
    .constructor<float, float, float>()
    .constructor<float, float, float, float>()
    .constructor<const Color&>()
    .method("r", [](Color& v){ return v.r; })
    .method("g", [](Color& v){ return v.g; })
    .method("b", [](Color& v){ return v.b; })
    .method("a", [](Color& v){ return v.a; })
    .method("r!", [](Color& v, float p){ v.r = p; })
    .method("g!", [](Color& v, float p){ v.g = p; })
    .method("b!", [](Color& v, float p){ v.b = p; })
    .method("a!", [](Color& v, float p){ v.a = p; })
    .method("set", [](Color& v, const Color& a){ return v.set(a); })
    .method("set", [](Color& v, float a, float b, float c, float d){ return v.set(a,b,c,d); })
    .method("set", [](Color& v, float a, float b, float c){ return v.set(a,b,c); })
    .method("set", [](Color& v, float a, float b){ return v.set(a,b); })
    .method("set", [](Color& v, float a){ return v.set(a); })
    .method("set!", [](Color& v, const Color& a){ return v.set(a); })
    .method("set!", [](Color& v, float a, float b, float c, float d){ return v.set(a,b,c,d); })
    .method("set!", [](Color& v, float a, float b, float c){ return v.set(a,b,c); })
    .method("set!", [](Color& v, float a, float b){ return v.set(a,b); })
    .method("set!", [](Color& v, float a){ return v.set(a); })
    .method("toHex", &Color::toHex)
    .method("toLinear", &Color::toLinear)
    .method("toHSB", &Color::toHSB)
    .method("toOKLab", &Color::toOKLab)
    .method("toOKLCH", &Color::toOKLCH)
    .method("clamped", &Color::clamped)
    .method("lerpRGB", &Color::lerpRGB)
    .method("lerpLinear", &Color::lerpLinear)
    .method("lerpHSB", &Color::lerpHSB)
    .method("lerpOKLab", &Color::lerpOKLab)
    .method("lerpOKLCH", &Color::lerpOKLCH)
    .method("lerp", &Color::lerp)
    ;

    // WORKAROUND
    mod.method("Color_fromBytes", [](int r, int g, int b, int a){ return Color::fromBytes(r,g,b,a); });
    mod.method("Color_fromBytes", [](int r, int g, int b){ return Color::fromBytes(r,g,b); });
    mod.method("Color_fromHex", [](uint32_t h, bool a){ return Color::fromHex(h, a); });
    mod.method("Color_fromHex", [](uint32_t h){ return Color::fromHex(h); });
    mod.method("Color_fromHSB", [](float a, float b, float c, float d){ return Color::fromHSB(a,b,c,d); });
    mod.method("Color_fromHSB", [](float a, float b, float c){ return Color::fromHSB(a,b,c); });
    mod.method("Color_fromOKLCH", [](float a, float b, float c, float d){ return Color::fromOKLCH(a,b,c,d); });
    mod.method("Color_fromOKLCH", [](float a, float b, float c){ return Color::fromOKLCH(a,b,c); });
    mod.method("Color_fromOKLab", [](float a, float b, float c, float d){ return Color::fromOKLab(a,b,c,d); });
    mod.method("Color_fromOKLab", [](float a, float b, float c){ return Color::fromOKLab(a,b,c); });
    mod.method("Color_fromLinear", [](float a, float b, float c, float d){ return Color::fromLinear(a,b,c,d); });
    mod.method("Color_fromLinear", [](float a, float b, float c){ return Color::fromLinear(a,b,c); });

    // WORKAROUND for color constants
    mod.method("Color_white", [](){ return colors::white; });
    mod.method("Color_black", [](){ return colors::black; });
    mod.method("Color_red", [](){ return colors::red; });
    mod.method("Color_green", [](){ return colors::green; });
    mod.method("Color_blue", [](){ return colors::blue; });
    mod.method("Color_yellow", [](){ return colors::yellow; });
    mod.method("Color_cyan", [](){ return colors::cyan; });
    mod.method("Color_magenta", [](){ return colors::magenta; });
    mod.method("Color_transparent", [](){ return colors::transparent; });
    mod.method("Color_gray", [](){ return colors::gray; });
    mod.method("Color_darkGray", [](){ return colors::darkGray; });
    mod.method("Color_dimGray", [](){ return colors::dimGray; });
    mod.method("Color_lightGray", [](){ return colors::lightGray; });
    mod.method("Color_silver", [](){ return colors::silver; });
    mod.method("Color_gainsboro", [](){ return colors::gainsboro; });
    mod.method("Color_whiteSmoke", [](){ return colors::whiteSmoke; });
    mod.method("Color_darkRed", [](){ return colors::darkRed; });
    mod.method("Color_fireBrick", [](){ return colors::fireBrick; });
    mod.method("Color_crimson", [](){ return colors::crimson; });
    mod.method("Color_indianRed", [](){ return colors::indianRed; });
    mod.method("Color_lightCoral", [](){ return colors::lightCoral; });
    mod.method("Color_salmon", [](){ return colors::salmon; });
    mod.method("Color_darkSalmon", [](){ return colors::darkSalmon; });
    mod.method("Color_lightSalmon", [](){ return colors::lightSalmon; });
    mod.method("Color_orange", [](){ return colors::orange; });
    mod.method("Color_darkOrange", [](){ return colors::darkOrange; });
    mod.method("Color_orangeRed", [](){ return colors::orangeRed; });
    mod.method("Color_tomato", [](){ return colors::tomato; });
    mod.method("Color_coral", [](){ return colors::coral; });
    mod.method("Color_gold", [](){ return colors::gold; });
    mod.method("Color_goldenRod", [](){ return colors::goldenRod; });
    mod.method("Color_darkGoldenRod", [](){ return colors::darkGoldenRod; });
    mod.method("Color_paleGoldenRod", [](){ return colors::paleGoldenRod; });
    mod.method("Color_lightGoldenRodYellow", [](){ return colors::lightGoldenRodYellow; });
    mod.method("Color_khaki", [](){ return colors::khaki; });
    mod.method("Color_darkKhaki", [](){ return colors::darkKhaki; });
    mod.method("Color_lime", [](){ return colors::lime; });
    mod.method("Color_limeGreen", [](){ return colors::limeGreen; });
    mod.method("Color_lightGreen", [](){ return colors::lightGreen; });
    mod.method("Color_paleGreen", [](){ return colors::paleGreen; });
    mod.method("Color_darkGreen", [](){ return colors::darkGreen; });
    mod.method("Color_forestGreen", [](){ return colors::forestGreen; });
    mod.method("Color_seaGreen", [](){ return colors::seaGreen; });
    mod.method("Color_mediumSeaGreen", [](){ return colors::mediumSeaGreen; });
    mod.method("Color_darkSeaGreen", [](){ return colors::darkSeaGreen; });
    mod.method("Color_lightSeaGreen", [](){ return colors::lightSeaGreen; });
    mod.method("Color_springGreen", [](){ return colors::springGreen; });
    mod.method("Color_mediumSpringGreen", [](){ return colors::mediumSpringGreen; });
    mod.method("Color_greenYellow", [](){ return colors::greenYellow; });
    mod.method("Color_yellowGreen", [](){ return colors::yellowGreen; });
    mod.method("Color_chartreuse", [](){ return colors::chartreuse; });
    mod.method("Color_lawnGreen", [](){ return colors::lawnGreen; });
    mod.method("Color_olive", [](){ return colors::olive; });
    mod.method("Color_oliveDrab", [](){ return colors::oliveDrab; });
    mod.method("Color_darkOliveGreen", [](){ return colors::darkOliveGreen; });
    mod.method("Color_aqua", [](){ return colors::aqua; });
    mod.method("Color_aquamarine", [](){ return colors::aquamarine; });
    mod.method("Color_mediumAquaMarine", [](){ return colors::mediumAquaMarine; });
    mod.method("Color_darkCyan", [](){ return colors::darkCyan; });
    mod.method("Color_teal", [](){ return colors::teal; });
    mod.method("Color_lightCyan", [](){ return colors::lightCyan; });
    mod.method("Color_turquoise", [](){ return colors::turquoise; });
    mod.method("Color_mediumTurquoise", [](){ return colors::mediumTurquoise; });
    mod.method("Color_darkTurquoise", [](){ return colors::darkTurquoise; });
    mod.method("Color_paleTurquoise", [](){ return colors::paleTurquoise; });
    mod.method("Color_navy", [](){ return colors::navy; });
    mod.method("Color_darkBlue", [](){ return colors::darkBlue; });
    mod.method("Color_mediumBlue", [](){ return colors::mediumBlue; });
    mod.method("Color_royalBlue", [](){ return colors::royalBlue; });
    mod.method("Color_steelBlue", [](){ return colors::steelBlue; });
    mod.method("Color_blueSteel", [](){ return colors::blueSteel; });
    mod.method("Color_lightSteelBlue", [](){ return colors::lightSteelBlue; });
    mod.method("Color_dodgerBlue", [](){ return colors::dodgerBlue; });
    mod.method("Color_deepSkyBlue", [](){ return colors::deepSkyBlue; });
    mod.method("Color_skyBlue", [](){ return colors::skyBlue; });
    mod.method("Color_lightSkyBlue", [](){ return colors::lightSkyBlue; });
    mod.method("Color_lightBlue", [](){ return colors::lightBlue; });
    mod.method("Color_powderBlue", [](){ return colors::powderBlue; });
    mod.method("Color_cornflowerBlue", [](){ return colors::cornflowerBlue; });
    mod.method("Color_cadetBlue", [](){ return colors::cadetBlue; });
    mod.method("Color_midnightBlue", [](){ return colors::midnightBlue; });
    mod.method("Color_aliceBlue", [](){ return colors::aliceBlue; });
    mod.method("Color_purple", [](){ return colors::purple; });
    mod.method("Color_darkMagenta", [](){ return colors::darkMagenta; });
    mod.method("Color_darkViolet", [](){ return colors::darkViolet; });
    mod.method("Color_blueViolet", [](){ return colors::blueViolet; });
    mod.method("Color_indigo", [](){ return colors::indigo; });
    mod.method("Color_slateBlue", [](){ return colors::slateBlue; });
    mod.method("Color_darkSlateBlue", [](){ return colors::darkSlateBlue; });
    mod.method("Color_mediumSlateBlue", [](){ return colors::mediumSlateBlue; });
    mod.method("Color_mediumPurple", [](){ return colors::mediumPurple; });
    mod.method("Color_darkOrchid", [](){ return colors::darkOrchid; });
    mod.method("Color_mediumOrchid", [](){ return colors::mediumOrchid; });
    mod.method("Color_orchid", [](){ return colors::orchid; });
    mod.method("Color_violet", [](){ return colors::violet; });
    mod.method("Color_plum", [](){ return colors::plum; });
    mod.method("Color_thistle", [](){ return colors::thistle; });
    mod.method("Color_lavender", [](){ return colors::lavender; });
    mod.method("Color_fuchsia", [](){ return colors::fuchsia; });
    mod.method("Color_pink", [](){ return colors::pink; });
    mod.method("Color_lightPink", [](){ return colors::lightPink; });
    mod.method("Color_hotPink", [](){ return colors::hotPink; });
    mod.method("Color_deepPink", [](){ return colors::deepPink; });
    mod.method("Color_mediumVioletRed", [](){ return colors::mediumVioletRed; });
    mod.method("Color_paleVioletRed", [](){ return colors::paleVioletRed; });
    mod.method("Color_brown", [](){ return colors::brown; });
    mod.method("Color_maroon", [](){ return colors::maroon; });
    mod.method("Color_saddleBrown", [](){ return colors::saddleBrown; });
    mod.method("Color_sienna", [](){ return colors::sienna; });
    mod.method("Color_chocolate", [](){ return colors::chocolate; });
    mod.method("Color_peru", [](){ return colors::peru; });
    mod.method("Color_sandyBrown", [](){ return colors::sandyBrown; });
    mod.method("Color_burlyWood", [](){ return colors::burlyWood; });
    mod.method("Color_tan", [](){ return colors::tan; });
    mod.method("Color_rosyBrown", [](){ return colors::rosyBrown; });
    mod.method("Color_snow", [](){ return colors::snow; });
    mod.method("Color_honeyDew", [](){ return colors::honeyDew; });
    mod.method("Color_mintCream", [](){ return colors::mintCream; });
    mod.method("Color_azure", [](){ return colors::azure; });
    mod.method("Color_ghostWhite", [](){ return colors::ghostWhite; });
    mod.method("Color_floralWhite", [](){ return colors::floralWhite; });
    mod.method("Color_ivory", [](){ return colors::ivory; });
    mod.method("Color_antiqueWhite", [](){ return colors::antiqueWhite; });
    mod.method("Color_linen", [](){ return colors::linen; });
    mod.method("Color_lavenderBlush", [](){ return colors::lavenderBlush; });
    mod.method("Color_mistyRose", [](){ return colors::mistyRose; });
    mod.method("Color_oldLace", [](){ return colors::oldLace; });
    mod.method("Color_seaShell", [](){ return colors::seaShell; });
    mod.method("Color_beige", [](){ return colors::beige; });
    mod.method("Color_cornsilk", [](){ return colors::cornsilk; });
    mod.method("Color_lemonChiffon", [](){ return colors::lemonChiffon; });
    mod.method("Color_lightYellow", [](){ return colors::lightYellow; });
    mod.method("Color_wheat", [](){ return colors::wheat; });
    mod.method("Color_moccasin", [](){ return colors::moccasin; });
    mod.method("Color_peachPuff", [](){ return colors::peachPuff; });
    mod.method("Color_papayaWhip", [](){ return colors::papayaWhip; });
    mod.method("Color_blanchedAlmond", [](){ return colors::blanchedAlmond; });
    mod.method("Color_bisque", [](){ return colors::bisque; });
    mod.method("Color_navajoWhite", [](){ return colors::navajoWhite; });
    mod.method("Color_slateGray", [](){ return colors::slateGray; });
    mod.method("Color_lightSlateGray", [](){ return colors::lightSlateGray; });
    mod.method("Color_darkSlateGray", [](){ return colors::darkSlateGray; });

  mod.add_enum<PrimitiveMode>("PrimitiveMode",
        std::vector<const char*>({
            "Triangles",
            "TriangleStrip",
            "TriangleFan",
            "Lines",
            "LineStrip",
            "LineLoop",
            "Points"
        }),
        std::vector<int>({
            (int)PrimitiveMode::Triangles,
            (int)PrimitiveMode::TriangleStrip,
            (int)PrimitiveMode::TriangleFan,
            (int)PrimitiveMode::Lines,
            (int)PrimitiveMode::LineStrip,
            (int)PrimitiveMode::LineLoop,
            (int)PrimitiveMode::Points
        })
    );

  auto img_type = mod.add_type<Image>("Image")
      .constructor<>(); // FIXME: move constructor?;
  auto tex_type = mod.add_type<Texture>("Texture")
      .constructor<>(); // FIXME: move constructor?;
  auto sg_image_type = mod.add_type<sg_image>("sg_image");
  auto sg_view_type = mod.add_type<sg_view>("sg_view");
  auto sg_sampler_type = mod.add_type<sg_sampler>("sg_sampler");
  auto sg_shader_desc_type = mod.add_type<sg_shader_desc>("sg_shader_desc");

  mod.add_enum<sg_pixel_format>("sg_pixel_format",
        std::vector<const char*>({
            "_SG_PIXELFORMAT_DEFAULT",
            "SG_PIXELFORMAT_NONE",
            "SG_PIXELFORMAT_R8",
            "SG_PIXELFORMAT_R8SN",
            "SG_PIXELFORMAT_R8UI",
            "SG_PIXELFORMAT_R8SI",
            "SG_PIXELFORMAT_R16",
            "SG_PIXELFORMAT_R16SN",
            "SG_PIXELFORMAT_R16UI",
            "SG_PIXELFORMAT_R16SI",
            "SG_PIXELFORMAT_R16F",
            "SG_PIXELFORMAT_RG8",
            "SG_PIXELFORMAT_RG8SN",
            "SG_PIXELFORMAT_RG8UI",
            "SG_PIXELFORMAT_RG8SI",
            "SG_PIXELFORMAT_R32UI",
            "SG_PIXELFORMAT_R32SI",
            "SG_PIXELFORMAT_R32F",
            "SG_PIXELFORMAT_RG16",
            "SG_PIXELFORMAT_RG16SN",
            "SG_PIXELFORMAT_RG16UI",
            "SG_PIXELFORMAT_RG16SI",
            "SG_PIXELFORMAT_RG16F",
            "SG_PIXELFORMAT_RGBA8",
            "SG_PIXELFORMAT_SRGB8A8",
            "SG_PIXELFORMAT_RGBA8SN",
            "SG_PIXELFORMAT_RGBA8UI",
            "SG_PIXELFORMAT_RGBA8SI",
            "SG_PIXELFORMAT_BGRA8",
            "SG_PIXELFORMAT_RGB10A2",
            "SG_PIXELFORMAT_RG11B10F",
            "SG_PIXELFORMAT_RGB9E5",
            "SG_PIXELFORMAT_RG32UI",
            "SG_PIXELFORMAT_RG32SI",
            "SG_PIXELFORMAT_RG32F",
            "SG_PIXELFORMAT_RGBA16",
            "SG_PIXELFORMAT_RGBA16SN",
            "SG_PIXELFORMAT_RGBA16UI",
            "SG_PIXELFORMAT_RGBA16SI",
            "SG_PIXELFORMAT_RGBA16F",
            "SG_PIXELFORMAT_RGBA32UI",
            "SG_PIXELFORMAT_RGBA32SI",
            "SG_PIXELFORMAT_RGBA32F",
            "SG_PIXELFORMAT_DEPTH",
            "SG_PIXELFORMAT_DEPTH_STENCIL",
            "SG_PIXELFORMAT_BC1_RGBA",
            "SG_PIXELFORMAT_BC2_RGBA",
            "SG_PIXELFORMAT_BC3_RGBA",
            "SG_PIXELFORMAT_BC3_SRGBA",
            "SG_PIXELFORMAT_BC4_R",
            "SG_PIXELFORMAT_BC4_RSN",
            "SG_PIXELFORMAT_BC5_RG",
            "SG_PIXELFORMAT_BC5_RGSN",
            "SG_PIXELFORMAT_BC6H_RGBF",
            "SG_PIXELFORMAT_BC6H_RGBUF",
            "SG_PIXELFORMAT_BC7_RGBA",
            "SG_PIXELFORMAT_BC7_SRGBA",
            "SG_PIXELFORMAT_ETC2_RGB8",
            "SG_PIXELFORMAT_ETC2_SRGB8",
            "SG_PIXELFORMAT_ETC2_RGB8A1",
            "SG_PIXELFORMAT_ETC2_RGBA8",
            "SG_PIXELFORMAT_ETC2_SRGB8A8",
            "SG_PIXELFORMAT_EAC_R11",
            "SG_PIXELFORMAT_EAC_R11SN",
            "SG_PIXELFORMAT_EAC_RG11",
            "SG_PIXELFORMAT_EAC_RG11SN",
            "SG_PIXELFORMAT_ASTC_4x4_RGBA",
            "SG_PIXELFORMAT_ASTC_4x4_SRGBA",
            "_SG_PIXELFORMAT_NUM",
        }),
        std::vector<int>({
            (int)sg_pixel_format::_SG_PIXELFORMAT_DEFAULT,
            (int)sg_pixel_format::SG_PIXELFORMAT_NONE,
            (int)sg_pixel_format::SG_PIXELFORMAT_R8,
            (int)sg_pixel_format::SG_PIXELFORMAT_R8SN,
            (int)sg_pixel_format::SG_PIXELFORMAT_R8UI,
            (int)sg_pixel_format::SG_PIXELFORMAT_R8SI,
            (int)sg_pixel_format::SG_PIXELFORMAT_R16,
            (int)sg_pixel_format::SG_PIXELFORMAT_R16SN,
            (int)sg_pixel_format::SG_PIXELFORMAT_R16UI,
            (int)sg_pixel_format::SG_PIXELFORMAT_R16SI,
            (int)sg_pixel_format::SG_PIXELFORMAT_R16F,
            (int)sg_pixel_format::SG_PIXELFORMAT_RG8,
            (int)sg_pixel_format::SG_PIXELFORMAT_RG8SN,
            (int)sg_pixel_format::SG_PIXELFORMAT_RG8UI,
            (int)sg_pixel_format::SG_PIXELFORMAT_RG8SI,
            (int)sg_pixel_format::SG_PIXELFORMAT_R32UI,
            (int)sg_pixel_format::SG_PIXELFORMAT_R32SI,
            (int)sg_pixel_format::SG_PIXELFORMAT_R32F,
            (int)sg_pixel_format::SG_PIXELFORMAT_RG16,
            (int)sg_pixel_format::SG_PIXELFORMAT_RG16SN,
            (int)sg_pixel_format::SG_PIXELFORMAT_RG16UI,
            (int)sg_pixel_format::SG_PIXELFORMAT_RG16SI,
            (int)sg_pixel_format::SG_PIXELFORMAT_RG16F,
            (int)sg_pixel_format::SG_PIXELFORMAT_RGBA8,
            (int)sg_pixel_format::SG_PIXELFORMAT_SRGB8A8,
            (int)sg_pixel_format::SG_PIXELFORMAT_RGBA8SN,
            (int)sg_pixel_format::SG_PIXELFORMAT_RGBA8UI,
            (int)sg_pixel_format::SG_PIXELFORMAT_RGBA8SI,
            (int)sg_pixel_format::SG_PIXELFORMAT_BGRA8,
            (int)sg_pixel_format::SG_PIXELFORMAT_RGB10A2,
            (int)sg_pixel_format::SG_PIXELFORMAT_RG11B10F,
            (int)sg_pixel_format::SG_PIXELFORMAT_RGB9E5,
            (int)sg_pixel_format::SG_PIXELFORMAT_RG32UI,
            (int)sg_pixel_format::SG_PIXELFORMAT_RG32SI,
            (int)sg_pixel_format::SG_PIXELFORMAT_RG32F,
            (int)sg_pixel_format::SG_PIXELFORMAT_RGBA16,
            (int)sg_pixel_format::SG_PIXELFORMAT_RGBA16SN,
            (int)sg_pixel_format::SG_PIXELFORMAT_RGBA16UI,
            (int)sg_pixel_format::SG_PIXELFORMAT_RGBA16SI,
            (int)sg_pixel_format::SG_PIXELFORMAT_RGBA16F,
            (int)sg_pixel_format::SG_PIXELFORMAT_RGBA32UI,
            (int)sg_pixel_format::SG_PIXELFORMAT_RGBA32SI,
            (int)sg_pixel_format::SG_PIXELFORMAT_RGBA32F,
            (int)sg_pixel_format::SG_PIXELFORMAT_DEPTH,
            (int)sg_pixel_format::SG_PIXELFORMAT_DEPTH_STENCIL,
            (int)sg_pixel_format::SG_PIXELFORMAT_BC1_RGBA,
            (int)sg_pixel_format::SG_PIXELFORMAT_BC2_RGBA,
            (int)sg_pixel_format::SG_PIXELFORMAT_BC3_RGBA,
            (int)sg_pixel_format::SG_PIXELFORMAT_BC3_SRGBA,
            (int)sg_pixel_format::SG_PIXELFORMAT_BC4_R,
            (int)sg_pixel_format::SG_PIXELFORMAT_BC4_RSN,
            (int)sg_pixel_format::SG_PIXELFORMAT_BC5_RG,
            (int)sg_pixel_format::SG_PIXELFORMAT_BC5_RGSN,
            (int)sg_pixel_format::SG_PIXELFORMAT_BC6H_RGBF,
            (int)sg_pixel_format::SG_PIXELFORMAT_BC6H_RGBUF,
            (int)sg_pixel_format::SG_PIXELFORMAT_BC7_RGBA,
            (int)sg_pixel_format::SG_PIXELFORMAT_BC7_SRGBA,
            (int)sg_pixel_format::SG_PIXELFORMAT_ETC2_RGB8,
            (int)sg_pixel_format::SG_PIXELFORMAT_ETC2_SRGB8,
            (int)sg_pixel_format::SG_PIXELFORMAT_ETC2_RGB8A1,
            (int)sg_pixel_format::SG_PIXELFORMAT_ETC2_RGBA8,
            (int)sg_pixel_format::SG_PIXELFORMAT_ETC2_SRGB8A8,
            (int)sg_pixel_format::SG_PIXELFORMAT_EAC_R11,
            (int)sg_pixel_format::SG_PIXELFORMAT_EAC_R11SN,
            (int)sg_pixel_format::SG_PIXELFORMAT_EAC_RG11,
            (int)sg_pixel_format::SG_PIXELFORMAT_EAC_RG11SN,
            (int)sg_pixel_format::SG_PIXELFORMAT_ASTC_4x4_RGBA,
            (int)sg_pixel_format::SG_PIXELFORMAT_ASTC_4x4_SRGBA,
            (int)sg_pixel_format::_SG_PIXELFORMAT_NUM,
        })
    );


  mod.add_type<Mesh>("Mesh")
    .constructor<>()
    .constructor<const Mesh&>()
    // FIXME: move constructor?
    .method("setMode", &Mesh::setMode)
    .method("getMode", &Mesh::getMode)
    .method("addVertex", [](Mesh& m, float x, float y){ return m.addVertex(x, y); })
    .method("addVertex", [](Mesh& m, float x, float y, float z){ return m.addVertex(x, y, z); })
    .method("addVertex", [](Mesh& m, const Vec2& v){ return m.addVertex(v); })
    .method("addVertex", [](Mesh& m, const Vec3& v){ return m.addVertex(v); })
    .method("addVertices", &Mesh::addVertices)
    .method("getVertices", [](Mesh& m){ return m.getVertices(); })
    // .method("addVertices", [](Mesh& m, jlcxx::ArrayRef<Vec3> vs){
    //     for(auto&& v: vs){
    //         m.addVertex(v);
    //     }
    // })
    // .method("getVertices", [](Mesh& m){ 
    //     auto&& vs = m.getVertices();
    //     jlcxx::Array<Vec3> data{};
    //     for(auto&& v: vs){
    //         data.push_back(v);
    //     }
    //     return data;
    // })
    .method("getNumVertices", &Mesh::getNumVertices)
    .method("addColor", [](Mesh& m, float x, float y, float z){ return m.addColor(x, y, z); })
    .method("addColor", [](Mesh& m, float x, float y, float z, float w){ return m.addColor(x, y, z, w); })
    .method("addColor", [](Mesh& m, const Color& v){ return m.addColor(v); })
    .method("addColors", &Mesh::addColors)
    .method("getColors", [](Mesh& m){ return m.getColors(); })
    // .method("addColors", [](Mesh& m, jlcxx::ArrayRef<Color> vs){
    //     for(auto&& v: vs){
    //         m.addColor(v);
    //     }
    // })
    // .method("getColors", [](Mesh& m){ 
    //     auto&& vs = m.getColors();
    //     jlcxx::Array<Color> data{};
    //     for(auto&& v: vs){
    //         data.push_back(v);
    //     }
    //     return data;
    // })
    .method("getNumColors", &Mesh::getNumColors)
    .method("hasColors", &Mesh::hasColors)
    .method("addIndex", &Mesh::addIndex)
    .method("addIndices", &Mesh::addIndices)
    // .method("addIndices", [](Mesh& m, jlcxx::ArrayRef<unsigned int> vs){
    //     for(auto&& v: vs){
    //         m.addIndex(v);
    //     }
    // })
    // .method("getIndices", [](Mesh& m){ 
    //     auto&& vs = m.getIndices();
    //     jlcxx::Array<unsigned int> data{};
    //     for(auto&& v: vs){
    //         data.push_back(v);
    //     }
    //     return data;
    // })
    .method("addTriangle", &Mesh::addTriangle)
    .method("getIndices", [](Mesh& m){ return m.getIndices(); })
    .method("hasIndices", &Mesh::hasIndices)
    .method("addNormal", [](Mesh& m, float x, float y, float z){ return m.addNormal(x, y, z); })
    .method("addNormal", [](Mesh& m, const Vec3& v){ return m.addNormal(v); })
    .method("addNormals", &Mesh::addNormals)
    // .method("addNormals", [](Mesh& m, jlcxx::ArrayRef<Vec3> vs){
    //     for(auto&& v: vs){
    //         m.addNormal(v);
    //     }
    // })
    // .method("getNormals", [](Mesh& m){ 
    //     auto&& vs = m.getNormals();
    //     jlcxx::Array<Vec3> data{};
    //     for(auto&& v: vs){
    //         data.push_back(v);
    //     }
    //     return data;
    // })
    .method("setNormal", &Mesh::setNormal)
    .method("getNormal", &Mesh::getNormal)
    .method("getNormals", [](Mesh& m){ return m.getNormals(); })
    .method("getNumNormals", &Mesh::getNumNormals)
    .method("hasNormals", &Mesh::hasNormals)
    .method("addTexCoord", [](Mesh& m, float x, float y){ return m.addTexCoord(x, y); })
    .method("addTexCoord", [](Mesh& m, const Vec2& v){ return m.addTexCoord(v); })
    .method("getTexCoords", [](Mesh& m){ return m.getTexCoords(); })
    // .method("getTexCoords", [](Mesh& m){ 
    //     auto&& vs = m.getTexCoords();
    //     jlcxx::Array<Vec2> data{};
    //     for(auto&& v: vs){
    //         data.push_back(v);
    //     }
    //     return data;
    // })
    .method("hasTexCoords", &Mesh::hasTexCoords)
    .method("hasValidTexCoords", &Mesh::hasValidTexCoords)
    .method("addTangent", [](Mesh& m, float x, float y, float z){ return m.addTangent(x, y, z); })
    .method("addTangent", [](Mesh& m, float x, float y, float z, float w){ return m.addTangent(x, y, z, w); })
    .method("addTangent", [](Mesh& m, const Vec4& v){ return m.addTangent(v); })
    .method("getTangents", [](Mesh& m){ return m.getTangents(); })
    // .method("getTangents", [](Mesh& m){ 
    //     auto&& vs = m.getTangents();
    //     jlcxx::Array<Vec4> data{};
    //     for(auto&& v: vs){
    //         data.push_back(v);
    //     }
    //     return data;
    // })
    .method("getNumTangents", &Mesh::getNumTangents)
    .method("hasTangents", &Mesh::hasTangents)
    .method("clear", &Mesh::clear)
    .method("clearVertices", &Mesh::clearVertices)
    .method("clearNormals", &Mesh::clearNormals)
    .method("clearColors", &Mesh::clearColors)
    .method("clearIndices", &Mesh::clearIndices)
    .method("clearTexCoords", &Mesh::clearTexCoords)
    .method("clearTangents", &Mesh::clearTangents)
    .method("translate", [](Mesh& m, float x, float y, float z){ return m.translate(x, y, z); })
    .method("translate", [](Mesh& m, const Vec3& v){ return m.translate(v); })
    .method("rotateX", &Mesh::rotateX)
    .method("rotateY", &Mesh::rotateY)
    .method("rotateZ", &Mesh::rotateZ)
    .method("scale", [](Mesh& m, float x, float y, float z){ return m.scale(x, y, z); })
    .method("scale", [](Mesh& m, float s){ return m.scale(s); })
    .method("transform", &Mesh::transform)
    .method("append", &Mesh::append)
    .method("draw", [](Mesh& m){ return m.draw(); })
    .method("draw", [](Mesh& m, const Image& image){ return m.draw(image); })
    .method("draw", [](Mesh& m, const Texture& tex){ return m.draw(tex); })
    .method("drawNoLighting", &Mesh::drawNoLighting)
    .method("drawWithLighting", &Mesh::drawWithLighting)
    .method("drawNoLightingWithTexture", &Mesh::drawNoLightingWithTexture)
    .method("drawWireframe", &Mesh::drawWireframe)
    ;

    mod.add_type<std::filesystem::path>("StdPath")
        .constructor<>()
        .constructor<const std::string&>()
        .method("c_str", [](std::filesystem::path& p){ return p.c_str(); })
        .method("string", [](std::filesystem::path& p){ return p.string(); })
        .method("exists", [](std::filesystem::path& p){ return std::filesystem::exists(p); })
        .method("is_directory", [](std::filesystem::path& p){ return std::filesystem::is_directory(p); })
        .method("is_dir", [](std::filesystem::path& p){ return std::filesystem::is_directory(p); })
        .method("is_file", [](std::filesystem::path& p){ return std::filesystem::is_regular_file(p); })
        .method("is_regular_file", [](std::filesystem::path& p){ return std::filesystem::is_regular_file(p); })
        .method("is_empty", [](std::filesystem::path& p){ return std::filesystem::is_empty(p); })
        .method("absolute", [](std::filesystem::path& p){ return std::filesystem::absolute(p); })
        .method("relative", [](std::filesystem::path& p){ return std::filesystem::relative(p); })
        .method("relative", [](std::filesystem::path& p, const std::filesystem::path& b){ return std::filesystem::relative(p, b); })
        .method("div", [](std::filesystem::path& p, const std::filesystem::path& b){ return p / b; })
        .method("div", [](std::filesystem::path& p, const std::string& b){ return p / b; })
        ;

    mod.method("path", [](const std::string& s){
      std::filesystem::path p(s);
      return p;
    });
    mod.method("toPath", [](const std::string& s){
      std::filesystem::path p(s);
      return p;
    });

    mod.add_enum<TextureFormat>("TextureFormat",
        std::vector<const char*>({
          "RGBA8",
          "RGBA16F",
          "RGBA32F",
          "R8",
          "R16F",
          "R32F",
          "RG8",
          "RG16F",
          "RG32F"
        }),
        std::vector<int>({
          (int)TextureFormat::RGBA8,
          (int)TextureFormat::RGBA16F,
          (int)TextureFormat::RGBA32F,
          (int)TextureFormat::R8,
          (int)TextureFormat::R16F,
          (int)TextureFormat::R32F,
          (int)TextureFormat::RG8,
          (int)TextureFormat::RG16F,
          (int)TextureFormat::RG32F
        }));

    mod.add_enum<TextureUsage>("TextureUsage",
        std::vector<const char*>({
          "Immutable",
          "Dynamic",
          "Stream",
          "RenderTarget"
        }),
        std::vector<int>({
          (int)TextureUsage::Immutable,
          (int)TextureUsage::Dynamic,
          (int)TextureUsage::Stream,
          (int)TextureUsage::RenderTarget
        }));

  mod.add_type<Fbo>("Fbo")
    .constructor<>()
    // FIXME: move constructor?
    .method("allocate", [](Fbo& f, int w, int h){ return f.allocate(w, h); })
    .method("allocate", [](Fbo& f, int w, int h, int sampleCount){ return f.allocate(w, h, sampleCount); })
    .method("allocate", [](Fbo& f, int w, int h, int sampleCount, TextureFormat t){ return f.allocate(w, h, sampleCount, t); })
    .method("clear", &Fbo::clear)
    .method("begin", [](Fbo& f){ return f.begin(); })
    .method("begin", [](Fbo& f, float r, float g, float b){ return f.begin(r, g, b); })
    .method("begin", [](Fbo& f, float r, float g, float b, float a){ return f.begin(r, g, b, a); })
    .method("begin_fbo", [](Fbo& f){ return f.begin(); })
    .method("begin_fbo", [](Fbo& f, float r, float g, float b){ return f.begin(r, g, b); })
    .method("begin_fbo", [](Fbo& f, float r, float g, float b, float a){ return f.begin(r, g, b, a); })
    .method("draw", [](Fbo& t, float x, float y){ return t.draw(x, y); })
    .method("draw", [](Fbo& t, float x, float y, float w, float h){ return t.draw(x, y, w, h); })
    .method("clearColor", &Fbo::clearColor)
    .method("end", &Fbo::end)
    .method("end_fbo", &Fbo::end)
    .method("readPixels", &Fbo::readPixels)
    .method("readPixelsFloat", &Fbo::readPixelsFloat)
    .method("copyTo", &Fbo::copyTo)
    .method("getWidth", &Fbo::getWidth)
    .method("getHeight", &Fbo::getHeight)
    .method("getSampleCount", &Fbo::getSampleCount)
    .method("getTextureFormat", &Fbo::getTextureFormat)
    .method("isAllocated", &Fbo::isAllocated)
    .method("isActive", &Fbo::isActive)
    .method("getTexture", [](Fbo& f) -> Texture& { return f.getTexture(); })
    .method("save", &Fbo::save)
    .method("save", [](Fbo& f, const std::string& path){ return f.save(path); })
    .method("getColorImage", &Fbo::getColorImage)
    .method("getTextureView", &Fbo::getTextureView)
    .method("getSampler", &Fbo::getSampler)
    ;

  auto pixels_type = mod.add_type<Pixels>("Pixels")
    .constructor<>() // FIXME: move constructor?
    ;

  mod.add_enum<TextureFilter>("TextureFilter",
    std::vector<const char*>({
        "Nearest",
        "Linear"
    }),
    std::vector<int>({
        (int)TextureFilter::Nearest,
        (int)TextureFilter::Linear
    }));

  mod.add_enum<TextureWrap>("TextureWrap",
    std::vector<const char*>({
        "Repeat",
        "ClampToEdge",
        "MirroredRepeat"
    }),
    std::vector<int>({
        (int)TextureWrap::Repeat,
        (int)TextureWrap::ClampToEdge,
        (int)TextureWrap::MirroredRepeat
    }));

  mod.add_enum<LightType>("LightType",
    std::vector<const char*>({
        "Directional",
        "Point",
        "Spot"
    }),
    std::vector<int>({
        (int)LightType::Directional,
        (int)LightType::Point,
        (int)LightType::Spot
    }));

  mod.add_enum<PixelFormat>("PixelFormat",
    std::vector<const char*>({
        "U8",
        "F32"
    }),
    std::vector<int>({
        (int)PixelFormat::U8,
        (int)PixelFormat::F32
    }));

  tex_type
    .method("allocate", [](Texture& f, int w, int h){ return f.allocate(w, h); })
    .method("allocate", [](Texture& f, int w, int h, int c){ return f.allocate(w, h, c); })
    .method("allocate", [](Texture& f, int w, int h, int c, TextureUsage t){ return f.allocate(w, h, c, t); })
    .method("allocate", [](Texture& f, int w, int h, int c, TextureUsage t, int s){ return f.allocate(w, h, c, t, s); })
    .method("allocate", [](Texture& f, int w, int h, TextureFormat c){ return f.allocate(w, h, c); })
    .method("allocate", [](Texture& f, int w, int h, TextureFormat c, TextureUsage t){ return f.allocate(w, h, c, t); })
    .method("allocate", [](Texture& f, int w, int h, TextureFormat c, TextureUsage t, int s){ return f.allocate(w, h, c, t, s); })
    .method("allocate", [](Texture& f, const Pixels& w){ return f.allocate(w); })
    .method("allocate", [](Texture& f, const Pixels& w, TextureUsage c){ return f.allocate(w, c); })
    .method("allocate", [](Texture& f, const Pixels& w, TextureUsage c, bool m){ return f.allocate(w, c, m); })
    .method("allocateCubemap", [](Texture& f, int w, TextureFormat c){ return f.allocateCubemap(w, c); })
    .method("allocateCubemap", [](Texture& f, int w, TextureFormat c, TextureUsage t){ return f.allocateCubemap(w, c, t); })
    .method("allocateCubemap", [](Texture& f, int w, TextureFormat c, TextureUsage t, int s){ return f.allocateCubemap(w, c, t, s); })
    .method("uploadCubemapFace", &Texture::uploadCubemapFace)
    .method("uploadCubemapMip", &Texture::uploadCubemapMip)
    .method("getCubemapFaceAttachmentView", &Texture::getCubemapFaceAttachmentView)
    .method("isCubemap", &Texture::isCubemap)
    .method("getNumMipLevels", &Texture::getNumMipLevels)
    .method("allocateCompressed", &Texture::allocateCompressed)
    .method("updateCompressed", &Texture::updateCompressed)
    .method("isCompressed", &Texture::isCompressed)
    .method("clear", &Texture::clear)
    .method("isAllocated", &Texture::isAllocated)
    .method("getWidth", &Texture::getWidth)
    .method("getHeight", &Texture::getHeight)
    .method("getChannels", &Texture::getChannels)
    .method("getUsage", &Texture::getUsage)
    .method("getSampleCount", &Texture::getSampleCount)
    .method("getPixelFormat", &Texture::getPixelFormat)
    .method("loadData", [](Texture& t, const Pixels& p){ return t.loadData(p); })
    .method("loadData", [](Texture& t, const unsigned char* d, int w, int h, int c){ return t.loadData(d, w, h, c); })
    .method("loadData", [](Texture& t, const void* d, int w, int h, int c){ return t.loadData(d, w, h, c); })
    .method("setMinFilter", &Texture::setMinFilter)
    .method("setMagFilter", &Texture::setMagFilter)
    .method("setFilter", &Texture::setFilter)
    .method("getMinFilter", &Texture::getMinFilter)
    .method("getMagFilter", &Texture::getMagFilter)
    .method("setPremultipliedAlpha", &Texture::setPremultipliedAlpha)
    .method("isPremultipliedAlpha", &Texture::isPremultipliedAlpha)
    .method("setWrapU", &Texture::setWrapU)
    .method("setWrapV", &Texture::setWrapV)
    .method("setWrap", &Texture::setWrap)
    .method("getWrapU", &Texture::getWrapU)
    .method("getWrapV", &Texture::getWrapV)
    .method("draw", [](Texture& t, float x, float y){ return t.draw(x, y); })
    .method("draw", [](Texture& t, float x, float y, float w, float h){ return t.draw(x, y, w, h); })
    .method("drawSubsection", &Texture::drawSubsection)
    .method("bind", &Texture::bind)
    .method("unbind", &Texture::unbind)
    .method("getImage", &Texture::getImage)
    .method("getView", &Texture::getView)
    .method("getSampler", &Texture::getSampler)
    .method("getAttachmentView", &Texture::getAttachmentView)
    ;

  img_type
    .method("load", &Image::load)
    .method("load", [](Image& img, const std::string& path){ return img.load(path); })
    .method("loadFromMemory", &Image::loadFromMemory)
    .method("draw", [](Image& t, float x, float y){ return t.draw(x, y); })
    .method("draw", [](Image& t, float x, float y, float w, float h){ return t.draw(x, y, w, h); })
    .method("save", &Image::save)
    .method("save", [](Image& img, const std::string& path){ return img.save(path); })
    .method("allocate", [](Image& t, int w, int h){ return t.allocate(w, h); })
    .method("allocate", [](Image& t, int w, int h, int c){ return t.allocate(w, h, c); })
    .method("clear", &Image::clear)
    .method("isAllocated", &Image::isAllocated)
    .method("getWidth", &Image::getWidth)
    .method("getHeight", &Image::getHeight)
    .method("getChannels", &Image::getChannels)
    .method("getPixels", [](Image& f) -> Pixels& { return f.getPixels(); })
    .method("getPixelsData", [](Image& f) -> unsigned char* { return f.getPixelsData(); })
    .method("getColor", &Image::getColor)
    .method("setColor", &Image::setColor)
    .method("update", &Image::update)
    .method("setDirty", &Image::setDirty)
    .method("getTexture", [](Image& f) -> Texture& { return f.getTexture(); })
    ;

  pixels_type
    .method("allocate", [](Pixels& f, int w, int h){ return f.allocate(w, h); })
    .method("allocate", [](Pixels& f, int w, int h, int c){ return f.allocate(w, h, c); })
    .method("allocate", [](Pixels& f, int w, int h, int c, PixelFormat t){ return f.allocate(w, h, c, t); })
    .method("clear", &Pixels::clear)
    .method("isAllocated", &Pixels::isAllocated)
    .method("getWidth", &Pixels::getWidth)
    .method("getHeight", &Pixels::getHeight)
    .method("getChannels", &Pixels::getChannels)
    .method("getFormat", &Pixels::getFormat)
    .method("isFloat", &Pixels::isFloat)
    .method("getTotalBytes", &Pixels::getTotalBytes)
    .method("getData", [](Pixels& f) -> unsigned char* { return f.getData(); })
    .method("getDataF32", [](Pixels& f) -> float* { return f.getDataF32(); })
    .method("getDataVoid", [](Pixels& f) -> void* { return f.getDataVoid(); })
    .method("getColor", &Pixels::getColor)
    .method("setColor", &Pixels::setColor)
    .method("setFromPixels", &Pixels::setFromPixels)
    .method("setFromFloats", &Pixels::setFromFloats)
    .method("copyTo", &Pixels::copyTo)
    .method("clone", &Pixels::clone)
    .method("load", &Pixels::load)
    .method("load", [](Pixels& p, const std::string& path){ return p.load(path); })
    .method("loadHDR", &Pixels::loadHDR)
    .method("loadPlatform", &Pixels::loadPlatform)
    .method("loadFromMemory", &Pixels::loadFromMemory)
    .method("save", &Pixels::save)
    .method("save", [](Pixels& p, const std::string& path){ return p.save(path); })
    ;

  auto light_type = mod.add_type<Light>("Light")
    .constructor<>()
    ;

  auto mate_type = mod.add_type<Material>("Material")
    .constructor<>()
    ;

  mod.add_type<LogStream>("LogStream");

  mod.add_type<FpsSettings>("FpsSettings");

  mod.add_type<IesProfile>("IesProfile");

//   mod.add_type<LogStream>("LogStream")
//     .constructor<LogLevel>()
//     .constructor<LogLevel, const std::string&>()
//     ;

  mod.add_enum<LogLevel>("LogLevel",
    std::vector<const char*>({
        "Verbose",
        "Notice",
        "Warning",
        "Error",
        "Fatal",
        "Silent"
    }),
    std::vector<int>({
        (int)LogLevel::Verbose,
        (int)LogLevel::Notice,
        (int)LogLevel::Warning,
        (int)LogLevel::Error,
        (int)LogLevel::Fatal,
        (int)LogLevel::Silent
    }));

  mod.add_enum<BlendMode>("BlendMode",
    std::vector<const char*>({
        "Alpha",
        "Add",
        "Multiply",
        "Screen",
        "Subtract",
        "Disabled"
    }),
    std::vector<int>({
        (int)BlendMode::Alpha,
        (int)BlendMode::Add,
        (int)BlendMode::Multiply,
        (int)BlendMode::Screen,
        (int)BlendMode::Subtract,
        (int)BlendMode::Disabled
    }));

  mod.add_enum<StrokeCap>("StrokeCap",
    std::vector<const char*>({
        "Butt",
        "Round",
        "Square"
    }),
    std::vector<int>({
        (int)StrokeCap::Butt,
        (int)StrokeCap::Round,
        (int)StrokeCap::Square
    }));

  mod.add_enum<StrokeJoin>("StrokeJoin",
    std::vector<const char*>({
        "Miter",
        "Round",
        "Bevel"
    }),
    std::vector<int>({
        (int)StrokeJoin::Miter,
        (int)StrokeJoin::Round,
        (int)StrokeJoin::Bevel
    }));

  mod.add_enum<Direction>("Direction",
    std::vector<const char*>({
        "Left",
        "Center",
        "Right",
        "Top",
        "Bottom",
        "Baseline"
    }),
    std::vector<int>({
        (int)Direction::Left,
        (int)Direction::Center,
        (int)Direction::Right,
        (int)Direction::Top,
        (int)Direction::Bottom,
        (int)Direction::Baseline
    }));

  mod.add_enum<Cursor>("Cursor",
    std::vector<const char*>({
        "Default",
        "Arrow",
        "IBeam",
        "Crosshair",
        "Hand",
        "ResizeEW",
        "ResizeNS",
        "ResizeNWSE",
        "ResizeNESW",
        "ResizeAll",
        "NotAllowed",
        "Custom0",
        "Custom1",
        "Custom2",
        "Custom3",
        "Custom4",
        "Custom5",
        "Custom6",
        "Custom7",
        "Custom8",
        "Custom9",
        "Custom10",
        "Custom11",
        "Custom12",
        "Custom13",
        "Custom14",
        "Custom15"
    }),
    std::vector<int>({
        (int)Cursor::Default,
        (int)Cursor::Arrow,
        (int)Cursor::IBeam,
        (int)Cursor::Crosshair,
        (int)Cursor::Hand,
        (int)Cursor::ResizeEW,
        (int)Cursor::ResizeNS,
        (int)Cursor::ResizeNWSE,
        (int)Cursor::ResizeNESW,
        (int)Cursor::ResizeAll,
        (int)Cursor::NotAllowed,
        (int)Cursor::Custom0,
        (int)Cursor::Custom1,
        (int)Cursor::Custom2,
        (int)Cursor::Custom3,
        (int)Cursor::Custom4,
        (int)Cursor::Custom5,
        (int)Cursor::Custom6,
        (int)Cursor::Custom7,
        (int)Cursor::Custom8,
        (int)Cursor::Custom9,
        (int)Cursor::Custom10,
        (int)Cursor::Custom11,
        (int)Cursor::Custom12,
        (int)Cursor::Custom13,
        (int)Cursor::Custom14,
        (int)Cursor::Custom15
    }));

    mod.add_enum<Orientation>("Orientation",
        std::vector<const char*>({
            "Portrait",
            "PortraitUpsideDown",
            "LandscapeLeft",
            "LandscapeRight",
            "Landscape",
            "All",
            "AllButUpsideDown"
        }),
        std::vector<uint32_t>({
            (int)Orientation::Portrait,
            (int)Orientation::PortraitUpsideDown,
            (int)Orientation::LandscapeLeft,
            (int)Orientation::LandscapeRight,
            (int)Orientation::Landscape,
            (int)Orientation::All,
            (int)Orientation::AllButUpsideDown
        }));

    mod.add_enum<PrimitiveType>("PrimitiveType",
        std::vector<const char*>({
          "Points",
          "Lines",
          "LineStrip",
          "Triangles",
          "TriangleStrip",
          "Quads"
        }),
        std::vector<uint32_t>({
          (int)PrimitiveType::Points,
          (int)PrimitiveType::Lines,
          (int)PrimitiveType::LineStrip,
          (int)PrimitiveType::Triangles,
          (int)PrimitiveType::TriangleStrip,
          (int)PrimitiveType::Quads
        }));

  mod.add_type<ShaderVertex>("ShaderVertex")
    .constructor<>() // FIXME: move constructor?
    .method("x", [](ShaderVertex& v){ return v.x; })
    .method("y", [](ShaderVertex& v){ return v.y; })
    .method("z", [](ShaderVertex& v){ return v.z; })
    .method("r", [](ShaderVertex& v){ return v.r; })
    .method("g", [](ShaderVertex& v){ return v.g; })
    .method("b", [](ShaderVertex& v){ return v.b; })
    .method("a", [](ShaderVertex& v){ return v.a; })
    .method("u", [](ShaderVertex& v){ return v.u; })
    .method("v", [](ShaderVertex& v){ return v.v; })
    .method("x!", [](ShaderVertex& v, float p){ v.x = p; })
    .method("y!", [](ShaderVertex& v, float p){ v.y = p; })
    .method("z!", [](ShaderVertex& v, float p){ v.z = p; })
    .method("u!", [](ShaderVertex& v, float p){ v.u = p; })
    .method("v!", [](ShaderVertex& v, float p){ v.v = p; })
    .method("r!", [](ShaderVertex& v, float p){ v.r = p; })
    .method("g!", [](ShaderVertex& v, float p){ v.g = p; })
    .method("b!", [](ShaderVertex& v, float p){ v.b = p; })
    .method("a!", [](ShaderVertex& v, float p){ v.a = p; })
    ;

  mod.add_type<Shader>("Shader")
    .constructor<>() // FIXME: move constructor?
    .method("load", [](Shader& f, void* desc_fn) -> bool {
      typedef const sg_shader_desc *(*func_type)(sg_backend);
      func_type fn_ptr = (func_type)(desc_fn);
      return f.load(fn_ptr);
    })
    .method("clear", &Shader::clear)
    .method("isLoaded", &Shader::isLoaded)
    .method("begin", &Shader::begin)
    .method("begin_shader", &Shader::begin)
    .method("end", &Shader::end)
    .method("end_shader", &Shader::end)
    .method("setUniform", [](Shader& f, int s, float v){ return f.setUniform(s, v); })
    .method("setUniform", [](Shader& f, int s, const Vec2& v){ return f.setUniform(s, v); })
    .method("setUniform", [](Shader& f, int s, const Vec3& v){ return f.setUniform(s, v); })
    .method("setUniform", [](Shader& f, int s, const Vec4& v){ return f.setUniform(s, v); })
    .method("setUniform", [](Shader& f, int s, const Color& v){ return f.setUniform(s, v); })
    .method("setUniform", [](Shader& f, int s, const std::vector<float>& v){ return f.setUniform(s, v); })
    .method("setUniform", [](Shader& f, int s, const std::vector<Vec2>& v){ return f.setUniform(s, v); })
    .method("setUniform", [](Shader& f, int s, const std::vector<Vec3>& v){ return f.setUniform(s, v); })
    .method("setUniform", [](Shader& f, int s, const std::vector<Vec4>& v){ return f.setUniform(s, v); })
    .method("setUniform", [](Shader& f, int s, const void* data, size_t size){ return f.setUniform(s, data, size); })
    .method("storeUniform", &Shader::storeUniform)
    .method("applyUniforms", &Shader::applyUniforms)
    .method("setTexture", [](Shader& f, int s, sg_image i, sg_sampler p){ return f.setTexture(s, i, p); })
    .method("setTexture", [](Shader& f, int s, sg_view i, sg_sampler p){ return f.setTexture(s, i, p); })
    .method("submitVertices", &Shader::submitVertices)
    .method("executeDeferredDraw", &Shader::executeDeferredDraw)
    ;

  mod.add_type<EasyCam>("EasyCam")
    .constructor<>() // FIXME: move constructor?
    .method("begin", &EasyCam::begin)
    .method("begin_cam", &EasyCam::begin)
    .method("begin_easycam", &EasyCam::begin)
    .method("end", &EasyCam::end)
    .method("end_cam", &EasyCam::end)
    .method("end_easycam", &EasyCam::end)
    .method("reset", &EasyCam::reset)
    .method("setTarget", [](EasyCam& m, float x, float y, float z){ return m.setTarget(x, y, z); })
    .method("setTarget", [](EasyCam& m, const Vec3& v){ return m.setTarget(v); })
    .method("getTarget", &EasyCam::getTarget)
    .method("setUpAxis", [](EasyCam& m, float x, float y, float z){ return m.setUpAxis(x, y, z); })
    .method("setUpAxis", [](EasyCam& m, const Vec3& v){ return m.setUpAxis(v); })
    .method("getUpAxis", &EasyCam::getUpAxis)
    .method("setDistance", &EasyCam::setDistance)
    .method("getDistance", &EasyCam::getDistance)
    .method("setFov", &EasyCam::setFov)
    .method("getFov", &EasyCam::getFov)
    .method("getPosition", &EasyCam::getPosition)
    .method("setFovDeg", &EasyCam::setFovDeg)
    .method("setNearClip", &EasyCam::setNearClip)
    .method("setFarClip", &EasyCam::setFarClip)
    .method("setSensitivity", &EasyCam::setSensitivity)
    .method("setZoomSensitivity", &EasyCam::setZoomSensitivity)
    .method("setPanSensitivity", &EasyCam::setPanSensitivity)
    .method("setControlArea", &EasyCam::setControlArea)
    .method("clearControlArea", &EasyCam::clearControlArea)
    .method("enableMouseInput", &EasyCam::enableMouseInput)
    .method("disableMouseInput", &EasyCam::disableMouseInput)
    .method("isMouseInputEnabled", &EasyCam::isMouseInputEnabled)
    .method("mousePressed", &EasyCam::mousePressed)
    .method("mouseReleased", &EasyCam::mouseReleased)
    .method("mouseDragged", &EasyCam::mouseDragged)
    .method("mouseScrolled", &EasyCam::mouseScrolled)
    ;

  light_type
    .method("setDirectional", [](Light& m, float x, float y, float z){ return m.setDirectional(x, y, z); })
    .method("setDirectional", [](Light& m, const Vec3& v){ return m.setDirectional(v); })
    .method("setPoint", [](Light& m, float x, float y, float z){ return m.setPoint(x, y, z); })
    .method("setPoint", [](Light& m, const Vec3& v){ return m.setPoint(v); })
    .method("setSpot", [](Light& m, const Vec3& p, const Vec3& d){ return m.setSpot(p, d); })
    .method("setSpot", [](Light& m, const Vec3& p, const Vec3& d, float i){ return m.setSpot(p, d, i); })
    .method("setSpot", [](Light& m, const Vec3& p, const Vec3& d, float i, float o){ return m.setSpot(p, d, i, o); })
    .method("setSpot", [](Light& m, float a, float b, float c, float d, float e, float f){ return m.setSpot(a,b,c,d,e,f); })
    .method("setSpot", [](Light& m, float a, float b, float c, float d, float e, float f, float i){ return m.setSpot(a,b,c,d,e,f, i); })
    .method("setSpot", [](Light& m, float a, float b, float c, float d, float e, float f, float i, float o){ return m.setSpot(a,b,c,d,e,f, i,o); })
    .method("getSpotInnerCos", &Light::getSpotInnerCos)
    .method("getSpotOuterCos", &Light::getSpotOuterCos)
    .method("setProjectionTexture", &Light::setProjectionTexture)
    .method("getProjectionTexture", &Light::getProjectionTexture)
    .method("hasProjectionTexture", &Light::hasProjectionTexture)
    .method("setLensShift", &Light::setLensShift)
    .method("getLensShiftX", &Light::getLensShiftX)
    .method("getLensShiftY", &Light::getLensShiftY)
    .method("setProjectorAspect", &Light::setProjectorAspect)
    .method("getProjectorAspect", &Light::getProjectorAspect)
    .method("computeProjectorViewProj", [](Light& m){ return m.computeProjectorViewProj(); })
    .method("computeProjectorViewProj", [](Light& m, float a){ return m.computeProjectorViewProj(a); })
    .method("computeProjectorViewProj", [](Light& m, float a, float b){ return m.computeProjectorViewProj(a, b); })
    .method("setIesProfile", &Light::setIesProfile)
    .method("getIesProfile", &Light::getIesProfile)
    .method("hasIesProfile", &Light::hasIesProfile)
    .method("enableShadow", &Light::enableShadow)
    .method("disableShadow", &Light::disableShadow)
    .method("isShadowEnabled", &Light::isShadowEnabled)
    .method("getShadowResolution", &Light::getShadowResolution)
    .method("setShadowBias", &Light::setShadowBias)
    .method("getShadowBias", &Light::getShadowBias)
    .method("getType", &Light::getType)
    .method("getDirection", &Light::getDirection)
    .method("getPosition", &Light::getPosition)
    .method("setAmbient", [](Light& m, const Color& c){ return m.setAmbient(c); })
    .method("setAmbient", [](Light& m, float a, float b, float c){ return m.setAmbient(a,b,c); })
    .method("setAmbient", [](Light& m, float a, float b, float c, float d){ return m.setAmbient(a,b,c,d); })
    .method("setDiffuse", [](Light& m, const Color& c){ return m.setDiffuse(c); })
    .method("setDiffuse", [](Light& m, float a, float b, float c){ return m.setDiffuse(a,b,c); })
    .method("setDiffuse", [](Light& m, float a, float b, float c, float d){ return m.setDiffuse(a,b,c,d); })
    .method("setSpecular", [](Light& m, const Color& c){ return m.setSpecular(c); })
    .method("setSpecular", [](Light& m, float a, float b, float c){ return m.setSpecular(a,b,c); })
    .method("setSpecular", [](Light& m, float a, float b, float c, float d){ return m.setSpecular(a,b,c,d); })
    .method("getAmbient", &Light::getAmbient)
    .method("getDiffuse", &Light::getDiffuse)
    .method("getSpecular", &Light::getSpecular)
    .method("getIntensity", &Light::getIntensity)
    .method("setIntensity", &Light::setIntensity)
    .method("setAttenuation", &Light::setAttenuation)
    .method("getConstantAttenuation", &Light::getConstantAttenuation)
    .method("getLinearAttenuation", &Light::getLinearAttenuation)
    .method("getQuadraticAttenuation", &Light::getQuadraticAttenuation)
    .method("enable", &Light::enable)
    .method("disable", &Light::disable)
    .method("isEnabled", &Light::isEnabled)
    .method("calculate", &Light::calculate)
    ;

  mate_type
    .method("getBaseColor", &Material::getBaseColor)
    .method("setBaseColor", [](Material& m, const Color& c){ return m.setBaseColor(c); })
    .method("setBaseColor", [](Material& m, float a, float b, float c){ return m.setBaseColor(a,b,c); })
    .method("setBaseColor", [](Material& m, float a, float b, float c, float d){ return m.setBaseColor(a,b,c,d); })
    .method("setMetallic", &Material::setMetallic)
    .method("getMetallic", &Material::getMetallic)
    .method("setRoughness", &Material::setRoughness)
    .method("getRoughness", &Material::getRoughness)
    .method("setAo", &Material::setAo)
    .method("getAo", &Material::getAo)
    .method("getEmissiveStrength", &Material::getEmissiveStrength)
    .method("setEmissiveStrength", &Material::setEmissiveStrength)
    .method("getEmissive", &Material::getEmissive)
    .method("setEmissive", [](Material& m, const Color& c){ return m.setEmissive(c); })
    .method("setEmissive", [](Material& m, float a, float b, float c){ return m.setEmissive(a,b,c); })
    .method("setNormalMap", &Material::setNormalMap)
    .method("getNormalMap", &Material::getNormalMap)
    .method("hasNormalMap", &Material::hasNormalMap)
    .method("setBaseColorTexture", &Material::setBaseColorTexture)
    .method("getBaseColorTexture", &Material::getBaseColorTexture)
    .method("hasBaseColorTexture", &Material::hasBaseColorTexture)
    .method("setMetallicRoughnessTexture", &Material::setMetallicRoughnessTexture)
    .method("getMetallicRoughnessTexture", &Material::getMetallicRoughnessTexture)
    .method("hasMetallicRoughnessTexture", &Material::hasMetallicRoughnessTexture)
    .method("setEmissiveTexture", &Material::setEmissiveTexture)
    .method("getEmissiveTexture", &Material::getEmissiveTexture)
    .method("hasEmissiveTexture", &Material::hasEmissiveTexture)
    .method("setOcclusionTexture", &Material::setOcclusionTexture)
    .method("getOcclusionTexture", &Material::getOcclusionTexture)
    .method("hasOcclusionTexture", &Material::hasOcclusionTexture)
    ;

  mod.method("Material_gold", [](){ return Material::gold(); });
  mod.method("Material_silver", [](){ return Material::silver(); });
  mod.method("Material_copper", [](){ return Material::copper(); });
  mod.method("Material_iron", [](){ return Material::iron(); });
  mod.method("Material_bronze", [](){ return Material::bronze(); });
  mod.method("Material_emerald", [](){ return Material::emerald(); });
  mod.method("Material_ruby", [](){ return Material::ruby(); });
  mod.method("Material_plastic", [](const Color& c, float r){ return Material::plastic(c, r); });
  mod.method("Material_plastic", [](const Color& c){ return Material::plastic(c); });
  mod.method("Material_rubber", [](const Color& c){ return Material::rubber(c); });
  mod.method("Material_fromPhong", [](const Color& d, const Color& p, float s){ return Material::fromPhong(d, p, s); });
  mod.method("Material_fromPhong", [](const Color& d, const Color& p, float s, const Color& e){ return Material::fromPhong(d, p, s, e); });

  auto json_type = mod.add_type<Json>("Json")
    .constructor<>() // FIXME: move constructor?
    ;

  json_type
    .method("get_string", [](Json& j){ return j.get<std::string>(); })
    .method("get_double", [](Json& j){ return j.get<double>(); })
    .method("get_float", [](Json& j){ return j.get<float>(); })
    .method("get_int", [](Json& j){ return j.get<int>(); })
    .method("get_bool", [](Json& j){ return j.get<bool>(); })
    .method("empty", &Json::empty)
    .method("size", &Json::size)
    .method("at", [](Json& j, size_t i){ return j[i]; })
    .method("at", [](Json& j, const std::string& s){ return j[s]; })
    .method("set", [](Json& j, size_t i, bool v){ return j[i] = v; })
    .method("set", [](Json& j, size_t i, int v){ return j[i] = v; })
    .method("set", [](Json& j, size_t i, float v){ return j[i] = v; })
    // .method("set", [](Json& j, size_t i, long v){ return j[i] = v; })
    .method("set", [](Json& j, size_t i, double v){ return j[i] = v; })
    .method("set", [](Json& j, size_t i, const std::string& v){ return j[i] = v; })
    .method("set", [](Json& j, size_t i, const Json& v){ return j[i] = v; })
    .method("set", [](Json& j, const std::string& s, bool v){ return j[s] = v; })
    .method("set", [](Json& j, const std::string& s, int v){ return j[s] = v; })
    .method("set", [](Json& j, const std::string& s, float v){ return j[s] = v; })
    // .method("set", [](Json& j, const std::string& s, long v){ return j[s] = v; })
    .method("set", [](Json& j, const std::string& s, double v){ return j[s] = v; })
    .method("set", [](Json& j, const std::string& s, const std::string& v){ return j[s] = v; })
    .method("set", [](Json& j, const std::string& s, const Json& v){ return j[s] = v; })
    ;

  mod.method("loadJson", &trussc::loadJson);
  mod.method("saveJson", [](const Json& j, const std::string& path){ return trussc::saveJson(j, path); });
  mod.method("saveJson", [](const Json& j, const std::string& path, int indent){ return trussc::saveJson(j, path, indent); });
  mod.method("parseJson", &trussc::parseJson);
  mod.method("toJsonString", [](const Json& j){ return trussc::toJsonString(j); });
  mod.method("toJsonString", [](const Json& j, int a){ return trussc::toJsonString(j, a); });

  using XmlDocument = pugi::xml_document;

  mod.add_type<XmlDocument>("XmlDocument")
    .constructor<>()
    ;

  mod.add_type<XmlAttribute>("XmlAttribute")
    .constructor<>()
    // .method("set", [](XmlAttribute& x, pugi::string_view_t s){ return (x = s); })
    // .method("set", [](XmlAttribute& x, const pugi::char_t* s){ return (x = s); })
    .method("set", [](XmlAttribute& x, const std::string& s){ return (x = s); })
    .method("set", [](XmlAttribute& x, int s){ return (x = s); })
    .method("set", [](XmlAttribute& x, float s){ return (x = s); })
    .method("set", [](XmlAttribute& x, double s){ return (x = s); })
    .method("set", [](XmlAttribute& x, bool s){ return (x = s); })
    // .method("set", [](XmlAttribute& x, long s){ return (x = s); })
    .method("name", [](XmlAttribute& x){ return std::string(x.name()); })
    .method("value", [](XmlAttribute& x){ return std::string(x.value()); })
    ;

    using XmlText = pugi::xml_text;

    mod.add_type<XmlText>("XmlText")
      .constructor<>()
      // .method("set", [](XmlText& x, pugi::string_view_t s){ return (x = s); })
      // .method("set", [](XmlText& x, const pugi::char_t* s){ return (x = s); })
      .method("set", [](XmlText& x, const std::string& s){ return (x = s); })
      .method("set", [](XmlText& x, int s){ return (x = s); })
      .method("set", [](XmlText& x, float s){ return (x = s); })
      .method("set", [](XmlText& x, double s){ return (x = s); })
      .method("set", [](XmlText& x, bool s){ return (x = s); })
      // .method("set", [](XmlText& x, long s){ return (x = s); })
      .method("get", &XmlText::get)
      ;

    mod.add_type<XmlNode>("XmlNode")
      .constructor<>()
      // .method("append_attribute", [](XmlNode& x, pugi::string_view_t n){ return x.append_attribute(n); })
      // .method("append_attribute", [](XmlNode& x, const pugi::char_t* n){ return x.append_attribute(n); })
      .method("append_attribute", [](XmlNode& x, const std::string& n){ return x.append_attribute(n); })
      // .method("prepend_attribute", [](XmlNode& x, pugi::string_view_t n){ return x.prepend_attribute(n); })
      // .method("prepend_attribute", [](XmlNode& x, const pugi::char_t* n){ return x.prepend_attribute(n); })
      .method("prepend_attribute", [](XmlNode& x, const std::string& n){ return x.prepend_attribute(n); })
      // .method("append_child", [](XmlNode& x, pugi::string_view_t n){ return x.append_child(n); })
      // .method("append_child", [](XmlNode& x, const pugi::char_t* n){ return x.append_child(n); })
      .method("append_child", [](XmlNode& x, const std::string& n){ return x.append_child(n); })
      // .method("prepend_child", [](XmlNode& x, pugi::string_view_t n){ return x.prepend_child(n); })
      // .method("prepend_child", [](XmlNode& x, const pugi::char_t* n){ return x.prepend_child(n); })
      .method("prepend_child", [](XmlNode& x, const std::string& n){ return x.prepend_child(n); })
      // .method("attribute", [](XmlNode& x, pugi::string_view_t n){ return x.attribute(n); })
      // .method("attribute", [](XmlNode& x, const pugi::char_t* n){ return x.attribute(n); })
      .method("attribute", [](XmlNode& x, const std::string& n){ return x.attribute(n); })
      // .method("child", [](XmlNode& x, pugi::string_view_t n){ return x.child(n); })
      // .method("child", [](XmlNode& x, const pugi::char_t* n){ return x.child(n); })
      .method("child", [](XmlNode& x, const std::string& n){ return x.child(n); })
      .method("text", &XmlNode::text)
      .method("name", [](XmlNode& x){ return std::string(x.name()); })
      .method("first_child", &XmlNode::first_child)
      .method("last_child", &XmlNode::last_child)
      .method("first_attribute", &XmlNode::first_attribute)
      .method("last_attribute", &XmlNode::last_attribute)
      .method("remove_children", &XmlNode::remove_children)
      .method("children", [](XmlNode& x){
        jlcxx::Array<XmlNode> a {};
        for(auto&& c: x.children()){
          a.push_back(c);
        }
        return a;
      })
      ;

    mod.add_type<Xml>("Xml")
      .constructor<>()
      .method("load", &Xml::load)
      .method("parse", &Xml::parse)
      .method("save", [](Xml& x, const std::string& s){ return x.save(s); })
      .method("save", [](Xml& x, const std::string& s, const std::string& i){ return x.save(s, i); })
      .method("toString", [](Xml& x){ return x.toString(); })
      .method("toString", [](Xml& x, const std::string& i){ return x.toString(i); })
      .method("root", [](Xml& x){ return x.root(); })
      .method("addRoot", &Xml::addRoot)
      .method("child", &Xml::child)
      .method("document", [](Xml& x) -> XmlDocument& { return x.document(); })
      .method("empty", &Xml::empty)
      .method("addDeclaration", [](Xml& x){ return x.addDeclaration(); })
      .method("addDeclaration", [](Xml& x, const std::string& a){ return x.addDeclaration(a); })
      .method("addDeclaration", [](Xml& x, const std::string& a, const std::string& b){ return x.addDeclaration(a, b); })
      ;

    mod.method("loadXml", &trussc::loadXml);
    mod.method("parseXml", &trussc::parseXml);

    mod.add_type<Path>("Path")
        .constructor<>()
        .constructor<const std::vector<Vec2>&>()
        .constructor<const std::vector<Vec3>&>()
        .constructor<const Path&>()
        // FIXME: move constructor?
        .method("addVertex", [](Path& p, float x, float y){ return p.addVertex(x, y); })
        .method("addVertex", [](Path& p, float x, float y, float z){ return p.addVertex(x, y, z); })
        .method("addVertex", [](Path& p, const Vec2& v){ return p.addVertex(v); })
        .method("addVertex", [](Path& p, const Vec3& v){ return p.addVertex(v); })
        .method("addVertices", [](Path& p, const std::vector<Vec2>& v){ return p.addVertices(v); })
        .method("addVertices", [](Path& p, const std::vector<Vec3>& v){ return p.addVertices(v); })
        .method("getVertices", [](Path& p){ return p.getVertices(); })
        .method("size", &Path::size)
        .method("empty", &Path::empty)
        .method("at", [](Path& p, int index){ return p[index]; })
        .method("clear", &Path::clear)
        .method("lineTo", [](Path& p, float x, float y){ return p.lineTo(x, y); })
        .method("lineTo", [](Path& p, float x, float y, float z){ return p.lineTo(x, y, z); })
        .method("lineTo", [](Path& p, const Vec2& v){ return p.lineTo(v); })
        .method("lineTo", [](Path& p, const Vec3& v){ return p.lineTo(v); })
        .method("bezierTo", [](Path& p, const Vec2& a, const Vec2& b, const Vec2& c){ return p.bezierTo(a, b, c); })
        .method("bezierTo", [](Path& p, const Vec2& a, const Vec2& b, const Vec2& c, int d){ return p.bezierTo(a, b, c, d); })
        .method("bezierTo", [](Path& p, const Vec3& a, const Vec3& b, const Vec3& c){ return p.bezierTo(a, b, c); })
        .method("bezierTo", [](Path& p, const Vec3& a, const Vec3& b, const Vec3& c, int d){ return p.bezierTo(a, b, c, d); })
        .method("bezierTo", [](Path& p,float a,float b,float c,float d,float e,float f){ return p.bezierTo(a,b,c,d,e,f); })
        .method("bezierTo", [](Path& p,float a,float b,float c,float d,float e,float f,int g){ return p.bezierTo(a,b,c,d,e,f,g); })
        .method("quadBezierTo", [](Path& p, const Vec2& a, const Vec2& b){ return p.quadBezierTo(a, b); })
        .method("quadBezierTo", [](Path& p, const Vec2& a, const Vec2& b, int d){ return p.quadBezierTo(a, b, d); })
        .method("quadBezierTo", [](Path& p, const Vec3& a, const Vec3& b){ return p.quadBezierTo(a, b); })
        .method("quadBezierTo", [](Path& p, const Vec3& a, const Vec3& b, int d){ return p.quadBezierTo(a, b, d); })
        .method("quadBezierTo", [](Path& p,float a,float b,float c,float d){ return p.quadBezierTo(a,b,c,d); })
        .method("quadBezierTo", [](Path& p,float a,float b,float c,float d,int g){ return p.quadBezierTo(a,b,c,d,g); })
        .method("curveTo", [](Path& p, float x, float y){ return p.curveTo(x, y); })
        .method("curveTo", [](Path& p, float x, float y, float z){ return p.curveTo(x, y, z); })
        .method("curveTo", [](Path& p, const Vec2& v){ return p.curveTo(v); })
        .method("curveTo", [](Path& p, const Vec3& v){ return p.curveTo(v); })
        .method("arc", [](Path& p, const Vec3& v, float a, float b, float c, float d) { return p.arc(v,a,b,c,d); })
        .method("arc", [](Path& p, const Vec3& v, float a, float b, float c, float d, bool e) { return p.arc(v,a,b,c,d,e); })
        .method("arc", [](Path& p, const Vec3& v, float a, float b, float c, float d, bool e, int f) { return p.arc(v,a,b,c,d,e,f); })
        .method("arc", [](Path& p, const Vec2& v, float a, float b, float c, float d, int f) { return p.arc(v,a,b,c,d,f); })
        .method("arc", [](Path& p, float a, float b, float c, float d, float e, float f, int g) { return p.arc(a,b,c,d,e,f,g); })
        .method("arc", [](Path& p, float a, float b, float c, float d, float e, float f) { return p.arc(a,b,c,d,e,f); })
        .method("close", &Path::close)
        .method("setClosed", &Path::setClosed)
        .method("isClosed", &Path::isClosed)
        .method("draw", &Path::draw)
        .method("getBounds", &Path::getBounds)
        .method("getPerimeter", &Path::getPerimeter)
        ;

  mod.add_enum<EaseType>("EaseType",
      std::vector<const char*>({
        "Linear",
        "Quad",
        "Cubic",
        "Quart",
        "Quint",
        "Sine",
        "Expo",
        "Circ",
        "Back",
        "Elastic",
        "Bounce"
      }),
      std::vector<int>({
          (int)EaseType::Linear,
          (int)EaseType::Quad,
          (int)EaseType::Cubic,
          (int)EaseType::Quart,
          (int)EaseType::Quint,
          (int)EaseType::Sine,
          (int)EaseType::Expo,
          (int)EaseType::Circ,
          (int)EaseType::Back,
          (int)EaseType::Elastic,
          (int)EaseType::Bounce
      })
  );

  mod.add_enum<EaseMode>("EaseMode",
      std::vector<const char*>({
          "In",
          "Out",
          "InOut",
      }),
      std::vector<int>({
          (int)EaseMode::In,
          (int)EaseMode::Out,
          (int)EaseMode::InOut,
      })
  );

  mod.add_type<Font>("Font")
    .constructor<>()
    .constructor<const Font&>()
    // FIXME: move constructor?
    .method("load", &Font::load)
    .method("isLoaded", &Font::isLoaded)
    .method("setAlign", [](Font& f, Direction a, Direction b){ return f.setAlign(a,b); })
    .method("setAlign", [](Font& f, Direction a){ return f.setAlign(a); })
    .method("getAlignH", &Font::getAlignH)
    .method("getAlignV", &Font::getAlignV)
    .method("drawString", [](Font& f, const std::string& s, float x, float y){
        f.drawString(s, x, y);
    })
    .method("drawString", [](Font& f, const std::string& s, float x, float y, Direction a, Direction b){
        f.drawString(s, x, y, a, b);
    })
    .method("setLineHeight", &Font::setLineHeight)
    .method("setLineHeightEm", &Font::setLineHeightEm)
    .method("getLineHeight", &Font::getLineHeight)
    .method("getDefaultLineHeight", &Font::getDefaultLineHeight)
    .method("resetLineHeight", &Font::resetLineHeight)
    .method("getWidth", &Font::getWidth)
    .method("getHeight", &Font::getHeight)
    .method("getBBox", &Font::getBBox)
    .method("getAscent", &Font::getAscent)
    .method("getDescent", &Font::getDescent)
    .method("getSize", &Font::getSize)
    ;

  defineTween<Tween<float>, float>(mod, "TweenFloat");
  defineTween<Tween<Vec2>, Vec2>(mod, "TweenVec2");
  defineTween<Tween<Vec3>, Vec3>(mod, "TweenVec3");
  defineTween<Tween<Color>, Color>(mod, "TweenColor");

  mod.add_type<PlayingSound>("PlayingSound")
      .constructor<>()

      // FIXME: need std::atomic treatments

      // .method("buffer", [](PlayingSound& p){ return p.buffer; })
      // .method("volume", [](PlayingSound& p){ return p.volume; })
      // .method("pan", [](PlayingSound& p){ return p.pan; })
      // .method("speed", [](PlayingSound& p){ return p.speed; })
      // .method("loop", [](PlayingSound& p){ return p.loop; })
      // .method("playing", [](PlayingSound& p){ return p.playing; })
      // .method("paused", [](PlayingSound& p){ return p.paused; })
      // .method("positionF", [](PlayingSound& p){ return p.positionF; })
      // .method("rateRatio", [](PlayingSound& p){ return p.rateRatio; })
      // .method("buffer!", [](PlayingSound& p, std::shared_ptr<SoundBuffer> v){ p.buffer = v; })
      // .method("volume!", [](PlayingSound& p, float v){ p.volume = v; })
      // .method("pan!", [](PlayingSound& p, float v){ p.pan = v; })
      // .method("speed!", [](PlayingSound& p, float v){ p.speed = v; })
      // .method("loop!", [](PlayingSound& p, bool v){ p.loop = v; })
      // .method("playing!", [](PlayingSound& p, bool v){ p.playing = v; })
      // .method("paused!", [](PlayingSound& p, bool v){ p.paused = v; })
      // .method("positionF!", [](PlayingSound& p, double v){ p.positionF = v; })
      // .method("positionF!", [](PlayingSound& p, float v){ p.positionF = v; })
      // .method("rateRatio!", [](PlayingSound& p, float v){ p.rateRatio = v; })
      ;

  mod.add_type<SoundBuffer>("SoundBuffer")
      .constructor<>()
      .constructor<const SoundBuffer&>()
      // FIXME: move constructor
      .method("loadOgg", &SoundBuffer::loadOgg)
      .method("loadWav", &SoundBuffer::loadWav)
      .method("loadMp3", &SoundBuffer::loadMp3)
      .method("loadMp3FromMemory", &SoundBuffer::loadMp3FromMemory)
      .method("loadAac", &SoundBuffer::loadAac)
      .method("loadAacFromMemory", &SoundBuffer::loadAacFromMemory)
      .method("loadPcmFromMemory", &SoundBuffer::loadPcmFromMemory)
      .method("getDuration", &SoundBuffer::getDuration)
      .method("generateSineWave", &SoundBuffer::generateSineWave)
      .method("generateSquareWave", &SoundBuffer::generateSquareWave)
      .method("generateTriangleWave", &SoundBuffer::generateTriangleWave)
      .method("generateSawtoothWave", &SoundBuffer::generateSawtoothWave)
      .method("generateNoise", &SoundBuffer::generateNoise)
      .method("generatePinkNoise", &SoundBuffer::generatePinkNoise)
      .method("generateSilence", &SoundBuffer::generateSilence)
      .method("applyADSR", &SoundBuffer::applyADSR)
      .method("mixFrom", &SoundBuffer::mixFrom)
      .method("clip", &SoundBuffer::clip)
      ;

  mod.method("SoundBuffer_getAdtsSampleRateIndex", &SoundBuffer::getAdtsSampleRateIndex);
  mod.method("SoundBuffer_createAdtsHeader", &SoundBuffer::createAdtsHeader);

  mod.add_type<AudioEngine>("AudioEngine")
      .method("init", &AudioEngine::init)
      .method("shutdown", &AudioEngine::shutdown)
      .method("getAnalysisBuffer", &AudioEngine::getAnalysisBuffer)
      .method("play", &AudioEngine::play)
      .method("mixAudio", &AudioEngine::mixAudio)
      ;

  mod.method("AudioEngine_getInstance", &AudioEngine::getInstance);

  mod.add_type<Sound>("Sound")
      .constructor<>()
      .constructor<const Sound&>()
      // FIXME: move constructor
      .method("load", &Sound::load)
      .method("loadTestTone", &Sound::loadTestTone)
      .method("loadFromBuffer", [](Sound& s, const SoundBuffer& b){ s.loadFromBuffer(b); })
      .method("loadFromBuffer", [](Sound& s, std::shared_ptr<SoundBuffer> b){ s.loadFromBuffer(b); })
      .method("isLoaded", &Sound::isLoaded)
      .method("play", &Sound::play)
      .method("stop", &Sound::stop)
      .method("pause", &Sound::pause)
      .method("resume", &Sound::resume)
      .method("setVolume", &Sound::setVolume)
      .method("getVolume", &Sound::getVolume)
      .method("setLoop", &Sound::setLoop)
      .method("isLoop", &Sound::isLoop)
      .method("setPan", &Sound::setPan)
      .method("getPan", &Sound::getPan)
      .method("setSpeed", &Sound::setSpeed)
      .method("getSpeed", &Sound::getSpeed)
      .method("isPlaying", &Sound::isPlaying)
      .method("isPaused", &Sound::isPaused)
      .method("getPosition", &Sound::getPosition)
      .method("setPosition", &Sound::setPosition)
      .method("getDuration", &Sound::getDuration)
      ;

  mod.add_type<MicInput>("MicInput")
      .constructor<>()
      .method("start", &MicInput::start)
      .method("stop", &MicInput::stop)
      .method("getBuffer", &MicInput::getBuffer)
      .method("isRunning", &MicInput::isRunning)
      .method("getSampleRate", &MicInput::getSampleRate)
      .method("onAudioData", &MicInput::onAudioData)
      ;

  // tcxOsc
  mod.add_type<OscMessage>("OscMessage")
      .constructor<>()
      .constructor<const OscMessage&>()
      .constructor<const std::string&>()
      .method("setAddress", &OscMessage::setAddress)
      .method("getAddress", &OscMessage::getAddress)
      .method("addInt", &OscMessage::addInt)
      .method("addFloat", &OscMessage::addFloat)
      .method("addString", &OscMessage::addString)
      .method("addBlob", &OscMessage::addBlob)
      .method("addBool", &OscMessage::addBool)
      .method("getArgCount", &OscMessage::getArgCount)
      .method("getTypeTags", &OscMessage::getTypeTags)
      .method("getArgAsInt", &OscMessage::getArgAsInt)
      .method("getArgAsFloat", &OscMessage::getArgAsFloat)
      .method("getArgAsString", &OscMessage::getArgAsString)
      .method("getArgAsBlob", &OscMessage::getArgAsBlob)
      .method("getArgAsBool", &OscMessage::getArgAsBool)
      .method("toBytes", &OscMessage::toBytes)
      .method("toString", &OscMessage::toString)
      .method("clear", &OscMessage::clear)
      ;

  mod.method("OscMessage_fromBytes", &OscMessage::fromBytes);

  mod.add_type<OscBundle>("OscBundle")
      .constructor<>()
      .constructor<const OscBundle&>()
      .constructor<uint64_t>()
      .method("setTimetag", &OscBundle::setTimetag)
      .method("getTimetag", &OscBundle::getTimetag)
      .method("addMessage", &OscBundle::addMessage)
      .method("addBundle", &OscBundle::addBundle)
      .method("getElementCount", &OscBundle::getElementCount)
      .method("isBundle", &OscBundle::isBundle)
      .method("isMessage", &OscBundle::isMessage)
      .method("getMessageAt", &OscBundle::getMessageAt)
      .method("getBundleAt", &OscBundle::getBundleAt)
      .method("toBytes", &OscBundle::toBytes)
      .method("clear", &OscBundle::clear)
      ;

  mod.method("OscBundle_fromBytes", &OscBundle::fromBytes);
  mod.method("OscBundle_isBundle", &OscBundle::isBundle);

  using OscSenderDestination = OscSender::Destination;
  mod.add_type<OscSenderDestination>("OscSenderDestination")
      .constructor<>()
      .method("host", [](OscSenderDestination& d){ return d.host; })
      .method("host!", [](OscSenderDestination& d, const std::string& h){ return d.host = h; })
      .method("port", [](OscSenderDestination& d){ return d.port; })
      .method("port!", [](OscSenderDestination& d, int p){ return d.port = p; })
      ;

  mod.add_type<OscSender>("OscSender")
      .constructor<>()
      .method("connect", &OscSender::connect)
      .method("disconnect", [](OscSender& o){ o.disconnect(); })
      .method("disconnect", [](OscSender& o, const std::string& h, int p){ o.disconnect(h, p); })
      .method("setup", &OscSender::setup)
      .method("close", &OscSender::close)
      .method("send", [](OscSender& o, const OscMessage& m){ o.send(m); })
      .method("send", [](OscSender& o, const OscBundle& b){ o.send(b); })
      .method("sendTo", [](OscSender& o, const std::string& h, int p, const OscMessage& m){ o.sendTo(h,p,m); })
      .method("sendTo", [](OscSender& o, const std::string& h, int p, const OscBundle& b){ o.sendTo(h,p,b); })
      .method("getConnectedAddresses", &OscSender::getConnectedAddresses)
      .method("isConnected", &OscSender::isConnected)
      ;

  mod.add_type<OscReceiver>("OscReceiver")
      .constructor<>()
      .method("setup", &OscReceiver::setup)
      .method("close", &OscReceiver::close)
      .method("getPort", &OscReceiver::getPort)
      .method("isListening", &OscReceiver::isListening)
      .method("hasNewMessage", &OscReceiver::hasNewMessage)
      .method("getNextMessage", &OscReceiver::getNextMessage)
      .method("setBufferSize", &OscReceiver::setBufferSize)
      .method("getBufferSize", &OscReceiver::getBufferSize)
      ;
  // End of tcxOsc

  // tcxHap
  using HapFormat = tcx::hap::HapFormat;
  using HapPlayer = tcx::hap::HapPlayer;

  mod.add_enum<HapFormat>("HapFormat",
      std::vector<const char*>({
          "Unknown",
          "DXT1",
          "DXT5",
          "YCoCgDXT5",
          "BC7",
          "RGTC1"
      }),
      std::vector<int>({
          (int)HapFormat::Unknown,
          (int)HapFormat::DXT1,
          (int)HapFormat::DXT5,
          (int)HapFormat::YCoCgDXT5,
          (int)HapFormat::BC7,
          (int)HapFormat::RGTC1
      })
  );

  mod.add_type<HapPlayer>("HapPlayer")
      .constructor<>()
      // FIXME: move constructor?
      .method("getDecodeTimeMs", &HapPlayer::getDecodeTimeMs)
      .method("getChunkCount", &HapPlayer::getChunkCount)
      .method("resetStats", &HapPlayer::resetStats)
      .method("getHapFormat", &HapPlayer::getHapFormat)
      // .method("setSpeed", &HapPlayer::setSpeed)
      // .method("isHapFile", &HapPlayer::isHapFile)
      .method("load", &HapPlayer::load)
      .method("close", &HapPlayer::close)
      .method("hasTexture", &HapPlayer::hasTexture)
      .method("draw", [](HapPlayer& p, float x, float y){ return p.draw(x, y); })
      .method("draw", [](HapPlayer& p, float x, float y, float w, float h){ return p.draw(x, y, w, h); })
      .method("isLoaded", &HapPlayer::isLoaded)
      .method("play", &HapPlayer::play)
      .method("stop", &HapPlayer::stop)
      .method("setPaused", &HapPlayer::setPaused)
      .method("togglePause", &HapPlayer::togglePause)
      .method("update", &HapPlayer::update)
      .method("isPlaying", &HapPlayer::isPlaying)
      .method("isPaused", &HapPlayer::isPaused)
      .method("isFrameNew", &HapPlayer::isFrameNew)
      .method("isDone", &HapPlayer::isDone)
      .method("getWidth", &HapPlayer::getWidth)
      .method("getHeight", &HapPlayer::getHeight)
      .method("getDuration", &HapPlayer::getDuration)
      .method("getPosition", &HapPlayer::getPosition)
      .method("setPosition", &HapPlayer::setPosition)
      .method("getCurrentTime", &HapPlayer::getCurrentTime)
      .method("setCurrentTime", &HapPlayer::setCurrentTime)
      .method("getVolume", &HapPlayer::getVolume)
      .method("setVolume", &HapPlayer::setVolume)
      .method("getSpeed", &HapPlayer::getSpeed)
      .method("setSpeed", &HapPlayer::setSpeed)
      .method("setPan", &HapPlayer::setPan)
      .method("getPan", &HapPlayer::getPan)
      .method("setLoop", &HapPlayer::setLoop)
      .method("isLoop", &HapPlayer::isLoop)
      .method("getCurrentFrame", &HapPlayer::getCurrentFrame)
      .method("getTotalFrames", &HapPlayer::getTotalFrames)
      .method("setFrame", &HapPlayer::setFrame)
      .method("nextFrame", &HapPlayer::nextFrame)
      .method("previousFrame", &HapPlayer::previousFrame)
      .method("getPixels", [](HapPlayer& p){ return p.getPixels(); })
      .method("hasAudio", &HapPlayer::hasAudio)
      .method("getAudioCodec", &HapPlayer::getAudioCodec)
      .method("getAudioData", &HapPlayer::getAudioData)
      .method("getAudioSampleRate", &HapPlayer::getAudioSampleRate)
      .method("getAudioChannels", &HapPlayer::getAudioChannels)
      .method("isUsingHwAccel", &HapPlayer::isUsingHwAccel)
      .method("getHwAccelName", &HapPlayer::getHwAccelName)
      .method("setResyncThreshold", &HapPlayer::setResyncThreshold)
      .method("getResyncThreshold", &HapPlayer::getResyncThreshold)
      // .method("getTexture", &HapPlayer::getTexture)
      // WORKAROUND
      .method("getTexturePtr", [](HapPlayer& p){ 
          Texture& tex = p.getTexture();
          return (void*) &tex;
      })
      ;

  mod.method("HapPlayer_isHapFile", &HapPlayer::isHapFile);
  // End of tcxHap

  define_julia_module_trussc_generated(mod);
}
