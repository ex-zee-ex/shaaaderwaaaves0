/*
 * Copyright (c) 2013 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxMidi for documentation
 *
 */
#include "ofApp.h"


#include <iostream>


float ss=10;
float dd=1;
float ff=1.01;
float xw=1.01;
float yw=1.01;


float gg=1;
float hh=0;

float theta=0;

float frequency=0;

float c1=1;
float c2=1;
float c3=1;
float c4=1;
float c5=1;
float c6=1;
float c7=1;
float c8=1;



//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);
	ofBackground(0);
	//ofSetLogLevel(OF_LOG_VERBOSE);
	
    
    /**MIDIBIX***/
    
	// print input ports to console
	midiIn.listInPorts();
	
	// open port by number (you may need to change this)
	midiIn.openPort(0);
	//midiIn.openPort("IAC Pure Data In");	// by name
	//midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
	
	// don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
	midiIn.ignoreTypes(false, false, false);
	
	// add ofApp as a listener
	midiIn.addListener(this);
	
	// print received messages to the console
	midiIn.setVerbose(true);
    
    /*******/
    
    
    /**shaderobiz***/
    
#ifdef TARGET_OPENGLES
    shaderBlurX.load("shadersES2/shaderBlurX");
    shaderBlurY.load("shadersES2/shaderBlurY");
#else
    if(ofIsGLProgrammableRenderer()){
        shaderBlurX.load("shadersGL3/shaderBlurX");
        shaderBlurY.load("shadersGL3/shaderBlurY");
    }else{
        shaderBlurX.load("shadersGL2/shaderBlurX");
        shaderBlurY.load("shadersGL2/shaderBlurY");
    }
#endif
    
    image.load("img.png");
    
    fboBlurOnePass.allocate(image.getWidth(), image.getHeight());
    fboBlurTwoPass.allocate(image.getWidth(), image.getHeight());
    fbo_feedback.allocate(image.getWidth(), image.getHeight());
    
    
    // fbo_feedback.begin();
    // image.draw(0, 0);
    // fbo_feedback.end();
    
    fbo_feedback.begin();

    ofClear(0,0,0,255);
 
       fbo_feedback.end();
    
    fboBlurTwoPass.begin();
  ofClear(0,0,0,255);
    fboBlurTwoPass.end();
    
    
}


