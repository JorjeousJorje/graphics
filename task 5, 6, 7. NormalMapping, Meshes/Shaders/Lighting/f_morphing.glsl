
#version 450
in vec4 col;
in vec2 TexCoords;

uniform sampler2D ourTexture;
out vec4 FragColor;

void main()
{
    if(wireframe) {
	    FragColor = vec4(1, 0.682, 0, 1.0f);
    }
    else {
        FragColor = vec4(col, 1.0f);
    }
}