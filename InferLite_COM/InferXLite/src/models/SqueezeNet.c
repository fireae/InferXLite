/*
	This file is generated by net_compiler.py.
	The use of included functions list as follows:

	Input:
	Input(int dim1,int dim2,int dim3,int dim4,char *top,char *name)

	Convolution:
	Convolution(int num_input,int num_output,int kernel_h,int kernel_w,int stride_h,int stride_w,int pad_h,int pad_w,int group,int dilation,int axis,bool bias_term,bool force_nd_im2col,char *bottom,char *top, char *name,int is_merge_relu,struct handler *hd)

	ReLU:
	ReLU(char *bottom,char *top,char *name,struct handler *hd)

	Pooling:
	inferx_pooling(int kernel_h,int kernel_w,int stride_h,int stride_w,int pad_h,int pad_w,enum PoolMethod pool,char *bottom,char *top,char *name,struct handler *hd)

	Concat:
	inferx_concat(int num_output,int axis,int concat_dim,int bottom_num,char **bottoms,char *top,char *name,struct handler *hd)

	Pooling:
	inferx_global_pooling(enum PoolMethod pool,char *bottom,char *top,char *name,struct handler *hd)

	Softmax:
	inferx_softmax(int axis,char *bottom,char *top,char *name,struct handler *hd)
*/

