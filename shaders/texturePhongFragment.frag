#sginclude "://shaders/commonlightmatdefs.inc"
#sginclude "://shaders/commonlightmodels.inc"

uniform sampler2D textureMap;

in vec3 viewPosition;
in vec3 viewNormal;

in vec2 texCoords;

out vec4 fragColor;

void main()
{
    vec4 textureFrag = texture(textureMap, texCoords);
	
	vec3 color = phong(viewPosition, -normalize(viewPosition), normalize(viewNormal), textureFrag.rgb);
	fragColor = vec4(color + material.emission.rgb, textureFrag.a);
	
    //fragColor = vec4(textureFrag.rgb, textureFrag.a);
    
	//vec3 color = phong(viewPosition, -normalize(viewPosition), normalize(viewNormal), vec3(1.0));
    //fragColor = vec4(color + material.emission.rgb, computeMaterialAlpha());
}
