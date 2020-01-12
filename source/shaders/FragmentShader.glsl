#version 430

in vec2 pass_position;
out vec4 out_Color;

uniform float elapsed;

void main(void)
{
    if(abs(sin(pass_position.x*3.14+elapsed)*0.8 - pass_position.y) >= 0.05)
    {
        discard;
    }

    out_Color = vec4(0.9, 0.9, 0.9, 1);
}