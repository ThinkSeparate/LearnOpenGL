#version 330 core

// �����Ӷ�����ɫ�������ͼԪ���ͣ�points��lines��lines_adjacency��triangles��triangles_adjacency��
layout(points) in;
// �������ͼԪ���ͣ�points��line_strip��triangle_strip�����Լ�ͼԪ֧�ֵ���󶥵���������Ķ��㲻�����
layout(line_strip, max_vertices = 2) out;

void main() {
	gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.0, 0.0, 0.0);
	// ���������ͼԪ
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(0.1, 0.0, 0.0, 0.0);
	EmitVertex();
	
	// ����ͼԪ
	EndPrimitive();
}