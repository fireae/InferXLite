/*
	This file is generated by net_compiler.py.
	The use of included functions list as follows:

	Input:
	Input(int dim1,int dim2,int dim3,int dim4,char *top,char *name)

	Convolution:
	Convolution(int num_input,int num_output,int kernel_h,int kernel_w,int stride_h,int stride_w,int pad_h,int pad_w,int group,int dilation,int axis,bool bias_term,bool force_nd_im2col,char *bottom,char *top, char *name,int is_merge_relu,struct handler *hd)

	BatchNorm:
	inferx_batchnorm(float moving_average_fraction,float eps,bool use_global_stats,char *bottom,char *top,char *name,struct handler *hd)

	Scale:
	inferx_scale(int axis,int num_axes,bool bias_term,char *bottom,char *top,char *name,struct handler *hd)

	ReLU:
	ReLU(char *bottom,char *top,char *name,struct handler *hd)

	Eltwise:
	inferx_eltwise(int coeffs_num, float* coeffs,enum EltwiseOp operation,bool stabel_prod_grad,int bottom_num,char **bottoms,char *top, char *name,struct handler *hd)

	Pooling:
	inferx_global_pooling(enum PoolMethod pool,char *bottom,char *top,char *name,struct handler *hd)

	Softmax:
	inferx_softmax(int axis,char *bottom,char *top,char *name,struct handler *hd)
*/

