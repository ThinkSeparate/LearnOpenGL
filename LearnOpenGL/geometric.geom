#version 330 core

// 声明从顶点着色器输入的图元类型（points，lines，lines_adjacency，triangles，triangles_adjacency）
layout(points) in;
// 声明输出图元类型（points，line_strip，triangle_strip），以及图元支持的最大顶点数，多余的顶点不会绘制
layout(triangle_strip, max_vertices = 5) out;

in VS_OUT {
	vec3 color;
} gs_in[];

out vec3 fColor;

void build_house(vec4 position);

void main() {
	build_house(gl_in[0].gl_Position);
}

void build_house(vec4 position)
{
	fColor = gs_in[0].color; // gs_in[0] 因为只有一个输入顶点
	gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0);    // 1:左下
    EmitVertex();   
    gl_Position = position + vec4( 0.2, -0.2, 0.0, 0.0);    // 2:右下
    EmitVertex();
    gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0);    // 3:左上
    EmitVertex();
    gl_Position = position + vec4( 0.2,  0.2, 0.0, 0.0);    // 4:右上
    EmitVertex();
    gl_Position = position + vec4( 0.0,  0.4, 0.0, 0.0);    // 5:顶部
	fColor = vec3(1.0, 1.0, 1.0);
    EmitVertex();
    EndPrimitive();
}