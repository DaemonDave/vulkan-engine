extern struct VkEngine vk;


struct VoxelRendererUniform {
	mat4 invViewProj; // matches cam.invViewProj
	vec3 camPos;      // matches cam.camPos
	float _pad0;      // matches cam._pad0
	mat4 invModel;    // matches model.invModel
};

struct VoxelRendererDatasetSSBO {
	uint32_t root;
	uint32_t leaf_count;
	uint32_t b;
	uint32_t enabledMask;
	uint32_t xs[16];
	uint32_t ys[16];
	uint32_t zs[16];
	uint32_t vals[16];
};

struct VoxelRendererCameraUBO {
	mat4 invViewProj;
	vec3 camPos;
	float _pad0;
};

struct VoxelRendererModelUBO {
	mat4 invModel;
};

// --- Example CPU voxel "tree dataset" you fill on the CPU ---
// Replace this with your real CPU-side voxel/tree data representation.
struct VoxelTreeCPU {
	uint32_t root;
	uint32_t leaf_count;
	uint32_t b;
	uint32_t enabledMask;

	// Typically these come from your traversal / brick / leaf builder.
	uint32_t xs[16];
	uint32_t ys[16];
	uint32_t zs[16];
	uint32_t vals[16];
};

struct VoxelRenderer {
	VkPipelineLayout pipeline_layout;
	VkPipeline       pipeline;

	// Fullscreen triangle (your shader uses gl_VertexIndex, so no vertex buffer is required)
	// Keep these only if your engine still wants a buffer abstraction.
	VkBuffer      vertex_buffer;
	VmaAllocation vertex_alloc;
	uint32_t      vertex_count;

	// Descriptor layout for:
	// set=0,binding0 CameraUBO (uniform)
	// set=0,binding1 DatasetSSBO (std430 storage buffer)
	// set=0,binding2 ModelUBO (uniform)
	VkDescriptorSetLayout scene_layout;

	// Descriptor set with bindings above
	VkDescriptorSet scene_descriptor;

	// Camera + Model uniforms (set=0 binding0 and binding2)
	VkBuffer      uniform_buffer;
	VmaAllocation uniform_alloc;

	// Dataset SSBO (set=0 binding1)
	VkBuffer      dataset_buffer;
	VmaAllocation dataset_alloc;

	// If you render into a target image via a render pass:
	VkRenderPass  renderpass;
	VkFramebuffer *framebuffers;
};

// assuming you have something like this global state object already:
static struct {
	// ...
	VoxelRenderer    gfx_voxel;
	GlobalTree       * globalTree; // or use your existing global if it's global-scope
	bool              pause;
	uint32_t          step;
	bool              cast;

	float              dist;
	float              grab_mass;

	// grabbed from mouse the vertex
	uint32_t          grab;		// stored as packedIndex
	
	// aim at the wider camera level
	Freecam * freecam;
	// (optional toggles)
	bool              voxel;  // enable disable
	bool              shadow;  // enable shadow generation
	bool              wireframe;	// enable wireframe
		
} vb; // the voxel buffer



void voxel_renderer_destroy(VoxelRenderer *handle)
{
    struct VoxelRenderer *restrict this = handle_deref(&alloc, *handle);

    // Buffers / allocations
    if (this->dataset_buffer != VK_NULL_HANDLE) {
        vmaDestroyBuffer(vk.vma, this->dataset_buffer, this->dataset_alloc);
    }

    if (this->uniform_buffer != VK_NULL_HANDLE) {
        vmaDestroyBuffer(vk.vma, this->uniform_buffer, this->uniform_alloc);
    }

    // Pipeline / layout
    if (this->pipeline != VK_NULL_HANDLE) {
        vkDestroyPipeline(vk.dev, this->pipeline, NULL);
    }
    if (this->pipeline_layout != VK_NULL_HANDLE) {
        vkDestroyPipelineLayout(vk.dev, this->pipeline_layout, NULL);
    }

    // Descriptor set layout
    if (this->scene_layout != VK_NULL_HANDLE) {
        vkDestroyDescriptorSetLayout(vk.dev, this->scene_layout, NULL);
    }

    // Renderpass / framebuffers
    if (this->framebuffers) {
        // We don't have vk.framebuffers_num on this struct; use your engine’s count.
        // If you have something like this->framebuffers_num, use it.
        for (size_t i = 0; i < vk.framebuffers_num; i++) {
            if (this->framebuffers[i] != VK_NULL_HANDLE) {
                vkDestroyFramebuffer(vk.dev, this->framebuffers[i], NULL);
            }
        }
        mem_free(this->framebuffers);
    }

    if (this->renderpass != VK_NULL_HANDLE) {
        vkDestroyRenderPass(vk.dev, this->renderpass, NULL);
    }

    // Vertex buffer (only if you created/kept it)
    if (this->vertex_buffer != VK_NULL_HANDLE) {
        vmaDestroyBuffer(vk.vma, this->vertex_buffer, this->vertex_alloc);
    }

    handle_free(&alloc, handle);
}


struct VoxelRendererUniform {
	mat4 invViewProj; // matches cam.invViewProj
	vec3 camPos;      // matches cam.camPos
	float _pad0;      // matches cam._pad0
	mat4 invModel;    // matches model.invModel
};

struct VoxelRendererDatasetSSBO {
	uint32_t root;
	uint32_t leaf_count;
	uint32_t b;
	uint32_t enabledMask;
	uint32_t xs[16];
	uint32_t ys[16];
	uint32_t zs[16];
	uint32_t vals[16];
};

struct VoxelRendererCameraUBO {
	mat4 invViewProj;
	vec3 camPos;
	float _pad0;
};

struct VoxelRendererModelUBO {
	mat4 invModel;
};

// --- Example CPU voxel "tree dataset" you fill on the CPU ---
// Replace this with your real CPU-side voxel/tree data representation.
struct VoxelTreeCPU {
	uint32_t root;
	uint32_t leaf_count;
	uint32_t b;
	uint32_t enabledMask;

	// Typically these come from your traversal / brick / leaf builder.
	uint32_t xs[16];
	uint32_t ys[16];
	uint32_t zs[16];
	uint32_t vals[16];
};

struct VoxelRenderer {
	VkPipelineLayout pipeline_layout;
	VkPipeline       pipeline;

	// Fullscreen triangle (your shader uses gl_VertexIndex, so no vertex buffer is required)
	// Keep these only if your engine still wants a buffer abstraction.
	VkBuffer      vertex_buffer;
	VmaAllocation vertex_alloc;
	uint32_t      vertex_count;

	// Descriptor layout for:
	// set=0,binding0 CameraUBO (uniform)
	// set=0,binding1 DatasetSSBO (std430 storage buffer)
	// set=0,binding2 ModelUBO (uniform)
	VkDescriptorSetLayout scene_layout;

	// Descriptor set with bindings above
	VkDescriptorSet scene_descriptor;

	// Camera + Model uniforms (set=0 binding0 and binding2)
	VkBuffer      uniform_buffer;
	VmaAllocation uniform_alloc;

	// Dataset SSBO (set=0 binding1)
	VkBuffer      dataset_buffer;
	VmaAllocation dataset_alloc;

	// If you render into a target image via a render pass:
	VkRenderPass  renderpass;
	VkFramebuffer *framebuffers;
};

// --- Your handle_deref pattern (assumed from your softbody sample) ---
struct VoxelRenderer *voxel_renderer_deref(void *alloc, struct VoxelRenderer *handle);

// Provide alloc in your codebase; keeping name consistent with your snippet.
extern void *alloc;

// This is the function you asked for: update GPU SSBO from CPU voxel-tree data,
// mirroring the "vertex update + vmaFlushAllocation" pattern in your softbody code.
void voxel_dataset_update(
		struct VoxelRenderer *restrict handle,
		const struct VoxelTreeCPU *restrict tree_data)
{
	struct VoxelRenderer *restrict this = voxel_renderer_deref(alloc, handle);

	// Single SSBO struct upload.
	// If your SSBO is bigger than one struct, change bytes and copy region accordingly.
	struct VoxelRendererDatasetSSBO dataset;

	dataset.root        = tree_data->root;
	dataset.leaf_count = tree_data->leaf_count;
	dataset.b           = tree_data->b;
	dataset.enabledMask= tree_data->enabledMask;

	memcpy(dataset.xs,   tree_data->xs,   sizeof(dataset.xs));
	memcpy(dataset.ys,   tree_data->ys,   sizeof(dataset.ys));
	memcpy(dataset.zs,   tree_data->zs,   sizeof(dataset.zs));
	memcpy(dataset.vals, tree_data->vals, sizeof(dataset.vals));

	size_t bytes = sizeof(struct VoxelRendererDatasetSSBO);

	// Copy from CPU -> mapped buffer memory
	// If `this->dataset_buffer` is persistently mapped, you can memcpy into mapped pointer directly.
	// If not, you should use vmaMapMemory/vmaUnmapMemory around this block.
	//
	// Here, we follow your softbody style assumption: SSBO is host-visible and can be flushed.
	memcpy(this->frame[0].vertex_mapping, &dataset, bytes);

	// Flush only the written byte range.
	// Note: in your softbody sample you call vmaFlushAllocation(vk.vma,...)
	vmaFlushAllocation(vk.vma, this->dataset_alloc, 0, bytes);
}

