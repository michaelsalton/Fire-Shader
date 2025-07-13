#version 120

uniform float time;
uniform sampler2D noise_texture;
uniform float animation_speed;
uniform float y_offset;

void main()
{
    vec2 uv;
    vec2 animated_uv;
    vec4 noise_color;
    vec4 final_color;
    
    // Get UV coordinates from texture coordinates
    uv = gl_TexCoord[0].xy;

    //gl_FragColor = vec4(uv.x, uv.y, 0.0, 1.0); return;
    
    // Animate the UV coordinates
    animated_uv = vec2(uv.x, uv.y + time * animation_speed);
    
    // Sample the noise texture
    noise_color = texture2D(noise_texture, animated_uv);

    gl_FragColor = noise_color; return;
    
    // Create the fire effect
    final_color = noise_color;
    final_color.rgb = final_color.rgb + vec3(uv.y - y_offset);
    final_color.rgb = step(final_color.rgb, vec3(0.5));
    final_color.rgb = vec3(1.0) - final_color.rgb;
    final_color.a = final_color.r;
    
    gl_FragColor = final_color;
}