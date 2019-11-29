#version 330 core

uniform sampler2D texture1;

in vec2 TexCoords;

// out定义输出值，即传递给下一个渲染步骤的值
out vec4 FragColor;

float near = 0.1; 
float far  = 100.0; 

float LinearizeDepth(float depth);

void main()
{
	float depth = LinearizeDepth(gl_FragCoord.z) / far; // 为了演示除以 far
    FragColor = vec4(vec3(depth), 1.0);
};

float LinearizeDepth(float depth) {
	float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));    
}