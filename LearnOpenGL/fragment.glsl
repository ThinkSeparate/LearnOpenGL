#version 330 core
// out定义输出值，即传递给下一个渲染步骤的值
out vec4 FragColor;

// 接受顶点着色器的输入
in vec3 ourColor;
in vec2 TexCoord;

// 接受一个纹理输入,sampler2D是2d纹理类型
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
	// OpenGL的rgba值为float类型，数值在0-1之间
	// glsl的变量支持组合，分量使用等操作
	// texture函数，根据给定的纹理和贴图坐标，计算出片段着色器的颜色
	// mix函数，将多个纹理以一定的比例混合，第三个值表示第二个图片在混合中占的比例
	FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
};