void voxel_geometry_prepare(
    VoxelRenderer handle,
    // If you have a GPU-ready blob to upload, pass it in.
    // Here we assume you already have CPU-side dataset data.
    const struct VoxelRendererDatasetSSBO *restrict dataset,
    size_t dataset_count // optional; if your SSBO is exactly one struct, you can ignore this
){
    struct VoxelRenderer *restrict this = handle_deref(&alloc, handle);

    // ---- Dataset SSBO ----
    // This renderer’s dataset is a single packed struct (as per your Vk shader layout):
    //   set=0,binding=1 => DatasetSSBO (std430) readonly
    // So we allocate exactly sizeof(VoxelRendererDatasetSSBO) bytes.
    VkDeviceSize ssboSize = sizeof(struct VoxelRendererDatasetSSBO);

    VkBufferCreateInfo buffer_info = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = ssboSize,
        .usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
    };

    VmaAllocationCreateInfo alloc_info = {
        .usage = VMA_MEMORY_USAGE_AUTO,
        .flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT |
                 VMA_ALLOCATION_CREATE_HOST_ACCESS_ALLOW_TRANSFER_INSTEAD_BIT
    };

    // If you might call this multiple times, destroy/recreate or update-in-place.
    // Here we (re)create once if the buffer doesn't exist yet.
    if (this->dataset_buffer != VK_NULL_HANDLE) {
        // If you support update, you can reuse allocation:
        // vmaMapMemory(vk.vma, this->dataset_alloc, &this->dataset_mapping);
        // memcpy(...); vmaUnmapMemory(...)
        // For simplicity, we reuse the allocation path by overwriting mapping below.
    } else {
        VkResult ret = vmaCreateBuffer(
            vk.vma,
            &buffer_info,
            &alloc_info,
            &this->dataset_buffer,
            &this->dataset_alloc,
            NULL
        );

        if (ret != VK_SUCCESS) engine_crash("vmaCreateBuffer dataset SSBO failed");
    }

    // Map + upload
    void *mapping = NULL;
    VkResult ret = vmaMapMemory(vk.vma, this->dataset_alloc, &mapping);
    if (ret != VK_SUCCESS || !mapping) engine_crash("vmaMapMemory dataset SSBO failed");

    if (dataset) {
        memcpy(mapping, dataset, sizeof(struct VoxelRendererDatasetSSBO));
    } else {
        struct VoxelRendererDatasetSSBO zero = {0};
        memcpy(mapping, &zero, sizeof(zero));
    }

    vmaUnmapMemory(vk.vma, this->dataset_alloc);

    (void)dataset_count; // suppress unused warning if present
}

void voxel_renderer_draw_shadowmap(
    VoxelRenderer handle,
    struct Frame *frame)
{
    struct VoxelRenderer *restrict this = handle_deref(&alloc, handle);

    VkCommandBuffer cmd = frame->vk->cmd_buf;
    uint32_t f = frame->vk->id;

    VkClearValue clear_color[] = {
        { .depthStencil = { 1.0f, 0.0f } }
    };

    VkExtent2D extent = {
        .width  = SHADOW_RESOLUTION,
        .height = SHADOW_RESOLUTION,
    };

    VkRenderPassBeginInfo pass_info = {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        .renderPass  = this->renderpass, // <-- use your voxel shadow renderpass
        .framebuffer = this->framebuffers[ frame->vk->image_index ],
        .renderArea.offset = (VkOffset2D){ 0, 0 },
        .renderArea.extent = extent,
        .clearValueCount = (uint32_t)LENGTH(clear_color),
        .pClearValues = clear_color,
    };

    vkCmdBeginRenderPass(cmd, &pass_info, VK_SUBPASS_CONTENTS_INLINE);

    // Bind descriptors once (your voxel shader uses:
    //   set=0 binding0 CameraUBO (uniform)
    //   set=0 binding1 DatasetSSBO (std430 storage)
    //   set=0 binding2 ModelUBO (uniform)
    vkCmdBindDescriptorSets(
        cmd,
        VK_PIPELINE_BIND_POINT_GRAPHICS,
        this->pipeline_layout,
        0, 1,
        &this->scene_descriptor,
        0, NULL
    );

    vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, this->pipeline);

    // Your shader uses gl_VertexIndex for a fullscreen triangle,
    // so no vertex/index buffers needed.
    // If your pipeline expects 3 vertices:
    vkCmdDraw(cmd, 3, 1, 0, 0);

    vkCmdEndRenderPass(cmd);
}


static void vk_create_voxel_uniform_buffers(struct VoxelRenderer *this)
{
	// CameraUBO (binding 0)
	vk_create_buffer_vma(
		sizeof(struct VoxelRendererCameraUBO),
		VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
		VMA_MEMORY_USAGE_CPU_TO_GPU,
		&this->camera_ubo,
		&this->camera_ubo_alloc
	);

	// ModelUBO (binding 2)
	vk_create_buffer_vma(
		sizeof(struct VoxelRendererModelUBO),
		VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
		VMA_MEMORY_USAGE_CPU_TO_GPU,
		&this->model_ubo,
		&this->model_ubo_alloc
	);

	// Fill once (or call these every frame if camera/model changes)
	{
		struct VoxelRendererCameraUBO cam_ubo = {0};

		// Example: you should set these from your engine’s camera
		// cam_ubo.invViewProj = ...
		// cam_ubo.camPos = ...

		void *data;
		vmaMapMemory(vk.vma, this->camera_ubo_alloc, &data);
		memcpy(data, &cam_ubo, sizeof(cam_ubo));
		vmaUnmapMemory(vk.vma, this->camera_ubo_alloc);
	}

	{
		struct VoxelRendererModelUBO model_ubo = {0};

		// Example: you should set this from your model transform
		// model_ubo.invModel = ...

		void *data;
		vmaMapMemory(vk.vma, this->model_ubo_alloc, &data);
		memcpy(data, &model_ubo, sizeof(model_ubo));
		vmaUnmapMemory(vk.vma, this->model_ubo_alloc);
	}
}

