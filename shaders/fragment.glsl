#version 120

uniform sampler2D noise_texture;
uniform float time;
uniform float animation_speed;

void main()
{
    vec4 final_color;
    
    vec2 uv = gl_TexCoord[0].xy;
    vec2 animated_uv = uv;
    animated_uv.y += time * animation_speed;
    animated_uv = fract(animated_uv);
    vec4 noise_color = texture2D(noise_texture, animated_uv);
    final_color = noise_color;
    final_color.rgb += vec3(uv.y);
    
    gl_FragColor = final_color;
}