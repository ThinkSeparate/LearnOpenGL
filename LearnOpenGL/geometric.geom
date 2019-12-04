#version 330 core

// �����Ӷ�����ɫ�������ͼԪ���ͣ�points��lines��lines_adjacency��triangles��triangles_adjacency��
layout(points) in;
// �������ͼԪ���ͣ�points��line_strip��triangle_strip�����Լ�ͼԪ֧�ֵ���󶥵���������Ķ��㲻�����
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
	fColor = gs_in[0].color; // gs_in[0] ��Ϊֻ��һ�����붥��
	gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0);    // 1:����
    EmitVertex();   
    gl_Position = position + vec4( 0.2, -0.2, 0.0, 0.0);    // 2:����
    EmitVertex();
    gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0);    // 3:����
    EmitVertex();
    gl_Position = position + vec4( 0.2,  0.2, 0.0, 0.0);    // 4:����
    EmitVertex();
    gl_Position = position + vec4( 0.0,  0.4, 0.0, 0.0);    // 5:����
	fColor = vec3(1.0, 1.0, 1.0);
    EmitVertex();
    EndPrimitive();
}