#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(true);

    cam.setDistance(buffer_history*0.01);
    ofBackground(0, 0, 0);
    
    
    sampleRate = 44100;
    ofSetFrameRate(0.1);
    

    soundSettingsGui.setup();


    volHistory.assign(400, 0.0);
    
    bufferCounter	= 0;

    
    // gui setup
    parameters.setName("parameters");
    parameters.add(buffer_history.set("buffer_history", 2048,buffer_size+1,4096));
    parameters.add(shapeScale.set("shapeScale",.85,0,2));
    parameters.add(line_width.set("line_width",1, 0.1,10));
    parameters.add(line_color.set("color",ofColor(255),ofColor(0,0),ofColor(255)));
    parameters.add(mesh_width_z.set("mesh_width_z", 1, -2, 2));
    parameters.add(cam_set_ortho.set("cam_set_ortho", 1));
    parameters.add(cam_set_reset.set("cam_set_reset", 1));
    parameters.add(set_fullscreen.set("fullscreen", 0));

    
    gui.setup(parameters);
    
    
    gui.loadFromFile("settings.xml");

    
    
}



//--------------------------------------------------------------
void ofApp::update(){
    
    
    
// ici, application devrait passer soundSettingGui.buffer_size vers une classe pour dessiner oscillo
    
    
   // timestamp=ofGetElapsedTimeMillis();
    
    vbo_mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    vbo_mesh.enableColors();
    

    int vertex_buffer = vbo_mesh.getNumVertices();

    for (unsigned int i = 0; i < (soundSettingsGui.buffer_size); i++)
    {
        ofVec3f coord (soundSettingsGui.left[i]*app_size_w/2*shapeScale,
                       soundSettingsGui.right[i]*app_size_w/2*shapeScale,
                       buffer_history-i);
        
        if (vertex_buffer > buffer_history)
        {
            vbo_mesh.removeVertex(i);
            vbo_mesh.setVertex(buffer_history-i, coord);
        } else {
            vbo_mesh.addVertex(coord);
        }
    }
    
    //au lieu de faire une lecture et une ecriture, mieux vaudrait utiliser un pointeur pour changer la derniere donnee
    //

//        for (unsigned int i =0; i< vertex_buffer; i++)
    for (unsigned int i =0; i< vbo_mesh.getNumVertices(); i++)
    {
        ofVec3f coord = vbo_mesh.getVertex(i);
        coord[2] = mesh_width_z*i*0.1;
        vbo_mesh.setVertex(i, coord);
   
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    if (set_fullscreen_old != set_fullscreen)
    {
        ofSetFullscreen(set_fullscreen);
        set_fullscreen_old = set_fullscreen;
    };
    
    ofEnableDepthTest();
    if (cam_set_ortho){cam.enableOrtho();}else{cam.disableOrtho();};
    if (cam_set_reset){cam.reset(); cam_set_reset=0;};
    
   // cam.setDistance(timestamp);
    cam.begin();
    ofNoFill();
    
    // draw the OSCILO channel:
    ofPushStyle();
    ofPushMatrix();

    
 
    ofSetLineWidth(line_width);

    vbo_mesh.draw();
   
    ofPopMatrix();
    ofPopStyle();
    
    cam.end();
    
    ofDisableDepthTest();
    
    if (gui_draw)
    {
        gui.draw();
       soundSettingsGui.draw();
    }
    if (screen_workaround_to_update)
    {
        windowResized(ofGetWidth(), ofGetHeight());
        screen_workaround_to_update = 0;
    }
}
//--------------------------------------------------------------





//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'g' ){
        gui_draw=!gui_draw;
    }
    
    if (key == 'f'){
        set_fullscreen=!set_fullscreen;
    }
    

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){


}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    app_size_w = w;
    app_size_h = h;
    cout << "app size = " << w << " by " << h <<endl;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------

void ofApp::exit(){
    
    
}

void ofApp::rhizome_init()
{
    sender.setup(HOST, RHIZOME_INPORT);
    ofxOscMessage m;
    m.setAddress("/sys/subscribe");
    m.addIntArg(RHIZOME_OUTPORT);
    m.addStringArg("/");
    sender.sendMessage(m, false);
}
