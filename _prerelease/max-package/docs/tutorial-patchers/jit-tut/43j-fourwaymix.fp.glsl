uniform vec4 a;
uniform vec4 b;
uniform vec4 c;
uniform vec4 d;

// define our varying texture coordinates
varying vec2 texcoord0;
varying vec2 texcoord1;
varying vec2 texcoord2;
varying vec2 texcoord3;

// define our rectangular texture samplers
uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
uniform sampler2DRect tex2;
uniform sampler2DRect tex3;

void main (void)
{
	// sample our textures
	vec4 input0 = texture2DRect(tex0, texcoord0);
	vec4 input1 = texture2DRect(tex1, texcoord1);
	vec4 input2 = texture2DRect(tex2, texcoord2);
	vec4 input3 = texture2DRect(tex3, texcoord3);
	
	// perform our calculation and write our data to the fragment color
	gl_FragColor = a*input0 + b*input1 + c*input2 + d*input3;
	
}
