#ifdef GL_ES
  precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_res;
// const vec2 size = vec2(800, 800);   // render size

void main() {
		vec2 uv = gl_FragCoord.xy/u_res;
		vec3 col = 0.5 + 0.5*cos(u_time+uv.xyx+vec3(0,2,4));
		// gl_FragColor = vec4(st.x,st.y,abs(sin(u_time))+st.x*st.y,1.0);
		gl_FragColor = vec4(col,1.0);
}

    // vec2 xy = fragCoord.xy / iResolution.xy;//Condensing this into one line
    // vec4 texColor = texture(iChannel0,xy);//Get the pixel at xy from iChannel0
    
    // float pixVal = (texColor.r + texColor.g + texColor.b) / 3.0;
    //    texColor.r = pixVal;
    //    texColor.g = pixVal;
    //    texColor.b = pixVal;

    // fragColor = texColor;//Set the screen pixel to that color
