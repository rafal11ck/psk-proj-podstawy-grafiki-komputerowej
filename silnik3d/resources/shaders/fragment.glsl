#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D textureDiffuse;
uniform sampler2D textureSpecular;

void main()
{
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    FragColor =max(texture(textureDiffuse, TexCoord), vec4(0,0,0,0));

}
