#version 120

uniform float time;
uniform vec2 resolution;

float rand(vec2 co) {
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

float noise(vec2 p) {
    vec2 i = floor(p);
    vec2 f = fract(p);
    
    float a = rand(i);
    float b = rand(i + vec2(1.0, 0.0));
    float c = rand(i + vec2(0.0, 1.0));
    float d = rand(i + vec2(1.0, 1.0));
    
    vec2 u = f * f * (3.0 - 2.0 * f);
    
    return mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
}

void main()
{
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    vec2 p = uv * 2.0 - 1.0;
    p.x *= resolution.x / resolution.y;
    
    float n = 0.0;
    float amplitude = 1.0;
    float frequency = 4.0;
    
    for (int i = 0; i < 4; i++) {
        n += noise(vec2(p.x * frequency, p.y * frequency - time * 2.0)) * amplitude;
        amplitude *= 0.5;
        frequency *= 2.0;
    }
    
    n = n * 0.5 + 0.5;
    n *= smoothstep(1.0, -0.2, uv.y);
    
    vec3 color = vec3(0.0);
    color = mix(vec3(0.0, 0.0, 0.0), vec3(1.0, 0.0, 0.0), smoothstep(0.0, 0.4, n));
    color = mix(color, vec3(1.0, 0.5, 0.0), smoothstep(0.4, 0.6, n));
    color = mix(color, vec3(1.0, 1.0, 0.0), smoothstep(0.6, 0.8, n));
    color = mix(color, vec3(1.0, 1.0, 1.0), smoothstep(0.8, 1.0, n));
    
    gl_FragColor = vec4(color, 1.0);
}