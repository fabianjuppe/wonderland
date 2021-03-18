#sginclude "://shaders/commonlight.vert.inc"

in vec2 textureCoords;

out vec2 texCoords;
out vec3 viewPosition;
out vec3 viewNormal;

uniform float Time;
uniform int translate;

void main()
{
	viewPosition = eyePosition().xyz;
    viewNormal = eyeNormalVec().xyz;
	
    float ltime = 2.*Time;
    vec4 t = vertexPosition;
	
	mat4 translationMatrix;					
	translationMatrix = mat4(1.0, 0.0, 0.0, 0.0, 
						0.0, 1.0 , 0.0, 0.0,
						0.0 , 0.0, 1.0, 0.0,
						0.0, 0.0, 0.0, 1.0);
	switch (translate)
	{
		case 0:
			translationMatrix = mat4(1.0, 0.0, 0.0, 0.0, 
						0.0, 1.0 , 0.0, 0.0,
						0.0 , 0.0, 1.0, 0.0,
						0.0, 50.0, 0.0, 1.0);
			break;							
	}

						
    gl_Position = projectionMatrix*modelViewMatrix*translationMatrix*t;
	
	texCoords=textureCoords;

}
