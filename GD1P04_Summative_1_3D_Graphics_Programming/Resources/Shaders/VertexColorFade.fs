#version 460 core

in vec3 FragColor;
uniform float CurrentTime;

out vec4 FinalColor;

void main()
{
	FinalColor.x = FragColor.x * abs(sin(CurrentTime));
	FinalColor.y = FragColor.y * abs(cos(CurrentTime));
	//FinalColor.z = FragColor.z * abs(tan(CurrentTime));

	FinalColor = vec4(FinalColor.xy, FragColor.z, 1.0f) * abs(sin(CurrentTime));
}