static void voxel_vk_create(struct VoxelRenderer *this)
{
	VkResult ret;

	/* Pipeline */

	VkShaderModule vert_shader = vk_create_shader_module(RES_SHADER_VERT_VOXEL);
	VkShaderModule frag_shader = vk_create_shader_module(RES_SHADER_FRAG_VOXEL);

	// Fullscreen triangle / vertex shader uses gl_VertexIndex:
	VkPipelineShaderStageCreateInfo shader_stages[] = {
		{
			.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			.stage  = VK_SHADER_STAGE_VERTEX_BIT,
			.module = vert_shader,
			.pName  = "main",
			.pSpecializationInfo = NULL,
		},
		{
			.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			.stage  = VK_SHADER_STAGE_FRAGMENT_BIT,
			.module = frag_shader,
			.pName  = "main",
			.pSpecializationInfo = NULL,
		}
	};

	// No vertex buffers required for gl_VertexIndex
	VkPipelineVertexInputStateCreateInfo vertex_info = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
		.vertexBindingDescriptionCount    = 0,
		.pVertexBindingDescriptions       = NULL,
		.vertexAttributeDescriptionCount  = 0,
		.pVertexAttributeDescriptions     = NULL,
	};

	VkPipelineInputAssemblyStateCreateInfo input_assembly_info = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
		.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
		.primitiveRestartEnable = VK_FALSE
	};

	VkViewport viewport = {
		.x = 0.0f,
		.y = 0.0f,
		.width  = vk.swapchain_extent.width,
		.height = vk.swapchain_extent.height,
		.minDepth = 0.0f,
		.maxDepth = 1.0f,
	};

	VkRect2D scissor = {
		.offset = {0, 0},
		.extent = vk.swapchain_extent,
	};

	VkPipelineViewportStateCreateInfo viewport_info = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
		.viewportCount = 1,
		.pViewports = &viewport,
		.scissorCount = 1,
		.pScissors = &scissor,
	};

	VkDynamicState dynamic_state[] = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};

	VkPipelineDynamicStateCreateInfo dynamic_info = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
		.flags = 0,
		.dynamicStateCount = LENGTH(dynamic_state),
		.pDynamicStates    = dynamic_state
	};

	VkPipelineRasterizationStateCreateInfo rasterizer_info = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
		.rasterizerDiscardEnable = VK_FALSE,
		.polygonMode             = VK_POLYGON_MODE_FILL,
		.cullMode                = VK_CULL_MODE_NONE,
		.frontFace               = VK_FRONT_FACE_CLOCKWISE,
		.lineWidth = 1.0f,
	};

	VkPipelineMultisampleStateCreateInfo multisampling_info = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
		.sampleShadingEnable = VK_FALSE,
		.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
		.minSampleShading = 1.0f,
		.pSampleMask = NULL,
		.alphaToCoverageEnable = VK_FALSE,
		.alphaToOneEnable = VK_FALSE,
	};

	VkPipelineColorBlendAttachmentState blending_attachment_info = {
		.colorWriteMask =
			VK_COLOR_COMPONENT_R_BIT |
			VK_COLOR_COMPONENT_G_BIT |
			VK_COLOR_COMPONENT_B_BIT |
			VK_COLOR_COMPONENT_A_BIT,
		.blendEnable = VK_TRUE,
		.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
		.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
		.colorBlendOp = VK_BLEND_OP_ADD,
		.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
		.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
		.alphaBlendOp = VK_BLEND_OP_ADD,
	};

	VkPipelineColorBlendStateCreateInfo blending_info = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
		.logicOpEnable = VK_FALSE,
		.logicOp = VK_LOGIC_OP_COPY,
		.attachmentCount = 1,
		.pAttachments = &blending_attachment_info,
		.blendConstants[0] = 0.0f,
		.blendConstants[1] = 0.0f,
		.blendConstants[2] = 0.0f,
		.blendConstants[3] = 0.0f,
	};

	VkPipelineDepthStencilStateCreateInfo depth_stencil_info = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
		.depthTestEnable       = VK_TRUE,
		.depthWriteEnable      = VK_TRUE,
		.depthCompareOp        = VK_COMPARE_OP_LESS,
		.depthBoundsTestEnable = VK_FALSE,
		.minDepthBounds        = 0.0f,
		.maxDepthBounds        = 1.0f,
		.stencilTestEnable     = VK_FALSE,
	};

	// If your voxel shaders do NOT use push constants, set pushConstantRangeCount = 0.
	// Keep the same pattern as Softbody but with a voxel uniform struct if you actually use it as a push constant.
	//
	// Since your voxel design lists UBO/SSBO sets, most likely you want NO push constants:
	VkPushConstantRange push_constants[] = {
		{
			.stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
			.offset = 0,
			.size = 0, // set to sizeof(struct VoxelRendererUniform) only if your voxel shader expects push constants
		}
	};

	// ----- Pipeline layout (descriptor set layouts + optional push constants) -----
	VkPipelineLayoutCreateInfo pipeline_layout_info = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
		.setLayoutCount = 1,
		.pSetLayouts = &this->scene_layout,
		.pushConstantRangeCount = 0, // change to LENGTH(push_constants) if you really use push constants
		.pPushConstantRanges = NULL,
	};

	ret = vkCreatePipelineLayout(
		vk.dev,
		&pipeline_layout_info,
		NULL,
		&this->pipeline_layout
	);
	if (ret != VK_SUCCESS) engine_crash("vkCreatePipelineLayout failed");

	VkGraphicsPipelineCreateInfo pipeline_info = {
		.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
		.stageCount = 2,
		.pStages = shader_stages,
		.pVertexInputState   = &vertex_info,
		.pInputAssemblyState = &input_assembly_info,
		.pViewportState      = &viewport_info,
		.pRasterizationState = &rasterizer_info,
		.pMultisampleState   = &multisampling_info,
		.pDepthStencilState  = &depth_stencil_info,
		.pColorBlendState    = &blending_info,
		.pDynamicState       = &dynamic_info,
		.layout              = this->pipeline_layout,
		.renderPass          = vk.renderpass,
		.subpass             = 0,
		.basePipelineHandle  = VK_NULL_HANDLE,
		.basePipelineIndex   = -1,
	};

	ret = vkCreateGraphicsPipelines(
		vk.dev,
		VK_NULL_HANDLE,
		1,
		&pipeline_info,
		NULL,
		&this->pipeline
	);
	if (ret != VK_SUCCESS) engine_crash("vkCreateGraphicsPipelines failed");

	vkDestroyShaderModule(vk.dev, frag_shader, NULL);
	vkDestroyShaderModule(vk.dev, vert_shader, NULL);
}
static void vk_create_voxel_shadow_uniform_buffer(struct VoxelRenderer *this)
{
	// Shadow pass binding=0 is a uniform buffer.
	// Your voxel shadow shaders can either use VoxelRendererUniform directly
	// or separate CameraUBO/ModelUBO. Here we match VoxelRendererUniform.
	vk_create_buffer_vma(
		sizeof(struct VoxelRendererUniform),
		VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
		VMA_MEMORY_USAGE_CPU_TO_GPU,
		&this->uniform_buffer,
		&this->uniform_alloc
	);

	// Example light params (mirrors your softbody code pattern).
	struct VoxelRendererUniform ubo = {0};

	// Direction is largely static (edit to match your engine's light).
	vec3 light_dir = { 0.0f, 5.0f, 5.0f };
	glm_normalize(light_dir);

	// ---- Build light view + ortho proj ----
	// These dimensions are placeholders; keep them consistent with SHADOW_RESOLUTION / your culling.
	const float size = 5.0f;

	mat4 proj;
	glm_ortho(
		-size,  size,
		-size,  size,
		0.01f, 30.0f,
		proj
	);
	proj[1][1] *= -1.0f;

	// Use light_dir as the "eye" direction source like your softbody code did.
	// If your light shader expects a different convention, adjust these.
	mat4 view;
	glm_lookat(
		light_dir,
		(float[]){0.0f, 0.0f, 0.0f},
		(float[]){0.0f, 1.0f, 0.0f},
		view
	);

	// Optional offset like softbody code.
	vec3 offset = {0.0f, 0.0f, 3.0f};
	glm_translate(view, offset);

	// viewProj
	mat4 viewproj;
	glm_mul(proj, view, viewproj);

	// ---- Fill inverse matrices expected by your UBO ----
	// invViewProj = inverse(viewProj)
	glm_inverse(viewproj, ubo.invViewProj);

	// For shadow pass, model is typically identity (or whatever model transform you use).
	mat4 model = {0};
	glm_identity(model);
	glm_inverse(model, ubo.invModel);

	// camPos in your struct: use the light "eye"/position convention.
	// If your shader uses camPos for ray direction reconstruction, this must match that math.
	ubo.camPos = light_dir;

	// ---- Upload to GPU ----
	void *data;
	vmaMapMemory(vk.vma, this->uniform_alloc, &data);
	memcpy(data, &ubo, sizeof(ubo));
	vmaUnmapMemory(vk.vma, this->uniform_alloc);
}

static void
vk_create_voxel_renderer_uniform(struct VoxelRenderer *this)
{
    // Combined uniform buffer could be separate for CameraUBO + ModelUBO.
    // But your VkVoxelRenderer uses ONE uniform_buffer + one uniform_alloc,
    // and your descriptor expects set=0 binding0 = CameraUBO and binding2 = ModelUBO.
    //
    // Easiest: create ONE buffer big enough for both structs,
    // then create two VkDescriptorBufferInfo ranges into the same buffer.
    //
    // However your layout says binding0 is CameraUBO and binding2 is ModelUBO.
    // We'll pack them into one buffer:
    //   offset 0:   VoxelRendererCameraUBO
    //   offset A:   VoxelRendererModelUBO
    //
    // This requires Vulkan descriptor range offsets to be supported (they are).
    const VkDeviceSize camOff   = 0;
    const VkDeviceSize modelOff = (VkDeviceSize)((sizeof(struct VoxelRendererCameraUBO) + 15) & ~15);

    VkDeviceSize uboSize = modelOff + sizeof(struct VoxelRendererModelUBO);

    VkBufferCreateInfo buf = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = uboSize,
        .usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
    };

    VmaAllocationCreateInfo ainfo = {
        .usage = VMA_MEMORY_USAGE_CPU_TO_GPU, // you may prefer GPU_TO_CPU if you write from GPU
        .requiredFlags = 0,
        .preferredFlags = 0,
    };

    // Create uniform buffer + allocation
    if (vk.buffer_create_uniform(&this->uniform_buffer, &this->uniform_alloc, &buf, &ainfo) != 0) {
        // adapt to your engine return style; below is a fallback pattern if needed.
        // exit(1);
    }

    // Initialize with sane defaults (optional)
    struct VoxelRendererCameraUBO cam = {0};
    struct VoxelRendererModelUBO  mdl = {0};
    // Example defaults:
    // cam.invViewProj = mat4_identity();
    // cam.camPos = (vec3){0,0,0};
    // mdl.invModel = mat4_identity();

    // Upload initial contents
    void *mapped = NULL;
    vmaMapMemory(vk.allocator, this->uniform_alloc, &mapped);
    if (mapped) {
        memcpy((uint8_t*)mapped + camOff, &cam, sizeof(cam));
        memcpy((uint8_t*)mapped + modelOff, &mdl, sizeof(mdl));
        vmaUnmapMemory(vk.allocator, this->uniform_alloc);
    }
}

