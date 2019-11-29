#version 330 core

uniform sampler2D texture1;

in vec2 TexCoords;

// out定义输出值，即传递给下一个渲染步骤的值
out vec4 FragColor;

void main()
{
	vec4 texColor = texture(texture1, TexCoords);
	if (texColor.a < 0.1f) {
		// 丢弃，保证片段不会被进一步处理，即透明片段不显示了
		discard;
	}
    FragColor = texColor;
};