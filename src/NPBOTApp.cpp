#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "ciUI.h"
#include "AxisData.h"
#include "AxisUI.h"
#include "ArmViewport.h"
#include "PositionUI.h"
#include "ArmPosition.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NPBOTApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    vector <AxisUI *> UIAxxisses;
    
    AxisData axis1;
    AxisUI axisUI1;
    
    AxisData axis2;
    AxisUI axisUI2;
    
    AxisData axis3;
    AxisUI axisUI3;
    
    AxisData axis4;
    AxisUI axisUI4;
    
    AxisData axis5;
    AxisUI axisUI5;
    
    AxisData axis6;
    AxisUI axisUI6;
    
 
    ciUICanvas *gui;
    ArmViewport view1;
      ArmViewport view2;
      ArmViewport view3;
    
    ArmPosition armPosition;
    
    PositionUI xposUI;
    PositionUI yposUI;
    PositionUI zposUI;
    
    PositionUI xRotposUI;
    PositionUI yRotposUI;
    PositionUI zRotposUI;
    
    
    vector <PositionUI *> UIpositions;
};

void NPBOTApp::setup()
{
    setWindowSize(1920, 1160);
    setWindowPos(0, 0);
    gui = new ciUICanvas(10,10,190,200-40);
    gui->addWidgetRight(new ciUILabelButton(100, false, "send", CI_UI_FONT_MEDIUM ,"send"));
    gui->addWidgetRight(new ciUILabelButton(100, false, "home", CI_UI_FONT_MEDIUM,"home"));
    
    int posX=10;
    int posY =220-40;
    int stepY=210;
    int stepX=200;
    axis1.setup(0, "A1 z-axis", 75.0f/1600.0f, 0, 400000, "mm");
    axisUI1.setup(&axis1,posX,posY);
    UIAxxisses.push_back(&axisUI1);
    
    
    
  
    posX+=stepX;
    axis2.setup(0, "A2 arm 1", 75.0f/1600.0f, 0, 400000, "deg");
    axisUI2.setup(&axis2,posX,posY);
    UIAxxisses.push_back(&axisUI2);
    
    
    posX+=stepX;
    axis3.setup(0, "A3 arm2", 75.0f/1600.0f, 0, 400000, "deg");
    axisUI3.setup(&axis3,posX,posY);
    UIAxxisses.push_back(&axisUI3);
    
    posX=10;
    posY+=stepY;
    axis4.setup(0, "A4 pols rot", 75.0f/1600.0f, 0, 400000, "°deg");
    axisUI4.setup(&axis4,posX,posY);
    UIAxxisses.push_back(&axisUI4);
    
    posX+=stepX;
    axis5.setup(0, "A5 posl bend", 75.0f/1600.0f, 0, 400000, "deg");
    axisUI5.setup(&axis5,posX,posY);
    UIAxxisses.push_back(&axisUI5);
    
    posX+=stepX;
    axis6.setup(0, "A6 hand rot", 75.0f/1600.0f, 0, 400000, "deg");
    axisUI6.setup(&axis6,posX,posY);
    UIAxxisses.push_back(&axisUI6);
    
    posX+=stepX;
    view1.setup(posX,10,1300,710);
    int vpY =710+20;
    view2.setup(posX,vpY,500,400);
    view3.setup(posX+510,vpY,1300-500-10,400);
    
    armPosition.setup();
     posY+=stepY;
    
    stepY =90;
    
    xposUI.setup(&armPosition.x, &armPosition.targetX,10, posY, "X", 100, 0);
    UIpositions.push_back(&xposUI);
   
    posY+=stepY;
    yposUI.setup(&armPosition.y, &armPosition.targetY,10, posY, "Y", 100, 0);
    UIpositions.push_back(&yposUI);
    
    posY+=stepY;
    zposUI.setup(&armPosition.z, &armPosition.targetZ,10, posY, "Z",2000, 0);
    UIpositions.push_back(&zposUI);
    
    posY+=stepY;
    xRotposUI.setup(&armPosition.rotX, &armPosition.targetRotX,10, posY, "rot X", 100, 0);
    UIpositions.push_back(&xRotposUI);
    
    posY+=stepY;
    yRotposUI.setup(&armPosition.rotY, &armPosition.targetRotY,10, posY, "rot Y", 100, 0);
    UIpositions.push_back(&yRotposUI);
    
    posY+=stepY;
    zRotposUI.setup(&armPosition.rotZ, &armPosition.targetRotZ,10, posY, "rot Z", 100, 0);
    UIpositions.push_back(&zRotposUI);
    
}

void NPBOTApp::mouseDown( MouseEvent event )
{
}

void NPBOTApp::update()
{
    for (int i=0;i<UIAxxisses.size();i++)
    {
        UIAxxisses[i]->update();
    }
    for (int i=0;i<UIpositions.size();i++)
    {
        UIpositions[i]->update();
    }
    view1.update();
    view2.update();
    view3.update();
}

void NPBOTApp::draw()
{
    
     glViewport (0  , 0 , getWindowWidth(), getWindowHeight());
    gl::setMatricesWindow(getWindowWidth(), getWindowHeight());
	// clear out the window with black
	gl::clear( Color( 0.2, 0.2, 0.2 ) );
     gui->draw();
    
    
    for (int i=0;i<UIAxxisses.size();i++)
    {
        UIAxxisses[i]->draw();
    }
    for (int i=0;i<UIpositions.size();i++)
    {
        UIpositions[i]->draw ();
    }
    view1.draw();
    view2.draw();
    view3.draw();
}

CINDER_APP_NATIVE( NPBOTApp, RendererGl )
