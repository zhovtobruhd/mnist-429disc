/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Sun Feb  7 14:41:57 2021
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */


#include "network.h"

#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "layers.h"



#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#define AI_TOOLS_VERSION_MAJOR 5
#define AI_TOOLS_VERSION_MINOR 2
#define AI_TOOLS_VERSION_MICRO 0


#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#define AI_TOOLS_API_VERSION_MAJOR 1
#define AI_TOOLS_API_VERSION_MINOR 3
#define AI_TOOLS_API_VERSION_MICRO 0

#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network
 
#undef AI_NETWORK_MODEL_SIGNATURE
#define AI_NETWORK_MODEL_SIGNATURE     "240af15d92083752c3bbf84e13236f17"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     "(rev-5.2.0)"
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Sun Feb  7 14:41:57 2021"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_N_BATCHES
#define AI_NETWORK_N_BATCHES         (1)

/**  Forward network declaration section  *************************************/
AI_STATIC ai_network AI_NET_OBJ_INSTANCE;


/**  Forward network array declarations  **************************************/
AI_STATIC ai_array conv2d_1_scratch0_array;   /* Array #0 */
AI_STATIC ai_array conv2d_scratch0_array;   /* Array #1 */
AI_STATIC ai_array dense_bias_array;   /* Array #2 */
AI_STATIC ai_array dense_weights_array;   /* Array #3 */
AI_STATIC ai_array conv2d_1_bias_array;   /* Array #4 */
AI_STATIC ai_array conv2d_1_weights_array;   /* Array #5 */
AI_STATIC ai_array conv2d_bias_array;   /* Array #6 */
AI_STATIC ai_array conv2d_weights_array;   /* Array #7 */
AI_STATIC ai_array input_0_output_array;   /* Array #8 */
AI_STATIC ai_array conv2d_output_array;   /* Array #9 */
AI_STATIC ai_array conv2d_1_output_array;   /* Array #10 */
AI_STATIC ai_array dense_output_array;   /* Array #11 */
AI_STATIC ai_array dense_nl_output_array;   /* Array #12 */


/**  Forward network tensor declarations  *************************************/
AI_STATIC ai_tensor conv2d_1_scratch0;   /* Tensor #0 */
AI_STATIC ai_tensor conv2d_scratch0;   /* Tensor #1 */
AI_STATIC ai_tensor dense_bias;   /* Tensor #2 */
AI_STATIC ai_tensor dense_weights;   /* Tensor #3 */
AI_STATIC ai_tensor conv2d_1_bias;   /* Tensor #4 */
AI_STATIC ai_tensor conv2d_1_weights;   /* Tensor #5 */
AI_STATIC ai_tensor conv2d_bias;   /* Tensor #6 */
AI_STATIC ai_tensor conv2d_weights;   /* Tensor #7 */
AI_STATIC ai_tensor input_0_output;   /* Tensor #8 */
AI_STATIC ai_tensor conv2d_output;   /* Tensor #9 */
AI_STATIC ai_tensor conv2d_1_output;   /* Tensor #10 */
AI_STATIC ai_tensor conv2d_1_output0;   /* Tensor #11 */
AI_STATIC ai_tensor dense_output;   /* Tensor #12 */
AI_STATIC ai_tensor dense_nl_output;   /* Tensor #13 */


/**  Forward network tensor chain declarations  *******************************/
AI_STATIC_CONST ai_tensor_chain conv2d_chain;   /* Chain #0 */
AI_STATIC_CONST ai_tensor_chain conv2d_1_chain;   /* Chain #1 */
AI_STATIC_CONST ai_tensor_chain dense_chain;   /* Chain #2 */
AI_STATIC_CONST ai_tensor_chain dense_nl_chain;   /* Chain #3 */


/**  Forward network layer declarations  **************************************/
AI_STATIC ai_layer_conv2d_nl_pool conv2d_layer; /* Layer #0 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_1_layer; /* Layer #1 */
AI_STATIC ai_layer_dense dense_layer; /* Layer #2 */
AI_STATIC ai_layer_nl dense_nl_layer; /* Layer #3 */


