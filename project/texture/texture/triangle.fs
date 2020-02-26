#version 330 core
out vec4 FragColor;
in vec4 ourColor;
void main()
{
	if (gl_FragCoord.z > 0.5f)					
	{												
		FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);//BLUE
	}												
	else											
	{												
		FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);	
	}												
};