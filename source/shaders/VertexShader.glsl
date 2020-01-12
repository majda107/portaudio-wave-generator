#version 430

in vec3 position;

out vec2 pass_position;

void main(void)
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
    pass_position = vec2(position);
}
