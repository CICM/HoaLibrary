/* 
	xray.jit.boidsrender.c by Wesley Smith 12/14/2005
*/

#include "jit.common.h"

typedef struct _xray_jit_boidsrender 
{
	t_object				ob;
	float					scale[2];
	long					scalecount;
	char					normalize;
} t_xray_jit_boidsrender;

void *_xray_jit_boidsrender_class;

t_jit_err xray_jit_boidsrender_init(void);
t_xray_jit_boidsrender *xray_jit_boidsrender_new(void);
void xray_jit_boidsrender_free(t_xray_jit_boidsrender *x);
t_jit_err xray_jit_boidsrender_matrix_calc(t_xray_jit_boidsrender *x, void *inputs, void *outputs);

void xray_jit_boidsrender_calculate_ndim(t_xray_jit_boidsrender *x, long dimcount, long *dim, long planecount, t_jit_matrix_info *in1_minfo, char *bip1, 
	t_jit_matrix_info *out_minfo, char *bop);
void xray_jit_boidsrender_make_texcoords(t_jit_matrix_info *out2_minfo, char *bop2);
	
void TransformPoint(float *p_in, float *p_out, float *X, float *Y, float *Z);
void InvTransformPoint(float *p_in, float *p_out, float *X, float *Y, float *Z);
void Vadd(float *p1, float *p2, float *p_out);

void postVect(float *vect);

t_jit_err xray_jit_boidsrender_init(void) 
{
	long attrflags=0;
	t_jit_object *attr,*mop,*o;
	t_symbol *atsym;
	t_atom a[3];
	
	atsym = gensym("jit_attr_offset");
	
	_xray_jit_boidsrender_class = jit_class_new("xray_jit_boidsrender",(method)xray_jit_boidsrender_new,(method)xray_jit_boidsrender_free,
		sizeof(t_xray_jit_boidsrender),0L);

	//add mop
	mop = jit_object_new(_jit_sym_jit_mop,1,2);
	jit_atom_setsym(a, _jit_sym_long);
	jit_atom_setsym(a+1,_jit_sym_float32);
	jit_atom_setsym(a+2,_jit_sym_float64);
	o = jit_object_method(mop,_jit_sym_getoutput,1);
	jit_object_method(o,_jit_sym_types,3,a);
	
	jit_class_addadornment(_xray_jit_boidsrender_class,mop);
	//add methods
	jit_class_addmethod(_xray_jit_boidsrender_class, (method)xray_jit_boidsrender_matrix_calc, 		"matrix_calc", 		A_CANT, 0L);
	//add attributes	
	attrflags = JIT_ATTR_GET_DEFER_LOW | JIT_ATTR_SET_USURP_LOW;
	attr = jit_object_new(_jit_sym_jit_attr_offset_array,"scale",_jit_sym_float32,2,attrflags,
		(method)0L,(method)0L,calcoffset(t_xray_jit_boidsrender,scalecount),calcoffset(t_xray_jit_boidsrender,scale));
	jit_class_addattr(_xray_jit_boidsrender_class,attr);
	attr = jit_object_new(atsym,"normalize",_jit_sym_char,attrflags,
		(method)0L,(method)0L,calcoffset(t_xray_jit_boidsrender,normalize));
	jit_class_addattr(_xray_jit_boidsrender_class,attr);
	//add methods
	
	jit_class_register(_xray_jit_boidsrender_class);

	return JIT_ERR_NONE;
}

