//
//  ArmViewport.cpp
//  NPBOT
//
//  Created by Kris Temmerman on 15/09/14.
//
//

#include "ArmViewport.h"
void ArmViewport::setup(int _x,int _y,int _w,int _h)
{

    x= _x;
    y=_y;
    w=_w;
    h=_h;
    gui = new ciUICanvas(x,y,w,200);
    gui->setColorBack(ColorA(1,1,0,0));
    gui->setColorFill(ColorA(1,0,0,1));
    gui->setColorFillHighlight(ColorA(1,0,0,1));
    
    
    
    
    
    
    
    vector<string> names;
    names.push_back("FRONT");    names.push_back("LEFT");    names.push_back(" TOP ");    names.push_back("F_T_L");
    
    
    ddl  = new ciUIDropDownList(100, "F_T_L", names, CI_UI_FONT_SMALL);
    ddl->setAutoClose(true);
    ddl->setColorFillHighlight(ColorA(1,0,0,1));
    ddl->setColorFill(ColorA(0,0,0,0));
    gui->addWidgetDown(ddl);
    gui->addWidgetRight(new ciUIToggle(20,20,true, "target", CI_UI_FONT_SMALL))->setColorBack(ColorA(0,0,0,1));
    gui->addWidgetRight(new ciUIToggle(20,20,true, "current", CI_UI_FONT_SMALL))->setColorBack(ColorA(0,0,0,1));
    gui->addWidgetRight(new ciUIToggle(20,20,false, "path", CI_UI_FONT_SMALL))->setColorBack(ColorA(0,0,0,1));;
    gui->registerUIEvents(this, &ArmViewport::guiEvent);
    
    
    
    float windowScale =2000;
    float asp =(float)w/h;
    
    center.set(500, 500, 1000);
    camera.setOrtho(windowScale, -windowScale, -windowScale/asp, windowScale/asp, 0.1, 10000);
     camera.lookAt( Vec3f(2000,2000,2000)+center, center, Vec3f(0,1,0) );

}
void ArmViewport::guiEvent(ciUIEvent *event)
{
    string name = event->widget->getName();
    
   // cout << "WIDGET NAME: " << name << endl;
    
    if(event->widget == ddl )
    {
        ciUIDropDownList *ddlist = (ciUIDropDownList *) event->widget;
        vector<ciUIWidget *> &selected = ddlist->getSelected();
        for(int i = 0; i < selected.size(); i++)
        {
           
            ddlist->getLabel() ->setLabel(selected[i]->getName());
            if(selected[i]->getName()=="FRONT")
            {
            
            camera.lookAt( Vec3f(2000,0,0)+center, center, Vec3f(0,1,0) );
            }
           else  if(selected[i]->getName()==" TOP ")
            {
                
                camera.lookAt( Vec3f(0,2000,0)+center, center, Vec3f(1,0,0) );
            }
            else if(selected[i]->getName()=="LEFT")
            {
                
                camera.lookAt( Vec3f(0,0,2000)+center, center, Vec3f(0,1,0) );
            } else if(selected[i]->getName()=="F_T_L")
            {
                
                camera.lookAt( Vec3f(2000,2000,2000)+center, center, Vec3f(0,1,0) );

            }
        }
    }
}
void ArmViewport::update()
{

}
void ArmViewport::draw()
{
     viewArea.set(x,getWindowHeight()- y, x+w,getWindowHeight()-y-h);
    gl::setViewport(viewArea);
   // gl::clear( Color( 0.3, 0.0, 0.3 ) );
    gl::setMatricesWindow(w, h);

    gl::pushMatrices();
    gl::color(0.0, 0.0, 0.0);
    gl::drawSolidRect(Rectf( 0,0,w,h));
    gl::color(0.1, 0.1, 0.1);
    gl::drawSolidRect(Rectf( 0,0,w,35));
    gl::popMatrices();
    
    
    gl::pushMatrices();
      gl::setMatrices(camera );
    //root->drawCurrent();
    root->drawTarget();
   // gl::drawCoordinateFrame (300,0,0);
    gl::color(ColorA(1,1,1,0.5));
    gl::drawLine(Vec3f(130,0,0), Vec3f(130,0,2000));
     gl::drawLine(Vec3f(-130,0,0), Vec3f(-130,0,2000));
    
    
    
    /// test
    gl::color(ColorA(1,1,1,1));
    gl::drawLine(Vec3f(0,250,0), Vec3f(0,250,2000));

    //gl::drawLine( Vec3f(0,350,1000), Vec3f(0,0,1000));
     //gl::drawLine( Vec3f(0,350,1000), Vec3f(390,350,1000));
    
    
    gl::popMatrices();
    
    glViewport (0  , 0 , getWindowWidth(), getWindowHeight());
    gl::setMatricesWindow(getWindowWidth(), getWindowHeight());

    gui->draw();
    
    
   
    

}
