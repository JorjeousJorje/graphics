#version 450
varying lowp vec4 col;
uniform bool wireframe;
void main()
{
    if(wireframe)
    {
	  gl_FragColor = vec4(1, 0.682, 0, 1.0f);
    }
    else {
        gl_FragColor = col;
    }
}
