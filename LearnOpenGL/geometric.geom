#version 330 core

// 声明从顶点着色器输入的图元类型（points，lines，lines_adjacency，triangles，triangles_adjacency）
layout(points) in;
// 声明输出图元类型（points，line_strip，triangle_strip），以及图元支持的最大顶点数，多余的顶点不会绘制
layout(line_strip, max_vertices = 2) out;

void main() {
	gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.0, 0.0, 0.0);
	// 添加向量到图元
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(0.1, 0.0, 0.0, 0.0);
	EmitVertex();
	
	// 生成图元
	EndPrimitive();
}