t_jit_err xray_jit_boidsrender_matrix_calc(t_xray_jit_boidsrender *x, void *inputs, void *outputs)
{
	t_jit_err err=JIT_ERR_NONE;
	long in1_savelock,out_savelock, out2_savelock;
	t_jit_matrix_info in1_minfo,out_minfo, out2_minfo;
	char *in1_bp,*out_bp, *out2_bp;
	long i,dimcount,planecount,dim[JIT_MATRIX_MAX_DIMCOUNT];
	void *in1_matrix,*out_matrix, *out2_matrix;
	
	in1_matrix 	= jit_object_method(inputs,_jit_sym_getindex,0);
	out_matrix 	= jit_object_method(outputs,_jit_sym_getindex,0);
	out2_matrix = jit_object_method(outputs,_jit_sym_getindex,1);

	if (x&&in1_matrix&&out_matrix&&out2_matrix)
	{
		in1_savelock = (long) jit_object_method(in1_matrix,_jit_sym_lock,1);
		out_savelock = (long) jit_object_method(out_matrix,_jit_sym_lock,1);
		out2_savelock = (long) jit_object_method(out2_matrix,_jit_sym_lock,1);
		
		jit_object_method(in1_matrix,_jit_sym_getinfo,&in1_minfo);
		jit_object_method(out_matrix,_jit_sym_getinfo,&out_minfo);
		jit_object_method(out2_matrix,_jit_sym_getinfo,&out2_minfo);
		
		//each row is a point turned into a quad
		out_minfo.dim[0] = 4;
		out_minfo.dim[1] = in1_minfo.dim[0];
		out_minfo.planecount = 3;
		
		out2_minfo.dim[0] = 4;
		out2_minfo.dim[1] = in1_minfo.dim[0];
		out2_minfo.planecount = 2;
		
		jit_object_method(out_matrix,_jit_sym_setinfo,&out_minfo);
		jit_object_method(out_matrix,_jit_sym_getinfo,&out_minfo);
		
		jit_object_method(out2_matrix,_jit_sym_setinfo,&out2_minfo);
		jit_object_method(out2_matrix,_jit_sym_getinfo,&out2_minfo);
		
		jit_object_method(in1_matrix,_jit_sym_getdata,&in1_bp);
		jit_object_method(out_matrix,_jit_sym_getdata,&out_bp);
		jit_object_method(out2_matrix,_jit_sym_getdata,&out2_bp);
		
		if (!in1_bp) { err=JIT_ERR_INVALID_INPUT; goto out;}
		if (!out_bp||!out2_bp) { err=JIT_ERR_INVALID_OUTPUT; goto out;}	
			
		//get dimensions/planecount
		dimcount   = in1_minfo.dimcount;
		planecount = in1_minfo.planecount;			
		
		for (i=0;i<dimcount;i++) {
			dim[i] = in1_minfo.dim[i];
		}
				
		xray_jit_boidsrender_calculate_ndim(x, dimcount, dim, planecount, &in1_minfo, in1_bp, &out_minfo, out_bp);
		xray_jit_boidsrender_make_texcoords(&out2_minfo, out2_bp);
	}
	else {
		return JIT_ERR_INVALID_PTR;
	}
	
out:
	jit_object_method(out2_matrix,gensym("lock"),out2_savelock);
	jit_object_method(out_matrix,gensym("lock"),out_savelock);
	jit_object_method(in1_matrix,gensym("lock"),in1_savelock);
	return err;
}

void TransformPoint(float *p_in, float *p_out, float *X, float *Y, float *Z)
{
	p_out[0] = p_in[0]*X[0] + p_in[1]*X[1] + p_in[2]*X[2];
	p_out[1] = p_in[0]*Y[0] + p_in[1]*Y[1] + p_in[2]*Y[2];  
	p_out[2] = p_in[0]*Z[0] + p_in[1]*Z[1] + p_in[2]*Z[2];  
}

void InvTransformPoint(float *p_in, float *p_out, float *X, float *Y, float *Z)
{
	p_out[0] = p_in[0]*X[0] + p_in[1]*Y[0] + p_in[2]*Z[0];
	p_out[1] = p_in[0]*X[1] + p_in[1]*Y[1] + p_in[2]*Z[1];  
	p_out[2] = p_in[0]*X[2] + p_in[1]*Y[2] + p_in[2]*Z[2];  
}

