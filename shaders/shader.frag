#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
/*layout(location = 2) in vec3 vfNormal;
layout(location = 3) in vec3 vfPosition;

layout(binding = 0) uniform SceneUBO {
	mat4 view;
	mat4 proj;
	vec4 light_point;
} subo;

layout(binding = 2) uniform ObjectUBO {
	vec4 oPosition;
	mat4 model;
} oubo;*/

layout(location = 0) out vec4 outColor;
layout(binding = 1) uniform sampler2D texSampler;

void main() {
	/*
	vec4 tmp_pos = oubo.oPosition;
	if (oubo.oPosition.x < 0) {
		tmp_pos.x *= -1;
	}
	if (oubo.oPosition.y < 0) {
		tmp_pos.y *= -1;
	}
	if (oubo.oPosition.z < 0) {
		tmp_pos.z *= -1;
	}
	if (tmp_pos.xyz == vec3(0.0)) {
		tmp_pos = vec4(1.0);
	}*/
	/*vec3 diffPosLightN = normalize(vfPosition - subo.light_point.xyz);
	vec3 diffuseC = vec3(1.0);
	float diffuseP = clamp(dot(diffPosLightN, vfNormal), 0, 1);
	vec3 diffuse = diffuseC * diffuseP;
	vec4 ambient = vec4(0.1);*/
	outColor =
		texture(texSampler, fragTexCoord)/*
		* (ambient + vec4(diffuse, 1.0))*/;
}
