#version 120

uniform float time;
uniform vec2 resolution;

float rand(vec2 co) {
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

vec2 gradient(vec2 p) {
    float angle = rand(p) * 6.28318530718; // 2*PI
    return vec2(cos(angle), sin(angle));
}

float noise(vec2 p) {
    vec2 i = floor(p);
    vec2 f = fract(p);
    
    // Get gradient vectors at corners
    vec2 ga = gradient(i);
    vec2 gb = gradient(i + vec2(1.0, 0.0));
    vec2 gc = gradient(i + vec2(0.0, 1.0));
    vec2 gd = gradient(i + vec2(1.0, 1.0));
    
    // Compute dot products
    float va = dot(ga, f);
    float vb = dot(gb, f - vec2(1.0, 0.0));
    float vc = dot(gc, f - vec2(0.0, 1.0));
    float vd = dot(gd, f - vec2(1.0, 1.0));
    
    // Smooth interpolation
    vec2 u = f * f * (3.0 - 2.0 * f);
    
    return mix(mix(va, vb, u.x), mix(vc, vd, u.x), u.y);
}

void main()
{
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    vec2 p = uv * 2.0 - 1.0;
    p.x *= resolution.x / resolution.y;
    
    // Distance from center
    float dist = length(p);
    
    // Create circular source
    float coreRadius = 0.15;  // Inner bright core
    float glowRadius = 0.8;   // Outer glow radius
    float coreMask = 1.0 - smoothstep(0.0, coreRadius, dist);
    float glowMask = 1.0 - smoothstep(coreRadius, glowRadius, dist);
    
    // Radial coordinates for outward flow
    float angle = atan(p.y, p.x);
    
    float n = 0.0;
    float amplitude = 1.0;
    float frequency = 4.0;
    
    for (int i = 0; i < 4; i++) {
        // Use angle and radius for radial turbulence
        float radialNoise = noise(vec2(angle * frequency * 2.0, dist * frequency - time)) * amplitude;
        // Add some angular variation
        float angleNoise = noise(vec2(dist * frequency, angle * frequency + time * 0.5)) * amplitude * 0.5;
        n += radialNoise + angleNoise;
        amplitude *= 0.5;
        frequency *= 2.0;
    }
    
    n = n * 0.5 + 0.5;
    
    // Combine core and glow
    float intensity = coreMask + glowMask * n * 0.8;
    
    // Sun-like color gradient
    vec3 color = vec3(0.0);
    color = mix(vec3(0.0, 0.0, 0.0), vec3(0.8, 0.2, 0.0), smoothstep(0.0, 0.2, intensity));
    color = mix(color, vec3(1.0, 0.4, 0.0), smoothstep(0.2, 0.4, intensity));
    color = mix(color, vec3(1.0, 0.7, 0.0), smoothstep(0.4, 0.6, intensity));
    color = mix(color, vec3(1.0, 0.9, 0.5), smoothstep(0.6, 0.8, intensity));
    color = mix(color, vec3(1.0, 1.0, 0.9), smoothstep(0.8, 1.0, intensity));
    
    gl_FragColor = vec4(color, 1.0);
}