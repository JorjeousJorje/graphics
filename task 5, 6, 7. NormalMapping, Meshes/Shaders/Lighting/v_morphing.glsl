
#version 450

in vec3 posAttr;
in vec4 colAttr;
in vec3 normalAttr;
in vec2 textureAttr;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


uniform float morphFactor;
out vec2 TexCoords;

void main()
{
    vec4 newPos = vec4(posAttr * (1 - morphFactor ) + morphFactor * normalize(posAttr), 1.f);
    col = colAttr;
    TexCoords = textureAttr;           
    gl_Position = projection * view * model * vec4(posAttr, 1.0);
}