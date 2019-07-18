#version 450

layout(binding = 0) uniform SceneUBO {
	mat4 view;
	mat4 proj;
	vec4 camera_position;
	vec4 light_point;
} subo;

layout(binding = 2) uniform ObjectUBO {
	vec4 oPosition;
	mat4 model;
} oubo;

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec2 vTexturePosition;
layout(location = 3) in vec3 vNormal;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 vfNormal;
layout(location = 3) out vec3 vfPosition;


void main() {
	gl_Position = subo.proj * subo.view * ((oubo.model * vec4(vPosition, 1.0)) + oubo.oPosition - subo.camera_position);
	fragColor = vColor;
	fragTexCoord = vTexturePosition;
	vfNormal = ((mat3(oubo.model) * vNormal) + oubo.oPosition.xyz);
	vfPosition = vPosition;
}