static void
vk_create_voxel_renderer_dataset_ssbo(struct VoxelRenderer *this, const struct VoxelRendererDatasetSSBO *initData)
{
    // Allocate SSBO for voxel dataset.
    // Your descriptor expects set=0,binding1 = DatasetSSBO (std430 storage buffer).
    VkDeviceSize ssboSize = sizeof(struct VoxelRendererDatasetSSBO);

    VkBufferCreateInfo buf = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = ssboSize,
        .usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
    };

    VmaAllocationCreateInfo ainfo = {
        .usage = VMA_MEMORY_USAGE_CPU_TO_GPU,
    };

    if (vk.buffer_create_ssbo(&this->dataset_buffer, &this->dataset_alloc, &buf, &ainfo) != 0) {
        // adapt to your engine
    }

    // Upload initial data if provided
    if (initData) {
        void *mapped = NULL;
        vmaMapMemory(vk.allocator, this->dataset_alloc, &mapped);
        if (mapped) {
            memcpy(mapped, initData, sizeof(*initData));
            vmaUnmapMemory(vk.allocator, this->dataset_alloc);
        }
    } else {
        // Zero-init
        struct VoxelRendererDatasetSSBO zero = {0};
        void *mapped = NULL;
        vmaMapMemory(vk.allocator, this->dataset_alloc, &mapped);
        if (mapped) {
            memcpy(mapped, &zero, sizeof(zero));
            vmaUnmapMemory(vk.allocator, this->dataset_alloc);
        }
    }
}

static VkShaderModule
vk_load_shader_module(const char *path)
{
    // You must adapt to your engine loader.
    // Placeholder:
    // return vk_create_shader_module_from_file(path);
    return (VkShaderModule)0;
}

static void
vk_create_voxel_renderer_pipeline(struct VoxelRenderer *this)
{
    // Create descriptor set layout:
    // set=0 binding0 CameraUBO (uniform)
    // set=0 binding1 DatasetSSBO (std430 storage buffer)
    // set=0 binding2 ModelUBO (uniform)
    //
    // Note: binding offsets for Camera vs Model are handled later in vkUpdateDescriptorSets.

    VkDescriptorSetLayoutBinding b0 = {
        .binding = 0,
        .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = 1,
        .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT,
        .pImmutableSamplers = NULL
    };

    VkDescriptorSetLayoutBinding b1 = {
        .binding = 1,
        .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
        .descriptorCount = 1,
        .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
        .pImmutableSamplers = NULL
    };

    VkDescriptorSetLayoutBinding b2 = {
        .binding = 2,
        .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = 1,
        .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT,
        .pImmutableSamplers = NULL
    };

    VkDescriptorSetLayoutBinding bindings[] = { b0, b1, b2 };

    VkDescriptorSetLayoutCreateInfo layoutInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = 3,
        .pBindings = bindings
    };

    if (vkCreateDescriptorSetLayout(vk.device, &layoutInfo, NULL, &this->scene_layout) != VK_SUCCESS) {
        // handle error
    }

    // Descriptor set allocation
    VkDescriptorSetAllocateInfo allocInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = vk.descriptor_pool,
        .descriptorSetCount = 1,
        .pSetLayouts = &this->scene_layout
    };

    if (vkAllocateDescriptorSets(vk.device, &allocInfo, &this->scene_descriptor) != VK_SUCCESS) {
        // handle error
    }

    // Create pipeline layout
    VkPipelineLayoutCreateInfo pl = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .setLayoutCount = 1,
        .pSetLayouts = &this->scene_layout,
    };

    if (vkCreatePipelineLayout(vk.device, &pl, NULL, &this->pipeline_layout) != VK_SUCCESS) {
        // handle error
    }

    // Update descriptor set bindings
    const VkDeviceSize camOff   = 0;
    const VkDeviceSize modelOff = (VkDeviceSize)((sizeof(struct VoxelRendererCameraUBO) + 15) & ~15);

    VkDescriptorBufferInfo camInfo = {
        .buffer = this->uniform_buffer,
        .offset = camOff,
        .range  = sizeof(struct VoxelRendererCameraUBO)
    };

    VkDescriptorBufferInfo modelInfo = {
        .buffer = this->uniform_buffer,
        .offset = modelOff,
        .range  = sizeof(struct VoxelRendererModelUBO)
    };

    VkDescriptorBufferInfo dsInfo = {
        .buffer = this->dataset_buffer,
        .offset = 0,
        .range  = sizeof(struct VoxelRendererDatasetSSBO)
    };

    VkWriteDescriptorSet writes[3] = {0};

    writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[0].dstSet = this->scene_descriptor;
    writes[0].dstBinding = 0;
    writes[0].dstArrayElement = 0;
    writes[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    writes[0].descriptorCount = 1;
    writes[0].pBufferInfo = &camInfo;

    writes[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[1].dstSet = this->scene_descriptor;
    writes[1].dstBinding = 1;
    writes[1].dstArrayElement = 0;
    writes[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    writes[1].descriptorCount = 1;
    writes[1].pBufferInfo = &dsInfo;

    writes[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[2].dstSet = this->scene_descriptor;
    writes[2].dstBinding = 2;
    writes[2].dstArrayElement = 0;
    writes[2].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    writes[2].descriptorCount = 1;
    writes[2].pBufferInfo = &modelInfo;

    vkUpdateDescriptorSets(vk.device, 3, writes, 0, NULL);

    // Shaders (adapt filenames to your build)
    // For shadows you likely have:
    //  - voxel shadow vertex:   .vert.shadow.glsl
    //  - voxel shadow fragment: .frag.shadow.glsl
    VkPipelineShaderStageCreateInfo stages[2] = {0};

    VkShaderModule vert = vk_load_shader_module("shaders/voxel.shadow.vert.spv");
    VkShaderModule frag = vk_load_shader_module("shaders/voxel.shadow.frag.spv");

    stages[0] = (VkPipelineShaderStageCreateInfo){
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage = VK_SHADER_STAGE_VERTEX_BIT,
        .module = vert,
        .pName = "main"
    };
    stages[1] = (VkPipelineShaderStageCreateInfo){
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
        .module = frag,
        .pName = "main"
    };

    // Fullscreen triangle: no vertex input bindings; use gl_VertexIndex.
    VkPipelineVertexInputStateCreateInfo vi = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .vertexBindingDescriptionCount = 0,
        .pVertexBindingDescriptions = NULL,
        .vertexAttributeDescriptionCount = 0,
        .pVertexAttributeDescriptions = NULL
    };

    VkPipelineInputAssemblyStateCreateInfo ia = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        .primitiveRestartEnable = VK_FALSE
    };

    VkViewport viewport = {0};
    viewport.x = 0;
    viewport.y = 0;
    viewport.width = (float)vk.swapchain_extent.width;
    viewport.height = (float)vk.swapchain_extent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor = {0};
    scissor.offset = (VkOffset2D){0,0};
    scissor.extent = vk.swapchain_extent;

    VkPipelineViewportStateCreateInfo vp = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .viewportCount = 1,
        .pViewports = &viewport,
        .scissorCount = 1,
        .pScissors = &scissor
    };

    VkPipelineRasterizationStateCreateInfo rs = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .depthClampEnable = VK_FALSE,
        .rasterizerDiscardEnable = VK_FALSE,
        .polygonMode = VK_POLYGON_MODE_FILL,
        .cullMode = VK_CULL_MODE_NONE,
        .frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE,
        .depthBiasEnable = VK_FALSE,
        .lineWidth = 1.0f
    };

    VkPipelineMultisampleStateCreateInfo ms = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT
    };

    VkPipelineColorBlendAttachmentState cbatt = {0};
    cbatt.colorWriteMask =
        VK_COLOR_COMPONENT_R_BIT |
        VK_COLOR_COMPONENT_G_BIT |
        VK_COLOR_COMPONENT_B_BIT |
        VK_COLOR_COMPONENT_A_BIT;

    // If your shadow pass writes to a single-channel texture, you may still just use blend disabled
    cbatt.blendEnable = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo cb = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .logicOpEnable = VK_FALSE,
        .attachmentCount = 1,
        .pAttachments = &cbatt
    };

    // Depth/stencil (usually disabled for fullscreen shadow)
    VkPipelineDepthStencilStateCreateInfo ds = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
        .depthTestEnable = VK_FALSE,
        .depthWriteEnable = VK_FALSE,
        .depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL,
        .stencilTestEnable = VK_FALSE
    };

    // Pipeline render pass + subpass
    // You have renderpass stored in this->renderpass; but we haven’t created it yet.
    // So create renderpass before calling this in your factory OR pass a renderpass parameter.
    //
    // In your earlier factory you call pipeline before renderpass, which would fail here.
    // Solution: either (1) create renderpass first, or (2) delay pipeline creation until after renderpass.
    //
    // We'll assume you will reorder calls to create renderpass first.
    // Otherwise: adapt to use vk_default_renderpass for now.

    extern VkRenderPass voxel_get_renderpass_default(void); // optional
    VkRenderPass rp = this->renderpass ? this->renderpass : voxel_get_renderpass_default();

    VkGraphicsPipelineCreateInfo gp = {
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .stageCount = 2,
        .pStages = stages,
        .pVertexInputState = &vi,
        .pInputAssemblyState = &ia,
        .pViewportState = &vp,
        .pRasterizationState = &rs,
        .pMultisampleState = &ms,
        .pDepthStencilState = &ds,
        .pColorBlendState = &cb,
        .layout = this->pipeline_layout,
        .renderPass = rp,
        .subpass = 0,
        .basePipelineHandle = VK_NULL_HANDLE
    };

    if (vkCreateGraphicsPipelines(vk.device, VK_NULL_HANDLE, 1, &gp, NULL, &this->pipeline) != VK_SUCCESS) {
        // handle error
    }

    // Cleanup shader modules if your engine wants it
    vkDestroyShaderModule(vk.device, vert, NULL);
    vkDestroyShaderModule(vk.device, frag, NULL);
}