void Vadd(float *p1, float *p2, float *p_out)
{
	p_out[0] = p1[0] + p2[0];
	p_out[1] = p1[1] + p2[1];
	p_out[2] = p1[2] + p2[2];
}

void postVect(float *vect)
{
	char er[90];
	
	sprintf(er, "%f %f %f", vect[0], vect[1], vect[2]);
	post(er);
}

void xray_jit_boidsrender_calculate_ndim(t_xray_jit_boidsrender *x, long dimcount, long *dim, long planecount, t_jit_matrix_info *in1_minfo, char *bip1, 
	t_jit_matrix_info *out_minfo, char *bop)
{
	long i,j,k,n;
	float *fip,*fop;
	double *dip, *dop;
	long height,width;
	long incolstride, inrowstride, outcolstride, outrowstride;
	float *scale;
	float F[3], E[3], G[3], center[3];
	float Flength;
	float centerPoint[3];
	float D;
	float X[3], Y[3], Z[3];
	float planePoint[3];
	float LL[3], UL[3], UR[3], LR[3];
	float LLt[3], ULt[3], URt[3], LRt[3];
	float vectNorm[3], xlength, ylength, distance;
	float scaleWidth, scaleHeight;
	char er[90];
	
	if (dimcount<1) return; //safety
	
	switch(dimcount) {
	case 1:
		dim[1]=1;
	case 2:
	default:			
		width  = dim[0];
		height = dim[1];
		
		incolstride = in1_minfo->dimstride[0];
		inrowstride = in1_minfo->dimstride[1];
		outcolstride = out_minfo->dimstride[0];
		outrowstride = out_minfo->dimstride[1];
		
		scaleWidth = x->scale[0]/2;
		scaleHeight = x->scale[1]/2;
		
		if (in1_minfo->type==_jit_sym_float32)
		{
			fip = (float *)bip1;
			
			switch(planecount) {
			case 2:
				for(i=0; i < dim[0]; i++) {
					//make quad in clockwise direction
					fop = (float *)(bop + i*outrowstride);
					
					fop[0] = fip[0]-scaleWidth;
					fop[1] = fip[1]-scaleHeight;
					fop[2] = 0;
					
					fop[3] = fip[0]-scaleWidth;
					fop[4] = fip[1]+scaleHeight;
					fop[5] = 0;
					
					fop[6] = fip[0]+scaleWidth;
					fop[7] = fip[1]+scaleHeight;
					fop[8] = 0;
					
					fop[9] = fip[0]+scaleWidth;
					fop[10] = fip[1]-scaleHeight;
					fop[11] = 0;
					
					fip += planecount;
				}	
			break;
			case 3:
				for(i=0; i < dim[0]; i++) {
					//make quad in clockwise direction
					fop = (float *)(bop + i*outrowstride);
					
					fop[0] = fip[0]-scaleWidth;
					fop[1] = fip[1]-scaleHeight;
					fop[2] = fip[2];
					
					fop[3] = fip[0]-scaleWidth;
					fop[4] = fip[1]+scaleHeight;
					fop[5] = fip[2];
					
					fop[6] = fip[0]+scaleWidth;
					fop[7] = fip[1]+scaleHeight;
					fop[8] = fip[2];
					
					fop[9] = fip[0]+scaleWidth;
					fop[10] = fip[1]-scaleHeight;
					fop[11] = fip[2];
					
					fip += planecount;
				}	
			break;
			case 4:
				if(x->normalize == 0) {
					for(i=0; i < dim[0]; i++) {
						fop = (float *)(bop + i*outrowstride);
						
						//calculate normalized vector direction
						vectNorm[0] = fip[2]-fip[0];
						vectNorm[1] = fip[3]-fip[1];
						
						centerPoint[0] = (fip[0] + fip[2])/2.0f;
						centerPoint[1] = (fip[1] + fip[3])/2.0f;
						
						/*
							widthOffset = { -vectNorm[1]*scaleWidth, vectNorm[0]*scaleWidth }
							heightOffset = { vectNorm[0]*scaleHeight, vectNorm[1]*scaleHeight }
						*/
						
						//P2 + widthOffset - heightOffset
						fop[0] = centerPoint[0] - vectNorm[1]*scaleWidth - vectNorm[0]*scaleHeight;
						fop[1] = centerPoint[1] + vectNorm[0]*scaleWidth - vectNorm[1]*scaleHeight;
						fop[2] = 0.0f;
						
						//P2 - widthOffset - heightOffset
						fop[3] = centerPoint[0] + vectNorm[1]*scaleWidth - vectNorm[0]*scaleHeight;
						fop[4] = centerPoint[1] - vectNorm[0]*scaleWidth - vectNorm[1]*scaleHeight;
						fop[5] = 0.0f;
						
						//P1 - widthOffset + heightOffset
						fop[6] = centerPoint[0] + vectNorm[1]*scaleWidth + vectNorm[0]*scaleHeight;
						fop[7] = centerPoint[1] - vectNorm[0]*scaleWidth + vectNorm[1]*scaleHeight;
						fop[8] = 0.0f;
						
						//P1 + widthOffset + heightOffset
						fop[9] = centerPoint[0] - vectNorm[1]*scaleWidth + vectNorm[0]*scaleHeight;
						fop[10] = centerPoint[1] + vectNorm[0]*scaleWidth + vectNorm[1]*scaleHeight;
						fop[11] = 0.0f;
						
						fip += planecount;
					}
				}
				else {
					for(i=0; i < dim[0]; i++) {
						fop = (float *)(bop + i*outrowstride);
						
						//calculate normalized vector direction
						vectNorm[0] = fip[2]-fip[0];
						vectNorm[1] = fip[3]-fip[1];
						
						distance = jit_math_sqrt( vectNorm[0]*vectNorm[0] + vectNorm[1]*vectNorm[1] );
						vectNorm[0] /= distance;
						vectNorm[1] /= distance;
						
						centerPoint[0] = (fip[0] + fip[2])/2.0f;
						centerPoint[1] = (fip[1] + fip[3])/2.0f;
						
						/*
							widthOffset = { -vectNorm[1]*scaleWidth, vectNorm[0]*scaleWidth }
							heightOffset = { vectNorm[0]*scaleHeight, vectNorm[1]*scaleHeight }
						*/
						
						//P2 + widthOffset - heightOffset
						fop[0] = centerPoint[0] - vectNorm[1]*scaleWidth - vectNorm[0]*scaleHeight;
						fop[1] = centerPoint[1] + vectNorm[0]*scaleWidth - vectNorm[1]*scaleHeight;
						fop[2] = 0.0f;
						
						//P2 - widthOffset - heightOffset
						fop[3] = centerPoint[0] + vectNorm[1]*scaleWidth - vectNorm[0]*scaleHeight;
						fop[4] = centerPoint[1] - vectNorm[0]*scaleWidth - vectNorm[1]*scaleHeight;
						fop[5] = 0.0f;
						
						//P1 - widthOffset + heightOffset
						fop[6] = centerPoint[0] + vectNorm[1]*scaleWidth + vectNorm[0]*scaleHeight;
						fop[7] = centerPoint[1] - vectNorm[0]*scaleWidth + vectNorm[1]*scaleHeight;
						fop[8] = 0.0f;
						
						//P1 + widthOffset + heightOffset
						fop[9] = centerPoint[0] - vectNorm[1]*scaleWidth + vectNorm[0]*scaleHeight;
						fop[10] = centerPoint[1] + vectNorm[0]*scaleWidth + vectNorm[1]*scaleHeight;
						fop[11] = 0.0f;
						
						fip += planecount;
					}
				}
			break;
			case 6:
			case 9:
				//set x-coordinate of point in plane to always be 0
				planePoint[0] = 0.0f;
				
				if(x->normalize) {
					for(i=0; i < dim[0]; i++) {
						//make quad in clockwise direction
						fop = (float *)(bop + i*outrowstride);
						
						//calculate normalized vector direction
						X[0] = fip[3]-fip[0];
						X[1] = fip[4]-fip[1];
						X[2] = fip[5]-fip[2];
						
						xlength = jit_math_sqrt(X[0]*X[0] + X[1]*X[1] + X[2]*X[2]);
						
						if(xlength != 0.0f) {
							X[0] /= xlength;
							X[1] /= xlength;
							X[2] /= xlength;
						}
						
						//calculate plane offset from origin
						D = -(X[0]*fip[0] + X[1]*fip[1] + X[2]*fip[2]);
						
						//check to see if vector is only in XY-plane
						//calculate a point in the plane defined by X as its normal
						if(X[2] != 0.0f) {
							planePoint[1] = 1.0f;						
							planePoint[2] = -(D + X[0]*planePoint[0] + X[1]*planePoint[1])/X[2];
						}
						else {
							planePoint[2] = 1.0f;
							
							//check for divide by zero
							if(X[1] != 0.0) {
								planePoint[1] = -(D + X[0]*planePoint[0] + X[2]*planePoint[2])/X[1];
							}
							else {
								planePoint[1] = 0.0f;
							}
						}
						
						//make planePoint - p1 the Y-axis
						//calculate normalized vector direction
						Y[0] = planePoint[0]-fip[0];
						Y[1] = planePoint[1]-fip[1];
						Y[2] = planePoint[2]-fip[2];
						
						ylength = jit_math_sqrt(Y[0]*Y[0] + Y[1]*Y[1] + Y[2]*Y[2]);
						
						if(ylength != 0.0f) {
							Y[0] /= ylength;
							Y[1] /= ylength;
							Y[2] /= ylength;
						}
						
						//get Z-axis from X x Y
						Z[0] = (X[1] * Y[2]) - (X[2] * Y[1]);
						Z[1] = (X[2] * Y[0]) - (X[0] * Y[2]);
						Z[2] = (X[0] * Y[1]) - (X[1] * Y[0]);
						
						xlength *= 0.5f;
						
						//the quad will be in the XY-plane in the transformed space
						LLt[0] = (xlength-scaleHeight);
						LLt[1] = scaleWidth;
						LLt[2] = 0.0;
						
						ULt[0] = (xlength+scaleHeight);
						ULt[1] = scaleWidth;
						ULt[2] = 0.0;
						
						URt[0] = (xlength+scaleHeight);
						URt[1] = -scaleWidth;
						URt[2] = 0.0;
						
						LRt[0] = (xlength-scaleHeight);
						LRt[1] = -scaleWidth;
						LRt[2] = 0.0;
						
						//transform quad points into line coordinate space
						InvTransformPoint(LLt, fop, X, Y, Z);
						InvTransformPoint(ULt, fop+3, X, Y, Z);
						InvTransformPoint(URt, fop+6, X, Y, Z);
						InvTransformPoint(LRt, fop+9, X, Y, Z);
						
						//shift coordinates to have the same origin as the start of the line
						Vadd(fip, fop, fop);
						Vadd(fip, fop+3, fop+3);
						Vadd(fip, fop+6, fop+6);
						Vadd(fip, fop+9, fop+9);
						
						fip += planecount;
					}
				}
				else {
					for(i=0; i < dim[0]; i++) {				
						//make quad in clockwise direction
						fop = (float *)(bop + i*outrowstride);
						
						//calculate normalized vector direction
						X[0] = fip[3]-fip[0];
						X[1] = fip[4]-fip[1];
						X[2] = fip[5]-fip[2];
						
						xlength = jit_math_sqrt(X[0]*X[0] + X[1]*X[1] + X[2]*X[2]);
						
						if(xlength != 0.0f) {
							X[0] /= xlength;
							X[1] /= xlength;
							X[2] /= xlength;
						}
						
						//calculate plane offset from origin
						D = -(X[0]*fip[0] + X[1]*fip[1] + X[2]*fip[2]);
						
						//check to see if vector is only in XY-plane
						//calculate a point in the plane defined by X as its normal
						if(X[2] != 0.0f) {
							planePoint[1] = 1.0f;						
							planePoint[2] = -(D + X[0]*planePoint[0] + X[1]*planePoint[1])/X[2];
						}
						else {
							planePoint[2] = 0.0f;
							
							//check for divide by zero
							if(X[1] != 0.0) {
								planePoint[1] = -(D + X[0]*planePoint[0] + X[2]*planePoint[2])/X[1];
							}
							else {
								planePoint[1] = 0.0f;
							}
						}
						
						//make planePoint - p1 the Y-axis
						//calculate normalized vector direction
						Y[0] = planePoint[0]-fip[0];
						Y[1] = planePoint[1]-fip[1];
						Y[2] = planePoint[2]-fip[2];
						
						ylength = jit_math_sqrt(Y[0]*Y[0] + Y[1]*Y[1] + Y[2]*Y[2]);
						
						if(ylength != 0.0f) {
							Y[0] /= ylength;
							Y[1] /= ylength;
							Y[2] /= ylength;
						}
						
						//get Z-axis from X x Y
						Z[0] = (X[1] * Y[2]) - (X[2] * Y[1]);
						Z[1] = (X[2] * Y[0]) - (X[0] * Y[2]);
						Z[2] = (X[0] * Y[1]) - (X[1] * Y[0]);
						
						
						//the quad will be in the XY-plane in the transformed space
						LLt[0] = (0.5f-scaleHeight)*xlength;
						LLt[1] = scaleWidth;
						LLt[2] = 0.0;
						
						ULt[0] = (0.5f+scaleHeight)*xlength;
						ULt[1] = scaleWidth;
						ULt[2] = 0.0;
						
						URt[0] = (0.5f+scaleHeight)*xlength;
						URt[1] = -scaleWidth;
						URt[2] = 0.0;
						
						LRt[0] = (0.5f-scaleHeight)*xlength;
						LRt[1] = -scaleWidth;
						LRt[2] = 0.0;
						
						//transform quad points into line coordinate space
						InvTransformPoint(LLt, fop, X, Y, Z);
						InvTransformPoint(ULt, fop+3, X, Y, Z);
						InvTransformPoint(URt, fop+6, X, Y, Z);
						InvTransformPoint(LRt, fop+9, X, Y, Z);
						
						//shift coordinates to have the same origin as the start of the line
						Vadd(fip, fop, fop);
						Vadd(fip, fop+3, fop+3);
						Vadd(fip, fop+6, fop+6);
						Vadd(fip, fop+9, fop+9);
						
						fip += planecount;
					}
				}
			break;
			}
		}
		break;
	}
}

void xray_jit_boidsrender_make_texcoords(t_jit_matrix_info *out2_minfo, char *bop2)
{
	long i, out2_rowspan;
	float *fop2;
	
	out2_rowspan = out2_minfo->dimstride[1];
	
	for(i=0; i < out2_minfo->dim[1]; i++) {
		fop2 = (float *)(bop2 + i*out2_rowspan);
	
		fop2[0] = 1.0;
		fop2[1] = 1.0;
		
		fop2[2] = 1.0;
		fop2[3] = 0.0;
		
		fop2[4] = 0.0;
		fop2[5] = 0.0;
		
		fop2[6] = 0.0;
		fop2[7] = 1.0;
	}
}

t_xray_jit_boidsrender *xray_jit_boidsrender_new(void)
{
	t_xray_jit_boidsrender *x;
		
	if (x=(t_xray_jit_boidsrender *)jit_object_alloc(_xray_jit_boidsrender_class)) {
		x->scale[0] = 1.0;
		x->scale[1] = 1.0;
		x->scalecount = 2;
		x->normalize = 0;
		
	} else {
		x = NULL;
	}	
	return x;
}

void xray_jit_boidsrender_free(t_xray_jit_boidsrender *x)
{
	//nada
}