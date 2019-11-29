#version 330 core

uniform sampler2D texture1;

in vec2 TexCoords;

// out�������ֵ�������ݸ���һ����Ⱦ�����ֵ
out vec4 FragColor;

float near = 0.1; 
float far  = 100.0; 

float LinearizeDepth(float depth);

void main()
{
	float depth = LinearizeDepth(gl_FragCoord.z) / far; // Ϊ����ʾ���� far
    FragColor = vec4(vec3(depth), 1.0);
};

float LinearizeDepth(float depth) {
	float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));    
}