#sginclude "://shaders/commonlight.vert.inc"

out vec3 viewPosition;
out vec3 viewNormal;

void main()
{
    viewPosition = eyePosition().xyz;
    viewNormal = eyeNormalVec().xyz;

    gl_Position = vPos();
}