static void
vk_create_voxel_renderer_renderpass(struct VoxelRenderer *this)
{
    // If your engine has a helper like:
    //   vk_create_shadow_renderpass(&this->renderpass, format)
    // use it.
    //
    // Otherwise you need to create a renderpass compatible with the shadow output.
    // Since you didn’t provide formats/attachments, I’ll implement a minimal
    // single color attachment renderpass (no depth).
    //
    // Replace vk.shadow_format with your actual format.
    VkFormat format = vk.shadow_format; // adapt

    VkAttachmentDescription att = {
        .format = format,
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
        .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
        .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
    };

    VkAttachmentReference aref = {
        .attachment = 0,
        .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
    };

    VkSubpassDescription sub = {
        .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
        .colorAttachmentCount = 1,
        .pColorAttachments = &aref
    };

    VkRenderPassCreateInfo rp = {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .attachmentCount = 1,
        .pAttachments = &att,
        .subpassCount = 1,
        .pSubpasses = &sub
    };

    vkCreateRenderPass(vk.device, &rp, NULL, &this->renderpass);

    // Framebuffers creation depends on your shadow image(s).
    // If you already allocate a shadow target image elsewhere, use it here.
    this->framebuffers = NULL; // adapt if you manage framebuffers elsewhere
}

static void
voxel_renderer_destroy_callback(void *user)
{
    struct VoxelRenderer *this = (struct VoxelRenderer*)user;
    if (!this) return;

    // Destroy pipeline & layout
    if (this->pipeline) vkDestroyPipeline(vk.device, this->pipeline, NULL);
    if (this->pipeline_layout) vkDestroyPipelineLayout(vk.device, this->pipeline_layout, NULL);

    // Destroy descriptors layout/pool allocations if needed
    if (this->scene_layout) vkDestroyDescriptorSetLayout(vk.device, this->scene_layout, NULL);

    // Destroy buffers via VMA
    if (this->uniform_buffer) vmaDestroyBuffer(vk.allocator, this->uniform_buffer, this->uniform_alloc);
    if (this->dataset_buffer) vmaDestroyBuffer(vk.allocator, this->dataset_buffer, this->dataset_alloc);

    // Destroy renderpass/framebuffers
    if (this->renderpass) vkDestroyRenderPass(vk.device, this->renderpass, NULL);
    // If framebuffers were allocated, destroy them too.
}

/* Final factory requested */
VoxelRenderer vk_create_voxel_renderer(void)
{
    VoxelRenderer handle = handle_alloc(&alloc);
    struct VoxelRenderer *restrict this = handle_deref(&alloc, handle);

    // (optional) sanity/info
    log_debug("VoxelRendererUniform size: %li", sizeof(struct VoxelRendererUniform));
    log_debug("VoxelRendererDatasetSSBO size: %li", sizeof(struct VoxelRendererDatasetSSBO));

    // Ensure renderpass is created BEFORE pipeline (pipeline depends on renderpass).
    vk_create_voxel_renderer_renderpass(this);

    vk_create_voxel_renderer_uniform(this);

    // If you have initial dataset values, pass them; otherwise NULL => zero init
    vk_create_voxel_renderer_dataset_ssbo(this, NULL);

    vk_create_voxel_renderer_pipeline(this);

    event_bind(EVENT_RENDERERS_DESTROY, voxel_renderer_destroy_callback, handle);

    return handle;
}


static void vk_create_voxel_shadow_sampler(struct VoxelRenderer *this)
{
	VkSamplerCreateInfo sampler_info = {
		.sType                   = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
		.magFilter               = SHADOW_FILTER,
		.minFilter               = SHADOW_FILTER,
		.addressModeU            = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
		.addressModeV            = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
		.addressModeW            = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
		.anisotropyEnable        = VK_TRUE,
		.maxAnisotropy           = vk.dev_properties.limits.maxSamplerAnisotropy,
		.borderColor             = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
		.unnormalizedCoordinates = VK_FALSE,
		.compareEnable           = VK_FALSE,
		.compareOp               = VK_COMPARE_OP_ALWAYS,
		.mipmapMode              = VK_SAMPLER_MIPMAP_MODE_LINEAR,
		.mipLodBias              = 0.0f,
		.minLod                  = 0.0f,
		.maxLod                  = 0.0f,
	};

	VkResult ret = vkCreateSampler(vk.dev, &sampler_info, NULL, &this->shadow_sampler);
	if (ret != VK_SUCCESS) engine_crash("vkCreateSampler failed");
}


static void vk_create_voxel_shadow_resources(struct VoxelRenderer *this)
{
	vk_create_image_vma(
		SHADOW_RESOLUTION,
		SHADOW_RESOLUTION,
		DEPTH_FORMAT,
		VK_IMAGE_TILING_OPTIMAL,
		VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
		VMA_MEMORY_USAGE_GPU_ONLY,
		&this->shadow_image,
		&this->shadow_alloc
	);

	VkImageViewCreateInfo create_info = {
		.sType    = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.image    = this->shadow_image,
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.format   = DEPTH_FORMAT,

		.components = {
			.r = VK_COMPONENT_SWIZZLE_R,
			.g = VK_COMPONENT_SWIZZLE_G,
			.b = VK_COMPONENT_SWIZZLE_B,
			.a = VK_COMPONENT_SWIZZLE_A,
		},

		.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT,
		.subresourceRange.baseMipLevel = 0,
		.subresourceRange.levelCount = 1,
		.subresourceRange.baseArrayLayer = 0,
		.subresourceRange.layerCount = 1,
	};

	VkResult ret = vkCreateImageView(vk.dev, &create_info, NULL, &this->shadow_view);
	if (ret != VK_SUCCESS) engine_crash("vkCreateImageView failed");
}

static void vk_create_voxel_shadow_renderpass(struct VoxelRenderer *this)
{
	VkAttachmentDescription depth_attachment = {
		.format  = DEPTH_FORMAT,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.loadOp  = VK_ATTACHMENT_LOAD_OP_CLEAR,
		.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
		.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
		.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
		.initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED,
		.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
	};

	VkAttachmentReference depth_attachment_reference = {
		.attachment = 0,
		.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
	};

	VkSubpassDescription subpass = {
		.pipelineBindPoint       = VK_PIPELINE_BIND_POINT_GRAPHICS,
		.colorAttachmentCount  = 0,
		.pColorAttachments      = NULL,
		.pDepthStencilAttachment = &depth_attachment_reference,
	};

	VkSubpassDependency dep[] = {
		{
			.srcSubpass     = VK_SUBPASS_EXTERNAL,
			.dstSubpass     = 0,

			.srcStageMask   = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
			.dstStageMask   = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,

			.srcAccessMask  = VK_ACCESS_SHADER_READ_BIT,
			.dstAccessMask  = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,

			.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT,
		},
		{
			.srcSubpass     = 0,
			.dstSubpass     = VK_SUBPASS_EXTERNAL,

			.srcStageMask   = VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
			.dstStageMask   = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,

			.srcAccessMask  = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
			.dstAccessMask  = VK_ACCESS_SHADER_READ_BIT,

			.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT,
		}
	};

	VkAttachmentDescription attachments[] = { depth_attachment };

	VkRenderPassCreateInfo render_pass_info = {
		.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
		.pAttachments    = attachments,
		.attachmentCount = LENGTH(attachments),
		.subpassCount    = 1,
		.pSubpasses      = &subpass,
		.dependencyCount = LENGTH(dep),
		.pDependencies   = dep
	};

	VkResult ret = vkCreateRenderPass(
		vk.dev,
		&render_pass_info,
		NULL,
		&this->shadow_renderpass
	);

	if (ret != VK_SUCCESS) engine_crash("vkCreateRenderPass failed");
}

