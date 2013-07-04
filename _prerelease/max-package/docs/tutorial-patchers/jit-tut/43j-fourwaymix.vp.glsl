// define our varying texture coordinates
varying vec2 texcoord0;
varying vec2 texcoord1;
varying vec2 texcoord2;
varying vec2 texcoord3;

void main( void )
{
	// the output vertex postion to the input vertex position
	// transformed by the current ModelViewProjection matrix 
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	// assign our varying texture coordinates to the
	// input texture coordinate values transformed 
	// by the appropriate texture matrix. This is
	// necessary for rectangular and flipped textures 
	texcoord0 = vec2(gl_TextureMatrix[0] * gl_MultiTexCoord0);
	texcoord1 = vec2(gl_TextureMatrix[1] * gl_MultiTexCoord1);
	texcoord2 = vec2(gl_TextureMatrix[2] * gl_MultiTexCoord2);
	texcoord3 = vec2(gl_TextureMatrix[3] * gl_MultiTexCoord3);
}