#include "inferxlite_common.h"
#include "interface.h"
void SqueezeNet(char* path, char* model, char* data, void* pdata, void** pout, struct handler *hd)
{
	char* bottom_vector[2];

	static int nchw[4];

	inferx_net_preprocess(data,model,nchw,hd);

	inferx_input(nchw,pdata,"data_data","data",model,data,hd);
	
	inferx_convolution(3,96,7,7,2,2,0,0,1,1,1,true,false,"data_data","conv1_data","conv1",model,data, 0,hd);
	inferx_relu("conv1_data","conv1_data","relu_conv1",model,data,hd);
	inferx_pooling(3,3,2,2,0,0,MAX,"conv1_data","pool1_data","pool1",model,data,hd);
	inferx_convolution(96,16,1,1,1,1,0,0,1,1,1,true,false,"pool1_data","fire2/squeeze1x1_data","fire2/squeeze1x1",model,data, 0,hd);
	inferx_relu("fire2/squeeze1x1_data","fire2/squeeze1x1_data","fire2/relu_squeeze1x1",model,data,hd);
	inferx_convolution(16,64,1,1,1,1,0,0,1,1,1,true,false,"fire2/squeeze1x1_data","fire2/expand1x1_data","fire2/expand1x1",model,data, 0,hd);
	inferx_relu("fire2/expand1x1_data","fire2/expand1x1_data","fire2/relu_expand1x1",model,data,hd);
	inferx_convolution(16,64,3,3,1,1,1,1,1,1,1,true,false,"fire2/squeeze1x1_data","fire2/expand3x3_data","fire2/expand3x3",model,data, 0,hd);
	inferx_relu("fire2/expand3x3_data","fire2/expand3x3_data","fire2/relu_expand3x3",model,data,hd);
	bottom_vector[0] = "fire2/expand1x1_data";	bottom_vector[1] = "fire2/expand3x3_data";
	inferx_concat(128,1,1,2,bottom_vector,"fire2/concat_data","fire2/concat",model,data,hd);
	inferx_convolution(128,16,1,1,1,1,0,0,1,1,1,true,false,"fire2/concat_data","fire3/squeeze1x1_data","fire3/squeeze1x1",model,data, 0,hd);
	inferx_relu("fire3/squeeze1x1_data","fire3/squeeze1x1_data","fire3/relu_squeeze1x1",model,data,hd);
	inferx_convolution(16,64,1,1,1,1,0,0,1,1,1,true,false,"fire3/squeeze1x1_data","fire3/expand1x1_data","fire3/expand1x1",model,data, 0,hd);
	inferx_relu("fire3/expand1x1_data","fire3/expand1x1_data","fire3/relu_expand1x1",model,data,hd);
	inferx_convolution(16,64,3,3,1,1,1,1,1,1,1,true,false,"fire3/squeeze1x1_data","fire3/expand3x3_data","fire3/expand3x3",model,data, 0,hd);
	inferx_relu("fire3/expand3x3_data","fire3/expand3x3_data","fire3/relu_expand3x3",model,data,hd);
	bottom_vector[0] = "fire3/expand1x1_data";	bottom_vector[1] = "fire3/expand3x3_data";
	inferx_concat(128,1,1,2,bottom_vector,"fire3/concat_data","fire3/concat",model,data,hd);
	inferx_convolution(128,32,1,1,1,1,0,0,1,1,1,true,false,"fire3/concat_data","fire4/squeeze1x1_data","fire4/squeeze1x1",model,data, 0,hd);
	inferx_relu("fire4/squeeze1x1_data","fire4/squeeze1x1_data","fire4/relu_squeeze1x1",model,data,hd);
	inferx_convolution(32,128,1,1,1,1,0,0,1,1,1,true,false,"fire4/squeeze1x1_data","fire4/expand1x1_data","fire4/expand1x1",model,data, 0,hd);
	inferx_relu("fire4/expand1x1_data","fire4/expand1x1_data","fire4/relu_expand1x1",model,data,hd);
	inferx_convolution(32,128,3,3,1,1,1,1,1,1,1,true,false,"fire4/squeeze1x1_data","fire4/expand3x3_data","fire4/expand3x3",model,data, 0,hd);
	inferx_relu("fire4/expand3x3_data","fire4/expand3x3_data","fire4/relu_expand3x3",model,data,hd);
	bottom_vector[0] = "fire4/expand1x1_data";	bottom_vector[1] = "fire4/expand3x3_data";
	inferx_concat(256,1,1,2,bottom_vector,"fire4/concat_data","fire4/concat",model,data,hd);
	inferx_pooling(3,3,2,2,0,0,MAX,"fire4/concat_data","pool4_data","pool4",model,data,hd);
	inferx_convolution(256,32,1,1,1,1,0,0,1,1,1,true,false,"pool4_data","fire5/squeeze1x1_data","fire5/squeeze1x1",model,data, 0,hd);
	inferx_relu("fire5/squeeze1x1_data","fire5/squeeze1x1_data","fire5/relu_squeeze1x1",model,data,hd);
	inferx_convolution(32,128,1,1,1,1,0,0,1,1,1,true,false,"fire5/squeeze1x1_data","fire5/expand1x1_data","fire5/expand1x1",model,data, 0,hd);
	inferx_relu("fire5/expand1x1_data","fire5/expand1x1_data","fire5/relu_expand1x1",model,data,hd);
	inferx_convolution(32,128,3,3,1,1,1,1,1,1,1,true,false,"fire5/squeeze1x1_data","fire5/expand3x3_data","fire5/expand3x3",model,data, 0,hd);
	inferx_relu("fire5/expand3x3_data","fire5/expand3x3_data","fire5/relu_expand3x3",model,data,hd);
	bottom_vector[0] = "fire5/expand1x1_data";	bottom_vector[1] = "fire5/expand3x3_data";
	inferx_concat(256,1,1,2,bottom_vector,"fire5/concat_data","fire5/concat",model,data,hd);
	inferx_convolution(256,48,1,1,1,1,0,0,1,1,1,true,false,"fire5/concat_data","fire6/squeeze1x1_data","fire6/squeeze1x1",model,data, 0,hd);
	inferx_relu("fire6/squeeze1x1_data","fire6/squeeze1x1_data","fire6/relu_squeeze1x1",model,data,hd);
	inferx_convolution(48,192,1,1,1,1,0,0,1,1,1,true,false,"fire6/squeeze1x1_data","fire6/expand1x1_data","fire6/expand1x1",model,data, 0,hd);
	inferx_relu("fire6/expand1x1_data","fire6/expand1x1_data","fire6/relu_expand1x1",model,data,hd);
	inferx_convolution(48,192,3,3,1,1,1,1,1,1,1,true,false,"fire6/squeeze1x1_data","fire6/expand3x3_data","fire6/expand3x3",model,data, 0,hd);
	inferx_relu("fire6/expand3x3_data","fire6/expand3x3_data","fire6/relu_expand3x3",model,data,hd);
	bottom_vector[0] = "fire6/expand1x1_data";	bottom_vector[1] = "fire6/expand3x3_data";
	inferx_concat(384,1,1,2,bottom_vector,"fire6/concat_data","fire6/concat",model,data,hd);
	inferx_convolution(384,48,1,1,1,1,0,0,1,1,1,true,false,"fire6/concat_data","fire7/squeeze1x1_data","fire7/squeeze1x1",model,data, 0,hd);
	inferx_relu("fire7/squeeze1x1_data","fire7/squeeze1x1_data","fire7/relu_squeeze1x1",model,data,hd);
	inferx_convolution(48,192,1,1,1,1,0,0,1,1,1,true,false,"fire7/squeeze1x1_data","fire7/expand1x1_data","fire7/expand1x1",model,data, 0,hd);
	inferx_relu("fire7/expand1x1_data","fire7/expand1x1_data","fire7/relu_expand1x1",model,data,hd);
	inferx_convolution(48,192,3,3,1,1,1,1,1,1,1,true,false,"fire7/squeeze1x1_data","fire7/expand3x3_data","fire7/expand3x3",model,data, 0,hd);
	inferx_relu("fire7/expand3x3_data","fire7/expand3x3_data","fire7/relu_expand3x3",model,data,hd);
	bottom_vector[0] = "fire7/expand1x1_data";	bottom_vector[1] = "fire7/expand3x3_data";
	inferx_concat(384,1,1,2,bottom_vector,"fire7/concat_data","fire7/concat",model,data,hd);
	inferx_convolution(384,64,1,1,1,1,0,0,1,1,1,true,false,"fire7/concat_data","fire8/squeeze1x1_data","fire8/squeeze1x1",model,data, 0,hd);
	inferx_relu("fire8/squeeze1x1_data","fire8/squeeze1x1_data","fire8/relu_squeeze1x1",model,data,hd);
	inferx_convolution(64,256,1,1,1,1,0,0,1,1,1,true,false,"fire8/squeeze1x1_data","fire8/expand1x1_data","fire8/expand1x1",model,data, 0,hd);
	inferx_relu("fire8/expand1x1_data","fire8/expand1x1_data","fire8/relu_expand1x1",model,data,hd);
	inferx_convolution(64,256,3,3,1,1,1,1,1,1,1,true,false,"fire8/squeeze1x1_data","fire8/expand3x3_data","fire8/expand3x3",model,data, 0,hd);
	inferx_relu("fire8/expand3x3_data","fire8/expand3x3_data","fire8/relu_expand3x3",model,data,hd);
	bottom_vector[0] = "fire8/expand1x1_data";	bottom_vector[1] = "fire8/expand3x3_data";
	inferx_concat(512,1,1,2,bottom_vector,"fire8/concat_data","fire8/concat",model,data,hd);
	inferx_pooling(3,3,2,2,0,0,MAX,"fire8/concat_data","pool8_data","pool8",model,data,hd);
	inferx_convolution(512,64,1,1,1,1,0,0,1,1,1,true,false,"pool8_data","fire9/squeeze1x1_data","fire9/squeeze1x1",model,data, 0,hd);
	inferx_relu("fire9/squeeze1x1_data","fire9/squeeze1x1_data","fire9/relu_squeeze1x1",model,data,hd);
	inferx_convolution(64,256,1,1,1,1,0,0,1,1,1,true,false,"fire9/squeeze1x1_data","fire9/expand1x1_data","fire9/expand1x1",model,data, 0,hd);
	inferx_relu("fire9/expand1x1_data","fire9/expand1x1_data","fire9/relu_expand1x1",model,data,hd);
	inferx_convolution(64,256,3,3,1,1,1,1,1,1,1,true,false,"fire9/squeeze1x1_data","fire9/expand3x3_data","fire9/expand3x3",model,data, 0,hd);
	inferx_relu("fire9/expand3x3_data","fire9/expand3x3_data","fire9/relu_expand3x3",model,data,hd);
	bottom_vector[0] = "fire9/expand1x1_data";	bottom_vector[1] = "fire9/expand3x3_data";
	inferx_concat(512,1,1,2,bottom_vector,"fire9/concat_data","fire9/concat",model,data,hd);
	inferx_convolution(512,1000,1,1,1,1,1,1,1,1,1,true,false,"fire9/concat_data","conv10_data","conv10",model,data, 0,hd);
	inferx_relu("conv10_data","conv10_data","relu_conv10",model,data,hd);
	inferx_global_pooling(AVE,"conv10_data","pool10_data","pool10",model,data,hd);
	inferx_softmax(1,"pool10_data","prob_data","prob",model,data,hd);

	//inferx_sort_data("prob_data", data, hd);
	inferx_print_data("prob_data", data, hd);
	if(pout)
	  *pout = inferx_get_data("prob_data", data, hd);
	inferx_finalize("SqueezeNet", hd);

	return;
}