#version 120

uniform sampler2DRect tex0;

uniform float blurAmnty;
uniform float ff;
uniform float yw;

uniform float blurAmntx;
uniform float xw;
varying vec2 texCoordVarying;

// Gaussian weights from http://dev.theomader.com/gaussian-kernel-calculator/

void main()
{
	vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
    /*

	color += 0.000229 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * 4.0));
	color += 0.005977 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * 3.0));
	color += 0.060598 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * 2.0));
	color += 0.241732 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * 1.0));

	color += 0.382928 * texture2DRect(tex0, texCoordVarying + vec2(0.0, 0.0));

	color += 0.241732 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * -1.0));
	color += 0.060598 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * -2.0));
	color += 0.005977 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * -3.0));
	color += 0.000229 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * -4.0));
    */
    
    color =texture2DRect(tex0, texCoordVarying + vec2(0.0, 0.0));
    vec4 color_x=texture2DRect(tex0, texCoordVarying  + vec2(blurAmntx * 1.0, 0.0));
    vec4 color_y=texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnty * -1.0));
    
    
 //   float color_bright =color.r;//
  //  float color_xbright=color_x.r;//
  //  float color_ybright=color_y.r;//

    
    float color_bright =0.33*color.r+0.5*color.g+0.16*color.b;
    float color_xbright=0.33*color_x.r+0.5*color_x.g+0.16*color_x.b;
    float color_ybright=0.33*color_y.r+0.5*color_y.g+0.16*color_y.b;
    
    /*
    //these is just pure vector calcuulations
     //there isn't any dection on x and y just blurring
    color = (color + yw*texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnty * -1.0)))/2.0;
    
    
    
    color =(color+ xw*texture2DRect(tex0, texCoordVarying  + vec2(blurAmntx * 1.0, 0.0)))/2.0;

    
    
    if(color==texture2DRect(tex0, texCoordVarying + vec2(0.0, 0.0))){
        color=color*ff;
    }
    
     
     */
    
    
    //this bits is using the brightness for comparing
    //this version is kind of messy and uses entire colors
    
    
    if(color_bright<color_ybright){
    
    color = (color + yw*texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnty * -1.0)))/2.0;
    }
    
    if(color_bright<color_xbright){
    
    
    color =(color+ xw*texture2DRect(tex0, texCoordVarying  + vec2(blurAmntx * 1.0, 0.0)))/2.0;
    }
    
    float current_bright=0.33*color.r+0.5*color.g+0.16*color.b;
    
    
    
    if(current_bright==color_bright){
        color=color*ff;
    }
    
    
    //this is supposed to be monochrome but there is something logically wrong with this whole thing
    /*
    
    if(color_bright<color_ybright){
        
        color.r = (color.r + yw*texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnty * -1.0)).r)/2.0;
    }
    
    if(color_bright<color_xbright){
        
        
        color.r =(color.r+ xw*texture2DRect(tex0, texCoordVarying  + vec2(blurAmntx * 1.0, 0.0)).r)/2.0;
    }
    
    float current_bright=color.r;
    
    
    
    if(current_bright==color_bright){
        color.r=color.r*ff;
    }
    color.g=color.r;
    color.b=color.r;
    
  //  color=(color.r,color.r,color.r,1.0);
    */

   // if(color<1){color=color*-1};
    
 //   color.r=mod(color.r,1);
  //  color.g=mod(color.g,1);
  //  color.b=mod(color.b,1);
    
   // color.r=abs(color.r);
   // color.g=abs(color.g);
   // color.g=abs(color.g);
    
    
    color=mod(color,1);
    color=abs(color);
     gl_FragColor = (color);
  //  gl_FragColor = (color.r,color.r,color.r,1.0);
}
