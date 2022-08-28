#version 460 core

// Vertex Shader Inputs
in vec3 FragColor;
in vec2 FragTexCoords;

// Uniform Inputs
uniform sampler2D ImageTexture;
uniform float AnimationFrameOffset;

// Output
out vec4 FinalColor;

void main()
{
	FinalColor = texture(ImageTexture, vec2(FragTexCoords.x + AnimationFrameOffset, FragTexCoords.y));
}