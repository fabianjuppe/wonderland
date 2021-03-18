in vec4 outputColor;

layout (location = 0) out vec4 fragColor;
uniform vec3 color;

void main()
{
    //fragColor = outputColor;
	
	fragColor = vec4(color, 1.0);
}