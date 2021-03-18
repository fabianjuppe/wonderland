#sginclude "://shaders/commonlight.vert.inc"

in vec2 textureCoords;

out vec2 texCoords;
out vec3 viewPosition;
out vec3 viewNormal;

uniform float Time;
uniform int rotate;

void main()
{
	viewPosition = eyePosition().xyz;
    viewNormal = eyeNormalVec().xyz;
	
    float ltime = 2.*Time;
    vec4 t = vertexPosition;

	mat4 rotationMatrix;					
	rotationMatrix = mat4(1.0, 0.0, 0.0, 0.0, 
						0.0, 1.0 , 0.0, 0.0,
						0.0 , 0.0, 1.0, 0.0,
						0.0, 0.0, 0.0, 1.0);
	switch (rotate)
	{
		case 0:
			rotationMatrix = mat4(0.0, 0.0, -1.0, 0.0, 
						0.0, 1.0 , 0.0, 0.0,
						1.0 , 0.0, 0.0, 0.0,
						0.0, 0.0, 0.0, 1.0);
			break;				
		case 1:
			rotationMatrix = mat4(-1.0, 0.0, 0.0, 0.0, 
						0.0, 1.0 , 0.0, 0.0,
						0.0 , 0.0, -1.0, 0.0,
						0.0, 0.0, 0.0, 1.0);
			break;
		case 2:
			rotationMatrix = mat4(0.0, 0.0, 1.0, 0.0, 
						0.0, 1.0 , 0.0, 0.0,
						-1.0 , 0.0, 0.0, 0.0,
						0.0, 0.0, 0.0, 1.0);
			break;
		case 3:
			rotationMatrix = mat4(1.0, 0.0, 0.0, 0.0, 
						0.0, 1.0 , 0.0, 0.0,
						0.0 , 0.0, 1.0, 0.0,
						0.0, 0.0, 0.0, 1.0);
			break;				
	}

						
    gl_Position = projectionMatrix*modelViewMatrix*rotationMatrix*t;
	
	texCoords=textureCoords;
}
