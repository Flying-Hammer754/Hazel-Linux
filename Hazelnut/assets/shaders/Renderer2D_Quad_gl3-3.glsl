// Basic Texture Shader

#type vertex
#version 330 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in float a_TilingFactor;
layout(location = 5) in int a_EntityID;

uniform mat4 u_ViewProjection;

struct VertexOutput
{
	vec4 Color;
	vec2 TexCoord;
	float TilingFactor;
};

out VertexOutput Output;
flat out float v_TexIndex;
flat out int v_EntityID;

void main() {
	Output.Color = a_Color;
	Output.TexCoord = a_TexCoord;
	Output.TilingFactor = a_TilingFactor;
	v_TexIndex = a_TexIndex;
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
	vec2 TexCoord;
	float TilingFactor;
};

in VertexOutput Output;
flat in float v_TexIndex;
flat in int v_EntityID;

uniform sampler2D u_Textures[32];

void main()
{
	vec4 texColor = Output.Color;

	switch(int(v_TexIndex))
	{
		case  0: texColor *= texture(u_Textures[ 0], Output.TexCoord * Output.TilingFactor); break;
		case  1: texColor *= texture(u_Textures[ 1], Output.TexCoord * Output.TilingFactor); break;
		case  2: texColor *= texture(u_Textures[ 2], Output.TexCoord * Output.TilingFactor); break;
		case  3: texColor *= texture(u_Textures[ 3], Output.TexCoord * Output.TilingFactor); break;
		case  4: texColor *= texture(u_Textures[ 4], Output.TexCoord * Output.TilingFactor); break;
		case  5: texColor *= texture(u_Textures[ 5], Output.TexCoord * Output.TilingFactor); break;
		case  6: texColor *= texture(u_Textures[ 6], Output.TexCoord * Output.TilingFactor); break;
		case  7: texColor *= texture(u_Textures[ 7], Output.TexCoord * Output.TilingFactor); break;
		case  8: texColor *= texture(u_Textures[ 8], Output.TexCoord * Output.TilingFactor); break;
		case  9: texColor *= texture(u_Textures[ 9], Output.TexCoord * Output.TilingFactor); break;
		case 10: texColor *= texture(u_Textures[10], Output.TexCoord * Output.TilingFactor); break;
		case 11: texColor *= texture(u_Textures[11], Output.TexCoord * Output.TilingFactor); break;
		case 12: texColor *= texture(u_Textures[12], Output.TexCoord * Output.TilingFactor); break;
		case 13: texColor *= texture(u_Textures[13], Output.TexCoord * Output.TilingFactor); break;
		case 14: texColor *= texture(u_Textures[14], Output.TexCoord * Output.TilingFactor); break;
		case 15: texColor *= texture(u_Textures[15], Output.TexCoord * Output.TilingFactor); break;
		case 16: texColor *= texture(u_Textures[16], Output.TexCoord * Output.TilingFactor); break;
		case 17: texColor *= texture(u_Textures[17], Output.TexCoord * Output.TilingFactor); break;
		case 18: texColor *= texture(u_Textures[18], Output.TexCoord * Output.TilingFactor); break;
		case 19: texColor *= texture(u_Textures[19], Output.TexCoord * Output.TilingFactor); break;
		case 20: texColor *= texture(u_Textures[20], Output.TexCoord * Output.TilingFactor); break;
		case 21: texColor *= texture(u_Textures[21], Output.TexCoord * Output.TilingFactor); break;
		case 22: texColor *= texture(u_Textures[22], Output.TexCoord * Output.TilingFactor); break;
		case 23: texColor *= texture(u_Textures[23], Output.TexCoord * Output.TilingFactor); break;
		case 24: texColor *= texture(u_Textures[24], Output.TexCoord * Output.TilingFactor); break;
		case 25: texColor *= texture(u_Textures[25], Output.TexCoord * Output.TilingFactor); break;
		case 26: texColor *= texture(u_Textures[26], Output.TexCoord * Output.TilingFactor); break;
		case 27: texColor *= texture(u_Textures[27], Output.TexCoord * Output.TilingFactor); break;
		case 28: texColor *= texture(u_Textures[28], Output.TexCoord * Output.TilingFactor); break;
		case 29: texColor *= texture(u_Textures[29], Output.TexCoord * Output.TilingFactor); break;
		case 30: texColor *= texture(u_Textures[30], Output.TexCoord * Output.TilingFactor); break;
		case 31: texColor *= texture(u_Textures[31], Output.TexCoord * Output.TilingFactor); break;
	}

	if (texColor.a == 0.0)
		discard;

	o_Color = texColor;
	o_EntityID = v_EntityID;
}
