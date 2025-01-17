//--------------------------
// - Hazel 2D -
// Renderer2D Line Shader
// --------------------------

#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in int a_EntityID;

uniform mat4 u_ViewProjection;

struct VertexOutput
{
	vec4 Color;
};

out VertexOutput Output;
flat out int v_EntityID;

void main()
{
	Output.Color = a_Color;
	v_EntityID = a_EntityID;

	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_EntityID;

struct VertexOutput
{
	vec4 Color;
};

in VertexOutput Output;
flat in int v_EntityID;

void main()
{
	o_Color = Output.Color;
	o_EntityID = v_EntityID;
}
