#extension GL_EXT_gpu_shader4 : enable

varying vec2 _texture;
varying vec2 _position;
uniform sampler2D _colour;
uniform float _fade;

void main(void)
{
    vec3 diffuseMaterial = texture2D(_colour, _texture.xy).rgb;
    gl_FragColor = vec4(diffuseMaterial, _fade);
}
