
uniform vec4 iMouse; // mouse pixel coords. xy: current pixel coords. zw = click pixel

void main(void) {
    col = vec3(iMouse.x, iMouse.z, iMouse.w);
    gl_FragColor = vec4(col,1.0);
}
