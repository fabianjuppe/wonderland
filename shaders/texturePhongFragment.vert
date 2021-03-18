#sginclude "://shaders/commonlight.vert.inc"

in vec2 textureCoords;

out vec2 texCoords;
out vec3 viewPosition;
out vec3 viewNormal;

void main()
{
	viewPosition = eyePosition().xyz;
    viewNormal = eyeNormalVec().xyz;

    gl_Position = vPos();
	
	texCoords = textureCoords;
}