static void vk_create_voxel_shadow_pipeline(struct VoxelRenderer *this)
{
	VkResult ret;

	/* Pipeline */

	VkShaderModule vert_shader = vk_create_shader_module(RES_SHADER_VERT_VOXEL_SHADOW);

	// If your shadow pass is depth-only with a fullscreen triangle (gl_VertexIndex),
	// then vertex input is empty (no vertex buffers).
	VkPipelineShaderStageCreateInfo shader_stages[] = {
		{
			.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
			.stage  = VK_SHADER_STAGE_VERTEX_BIT,
			.module = vert_shader,
			.pName  = "main",
			.pSpecializationInfo = NULL,
		}
	};

	VkPipelineVertexInputStateCreateInfo vertex_info = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
		.vertexBindingDescriptionCount    = 0,
		.pVertexBindingDescriptions       = NULL,
		.vertexAttributeDescriptionCount  = 0,
		.pVertexAttributeDescriptions     = NULL,
	};

	VkPipelineInputAssemblyStateCreateInfo input_assembly_info = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
		.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
		.primitiveRestartEnable = VK_FALSE
	};

	VkViewport viewport = {
		.x = 0.0f,
		.y = 0.0f,
		.width  = SHADOW_RESOLUTION,
		.height = SHADOW_RESOLUTION,
		.minDepth = 0.0f,
		.maxDepth = 1.0f,
	};

	VkRect2D scissor = {
		.offset = {0, 0},
		.extent = {
			.width = SHADOW_RESOLUTION,
			.height = SHADOW_RESOLUTION,
		}
	};

	VkPipelineViewportStateCreateInfo viewport_info = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
		.viewportCount = 1,
		.pViewports = &viewport,
		.scissorCount = 1,
		.pScissors = &scissor,
	};

	VkPipelineRasterizationStateCreateInfo rasterizer_info = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
		.rasterizerDiscardEnable = VK_FALSE,
		.polygonMode             = VK_POLYGON_MODE_FILL,
		.cullMode                = VK_CULL_MODE_NONE,
		.frontFace               = VK_FRONT_FACE_CLOCKWISE,
		.lineWidth = 1.0f,
	};

	VkPipelineMultisampleStateCreateInfo multisampling_info = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
		.sampleShadingEnable = VK_FALSE,
		.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
		.minSampleShading = 1.0f,
		.pSampleMask = NULL,
		.alphaToCoverageEnable = VK_FALSE,
		.alphaToOneEnable = VK_FALSE,
	};

	VkPipelineDepthStencilStateCreateInfo depth_stencil_info = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
		.depthTestEnable       = VK_TRUE,
		.depthWriteEnable      = VK_TRUE,
		.depthCompareOp        = VK_COMPARE_OP_LESS,
		.depthBoundsTestEnable = VK_FALSE,
		.minDepthBounds        = 0.0f,
		.maxDepthBounds        = 1.0f,
		.stencilTestEnable     = VK_FALSE,
	};

	// If your shadow vertex/fragment shaders do NOT use push constants,
	// set pushConstantRangeCount = 0 and omit push constants.
	VkPushConstantRange push_constants[] = {
		{
			.stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
			.offset = 0,
			.size = sizeof(struct VoxelRendererUniform) // <-- change to what your shadow shader expects
		}
	};

	VkPipelineLayoutCreateInfo pipeline_layout_info = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
		.setLayoutCount = 1,
		.pSetLayouts    = &this->scene_layout,
		.pushConstantRangeCount = LENGTH(push_constants),
		.pPushConstantRanges = push_constants,
	};

	ret = vkCreatePipelineLayout(vk.dev,
			&pipeline_layout_info, NULL, &this->shadow_pipeline_layout);
	if (ret != VK_SUCCESS) engine_crash("vkCreatePipelineLayout failed");

	VkGraphicsPipelineCreateInfo pipeline_info = {
		.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
		.stageCount          = LENGTH(shader_stages),
		.pStages             = shader_stages,
		.pVertexInputState   = &vertex_info,
		.pInputAssemblyState = &input_assembly_info,
		.pViewportState      = &viewport_info,
		.pRasterizationState = &rasterizer_info,
		.pMultisampleState   = &multisampling_info,
		.pDepthStencilState  = &depth_stencil_info,
		.pColorBlendState    = NULL,
		.pDynamicState       = NULL,
		.layout              = this->shadow_pipeline_layout,
		.renderPass          = this->shadow_renderpass,
		.subpass             = 0,
		.basePipelineHandle  = VK_NULL_HANDLE,
		.basePipelineIndex   = -1,
	};

	ret = vkCreateGraphicsPipelines(
		vk.dev,
		VK_NULL_HANDLE,
		1,
		&pipeline_info,
		NULL,
		&this->shadow_pipeline
	);

	if (ret != VK_SUCCESS) engine_crash("vkCreateGraphicsPipelines failed");

	vkDestroyShaderModule(vk.dev, vert_shader, NULL);
}


static void vk_create_voxel_shadow_layout(struct VoxelRenderer *this)
{
	VkResult ret;

	// For a voxel shadow pass, you typically need:
	// - binding0: Camera/Scene UBO (uniform)
	// - binding1: Dataset / voxel data as an SSBO or texture (depends on your voxel shader)
	//
	// Below matches the pattern of your softbody shadow layout:
	//   binding0 = uniform buffer
	//   binding1 = combined image sampler
	VkDescriptorSetLayoutBinding binding[] = {
		{
			.binding = 0,
			.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			.descriptorCount = 1,
			.stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
			.pImmutableSamplers = NULL,
		},
		{
			.binding = 1,
			.descriptorCount = 1,
			.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			.pImmutableSamplers = NULL,
			.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
		}
	};

	VkDescriptorSetLayoutCreateInfo layout_info = {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
		.bindingCount = LENGTH(binding),
		.pBindings = binding,
	};

	ret = vkCreateDescriptorSetLayout(vk.dev, &layout_info, NULL, &this->scene_layout);
	if (ret != VK_SUCCESS) engine_crash("vkCreateDescriptorSetLayout failed");
}

static void vk_create_voxel_shadow_descriptor(struct VoxelRenderer *this)
{
	VkResult ret;

	for (size_t i = 0; i < VK_FRAMES; i++) {
		struct VoxelRendererFrame *frame = &this->frame[i];

		VkDescriptorSetAllocateInfo desc_ainfo = {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
			.descriptorPool     = vk.descriptor_pool,
			.descriptorSetCount = 1,
			.pSetLayouts        = &this->scene_layout
		};

		ret = vkAllocateDescriptorSets(vk.dev, &desc_ainfo, &frame->scene_descriptor);
		if (ret != VK_SUCCESS) engine_crash("vkAllocateDescriptorSets failed");

		VkWriteDescriptorSet desc_write[] = {
			{
				.sType           = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.dstSet          = frame->scene_descriptor,
				.dstBinding      = 0,
				.dstArrayElement = 0,
				.descriptorType  = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				.descriptorCount = 1,
				.pBufferInfo     = (VkDescriptorBufferInfo[]){{
					.buffer = this->uniform_buffer,
					.offset = 0,
					.range  = sizeof(struct VoxelRendererUniform), // or your actual camera/light UBO struct used by voxel shadow
				}},
				.pImageInfo       = NULL,
				.pTexelBufferView = NULL,
			},
			{
				.sType           = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.dstSet          = frame->scene_descriptor,
				.dstBinding      = 1,
				.dstArrayElement = 0,
				.descriptorType  = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
				.descriptorCount = 1,
				.pBufferInfo     = NULL,
				.pImageInfo      = (VkDescriptorImageInfo[]){{
					.imageLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
					.imageView   = this->shadow_view,
					.sampler     = this->shadow_sampler,
				}},
				.pTexelBufferView = NULL,
			},
		};

		vkUpdateDescriptorSets(vk.dev, LENGTH(desc_write), desc_write, 0, NULL);
	}
}

static void vk_create_voxel_shadow_layout(struct VoxelRenderer *this)
{
	VkResult ret;

	VkDescriptorSetLayoutBinding binding[] = {
		{
			.binding = 0,
			.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			.descriptorCount = 1,
			.stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
			.pImmutableSamplers = NULL,
		},
		{
			.binding = 1,
			.descriptorCount = 1,
			.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			.pImmutableSamplers = NULL,
			.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
		}
	};

	VkDescriptorSetLayoutCreateInfo layout_info = {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
		.bindingCount = LENGTH(binding),
		.pBindings = binding,
	};

	ret = vkCreateDescriptorSetLayout(vk.dev, &layout_info, NULL, &this->scene_layout);
	if (ret != VK_SUCCESS) engine_crash("vkCreateDescriptorSetLayout failed");
}


static void vk_create_voxel_shadow(struct VoxelRenderer *this)
{
	vk_create_voxel_shadow_resources(this);
	vk_create_voxel_shadow_renderpass(this);

	vk_create_voxel_shadow_sampler(this);
	vk_create_voxel_shadow_layout(this);
	vk_create_voxel_shadow_descriptor(this);

	vk_create_voxel_shadow_framebuffer(this);

	vk_create_voxel_shadow_pipeline(this);
}
// Your shader uses findVoxelAt() which compares ds.xs/ys/zs with an ivec3 c.
// Given your tree encoding, a voxel u32 must contain:
//   x,y,z packed with child-bit width b (bChild), and payload/value in the same uint (as you already use ds.vals[i] as color bits).
//
// However your snippet only shows how to compute a packed index from (x,y,z,bChild):
//   i = (z << (2*bChild)) | (y << bChild) | x;
// That gives x,y,z from i via bit extraction.
// We'll implement a decode that treats the uint as that packed index,
// and sets payload=value=u (or you can split payload bits if your actual encoding uses spare bits).

