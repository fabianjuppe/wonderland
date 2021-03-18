#sginclude "://shaders/commonlight.vert.inc"

uniform vec3 Schwerpunkt;
out vec4 color;
uniform float Time;

void main()
{
    vec3 sphereProj = vertexPosition.xyz-Schwerpunkt;
    vec3 vertex;
    vec3 normal;
    sphereProj = normalize(sphereProj);
    normal = sphereProj;
    vertex = mix(vertexPosition.xyz-Schwerpunkt, sphereProj, Time)+Schwerpunkt;
    normal = mix(vertexNormal.xyz, normal, Time);
    vertex = (modelViewMatrix * vec4(vertex, 1.0)).xyz;
    normal = normalMatrix * normal;

    vec3 vertexColor = phong(vertex, -normalize(vertex), normal, vec3(1.0));
    color = vec4(vertexColor + material.emission.rgb, computeMaterialAlpha());

    gl_Position = projectionMatrix * vec4(vertex, 1.0);
}
