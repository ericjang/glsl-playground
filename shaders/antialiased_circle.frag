float circle_transparency(vec2 uv, vec2 center, float radius) {
    float d = length(uv - center) - radius; // if d positive, then is outside circle
    return clamp(d,0.0,1.0); // if d between 0 and 1, blend for anti-aliasing.
}

void main(void) {
    vec2 uv = gl_FragCoord.xy;
    vec2 center = iResolution.xy * 0.5;
    float radius = 0.25 * iResolution.y;

    vec3 background = vec3(.2);
    vec3 foreground = vec3(1,0,0);
    float alpha = circle_transparency(uv, center, radius);
    vec3 col = mix(foreground, background, alpha);
    gl_FragColor = vec4(col,1.0);
}
