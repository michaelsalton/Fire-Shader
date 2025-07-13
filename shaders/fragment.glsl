#version 120

uniform sampler2D noise_texture;
uniform float time;
uniform float animation_speed;
uniform vec4 flame_color_outer;
uniform vec4 flame_color_middle;
uniform vec4 flame_color_inner;

void main()
{
    vec4 final_color;
    float y_offset = 0.5; 
    vec2 uv = gl_TexCoord[0].xy;
    vec2 animated_uv = uv;
    animated_uv.y += time * animation_speed;
    animated_uv = fract(animated_uv);
    vec4 noise_color = texture2D(noise_texture, animated_uv);
    float intensity = noise_color.r + (uv.y - y_offset);
    intensity = clamp(intensity, 0.0, 1.0);
    float outerBand = step(0.2, intensity);
    float middleBand = step(0.5, intensity);
    float innerBand = step(0.7, intensity);
    vec3 fire_color = flame_color_outer.rgb;
    fire_color = mix(fire_color, flame_color_middle.rgb, middleBand);
    fire_color = mix(fire_color, flame_color_inner.rgb, innerBand);
    final_color.rgb = fire_color;
    final_color.a = outerBand;
    gl_FragColor = final_color;
}