/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1408, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1664, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  dense_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  dense_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16000, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 18432, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 32, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 288, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  input_0_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 784, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 5408, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1600, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  dense_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  dense_nl_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 10, AI_STATIC)

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_scratch0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 11, 2), AI_STRIDE_INIT(4, 4, 4, 256, 2816),
  1, &conv2d_1_scratch0_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_scratch0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 26, 2), AI_STRIDE_INIT(4, 4, 4, 128, 3328),
  1, &conv2d_scratch0_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  dense_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &dense_bias_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  dense_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1600, 10, 1, 1), AI_STRIDE_INIT(4, 4, 6400, 64000, 64000),
  1, &dense_weights_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &conv2d_1_bias_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 64), AI_STRIDE_INIT(4, 4, 128, 384, 1152),
  1, &conv2d_1_weights_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_bias_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 3, 32), AI_STRIDE_INIT(4, 4, 4, 12, 36),
  1, &conv2d_weights_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  input_0_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 28, 28), AI_STRIDE_INIT(4, 4, 4, 4, 112),
  1, &input_0_output_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 13, 13), AI_STRIDE_INIT(4, 4, 4, 128, 1664),
  1, &conv2d_output_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 5, 5), AI_STRIDE_INIT(4, 4, 4, 256, 1280),
  1, &conv2d_1_output_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_output0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 1600, 1, 1), AI_STRIDE_INIT(4, 4, 4, 6400, 6400),
  1, &conv2d_1_output_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  dense_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &dense_output_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  dense_nl_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 10, 1, 1), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &dense_nl_output_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_weights, &conv2d_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_layer, 0,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &conv2d_1_layer, AI_STATIC,
  .tensors = &conv2d_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_1_weights, &conv2d_1_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_1_layer, 2,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool,
  &AI_NET_OBJ_INSTANCE, &dense_layer, AI_STATIC,
  .tensors = &conv2d_1_chain, 
  .groups = 1, 
  .nl_func = nl_func_relu_array_f32, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_f32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_weights, &dense_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_layer, 6,
  DENSE_TYPE,
  dense, forward_dense,
  &AI_NET_OBJ_INSTANCE, &dense_nl_layer, AI_STATIC,
  .tensors = &dense_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_nl_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_nl_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_nl_layer, 6,
  NL_TYPE,
  nl, forward_sm,
  &AI_NET_OBJ_INSTANCE, &dense_nl_layer, AI_STATIC,
  .tensors = &dense_nl_chain, 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 139304, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 29824, 1,
                     NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &input_0_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &dense_nl_output),
  &conv2d_layer, 0, NULL)



AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_buffer* activation_buffer)
{
  AI_ASSERT(net_ctx &&  activation_buffer && activation_buffer->data)

  ai_ptr activations = AI_PTR(AI_PTR_ALIGN(activation_buffer->data, AI_NETWORK_ACTIVATIONS_ALIGNMENT));
  AI_ASSERT(activations)
  AI_UNUSED(net_ctx)

  {
    /* Updating activations (byte) offsets */
    conv2d_1_scratch0_array.data = AI_PTR(activations + 23168);
    conv2d_1_scratch0_array.data_start = AI_PTR(activations + 23168);
    conv2d_scratch0_array.data = AI_PTR(activations + 23168);
    conv2d_scratch0_array.data_start = AI_PTR(activations + 23168);
    input_0_output_array.data = AI_PTR(NULL);
    input_0_output_array.data_start = AI_PTR(NULL);
    conv2d_output_array.data = AI_PTR(activations + 1536);
    conv2d_output_array.data_start = AI_PTR(activations + 1536);
    conv2d_1_output_array.data = AI_PTR(activations + 0);
    conv2d_1_output_array.data_start = AI_PTR(activations + 0);
    dense_output_array.data = AI_PTR(activations + 6400);
    dense_output_array.data_start = AI_PTR(activations + 6400);
    dense_nl_output_array.data = AI_PTR(NULL);
    dense_nl_output_array.data_start = AI_PTR(NULL);
    
  }
  return true;
}



AI_DECLARE_STATIC
ai_bool network_configure_weights(
  ai_network* net_ctx, const ai_buffer* weights_buffer)
{
  AI_ASSERT(net_ctx &&  weights_buffer && weights_buffer->data)

  ai_ptr weights = AI_PTR(weights_buffer->data);
  AI_ASSERT(weights)
  AI_UNUSED(net_ctx)

  {
    /* Updating weights (byte) offsets */
    
    dense_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_bias_array.data = AI_PTR(weights + 139264);
    dense_bias_array.data_start = AI_PTR(weights + 139264);
    dense_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_weights_array.data = AI_PTR(weights + 75264);
    dense_weights_array.data_start = AI_PTR(weights + 75264);
    conv2d_1_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_bias_array.data = AI_PTR(weights + 75008);
    conv2d_1_bias_array.data_start = AI_PTR(weights + 75008);
    conv2d_1_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_weights_array.data = AI_PTR(weights + 1280);
    conv2d_1_weights_array.data_start = AI_PTR(weights + 1280);
    conv2d_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_bias_array.data = AI_PTR(weights + 1152);
    conv2d_bias_array.data_start = AI_PTR(weights + 1152);
    conv2d_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_weights_array.data = AI_PTR(weights + 0);
    conv2d_weights_array.data_start = AI_PTR(weights + 0);
  }

  return true;
}


/**  PUBLIC APIs SECTION  *****************************************************/

AI_API_ENTRY
ai_bool ai_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if ( report && net_ctx )
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = {AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR,
                            AI_TOOLS_API_VERSION_MICRO, 0x0},

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 2498614,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .activations       = AI_STRUCT_INIT,
      .params            = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if ( !ai_platform_api_get_network_report(network, &r) ) return false;

    *report = r;
    return true;
  }

  return false;
}

AI_API_ENTRY
ai_error ai_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if ( !net_ctx ) return false;

  ai_bool ok = true;
  ok &= network_configure_weights(net_ctx, &params->params);
  ok &= network_configure_activations(net_ctx, &params->activations);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}




#undef AI_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

