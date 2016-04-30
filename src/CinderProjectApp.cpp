#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderProjectApp : public AppNative {
    CameraPersp         camera; //  амера
    Quatf sceneRotation; // поворот камеры
    Vec3f eyePosition; // позици€ камеры
    float cameraDistance; // рассто€ние от камеры до цели

    Vec3f objectPosition;

 params::InterfaceGl cameraParams; // ѕользовательский интерфейс дл€ работы с камерой
  public:
    void setup() { // вызоветс€ при запуске приложени€
        objectPosition =  Vec3f::zero();
        cameraDistance = 500; 
        camera.setPerspective( 60.0f, getWindowAspectRatio(), 5.0f, 3000.0f ); // настроим перспективу камеры

        cameraParams = params::InterfaceGl( "Camera Settings", Vec2i( 225, 200 ) ); // окно интерфейса
        cameraParams.addParam( "Scene Rotation", &sceneRotation );
        cameraParams.addParam( "Eye Distance", &cameraDistance, "min=50.0 max=1000.0 step=50.0 keyIncr=s keyDecr=w" ); 
    }

    void keyDown( KeyEvent event ) {
        if( event.getCode() == KeyEvent::KEY_UP) {
            objectPosition.y += 15;
        }
        if( event.getCode() == KeyEvent::KEY_DOWN) {
            objectPosition.y -= 15;
        }
        if( event.getCode() == KeyEvent::KEY_LEFT) {
            objectPosition.x -= 15;
        }
        if( event.getCode() == KeyEvent::KEY_RIGHT) {
            objectPosition.x += 15;
        }
    }

    void update() {
        eyePosition = Vec3f( 0.0f, 0.0f, cameraDistance ); // x, y, рассто€ние от камеры до цели
        gl::setMatrices( camera ); 

        gl::rotate( sceneRotation ); 
    }

    
void draw() { 
        gl::clear( Color( 0, 1.0f, 1.0f ) ); // стереть все 
        gl::drawSphere(objectPosition , 25 ); 
		glColor3f(1.0f,0.0f,0.0f);
        




    }
};

CINDER_APP_NATIVE( CinderProjectApp, RendererGl )