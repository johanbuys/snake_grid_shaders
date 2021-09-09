#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;
// const vec2 size = vec2(800, 800);   // render size
float circle(vec2 uv, vec2 p, float r, float blur){
	float d = length(uv - p);
	float c = smoothstep(r, r-blur, d);
	return c;
}
void main() {
		vec2 uv = gl_FragCoord.xy / u_resolution.xy; // 0 <> 1.
		// gl_FragColor = vec4(st.x,st.y,abs(sin(u_time))+st.x*st.y,1.0);
		uv -= 0.5; //-0.5 <> 0.5
		uv.x *= u_resolution.x/u_resolution.y;
		
		vec2 p = vec2(0.2, -0.1);
		float d = length(uv);
		float r = 0.3;
		float c = circle(uv, vec2(0), 0.4, 0.05);
		c -= circle(uv, vec2(0.13, 0.1),0.07, 0.01);
		c -= circle(uv,vec2(-.13,.1), 0.07, 0.01);
		c -= circle(uv,vec2(0,-.075),.07,.01);




		vec3 col = vec3(1.,0., 1.0);
		col *= c; //mask
		// if (d < 0.3) c = 1.0; else c = 0.0;
		gl_FragColor = vec4(col, 1.0);
}