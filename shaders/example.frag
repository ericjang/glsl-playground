#version 130

// SHADER INPUTS:
// gl_FragCoord.xy: fragment coordinate, in pixels
// iResolution: viewport resolution, in pixels. X=width, Y=height, Z=1.0
// iGlobalTime: shader playback time (in seconds)
// iMouse: x,y = mouse pixel coords (hold down lmb). zw = left, right click

// SHADER_OUTPUTS:
// gl_FragColor : final RGB color and alpha outputted to the fullscreen quad

uniform vec3 iResolution;
uniform float iGlobalTime;
uniform vec4 iMouse;

void main(void)
{
    vec2 uv = gl_FragCoord.xy / iResolution.xy;
    gl_FragColor = vec4(uv,0.5+0.5*sin(iGlobalTime),1.0);
}
