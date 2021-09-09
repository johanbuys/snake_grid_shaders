#version 100

precision mediump float;

// Input vertex attributes (from vertex shader)
varying vec2 fragTexCoord;
varying vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// NOTE: Add here your custom variables

float gamma=.6;
float numColors=8.;

void main()
{
  vec3 color=texture2D(texture0,fragTexCoord.xy).rgb;
  
  color=pow(color,vec3(gamma,gamma,gamma));
  color=color*numColors;
  color=floor(color);
  color=color/numColors;
  color=pow(color,vec3(1./gamma));
  
  gl_FragColor=vec4(color,1.);
}