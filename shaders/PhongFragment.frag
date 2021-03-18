#sginclude "://shaders/commonlightmatdefs.inc"
#sginclude "://shaders/commonlightmodels.inc"

in vec3 viewPosition;
in vec3 viewNormal;

out vec4 fragColor;

void main()
{
     vec3 color = phong(viewPosition, -normalize(viewPosition), normalize(viewNormal), vec3(1.0));
     fragColor = vec4(color + material.emission.rgb, computeMaterialAlpha());
}
