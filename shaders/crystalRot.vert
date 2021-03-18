#sginclude "://shaders/commonlight.vert.inc"

in vec2 textureCoords;

out vec2 texCoords;
out vec3 viewPosition;
out vec3 viewNormal;

uniform float Time;

void main()
{
	viewPosition = eyePosition().xyz;
    viewNormal = eyeNormalVec().xyz;
	
	float ltime = 0.5*Time;
    vec4 t = vertexPosition;

    mat4 translationMatrix = mat4(	1.0,	0.0,	0.0,	0.0,
									0.0,	1.0,	0.0,	0.0,
									0.0,	0.0,	1.0,	0.0,
									0.0,	cos(3.141*ltime*4)*0.5,	0.0,	1.0);

	mat4 rotationMatrix = mat4(	cos(3.141f*ltime), 	0.0, -sin(3.141f*ltime), 	0.0, 
							0.0, 				1.0, 				0.0, 	0.0,
							sin(3.141f*ltime), 	0.0, cos(3.141f*ltime) , 	0.0,
							0.0, 				0.0, 				0.0, 	1.0);

						
    gl_Position = projectionMatrix*modelViewMatrix*translationMatrix*rotationMatrix*t;
	
	texCoords = textureCoords;
}