static inline void decode_child_index(uint32_t packed, uint32_t bChild,
                                        uint32_t *out_x, uint32_t *out_y, uint32_t *out_z)
{
	// x uses lowest bChild bits, y next bChild bits, z next bChild bits.
	const uint32_t mask = (bChild == 32) ? 0xFFFFFFFFu : ((1u << bChild) - 1u);
	*out_x =  packed & mask;
	*out_y = (packed >> bChild) & mask;
	*out_z = (packed >> (2u * bChild)) & mask;
}

// ---- Build the dataset SSBO from global.tree_flat ----
// This uploads at most 16 voxels per update because your GLSL loops i<16.
static void build_dataset_from_global(struct VoxelRendererDatasetSSBO *out, uint32_t max16)
{
	memset(out, 0, sizeof(*out));

	out->root = global.root;

	// In your shader you never actually use ds.leaf_count for math,
	// but fill it anyway consistently.
	out->leaf_count = global.tree_total;

	// ds.b is used by pToLeafCoord via ds.root only in your shown shader,
	// but still set it to what the CPU uses.
	out->b = (uint32_t)global.bitw;

	// If you truly need masking, set accordingly; else all enabled.
	out->enabledMask = 0xFFFFFFFFu;

	// We decode (x,y,z) from each Voxel uint using bChild = global.bitw
	// (adjust if your voxels were encoded with a different bChild per-level).
	uint32_t n = global.tree_total;
	if (n > max16) n = max16;

	for (uint32_t i = 0; i < n; ++i) {
		uint32_t u = global.tree_flat[i];

		uint32_t x, y, z;
		decode_child_index(u, (uint32_t)global.bitw, &x, &y, &z);

		out->xs[i] = x;
		out->ys[i] = y;
		out->zs[i] = z;

		// Your shader expects ds.vals[i] == the uint32 payload it uses for RGB:
		//   r=(u>>16)&0xFF, g=(u>>8)&0xFF, b=(u>>0)&0xFF
		//
		// If your Voxel uint stores payload directly in the same bits as x/y/z,
		// then set vals[i]=u as below.
		out->vals[i] = u;
	}
}

// ---- Upload function: memcpy + vmaFlushAllocation ----
// Assumes your VoxelRenderer has dataset_buffer/dataset_alloc, and the SSBO is not persistently mapped.
// If you DO have a persistently mapped pointer, replace the map/unmap with memcpy into it.
extern struct VkEngine vk;
extern void *alloc; // if your deref API needs it

typedef struct VoxelRenderer VoxelRenderer;
extern VoxelRenderer *voxel_renderer_deref(void *alloc, VoxelRenderer *handle);

void voxel_tree_copy_and_upload(VoxelRenderer handle)
{
	struct VoxelRenderer *this = voxel_renderer_deref(alloc, handle);

	struct VoxelRendererDatasetSSBO ds;
	build_dataset_from_global(&ds, BATCH);

	const size_t bytes = sizeof(struct VoxelRendererDatasetSSBO);

	void *mapped = NULL;
	vmaMapMemory(vk.vma, this->dataset_alloc, &mapped);
	memcpy(mapped, &ds, bytes);
	vmaUnmapMemory(vk.vma, this->dataset_alloc);

	vmaFlushAllocation(vk.vma, this->dataset_alloc, 0, bytes);
}

void voxel_renderer_draw(VoxelRenderer handle, struct Frame *frame)
{
    struct VoxelRenderer *restrict this = handle_deref(&alloc, handle);

    // You must use the correct per-frame swapchain image index from your engine.
    // Replace `frame->image_index` with the actual field name in your Frame struct.
    uint32_t i = frame->image_index % vk.framebuffers_num;

    VkCommandBuffer cmd = frame->cmd_buf;

    VkClearValue clear;
    clear.color = (VkClearColorValue){{0.0f, 0.0f, 0.0f, 1.0f}};

    VkRenderPassBeginInfo rpbi = {0};
    rpbi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rpbi.renderPass = this->renderpass;              // If your voxel renderer has its own renderpass.
    rpbi.framebuffer = vk.framebuffers[i];         // Created for vk.renderpass in vk_create_framebuffers().
    rpbi.renderArea.offset = (VkOffset2D){0, 0};
    rpbi.renderArea.extent = vk.swapchain_extent;   // Matches vk_create_framebuffers()

    rpbi.clearValueCount = 1;
    rpbi.pClearValues = &clear;

    vkCmdBeginRenderPass(cmd, &rpbi, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, this->pipeline);

    vkCmdBindDescriptorSets(
        cmd,
        VK_PIPELINE_BIND_POINT_GRAPHICS,
        this->pipeline_layout,
        0, 1,
        &this->scene_descriptor,
        0, NULL
    );

    // Fullscreen triangle
    vkCmdDraw(cmd, 3, 1, 0, 0);

    vkCmdEndRenderPass(cmd);
}



void voxel_create()
{
	// 1) Build/fill the CPU-side voxel tree (GlobalTree global)
	//    This part is totally dependent on your voxel generator.
	//    You must populate:
	//      global.root
	//      global.bitw
	//      global.tree_total
	//      global.tree_flat  (array of Voxel uint32_t)
	//    and/or anything else your builder needs.
	//
	// Example placeholders (replace with your actual generator):
	//
	// global = build_global_tree(...);
	// mem_debug();

	// 2) Create renderer objects
	vb.gfx_voxel = voxel_renderer_create();

	// 3) Upload initial dataset to GPU (SSBO)
	//    This copies CPU GlobalTree -> shader DatasetSSBO fields.
	voxel_tree_copy_and_upload(vb.gfx_voxel);

	// 4) Optional renderer toggles / state
	vb.pause = true;
	vb.voxel = true;

	log_info("Voxel renderer created");

	// (optional) debug sizes like your softbody_create did
	// log_info("VoxelRendererDatasetSSBO size: %zu", sizeof(struct VoxelRendererDatasetSSBO));
}


// Upload: write directly into the mapped SSBO memory for this renderer.
// Note: you can’t avoid *writing* the SSBO contents; but this version avoids
// building a separate temporary ds struct and then memcpy-ing it.
void voxel_tree_insert_and_upload(VoxelRenderer sb_gfx_voxel, GlobalTree *globalTree)
{
    struct VoxelRenderer *restrict this = handle_deref(&alloc, handle);

	if (!this || !globalTree) return;

	// Determine how many entries the shader consumes
	uint32_t n = globalTree->tree_total;
	if (n > BATCH) n = BATCH;

	const size_t bytes = sizeof(struct VoxelRendererDatasetSSBO);

	if (this->dataset_mapping) {
		// Direct access: compute the destination pointer and write fields/arrays in place.
		struct VoxelRendererDatasetSSBO *dst =
			(struct VoxelRendererDatasetSSBO *)this->dataset_mapping;

		dst->root        = globalTree->root;
		dst->leaf_count  = globalTree->tree_total;
		dst->b           = (uint32_t)globalTree->bitw;
		dst->enabledMask= 0xFFFFFFFFu;

		for (uint32_t i = 0; i < n; ++i) {
			uint32_t u = globalTree->tree_flat[i];

			uint32_t x, y, z;
			decode_child_index(u, (uint32_t)globalTree->bitw, &x, &y, &z);

			dst->xs[i]   = x;
			dst->ys[i]   = y;
			dst->zs[i]   = z;

			// Shader expects vals[i] as packed voxel payload (colorFromVoxel uses u bits)
			dst->vals[i] = u;
		}

		// Optional: if you care about deterministic contents for unused slots,
		// zero remaining [n..15]. (Uncomment if needed.)
		/*
		for (uint32_t i = n; i < BATCH; ++i) {
			dst->xs[i] = dst->ys[i] = dst->zs[i] = dst->vals[i] = 0;
		}
		*/

		vmaFlushAllocation(vk.vma, this->dataset_alloc, 0, bytes);
	} else {
		// Not persistently mapped: map once, write directly into mapped memory, flush, unmap.
		void *mapped = NULL;
		vmaMapMemory(vk.vma, this->dataset_alloc, &mapped);

		struct VoxelRendererDatasetSSBO *dst =
			(struct VoxelRendererDatasetSSBO *)mapped;

		dst->root        = globalTree->root;
		dst->leaf_count  = globalTree->tree_total;
		dst->b           = (uint32_t)globalTree->bitw;
		dst->enabledMask= 0xFFFFFFFFu;

		for (uint32_t i = 0; i < n; ++i) {
			uint32_t u = globalTree->tree_flat[i];

			uint32_t x, y, z;
			decode_child_index(u, (uint32_t)globalTree->bitw, &x, &y, &z);

			dst->xs[i]   = x;
			dst->ys[i]   = y;
			dst->zs[i]   = z;
			dst->vals[i] = u;
		}

		// Optional: zero remaining slots if desired.
		/*
		for (uint32_t i = n; i < BATCH; ++i) {
			dst->xs[i] = dst->ys[i] = dst->zs[i] = dst->vals[i] = 0;
		}
		*/

		vmaFlushAllocation(vk.vma, this->dataset_alloc, 0, bytes);
		vmaUnmapMemory(vk.vma, this->dataset_alloc);
	}
}



