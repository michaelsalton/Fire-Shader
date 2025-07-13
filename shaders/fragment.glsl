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

    float band1 = step(0.3, intensity);
    float band2 = step(0.6, intensity);

    vec3 fire_color = flame_color_inner.rgb;
    fire_color = mix(fire_color, flame_color_middle.rgb, band1);
    fire_color = mix(fire_color, flame_color_outer.rgb, band2);


    float fire_mask = step(0.2, intensity);


    // final_color = noise_color;
    // final_color.rgb += vec3(uv.y - y_offset);
    // final_color.rgb = step(final_color.rgb, vec3(0.5));
    // final_color.rgb = vec3(1.0) - final_color.rgb;
    // final_color.a = final_color.r;
    // final_color.rgb = flame_color_outer.rgb;
    
    // gl_FragColor = final_color;

    final_color.rgb = fire_color;
    final_color.a = fire_mask;
    
    gl_FragColor = final_color;
}