//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    
/*midimessagesbiz**/
    
    
    ofTranslate(0,0,-100);
	for(unsigned int i = 0; i < midiMessages.size(); ++i) {

		ofxMidiMessage &message = midiMessages[i];
		int x = 10;
		int y = i*40 + 40;
	
		// draw the last recieved message contents to the screen,
		// this doesn't print all the data from every status type
		// but you should get the general idea
		stringstream text;
		text << ofxMidiMessage::getStatusString(message.status);
		while(text.str().length() < 16) { // pad status width
			text << " ";
		}

		ofSetColor(127);
		if(message.status < MIDI_SYSEX) {
			//text << "chan: " << message.channel;
            if(message.status == MIDI_CONTROL_CHANGE) {
                 // cout << "message.control"<< message.control<< endl;
                 // cout << "message.value"<< message.value<< endl;
                
                
                if(message.control==20){
                    c1=(message.value-63.0)/63.0;
                    
                }
                
                if(message.control==21){
                    c2=(message.value-63.0)/63.0;
                    
                }
                
                if(message.control==22){
                    c3=(message.value-63.0)/63.00;
                    
                }
                
                if(message.control==23){
                    c4=(message.value-63.0)/63.00;
                    
                }
                
                if(message.control==24){
                    c5=(message.value-63.0)/63.00;
                    
                }
                if(message.control==25){
                    c6=(message.value-63.0)/63.0;
                    
                }
                
                
                if(message.control==26){
                    c7=(message.value-63.0)/63.0;
                    
                }
                if(message.control==27){
                    c8=(message.value-63.0)/63.0;
                    
                }
                
                
                //text << "\tctl: " << message.control;
                //ofDrawRectangle(x + ofGetWidth()*0.2, y + 12,
                //	ofMap(message.control, 0, 127, 0, ofGetWidth()*0.2), 10);
            }
            else if(message.status == MIDI_PITCH_BEND) {
                //text << "\tval: " << message.value;
				//ofDrawRectangle(x + ofGetWidth()*0.2, y + 12,
					//ofMap(message.value, 0, MIDI_MAX_BEND, 0, ofGetWidth()*0.2), 10);
			}
			else {
				//text << "\tpitch: " << message.pitch;
				//ofDrawRectangle(x + ofGetWidth()*0.2, y + 12,
					//ofMap(message.pitch, 0, 127, 0, ofGetWidth()*0.2), 10);
                
               // int N= message.pitch;
               // int FN=N-69;
                // frequency=pow(2.0,FN/12.0)*440;
                //text << "frequency: " << frequency;

				////text << "\tvel: " << message.velocity;
				//ofDrawRectangle(x + (ofGetWidth()*0.2 * 2), y + 12,
					//ofMap(message.velocity, 0, 127, 0, ofGetWidth()*0.2), 10);
			}
			//text << " "; // pad for delta print
		}//

		//text << "delta: " << message.deltatime;
		//ofSetColor(0);
		//ofDrawBitmapString(text.str(), x, y);
		//text.str(""); // clear
	}
   /******* endmidimessagesbiz*********/
   
 
    
    /***shaderbix**/
    
 //   float blurx = ofMap(mouseX-ofGetWidth()/2, -ofGetWidth()/2, ofGetWidth()/2, -100, 100, true);
 //   float blury = ofMap(mouseY-ofGetHeight()/2, -ofGetHeight()/2, ofGetHeight()/2, -100, 100, true);
    
    float blurx =c7;
    float blury = c6;
    
    
    /*
     //----------------------------------------------------------
     fboBlurOnePass.begin();
     
     shaderBlurX.begin();
     shaderBlurX.setUniform1f("blurAmnt", blurx);
     shaderBlurX.setUniform1f("xw", xw);
     
     // if(sw1==0){
     // image.draw(0, 0);
     //  }//endsw1
     // if(sw1==1) {
     fbo_feedback.draw(0,0);
     //  }
     
     shaderBlurX.end();
     
     fboBlurOnePass.end();
     */
    //----------------------------------------------------------
    fboBlurTwoPass.begin();
    
    shaderBlurY.begin();
    shaderBlurY.setUniform1f("blurAmnty", blury);
    shaderBlurY.setUniform1f("ff", ff*c1);
    shaderBlurY.setUniform1f("yw", yw*c2);
    shaderBlurY.setUniform1f("blurAmntx", blurx);
    shaderBlurY.setUniform1f("xw", xw*c3);
    
    
    fbo_feedback.draw(0,0);
    
    shaderBlurY.end();
    
    fboBlurTwoPass.end();
    
    //----------------------------------------------------------
    
    
    /*this part gets drawn to screen*/
    ofSetColor(ofColor::white);
    fboBlurTwoPass.draw(0, 0);
    
    
    // ofDrawRectangle(ofGetWidth()/2,ofGetHeight()/2,20,20);
    int c=5;
    for(int i=0;i<image.getWidth();i+=c){
        
        ofVec2f v= sineWave(i,ss,dd);
        
        //  ofSetColor(fmod(174.0+10*v.x,255.0),30,fmod(245+10*v.y,255));
        
        ofSetColor(225,255,225);
        
        ofDrawRectangle(v.x,v.y,c,c);
    }
    
    
    
    /*this part getsdrawn to the feedback buffer*/
    
    fbo_feedback.begin();
    fboBlurTwoPass.draw(0, 0);
    for(int i=0;i<image.getWidth();i+=c){
        
        ofVec2f v= sineWave(i,ss,dd);
        // ofSetColor(fmod(174.0+10*v.x,255.0),30,fmod(245+10*v.y,255));
        ofSetColor(225,255,225);
        
        ofDrawRectangle(v.x,v.y,c,c);
    }
    // ofDrawRectangle(ofGetWidth()/2,ofGetHeight()/2,20,20);
    fbo_feedback.end();

   
    
    ofSetHexColor(0xFFFFFF);
    ofDrawBitmapString("ff: "+ofToString(ff*c1)
                       +" yw: "+ofToString(yw*c2) +" xw: "+ofToString(xw*c3),
                       10, ofGetHeight()-5 );
    

}


 
 /****************************************************/

ofVec2f ofApp::sineWave(int i,float rate,float amp){
    ofVec2f v;
    i=ss*i;
    v.y=i;
    v.x=ofGetWidth()/2+int(dd*100*sin(i+ofGetElapsedTimef()));
    
    return v;
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key=='1'){
        
        fbo_feedback.begin();
        
        ofClear(0,0,0,255);
        
        fbo_feedback.end();
        
        fboBlurTwoPass.begin();
        ofClear(0,0,0,255);
        fboBlurTwoPass.end();
    }
    //if(key=='q'){sw1==0;}
    
    if(key=='s'){ss+=0.01;}
    if(key=='x'){ss-=0.01;}
    
    if(key=='d'){dd+=0.01;}
    if(key=='c'){dd-=0.01;}
    
    if(key=='f'){ff+=0.1;}
    if(key=='v'){ff-=0.1;}
    
    if(key=='g'){xw+=0.01;}
    if(key=='b'){xw-=0.01;}
    if(key=='h'){yw+=0.01;}
    if(key=='n'){yw-=0.01;}
}

/************************/
//--------------------------------------------------------------
void ofApp::exit() {
	
	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {

	// add the latest message to the message queue
	midiMessages.push_back(msg);

	// remove any old messages if we have too many
	while(midiMessages.size() > maxMessages) {
		midiMessages.erase(midiMessages.begin());
	}
}

//--------------------------------------------------------------


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
   
}


//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
   
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased() {
}
