#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D textureDiffuse;
uniform sampler2D textureSpecular;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	//FragColor =  vec4(1.0f, 0.5f, 0.2f, 1.0f);
	FragColor = mix(texture(textureDiffuse, TexCoord), texture(textureSpecular, TexCoord), 0.5);
	//FragColor = texture(texture1, TexCoord);
}
