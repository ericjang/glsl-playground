bool is_in_circle(vec2 uv, vec2 center, float radius) {
    return length(uv - center) < radius;
}

void main(void) {
    vec2 uv = gl_FragCoord.xy;
    vec2 center = iResolution.xy * 0.5;    
    float radius = 0.25 * iResolution.y;
    vec3 col = vec3(.2); // background
    if (is_in_circle(uv,center,radius)) {
        col = vec3(1,0,0); // red
    }
    float alpha = 1.0;
    gl_FragColor = vec4(col,alpha);
}