// Assuming you store these somewhere accessible:
// - vb.cast / vb.grab, etc.
// - vb.globalTree points to GlobalTree
// - vb.gfx_voxel has uniform buffers with camera/model,
//   OR you already have cam invViewProj + camPos on CPU.
// We'll assume you can read CPU-side uniforms from the engine
// or keep a CPU copy updated every frame.
// Your renderer CPU inverse view-proj + camera position must exist on CPU.
// If you already have these in CPU memory, use them directly.
extern mat4 get_invViewProj_cpu(void);
extern void get_camPos_cpu(vec3 out); // or provide vec3 camPos as a global

static inline uint32_t pack_xyz(uint32_t x, uint32_t y, uint32_t z, uint32_t b)
{
    uint32_t mask = (b == 32u) ? 0xFFFFFFFFu : ((1u << b) - 1u);
    x &= mask; y &= mask; z &= mask;
    return (x) | (y << b) | (z << (2u * b));
}

static inline int ray_aabb(vec3 ro, vec3 rd, vec3 mn, vec3 mx, float *tHitNear)
{
    float tmin = -INFINITY;
    float tmax =  INFINITY;

    for (int axis = 0; axis < 3; ++axis) {
        float rO = ro[axis];
        float rD = rd[axis];
        float b0 = mn[axis];
        float b1 = mx[axis];

        if (fabsf(rD) < 1e-8f) {
            if (rO < b0 || rO > b1) return 0;
        } else {
            float invD = 1.0f / rD;
            float t0 = (b0 - rO) * invD;
            float t1 = (b1 - rO) * invD;
            if (t0 > t1) { float tmp = t0; t0 = t1; t1 = tmp; }
            if (t0 > tmin) tmin = t0;
            if (t1 < tmax) tmax = t1;
            if (tmin > tmax) return 0;
        }
    }

    if (tmax < 0.0f) return 0;
    *tHitNear = (tmin >= 0.0f) ? tmin : tmax;
    return 1;
}

// Converts a world-space point to voxel indices given volume bounds [boxMin, boxMax] and bChild.
static inline void world_to_voxel_xyz(vec3 hitP, vec3 boxMin, vec3 boxMax, uint32_t bChild,
                                        uint32_t *out_x, uint32_t *out_y, uint32_t *out_z)
{
    uint32_t res = 1u << bChild; // assumes bChild <= 31

    float u = (hitP[0] - boxMin[0]) / (boxMax[0] - boxMin[0]);
    float v = (hitP[1] - boxMin[1]) / (boxMax[1] - boxMin[1]);
    float w = (hitP[2] - boxMin[2]) / (boxMax[2] - boxMin[2]);

    if (u < 0.0f) u = 0.0f; if (u > 1.0f) u = 1.0f;
    if (v < 0.0f) v = 0.0f; if (v > 1.0f) v = 1.0f;
    if (w < 0.0f) w = 0.0f; if (w > 1.0f) w = 1.0f;

    uint32_t x = (uint32_t)(u * (float)res);
    uint32_t y = (uint32_t)(v * (float)res);
    uint32_t z = (uint32_t)(w * (float)res);

    if (x >= res) x = res - 1;
    if (y >= res) y = res - 1;
    if (z >= res) z = res - 1;

    *out_x = x; *out_y = y; *out_z = z;
}

// Build ray in world space from yaw/pitch + cursor, then hit AABB and pack voxel.
void voxel_button_callback(int key, int action, int mods)
{
	(void)mods;

	if (key != GLFW_MOUSE_BUTTON_LEFT) return;

	if (action != GLFW_PRESS) {
		vb.cast = false;
		return;
	}
	vb.cast = true;

	double mx, my;
	glfwGetCursorPos(window, &mx, &my);

	int fbW, fbH;
	glfwGetFramebufferSize(window, &fbW, &fbH);

	// NDC in [-1,1]
	float ndcX = (float)((2.0 * mx) / (double)fbW - 1.0);
	float ndcY = (float)(1.0 - (2.0 * my) / (double)fbH);

	Freecam *cam = &vb.freecam;

	// Compute forward from yaw/pitch (if cam.dir isn't already correct, overwrite it)
	// yaw: rotation around Y axis, pitch: up/down
	float cy = cosf(cam->yaw), sy = sinf(cam->yaw);
	float cp = cosf(cam->pitch), sp = sinf(cam->pitch);

	vec3 forward = { sy * cp, sp, cy * cp };

	// World up
	vec3 worldUp = { 0.0f, 1.0f, 0.0f };

	// right = normalize(cross(forward, up))
	vec3 right;
	glm_vec3_cross(forward, worldUp, right);
	glm_vec3_normalize(right);

	// up = cross(right, forward)
	vec3 up;
	glm_vec3_cross(right, forward, up);
	glm_vec3_normalize(up);

	// Perspective ray: map NDC to camera plane.
	// vertical FOV => scale by tan(fov/2)
	float tanHalfFov = tanf(cam->fov * 0.5f);
	float aspect = (float)fbW / (float)fbH;

	// camera space direction
	// x = ndcX * aspect * tanHalfFov
	// y = ndcY * tanHalfFov
	// z = -1 (or +1 depending on your convention; here we use -forward-facing camera plane)
	vec3 rayDirCam = {
		ndcX * aspect * tanHalfFov,
		ndcY * tanHalfFov,
		-1.0f
	};
	glm_vec3_normalize(rayDirCam);

	// Transform from camera space to world space:
	// dirWorld = rayDirCam.x * right + rayDirCam.y * up + rayDirCam.z * forward
	vec3 rayDir;
	rayDir[0] = rayDirCam[0] * right[0] + rayDirCam[1] * up[0] + rayDirCam[2] * forward[0];
	rayDir[1] = rayDirCam[0] * right[1] + rayDirCam[1] * up[1] + rayDirCam[2] * forward[1];
	rayDir[2] = rayDirCam[0] * right[2] + rayDirCam[1] * up[2] + rayDirCam[2] * forward[2];
	glm_vec3_normalize(rayDir);

	vec3 rayOrg = { cam->pos[0], cam->pos[1], cam->pos[2] };

	// Voxel volume bounds (replace with your real ones!)
	vec3 boxMin = { 0.0f, 0.0f, 0.0f };
	vec3 boxMax = { 1.0f, 1.0f, 1.0f };

	float tHit = 0.0f;
	if (!ray_aabb(rayOrg, rayDir, boxMin, boxMax, &tHit)) {
		return; // miss
	}

	vec3 hitP;
	hitP[0] = rayOrg[0] + rayDir[0] * tHit;
	hitP[1] = rayOrg[1] + rayDir[1] * tHit;
	hitP[2] = rayOrg[2] + rayDir[2] * tHit;

	// Convert hit point -> voxel grid coords
	uint32_t bChild = (uint32_t)vb.globalTree->bitw;
	uint32_t res = 1u << bChild; // assumes bChild <= 31

	// u in [0,1]
	float u = (hitP[0] - boxMin[0]) / (boxMax[0] - boxMin[0]);
	float v = (hitP[1] - boxMin[1]) / (boxMax[1] - boxMin[1]);
	float w = (hitP[2] - boxMin[2]) / (boxMax[2] - boxMin[2]);

	if (u < 0.0f) u = 0.0f; if (u > 1.0f) u = 1.0f;
	if (v < 0.0f) v = 0.0f; if (v > 1.0f) v = 1.0f;
	if (w < 0.0f) w = 0.0f; if (w > 1.0f) w = 1.0f;

	uint32_t x = (uint32_t)(u * (float)res);
	uint32_t y = (uint32_t)(v * (float)res);
	uint32_t z = (uint32_t)(w * (float)res);

	if (x >= res) x = res - 1;
	if (y >= res) y = res - 1;
	if (z >= res) z = res - 1;

	// Pack to the same packed uint your decode_child_index expects
	uint32_t packedIndex = pack_xyz(x, y, z, bChild);

	// Example: store it
	vb.grab = packedIndex;
}


void voxel_scroll_callback(double x, double y)
{

	if (vb.cast) {
		vb.dist += 0.03 * y;
	}

}

void voxel_button_callback(int key, int action, int mods)
{
	if (key == GLFW_MOUSE_BUTTON_LEFT)  {
	
		if (action == GLFW_PRESS) {
			vb.cast = true;
		} else {
			vb.cast = false;
		}
	}


}

void voxel_key_callback(int key, int scancode, int action, int mods)
{
	if (action != GLFW_RELEASE) return;
	
	switch (key) {
	case (GLFW_KEY_P):
		vb.pause = !vb.pause;
		log_info("Toggle simulation");
		break;
	case (GLFW_KEY_BACKSLASH):
		vb.step += SUBSTEPS;
		break;
	case (GLFW_KEY_RIGHT_BRACKET):
		vb.step += 1;
		break;
	case (GLFW_KEY_LEFT_BRACKET):
		vb.step += 1;
		break;
	case (GLFW_KEY_F):
		log_info("Toggle wireframe");
		vb.wireframe = !vb.wireframe;
		break;
	case (GLFW_KEY_G):
		log_info("Toggle sphere");
		vb.sphere = !vb.sphere;
		break;
	}
}