#include "inferxlite_common.h"
#include "interface.h"
void MOBILENETV2(char* path, char* model, char* data, void* pdata, void** pout, struct handler *hd)
{
	float coeffs[2];
	char* bottom_vector[2];

	static int nchw[4];
	inferx_net_preprocess(data,model,nchw,hd);

	inferx_input(nchw,pdata,"data_data","data",model,data,hd);
	inferx_convolution(3,32,3,3,2,2,1,1,1,1,1,false,false,"data_data","conv1_data","conv1",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv1_data","conv1/bn_data","conv1/bn",model,data,hd);
	inferx_scale(1,1,true,"conv1/bn_data","conv1/bn_data","conv1/scale",model,data,hd);
	inferx_relu("conv1/bn_data","conv1/bn_data","relu1",model,data,hd);
	inferx_convolution(32,32,1,1,1,1,0,0,1,1,1,false,false,"conv1/bn_data","conv2_1/expand_data","conv2_1/expand",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv2_1/expand_data","conv2_1/expand/bn_data","conv2_1/expand/bn",model,data,hd);
	inferx_scale(1,1,true,"conv2_1/expand/bn_data","conv2_1/expand/bn_data","conv2_1/expand/scale",model,data,hd);
	inferx_relu("conv2_1/expand/bn_data","conv2_1/expand/bn_data","relu2_1/expand",model,data,hd);



	inferx_convolution(32,32,3,3,1,1,1,1,32,1,1,false,false,"conv2_1/expand/bn_data","conv2_1/dwise_data","conv2_1/dwise",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv2_1/dwise_data","conv2_1/dwise/bn_data","conv2_1/dwise/bn",model,data,hd);
	inferx_scale(1,1,true,"conv2_1/dwise/bn_data","conv2_1/dwise/bn_data","conv2_1/dwise/scale",model,data,hd);
	inferx_relu("conv2_1/dwise/bn_data","conv2_1/dwise/bn_data","relu2_1/dwise",model,data,hd);

	inferx_convolution(32,16,1,1,1,1,0,0,1,1,1,false,false,"conv2_1/dwise/bn_data","conv2_1/linear_data","conv2_1/linear",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv2_1/linear_data","conv2_1/linear/bn_data","conv2_1/linear/bn",model,data,hd);
	inferx_scale(1,1,true,"conv2_1/linear/bn_data","conv2_1/linear/bn_data","conv2_1/linear/scale",model,data,hd);
	


	inferx_convolution(16,96,1,1,1,1,0,0,1,1,1,false,false,"conv2_1/linear/bn_data","conv2_2/expand_data","conv2_2/expand",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv2_2/expand_data","conv2_2/expand/bn_data","conv2_2/expand/bn",model,data,hd);
	inferx_scale(1,1,true,"conv2_2/expand/bn_data","conv2_2/expand/bn_data","conv2_2/expand/scale",model,data,hd);
	inferx_relu("conv2_2/expand/bn_data","conv2_2/expand/bn_data","relu2_2/expand",model,data,hd);
	inferx_convolution(96,96,3,3,2,2,1,1,96,1,1,false,false,"conv2_2/expand/bn_data","conv2_2/dwise_data","conv2_2/dwise",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv2_2/dwise_data","conv2_2/dwise/bn_data","conv2_2/dwise/bn",model,data,hd);
	inferx_scale(1,1,true,"conv2_2/dwise/bn_data","conv2_2/dwise/bn_data","conv2_2/dwise/scale",model,data,hd);
	inferx_relu("conv2_2/dwise/bn_data","conv2_2/dwise/bn_data","relu2_2/dwise",model,data,hd);
	inferx_convolution(96,24,1,1,1,1,0,0,1,1,1,false,false,"conv2_2/dwise/bn_data","conv2_2/linear_data","conv2_2/linear",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv2_2/linear_data","conv2_2/linear/bn_data","conv2_2/linear/bn",model,data,hd);
	inferx_scale(1,1,true,"conv2_2/linear/bn_data","conv2_2/linear/bn_data","conv2_2/linear/scale",model,data,hd);
	inferx_convolution(24,144,1,1,1,1,0,0,1,1,1,false,false,"conv2_2/linear/bn_data","conv3_1/expand_data","conv3_1/expand",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv3_1/expand_data","conv3_1/expand/bn_data","conv3_1/expand/bn",model,data,hd);
	inferx_scale(1,1,true,"conv3_1/expand/bn_data","conv3_1/expand/bn_data","conv3_1/expand/scale",model,data,hd);
	inferx_relu("conv3_1/expand/bn_data","conv3_1/expand/bn_data","relu3_1/expand",model,data,hd);
	inferx_convolution(144,144,3,3,1,1,1,1,144,1,1,false,false,"conv3_1/expand/bn_data","conv3_1/dwise_data","conv3_1/dwise",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv3_1/dwise_data","conv3_1/dwise/bn_data","conv3_1/dwise/bn",model,data,hd);
	inferx_scale(1,1,true,"conv3_1/dwise/bn_data","conv3_1/dwise/bn_data","conv3_1/dwise/scale",model,data,hd);
	inferx_relu("conv3_1/dwise/bn_data","conv3_1/dwise/bn_data","relu3_1/dwise",model,data,hd);
	inferx_convolution(144,24,1,1,1,1,0,0,1,1,1,false,false,"conv3_1/dwise/bn_data","conv3_1/linear_data","conv3_1/linear",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv3_1/linear_data","conv3_1/linear/bn_data","conv3_1/linear/bn",model,data,hd);
	inferx_scale(1,1,true,"conv3_1/linear/bn_data","conv3_1/linear/bn_data","conv3_1/linear/scale",model,data,hd);
	bottom_vector[0] = "conv2_2/linear/bn_data";	bottom_vector[1] = "conv3_1/linear/bn_data";
	coeffs[0]=1.000000; coeffs[1]=1.000000; 
	inferx_eltwise(2,coeffs,SUM,true,2,bottom_vector,"block_3_1_data","block_3_1",model,data,hd);
	inferx_convolution(24,144,1,1,1,1,0,0,1,1,1,false,false,"block_3_1_data","conv3_2/expand_data","conv3_2/expand",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv3_2/expand_data","conv3_2/expand/bn_data","conv3_2/expand/bn",model,data,hd);
	inferx_scale(1,1,true,"conv3_2/expand/bn_data","conv3_2/expand/bn_data","conv3_2/expand/scale",model,data,hd);
	inferx_relu("conv3_2/expand/bn_data","conv3_2/expand/bn_data","relu3_2/expand",model,data,hd);
	inferx_convolution(144,144,3,3,2,2,1,1,144,1,1,false,false,"conv3_2/expand/bn_data","conv3_2/dwise_data","conv3_2/dwise",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv3_2/dwise_data","conv3_2/dwise/bn_data","conv3_2/dwise/bn",model,data,hd);
	inferx_scale(1,1,true,"conv3_2/dwise/bn_data","conv3_2/dwise/bn_data","conv3_2/dwise/scale",model,data,hd);
	inferx_relu("conv3_2/dwise/bn_data","conv3_2/dwise/bn_data","relu3_2/dwise",model,data,hd);
	inferx_convolution(144,32,1,1,1,1,0,0,1,1,1,false,false,"conv3_2/dwise/bn_data","conv3_2/linear_data","conv3_2/linear",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv3_2/linear_data","conv3_2/linear/bn_data","conv3_2/linear/bn",model,data,hd);
	inferx_scale(1,1,true,"conv3_2/linear/bn_data","conv3_2/linear/bn_data","conv3_2/linear/scale",model,data,hd);
	inferx_convolution(32,192,1,1,1,1,0,0,1,1,1,false,false,"conv3_2/linear/bn_data","conv4_1/expand_data","conv4_1/expand",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_1/expand_data","conv4_1/expand/bn_data","conv4_1/expand/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_1/expand/bn_data","conv4_1/expand/bn_data","conv4_1/expand/scale",model,data,hd);
	inferx_relu("conv4_1/expand/bn_data","conv4_1/expand/bn_data","relu4_1/expand",model,data,hd);
	inferx_convolution(192,192,3,3,1,1,1,1,192,1,1,false,false,"conv4_1/expand/bn_data","conv4_1/dwise_data","conv4_1/dwise",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_1/dwise_data","conv4_1/dwise/bn_data","conv4_1/dwise/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_1/dwise/bn_data","conv4_1/dwise/bn_data","conv4_1/dwise/scale",model,data,hd);
	inferx_relu("conv4_1/dwise/bn_data","conv4_1/dwise/bn_data","relu4_1/dwise",model,data,hd);
	inferx_convolution(192,32,1,1,1,1,0,0,1,1,1,false,false,"conv4_1/dwise/bn_data","conv4_1/linear_data","conv4_1/linear",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_1/linear_data","conv4_1/linear/bn_data","conv4_1/linear/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_1/linear/bn_data","conv4_1/linear/bn_data","conv4_1/linear/scale",model,data,hd);
	bottom_vector[0] = "conv3_2/linear/bn_data";	bottom_vector[1] = "conv4_1/linear/bn_data";
	coeffs[0]=1.000000; coeffs[1]=1.000000; 
	inferx_eltwise(2,coeffs,SUM,true,2,bottom_vector,"block_4_1_data","block_4_1",model,data,hd);
	inferx_convolution(32,192,1,1,1,1,0,0,1,1,1,false,false,"block_4_1_data","conv4_2/expand_data","conv4_2/expand",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_2/expand_data","conv4_2/expand/bn_data","conv4_2/expand/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_2/expand/bn_data","conv4_2/expand/bn_data","conv4_2/expand/scale",model,data,hd);
	inferx_relu("conv4_2/expand/bn_data","conv4_2/expand/bn_data","relu4_2/expand",model,data,hd);
	inferx_convolution(192,192,3,3,1,1,1,1,192,1,1,false,false,"conv4_2/expand/bn_data","conv4_2/dwise_data","conv4_2/dwise",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_2/dwise_data","conv4_2/dwise/bn_data","conv4_2/dwise/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_2/dwise/bn_data","conv4_2/dwise/bn_data","conv4_2/dwise/scale",model,data,hd);
	inferx_relu("conv4_2/dwise/bn_data","conv4_2/dwise/bn_data","relu4_2/dwise",model,data,hd);
	inferx_convolution(192,32,1,1,1,1,0,0,1,1,1,false,false,"conv4_2/dwise/bn_data","conv4_2/linear_data","conv4_2/linear",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_2/linear_data","conv4_2/linear/bn_data","conv4_2/linear/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_2/linear/bn_data","conv4_2/linear/bn_data","conv4_2/linear/scale",model,data,hd);
	bottom_vector[0] = "block_4_1_data";	bottom_vector[1] = "conv4_2/linear/bn_data";
	coeffs[0]=1.000000; coeffs[1]=1.000000; 
	inferx_eltwise(2,coeffs,SUM,true,2,bottom_vector,"block_4_2_data","block_4_2",model,data,hd);
	inferx_convolution(32,192,1,1,1,1,0,0,1,1,1,false,false,"block_4_2_data","conv4_3/expand_data","conv4_3/expand",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_3/expand_data","conv4_3/expand/bn_data","conv4_3/expand/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_3/expand/bn_data","conv4_3/expand/bn_data","conv4_3/expand/scale",model,data,hd);
	inferx_relu("conv4_3/expand/bn_data","conv4_3/expand/bn_data","relu4_3/expand",model,data,hd);
	inferx_convolution(192,192,3,3,1,1,1,1,192,1,1,false,false,"conv4_3/expand/bn_data","conv4_3/dwise_data","conv4_3/dwise",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_3/dwise_data","conv4_3/dwise/bn_data","conv4_3/dwise/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_3/dwise/bn_data","conv4_3/dwise/bn_data","conv4_3/dwise/scale",model,data,hd);
	inferx_relu("conv4_3/dwise/bn_data","conv4_3/dwise/bn_data","relu4_3/dwise",model,data,hd);
	inferx_convolution(192,64,1,1,1,1,0,0,1,1,1,false,false,"conv4_3/dwise/bn_data","conv4_3/linear_data","conv4_3/linear",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_3/linear_data","conv4_3/linear/bn_data","conv4_3/linear/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_3/linear/bn_data","conv4_3/linear/bn_data","conv4_3/linear/scale",model,data,hd);
	inferx_convolution(64,384,1,1,1,1,0,0,1,1,1,false,false,"conv4_3/linear/bn_data","conv4_4/expand_data","conv4_4/expand",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_4/expand_data","conv4_4/expand/bn_data","conv4_4/expand/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_4/expand/bn_data","conv4_4/expand/bn_data","conv4_4/expand/scale",model,data,hd);
	inferx_relu("conv4_4/expand/bn_data","conv4_4/expand/bn_data","relu4_4/expand",model,data,hd);
	inferx_convolution(384,384,3,3,1,1,1,1,384,1,1,false,false,"conv4_4/expand/bn_data","conv4_4/dwise_data","conv4_4/dwise",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_4/dwise_data","conv4_4/dwise/bn_data","conv4_4/dwise/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_4/dwise/bn_data","conv4_4/dwise/bn_data","conv4_4/dwise/scale",model,data,hd);
	inferx_relu("conv4_4/dwise/bn_data","conv4_4/dwise/bn_data","relu4_4/dwise",model,data,hd);
	inferx_convolution(384,64,1,1,1,1,0,0,1,1,1,false,false,"conv4_4/dwise/bn_data","conv4_4/linear_data","conv4_4/linear",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_4/linear_data","conv4_4/linear/bn_data","conv4_4/linear/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_4/linear/bn_data","conv4_4/linear/bn_data","conv4_4/linear/scale",model,data,hd);
	bottom_vector[0] = "conv4_3/linear/bn_data";	bottom_vector[1] = "conv4_4/linear/bn_data";
	coeffs[0]=1.000000; coeffs[1]=1.000000; 
	inferx_eltwise(2,coeffs,SUM,true,2,bottom_vector,"block_4_4_data","block_4_4",model,data,hd);
	inferx_convolution(64,384,1,1,1,1,0,0,1,1,1,false,false,"block_4_4_data","conv4_5/expand_data","conv4_5/expand",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_5/expand_data","conv4_5/expand/bn_data","conv4_5/expand/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_5/expand/bn_data","conv4_5/expand/bn_data","conv4_5/expand/scale",model,data,hd);
	inferx_relu("conv4_5/expand/bn_data","conv4_5/expand/bn_data","relu4_5/expand",model,data,hd);
	inferx_convolution(384,384,3,3,1,1,1,1,384,1,1,false,false,"conv4_5/expand/bn_data","conv4_5/dwise_data","conv4_5/dwise",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_5/dwise_data","conv4_5/dwise/bn_data","conv4_5/dwise/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_5/dwise/bn_data","conv4_5/dwise/bn_data","conv4_5/dwise/scale",model,data,hd);
	inferx_relu("conv4_5/dwise/bn_data","conv4_5/dwise/bn_data","relu4_5/dwise",model,data,hd);
	inferx_convolution(384,64,1,1,1,1,0,0,1,1,1,false,false,"conv4_5/dwise/bn_data","conv4_5/linear_data","conv4_5/linear",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_5/linear_data","conv4_5/linear/bn_data","conv4_5/linear/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_5/linear/bn_data","conv4_5/linear/bn_data","conv4_5/linear/scale",model,data,hd);
	bottom_vector[0] = "block_4_4_data";	bottom_vector[1] = "conv4_5/linear/bn_data";
	coeffs[0]=1.000000; coeffs[1]=1.000000; 
	inferx_eltwise(2,coeffs,SUM,true,2,bottom_vector,"block_4_5_data","block_4_5",model,data,hd);
	inferx_convolution(64,384,1,1,1,1,0,0,1,1,1,false,false,"block_4_5_data","conv4_6/expand_data","conv4_6/expand",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_6/expand_data","conv4_6/expand/bn_data","conv4_6/expand/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_6/expand/bn_data","conv4_6/expand/bn_data","conv4_6/expand/scale",model,data,hd);
	inferx_relu("conv4_6/expand/bn_data","conv4_6/expand/bn_data","relu4_6/expand",model,data,hd);
	inferx_convolution(384,384,3,3,1,1,1,1,384,1,1,false,false,"conv4_6/expand/bn_data","conv4_6/dwise_data","conv4_6/dwise",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_6/dwise_data","conv4_6/dwise/bn_data","conv4_6/dwise/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_6/dwise/bn_data","conv4_6/dwise/bn_data","conv4_6/dwise/scale",model,data,hd);
	inferx_relu("conv4_6/dwise/bn_data","conv4_6/dwise/bn_data","relu4_6/dwise",model,data,hd);
	inferx_convolution(384,64,1,1,1,1,0,0,1,1,1,false,false,"conv4_6/dwise/bn_data","conv4_6/linear_data","conv4_6/linear",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_6/linear_data","conv4_6/linear/bn_data","conv4_6/linear/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_6/linear/bn_data","conv4_6/linear/bn_data","conv4_6/linear/scale",model,data,hd);
	bottom_vector[0] = "block_4_5_data";	bottom_vector[1] = "conv4_6/linear/bn_data";
	coeffs[0]=1.000000; coeffs[1]=1.000000; 
	inferx_eltwise(2,coeffs,SUM,true,2,bottom_vector,"block_4_6_data","block_4_6",model,data,hd);
	inferx_convolution(64,384,1,1,1,1,0,0,1,1,1,false,false,"block_4_6_data","conv4_7/expand_data","conv4_7/expand",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_7/expand_data","conv4_7/expand/bn_data","conv4_7/expand/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_7/expand/bn_data","conv4_7/expand/bn_data","conv4_7/expand/scale",model,data,hd);
	inferx_relu("conv4_7/expand/bn_data","conv4_7/expand/bn_data","relu4_7/expand",model,data,hd);
	inferx_convolution(384,384,3,3,2,2,1,1,384,1,1,false,false,"conv4_7/expand/bn_data","conv4_7/dwise_data","conv4_7/dwise",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_7/dwise_data","conv4_7/dwise/bn_data","conv4_7/dwise/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_7/dwise/bn_data","conv4_7/dwise/bn_data","conv4_7/dwise/scale",model,data,hd);
	inferx_relu("conv4_7/dwise/bn_data","conv4_7/dwise/bn_data","relu4_7/dwise",model,data,hd);
	inferx_convolution(384,96,1,1,1,1,0,0,1,1,1,false,false,"conv4_7/dwise/bn_data","conv4_7/linear_data","conv4_7/linear",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv4_7/linear_data","conv4_7/linear/bn_data","conv4_7/linear/bn",model,data,hd);
	inferx_scale(1,1,true,"conv4_7/linear/bn_data","conv4_7/linear/bn_data","conv4_7/linear/scale",model,data,hd);
	inferx_convolution(96,576,1,1,1,1,0,0,1,1,1,false,false,"conv4_7/linear/bn_data","conv5_1/expand_data","conv5_1/expand",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv5_1/expand_data","conv5_1/expand/bn_data","conv5_1/expand/bn",model,data,hd);
	inferx_scale(1,1,true,"conv5_1/expand/bn_data","conv5_1/expand/bn_data","conv5_1/expand/scale",model,data,hd);
	inferx_relu("conv5_1/expand/bn_data","conv5_1/expand/bn_data","relu5_1/expand",model,data,hd);
	inferx_convolution(576,576,3,3,1,1,1,1,576,1,1,false,false,"conv5_1/expand/bn_data","conv5_1/dwise_data","conv5_1/dwise",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv5_1/dwise_data","conv5_1/dwise/bn_data","conv5_1/dwise/bn",model,data,hd);
	inferx_scale(1,1,true,"conv5_1/dwise/bn_data","conv5_1/dwise/bn_data","conv5_1/dwise/scale",model,data,hd);
	inferx_relu("conv5_1/dwise/bn_data","conv5_1/dwise/bn_data","relu5_1/dwise",model,data,hd);
	inferx_convolution(576,96,1,1,1,1,0,0,1,1,1,false,false,"conv5_1/dwise/bn_data","conv5_1/linear_data","conv5_1/linear",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv5_1/linear_data","conv5_1/linear/bn_data","conv5_1/linear/bn",model,data,hd);
	inferx_scale(1,1,true,"conv5_1/linear/bn_data","conv5_1/linear/bn_data","conv5_1/linear/scale",model,data,hd);
	bottom_vector[0] = "conv4_7/linear/bn_data";	bottom_vector[1] = "conv5_1/linear/bn_data";
	coeffs[0]=1.000000; coeffs[1]=1.000000; 
	inferx_eltwise(2,coeffs,SUM,true,2,bottom_vector,"block_5_1_data","block_5_1",model,data,hd);
	inferx_convolution(96,576,1,1,1,1,0,0,1,1,1,false,false,"block_5_1_data","conv5_2/expand_data","conv5_2/expand",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv5_2/expand_data","conv5_2/expand/bn_data","conv5_2/expand/bn",model,data,hd);
	inferx_scale(1,1,true,"conv5_2/expand/bn_data","conv5_2/expand/bn_data","conv5_2/expand/scale",model,data,hd);
	inferx_relu("conv5_2/expand/bn_data","conv5_2/expand/bn_data","relu5_2/expand",model,data,hd);
	inferx_convolution(576,576,3,3,1,1,1,1,576,1,1,false,false,"conv5_2/expand/bn_data","conv5_2/dwise_data","conv5_2/dwise",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv5_2/dwise_data","conv5_2/dwise/bn_data","conv5_2/dwise/bn",model,data,hd);
	inferx_scale(1,1,true,"conv5_2/dwise/bn_data","conv5_2/dwise/bn_data","conv5_2/dwise/scale",model,data,hd);
	inferx_relu("conv5_2/dwise/bn_data","conv5_2/dwise/bn_data","relu5_2/dwise",model,data,hd);
	inferx_convolution(576,96,1,1,1,1,0,0,1,1,1,false,false,"conv5_2/dwise/bn_data","conv5_2/linear_data","conv5_2/linear",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv5_2/linear_data","conv5_2/linear/bn_data","conv5_2/linear/bn",model,data,hd);
	inferx_scale(1,1,true,"conv5_2/linear/bn_data","conv5_2/linear/bn_data","conv5_2/linear/scale",model,data,hd);
	bottom_vector[0] = "block_5_1_data";	bottom_vector[1] = "conv5_2/linear/bn_data";
	coeffs[0]=1.000000; coeffs[1]=1.000000; 
	inferx_eltwise(2,coeffs,SUM,true,2,bottom_vector,"block_5_2_data","block_5_2",model,data,hd);
	inferx_convolution(96,576,1,1,1,1,0,0,1,1,1,false,false,"block_5_2_data","conv5_3/expand_data","conv5_3/expand",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv5_3/expand_data","conv5_3/expand/bn_data","conv5_3/expand/bn",model,data,hd);
	inferx_scale(1,1,true,"conv5_3/expand/bn_data","conv5_3/expand/bn_data","conv5_3/expand/scale",model,data,hd);
	inferx_relu("conv5_3/expand/bn_data","conv5_3/expand/bn_data","relu5_3/expand",model,data,hd);
	inferx_convolution(576,576,3,3,2,2,1,1,576,1,1,false,false,"conv5_3/expand/bn_data","conv5_3/dwise_data","conv5_3/dwise",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv5_3/dwise_data","conv5_3/dwise/bn_data","conv5_3/dwise/bn",model,data,hd);
	inferx_scale(1,1,true,"conv5_3/dwise/bn_data","conv5_3/dwise/bn_data","conv5_3/dwise/scale",model,data,hd);
	inferx_relu("conv5_3/dwise/bn_data","conv5_3/dwise/bn_data","relu5_3/dwise",model,data,hd);
	inferx_convolution(576,160,1,1,1,1,0,0,1,1,1,false,false,"conv5_3/dwise/bn_data","conv5_3/linear_data","conv5_3/linear",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv5_3/linear_data","conv5_3/linear/bn_data","conv5_3/linear/bn",model,data,hd);
	inferx_scale(1,1,true,"conv5_3/linear/bn_data","conv5_3/linear/bn_data","conv5_3/linear/scale",model,data,hd);
	inferx_convolution(160,960,1,1,1,1,0,0,1,1,1,false,false,"conv5_3/linear/bn_data","conv6_1/expand_data","conv6_1/expand",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv6_1/expand_data","conv6_1/expand/bn_data","conv6_1/expand/bn",model,data,hd);
	inferx_scale(1,1,true,"conv6_1/expand/bn_data","conv6_1/expand/bn_data","conv6_1/expand/scale",model,data,hd);
	inferx_relu("conv6_1/expand/bn_data","conv6_1/expand/bn_data","relu6_1/expand",model,data,hd);
	inferx_convolution(960,960,3,3,1,1,1,1,960,1,1,false,false,"conv6_1/expand/bn_data","conv6_1/dwise_data","conv6_1/dwise",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv6_1/dwise_data","conv6_1/dwise/bn_data","conv6_1/dwise/bn",model,data,hd);
	inferx_scale(1,1,true,"conv6_1/dwise/bn_data","conv6_1/dwise/bn_data","conv6_1/dwise/scale",model,data,hd);
	inferx_relu("conv6_1/dwise/bn_data","conv6_1/dwise/bn_data","relu6_1/dwise",model,data,hd);
	inferx_convolution(960,160,1,1,1,1,0,0,1,1,1,false,false,"conv6_1/dwise/bn_data","conv6_1/linear_data","conv6_1/linear",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv6_1/linear_data","conv6_1/linear/bn_data","conv6_1/linear/bn",model,data,hd);
	inferx_scale(1,1,true,"conv6_1/linear/bn_data","conv6_1/linear/bn_data","conv6_1/linear/scale",model,data,hd);
	bottom_vector[0] = "conv5_3/linear/bn_data";	bottom_vector[1] = "conv6_1/linear/bn_data";
	coeffs[0]=1.000000; coeffs[1]=1.000000; 
	inferx_eltwise(2,coeffs,SUM,true,2,bottom_vector,"block_6_1_data","block_6_1",model,data,hd);
	inferx_convolution(160,960,1,1,1,1,0,0,1,1,1,false,false,"block_6_1_data","conv6_2/expand_data","conv6_2/expand",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv6_2/expand_data","conv6_2/expand/bn_data","conv6_2/expand/bn",model,data,hd);
	inferx_scale(1,1,true,"conv6_2/expand/bn_data","conv6_2/expand/bn_data","conv6_2/expand/scale",model,data,hd);
	inferx_relu("conv6_2/expand/bn_data","conv6_2/expand/bn_data","relu6_2/expand",model,data,hd);
	inferx_convolution(960,960,3,3,1,1,1,1,960,1,1,false,false,"conv6_2/expand/bn_data","conv6_2/dwise_data","conv6_2/dwise",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv6_2/dwise_data","conv6_2/dwise/bn_data","conv6_2/dwise/bn",model,data,hd);
	inferx_scale(1,1,true,"conv6_2/dwise/bn_data","conv6_2/dwise/bn_data","conv6_2/dwise/scale",model,data,hd);
	inferx_relu("conv6_2/dwise/bn_data","conv6_2/dwise/bn_data","relu6_2/dwise",model,data,hd);
	inferx_convolution(960,160,1,1,1,1,0,0,1,1,1,false,false,"conv6_2/dwise/bn_data","conv6_2/linear_data","conv6_2/linear",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv6_2/linear_data","conv6_2/linear/bn_data","conv6_2/linear/bn",model,data,hd);
	inferx_scale(1,1,true,"conv6_2/linear/bn_data","conv6_2/linear/bn_data","conv6_2/linear/scale",model,data,hd);
	bottom_vector[0] = "block_6_1_data";	bottom_vector[1] = "conv6_2/linear/bn_data";
	coeffs[0]=1.000000; coeffs[1]=1.000000; 
	inferx_eltwise(2,coeffs,SUM,true,2,bottom_vector,"block_6_2_data","block_6_2",model,data,hd);
	inferx_convolution(160,960,1,1,1,1,0,0,1,1,1,false,false,"block_6_2_data","conv6_3/expand_data","conv6_3/expand",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv6_3/expand_data","conv6_3/expand/bn_data","conv6_3/expand/bn",model,data,hd);
	inferx_scale(1,1,true,"conv6_3/expand/bn_data","conv6_3/expand/bn_data","conv6_3/expand/scale",model,data,hd);
	inferx_relu("conv6_3/expand/bn_data","conv6_3/expand/bn_data","relu6_3/expand",model,data,hd);
	inferx_convolution(960,960,3,3,1,1,1,1,960,1,1,false,false,"conv6_3/expand/bn_data","conv6_3/dwise_data","conv6_3/dwise",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv6_3/dwise_data","conv6_3/dwise/bn_data","conv6_3/dwise/bn",model,data,hd);
	inferx_scale(1,1,true,"conv6_3/dwise/bn_data","conv6_3/dwise/bn_data","conv6_3/dwise/scale",model,data,hd);
	inferx_relu("conv6_3/dwise/bn_data","conv6_3/dwise/bn_data","relu6_3/dwise",model,data,hd);
	inferx_convolution(960,320,1,1,1,1,0,0,1,1,1,false,false,"conv6_3/dwise/bn_data","conv6_3/linear_data","conv6_3/linear",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv6_3/linear_data","conv6_3/linear/bn_data","conv6_3/linear/bn",model,data,hd);
	inferx_scale(1,1,true,"conv6_3/linear/bn_data","conv6_3/linear/bn_data","conv6_3/linear/scale",model,data,hd);
	inferx_convolution(320,1280,1,1,1,1,0,0,1,1,1,false,false,"conv6_3/linear/bn_data","conv6_4_data","conv6_4",model,data, 0,hd);
	inferx_batchnorm(0.999,1e-5,true,"conv6_4_data","conv6_4/bn_data","conv6_4/bn",model,data,hd);
	inferx_scale(1,1,true,"conv6_4/bn_data","conv6_4/bn_data","conv6_4/scale",model,data,hd);
	inferx_relu("conv6_4/bn_data","conv6_4/bn_data","relu6_4",model,data,hd);
	inferx_global_pooling(AVE,"conv6_4/bn_data","pool6_data","pool6",model,data,hd);
	inferx_convolution(1280,1000,1,1,1,1,0,0,1,1,1,true,false,"pool6_data","fc7_data","fc7",model,data, 0,hd);
	inferx_softmax(1,"fc7_data","prob_data","prob",model,data,hd);

	

	if (hd->data_has_init == true)
	{
		inferx_sort_data("prob_data", data, hd);
		inferx_print_data("prob_data", data, hd);

		inferx_save_data("./", "prob_data", data, hd);
		//conv2_1/expand_data
		//conv2_1/expand/bn_data
		//conv2_1/dwise_data 
		//conv2_1/dwise/bn_data
		//conv2_1/linear_data

	}

	    



	
	if(pout)
	  *pout = inferx_get_data("prob_data",data,hd);
	inferx_finalize("MOBILENETV2",hd);

	return;
}
