

void
log_nk_glfw_device_settings(const struct nk_glfw_device *device)
{
    if (device == NULL)
    {
        log_error("nk_glfw_device is NULL");
        return;
    }

    log_info("nk_glfw_device settings:");
    log_info("  %-32s = %zu bytes",
             "struct size",
             sizeof(*device));

    /*
     * Nuklear structures. Their individual fields are not logged here
     * because their layout depends on the Nuklear version and configuration.
     */
    log_info("  %-32s = %zu bytes",
             "cmds size",
             sizeof(device->cmds));

    log_info("  %-32s = %zu bytes",
             "tex_null size",
             sizeof(device->tex_null));

    LOG_INT("max_vertex_buffer", device->max_vertex_buffer);
    LOG_INT("max_element_buffer", device->max_element_buffer);

    LOG_VK_HANDLE("logical_device", device->logical_device);
    LOG_VK_HANDLE("physical_device", device->physical_device);

    LOG_POINTER("image_views", device->image_views);
    LOG_UINT("image_views_len", device->image_views_len);

    LOG_VK_HANDLE("color_format", device->color_format);

    LOG_POINTER("framebuffers", device->framebuffers);
    LOG_UINT("framebuffers_len", device->framebuffers_len);

    LOG_POINTER("command_buffers", device->command_buffers);
    LOG_UINT("command_buffers_len", device->command_buffers_len);

    LOG_VK_HANDLE("sampler", device->sampler);
    LOG_VK_HANDLE("command_pool", device->command_pool);
    LOG_VK_HANDLE("render_completed", device->render_completed);

    LOG_VK_HANDLE("vertex_buffer", device->vertex_buffer);
    LOG_VK_HANDLE("vertex_memory", device->vertex_memory);
    LOG_POINTER("mapped_vertex", device->mapped_vertex);

    LOG_VK_HANDLE("index_buffer", device->index_buffer);
    LOG_VK_HANDLE("index_memory", device->index_memory);
    LOG_POINTER("mapped_index", device->mapped_index);

    LOG_VK_HANDLE("uniform_buffer", device->uniform_buffer);
    LOG_VK_HANDLE("uniform_memory", device->uniform_memory);
    LOG_POINTER("mapped_uniform", device->mapped_uniform);

    LOG_VK_HANDLE("render_pass", device->render_pass);
    LOG_VK_HANDLE("descriptor_pool", device->descriptor_pool);

    LOG_VK_HANDLE(
        "uniform_descriptor_set_layout",
        device->uniform_descriptor_set_layout
    );

    LOG_VK_HANDLE(
        "uniform_descriptor_set",
        device->uniform_descriptor_set
    );

    LOG_VK_HANDLE(
        "texture_descriptor_set_layout",
        device->texture_descriptor_set_layout
    );

    LOG_POINTER(
        "texture_descriptor_sets",
        device->texture_descriptor_sets
    );

    LOG_UINT(
        "texture_descriptor_sets_len",
        device->texture_descriptor_sets_len
    );

    LOG_VK_HANDLE("pipeline_layout", device->pipeline_layout);
    LOG_VK_HANDLE("pipeline", device->pipeline);

    LOG_VK_HANDLE("font_image", device->font_image);
    LOG_VK_HANDLE("font_image_view", device->font_image_view);
    LOG_VK_HANDLE("font_memory", device->font_memory);

    log_info("Finished logging nk_glfw_device settings");
}

void
log_nk_vulkan_texture_descriptor_sets(
    const struct nk_glfw_device *device
)
{
    if (device == NULL)
    {
        log_error("nk_glfw_device is NULL");
        return;
    }

    if (device->texture_descriptor_sets == NULL)
    {
        log_info("texture_descriptor_sets = NULL");
        return;
    }

    log_info(
        "texture descriptor sets: count=%" PRIu32,
        device->texture_descriptor_sets_len
    );

    for (uint32_t i = 0;
            i < device->texture_descriptor_sets_len;
            ++i)
    {
        const struct nk_vulkan_texture_descriptor_set *set =
                &device->texture_descriptor_sets[i];

        log_info(
            "texture_descriptor_sets[%" PRIu32 "]:",
            i
        );

        LOG_VK_HANDLE(
            "  image_view",
            set->image_view
        );

        LOG_VK_HANDLE(
            "  descriptor_set",
            set->descriptor_set
        );
    }
}
static void
log_nk_configuration_stacks(
    const struct nk_configuration_stacks *stacks
)
{
    if (stacks == NULL)
    {
        log_error("nk_configuration_stacks is NULL");
        return;
    }

    log_info("nk_configuration_stacks:");

    LOG_NK_STRUCT("stacks.style_items", stacks->style_items);
    LOG_NK_STRUCT("stacks.floats", stacks->floats);
    LOG_NK_STRUCT("stacks.vectors", stacks->vectors);
    LOG_NK_STRUCT("stacks.flags", stacks->flags);
    LOG_NK_STRUCT("stacks.colors", stacks->colors);
    LOG_NK_STRUCT("stacks.fonts", stacks->fonts);
    LOG_NK_STRUCT(
        "stacks.button_behaviors",
        stacks->button_behaviors
    );
}

static void
log_nk_pool(const struct nk_pool *pool)
{
    if (pool == NULL)
    {
        log_error("nk_pool is NULL");
        return;
    }

    log_info("nk_pool:");

    LOG_NK_STRUCT("pool.alloc", pool->alloc);

    log_info(
        "  %-32s = %d",
        "pool.type",
        (int)pool->type
    );

    LOG_NK_UINT("pool.page_count", pool->page_count);

    LOG_NK_POINTER("pool.pages", pool->pages);
    LOG_NK_POINTER("pool.freelist", pool->freelist);

    LOG_NK_UINT("pool.capacity", pool->capacity);

    LOG_NK_SIZE("pool.size", pool->size);
    LOG_NK_SIZE("pool.cap", pool->cap);
}

static void
log_nk_page_element(
    const struct nk_page_element *element,
    const char *name
)
{
    if (element == NULL)
    {
        log_info("  %-32s = NULL", name);
        return;
    }

    log_info(
        "  %-32s = %p",
        name,
        (const void *)element
    );

    LOG_NK_POINTER("    next", element->next);
    LOG_NK_POINTER("    prev", element->prev);

    log_info(
        "    %-28s = %zu bytes",
        "data",
        sizeof(element->data)
    );
}

static void
log_nk_page(
    const struct nk_page *page,
    const char *name
)
{
    if (page == NULL)
    {
        log_info("  %-32s = NULL", name);
        return;
    }

    log_info(
        "  %-32s = %p",
        name,
        (const void *)page
    );

    LOG_NK_UINT("    size", page->size);
    LOG_NK_POINTER("    next", page->next);

    log_nk_page_element(
        &page->win[0],
        "page.win[0]"
    );
}


static void
log_nk_chart_slot(
    const struct nk_chart_slot *slot,
    unsigned int index
)
{
    if (slot == NULL)
    {
        log_error("nk_chart_slot[%u] is NULL", index);
        return;
    }

    log_info("nk_chart_slot[%u]:", index);

    log_info(
        "  %-32s = %d",
        "type",
        (int)slot->type
    );

    LOG_NK_STRUCT("color", slot->color);
    LOG_NK_STRUCT("highlight", slot->highlight);

    LOG_NK_FLOAT("min", slot->min);
    LOG_NK_FLOAT("max", slot->max);
    LOG_NK_FLOAT("range", slot->range);

    LOG_NK_INT("count", slot->count);

    LOG_NK_STRUCT("last", slot->last);

    LOG_NK_INT("index", slot->index);

    log_info(
        "  %-32s = %d",
        "show_markers",
        (int)slot->show_markers
    );
}


static void
log_nk_chart(const struct nk_chart *chart)
{
    if (chart == NULL)
    {
        log_error("nk_chart is NULL");
        return;
    }

    log_info("nk_chart:");

    LOG_NK_INT("slot", chart->slot);

    LOG_NK_FLOAT("x", chart->x);
    LOG_NK_FLOAT("y", chart->y);
    LOG_NK_FLOAT("w", chart->w);
    LOG_NK_FLOAT("h", chart->h);

    for (unsigned int i = 0; i < NK_CHART_MAX_SLOT; ++i)
    {
        log_nk_chart_slot(&chart->slots[i], i);
    }
}


static void
log_nk_row_layout(const struct nk_row_layout *row)
{
    if (row == NULL)
    {
        log_error("nk_row_layout is NULL");
        return;
    }

    log_info("nk_row_layout:");

    log_info(
        "  %-32s = %d",
        "type",
        (int)row->type
    );

    LOG_NK_INT("index", row->index);

    LOG_NK_FLOAT("height", row->height);
    LOG_NK_FLOAT("min_height", row->min_height);

    LOG_NK_INT("columns", row->columns);

    LOG_NK_POINTER("ratio", row->ratio);

    LOG_NK_FLOAT("item_width", row->item_width);
    LOG_NK_FLOAT("item_height", row->item_height);
    LOG_NK_FLOAT("item_offset", row->item_offset);
    LOG_NK_FLOAT("filled", row->filled);

    LOG_NK_STRUCT("item", row->item);

    LOG_NK_INT("tree_depth", row->tree_depth);

    log_info(
        "  %-32s = %d entries",
        "templates",
        NK_MAX_LAYOUT_ROW_TEMPLATE_COLUMNS
    );

    for (unsigned int i = 0;
            i < NK_MAX_LAYOUT_ROW_TEMPLATE_COLUMNS;
            ++i)
    {
        log_info(
            "  templates[%u]              = %.9g",
            i,
            (double)row->templates[i]
        );
    }
}


static void
log_nk_popup_buffer(const struct nk_popup_buffer *popup)
{
    if (popup == NULL)
    {
        log_error("nk_popup_buffer is NULL");
        return;
    }

    log_info("nk_popup_buffer:");

    LOG_NK_SIZE("begin", popup->begin);
    LOG_NK_SIZE("parent", popup->parent);
    LOG_NK_SIZE("last", popup->last);
    LOG_NK_SIZE("end", popup->end);

    log_info(
        "  %-32s = %d",
        "active",
        (int)popup->active
    );
}


static void
log_nk_menu_state(const struct nk_menu_state *menu)
{
    if (menu == NULL)
    {
        log_error("nk_menu_state is NULL");
        return;
    }

    log_info("nk_menu_state:");

    LOG_NK_FLOAT("x", menu->x);
    LOG_NK_FLOAT("y", menu->y);
    LOG_NK_FLOAT("w", menu->w);
    LOG_NK_FLOAT("h", menu->h);

    LOG_NK_STRUCT("offset", menu->offset);
}


static void
log_nk_panel(const struct nk_panel *panel)
{
    if (panel == NULL)
    {
        log_error("nk_panel is NULL");
        return;
    }

    log_info("nk_panel:");

    log_info(
        "  %-32s = %d",
        "type",
        (int)panel->type
    );

    LOG_NK_FLAGS("flags", panel->flags);

    LOG_NK_STRUCT("bounds", panel->bounds);

    LOG_NK_POINTER("offset_x", panel->offset_x);
    LOG_NK_POINTER("offset_y", panel->offset_y);

    LOG_NK_FLOAT("at_x", panel->at_x);
    LOG_NK_FLOAT("at_y", panel->at_y);
    LOG_NK_FLOAT("max_x", panel->max_x);

    LOG_NK_FLOAT("footer_height", panel->footer_height);
    LOG_NK_FLOAT("header_height", panel->header_height);
    LOG_NK_FLOAT("border", panel->border);

    LOG_NK_UINT("has_scrolling", panel->has_scrolling);

    LOG_NK_STRUCT("clip", panel->clip);

    log_nk_menu_state(&panel->menu);
    log_nk_row_layout(&panel->row);
    log_nk_chart(&panel->chart);

    LOG_NK_POINTER("buffer", panel->buffer);
    LOG_NK_POINTER("parent", panel->parent);
}


static void
log_nk_table(const struct nk_table *table)
{
    if (table == NULL)
    {
        log_error("nk_table is NULL");
        return;
    }

    log_info("nk_table:");

    LOG_NK_UINT("seq", table->seq);
    LOG_NK_UINT("size", table->size);

    log_info(
        "  %-32s = %d entries",
        "keys",
        NK_VALUE_PAGE_CAPACITY
    );

    for (unsigned int i = 0; i < table->size &&
            i < NK_VALUE_PAGE_CAPACITY; ++i)
    {
        log_info(
            "  keys[%u]                    = 0x%" PRIx64,
            i,
            (uint64_t)table->keys[i]
        );

        log_info(
            "  values[%u]                  = %" PRIu64,
            i,
            (uint64_t)table->values[i]
        );
    }

    LOG_NK_POINTER("next", table->next);
    LOG_NK_POINTER("prev", table->prev);
}


void
log_nk_context_settings(const struct nk_context *ctx)
{
    if (ctx == NULL)
    {
        log_error("nk_context is NULL");
        return;
    }

    log_info("nk_context settings:");

    LOG_NK_STRUCT("input", ctx->input);
    LOG_NK_STRUCT("style", ctx->style);
    LOG_NK_STRUCT("memory", ctx->memory);
    LOG_NK_STRUCT("clip", ctx->clip);

    LOG_NK_FLAGS(
        "last_widget_state",
        ctx->last_widget_state
    );

    log_info(
        "  %-32s = %d",
        "button_behavior",
        (int)ctx->button_behavior
    );

    log_nk_configuration_stacks(&ctx->stacks);

    LOG_NK_FLOAT(
        "delta_time_seconds",
        ctx->delta_time_seconds
    );

#ifdef NK_INCLUDE_VERTEX_BUFFER_OUTPUT
    LOG_NK_STRUCT("draw_list", ctx->draw_list);
#endif

#ifdef NK_INCLUDE_COMMAND_USERDATA
    LOG_NK_STRUCT("userdata", ctx->userdata);
#endif

    LOG_NK_STRUCT("text_edit", ctx->text_edit);
    LOG_NK_STRUCT("overlay", ctx->overlay);

    LOG_NK_INT("build", ctx->build);
    LOG_NK_INT("use_pool", ctx->use_pool);

    log_nk_pool(&ctx->pool);

    LOG_NK_POINTER("begin", ctx->begin);
    LOG_NK_POINTER("end", ctx->end);
    LOG_NK_POINTER("active", ctx->active);
    LOG_NK_POINTER("current", ctx->current);
    LOG_NK_POINTER("context.freelist", ctx->freelist);

    LOG_NK_UINT("count", ctx->count);
    LOG_NK_UINT("seq", ctx->seq);

    if (ctx->pool.pages != NULL)
    {
        log_nk_page(ctx->pool.pages, "pool.pages[0]");
    }

    if (ctx->freelist != NULL)
    {
        log_nk_page_element(
            ctx->freelist,
            "context.freelist"
        );
    }

    /*
     * If the current context has a current panel, dump it as well.
     */
    if (ctx->current != NULL && ctx->current->layout != NULL)
    {
        log_nk_panel(ctx->current->layout);
    }

    log_info("Finished logging nk_context settings");
}


NK_INTERN void
nk_glfw3_log_pipeline_config(
    const struct nk_glfw_device *dev,
    const VkPipelineInputAssemblyStateCreateInfo *input_assembly_state,
    const VkPipelineRasterizationStateCreateInfo *rasterization_state,
    const VkPipelineColorBlendAttachmentState *attachment_state,
    const VkPipelineColorBlendStateCreateInfo *color_blend_state,
    const VkPipelineViewportStateCreateInfo *viewport_state,
    const VkPipelineMultisampleStateCreateInfo *multisample_state,
    const VkDynamicState *dynamic_states,
    const VkPipelineDynamicStateCreateInfo *dynamic_state,
    const VkPipelineShaderStageCreateInfo *shader_stages,
    const VkVertexInputBindingDescription *vertex_input_info,
    const VkVertexInputAttributeDescription *vertex_attributes,
    const VkPipelineVertexInputStateCreateInfo *vertex_input,
    const VkGraphicsPipelineCreateInfo *pipeline_info,
    VkResult result)
{
    uint32_t i;

    log_info("Graphics pipeline configuration:");

    LOG_VK_HANDLE("logical_device", dev->logical_device);
    LOG_VK_HANDLE("pipeline_layout", pipeline_info->layout);
    LOG_VK_HANDLE("render_pass", pipeline_info->renderPass);
    LOG_VK_HANDLE("pipeline", dev->pipeline);

    LOG_NK_STRUCT("input_assembly_state", *input_assembly_state);
    LOG_NK_INT("input_assembly.sType", input_assembly_state->sType);
    LOG_NK_INT("input_assembly.topology",
               input_assembly_state->topology);
    LOG_NK_INT("input_assembly.primitiveRestartEnable",
               input_assembly_state->primitiveRestartEnable);

    LOG_NK_STRUCT("rasterization_state", *rasterization_state);
    LOG_NK_INT("rasterization.sType", rasterization_state->sType);
    LOG_NK_FLAGS("rasterization.flags", rasterization_state->flags);
    LOG_NK_INT("rasterization.depthClampEnable",
               rasterization_state->depthClampEnable);
    LOG_NK_INT("rasterization.rasterizerDiscardEnable",
               rasterization_state->rasterizerDiscardEnable);
    LOG_NK_INT("rasterization.polygonMode",
               rasterization_state->polygonMode);
    LOG_NK_FLAGS("rasterization.cullMode",
                 rasterization_state->cullMode);
    LOG_NK_INT("rasterization.frontFace",
               rasterization_state->frontFace);
    LOG_NK_FLOAT("rasterization.lineWidth",
                 rasterization_state->lineWidth);

    LOG_NK_STRUCT("color_blend_attachment", *attachment_state);
    LOG_NK_INT("blend.blendEnable", attachment_state->blendEnable);
    LOG_NK_INT("blend.srcColorBlendFactor",
               attachment_state->srcColorBlendFactor);
    LOG_NK_INT("blend.dstColorBlendFactor",
               attachment_state->dstColorBlendFactor);
    LOG_NK_INT("blend.colorBlendOp", attachment_state->colorBlendOp);
    LOG_NK_INT("blend.srcAlphaBlendFactor",
               attachment_state->srcAlphaBlendFactor);
    LOG_NK_INT("blend.dstAlphaBlendFactor",
               attachment_state->dstAlphaBlendFactor);
    LOG_NK_INT("blend.alphaBlendOp", attachment_state->alphaBlendOp);
    LOG_NK_FLAGS("blend.colorWriteMask",
                 attachment_state->colorWriteMask);

    LOG_NK_STRUCT("color_blend_state", *color_blend_state);
    LOG_NK_INT("color_blend.sType", color_blend_state->sType);
    LOG_NK_FLAGS("color_blend.flags", color_blend_state->flags);
    LOG_NK_INT("color_blend.logicOpEnable",
               color_blend_state->logicOpEnable);
    LOG_NK_INT("color_blend.logicOp", color_blend_state->logicOp);
    LOG_NK_UINT("color_blend.attachmentCount",
                color_blend_state->attachmentCount);

    LOG_NK_STRUCT("viewport_state", *viewport_state);
    LOG_NK_INT("viewport_state.sType", viewport_state->sType);
    LOG_NK_UINT("viewport_state.viewportCount",
                viewport_state->viewportCount);
    LOG_NK_UINT("viewport_state.scissorCount",
                viewport_state->scissorCount);

    LOG_NK_STRUCT("multisample_state", *multisample_state);
    LOG_NK_INT("multisample.sType", multisample_state->sType);
    LOG_NK_INT("multisample.rasterizationSamples",
               multisample_state->rasterizationSamples);
    LOG_NK_INT("multisample.sampleShadingEnable",
               multisample_state->sampleShadingEnable);

    LOG_NK_STRUCT("dynamic_state", *dynamic_state);
    LOG_NK_INT("dynamic_state.sType", dynamic_state->sType);
    LOG_NK_UINT("dynamic_state.dynamicStateCount",
                dynamic_state->dynamicStateCount);

    for (i = 0; i < dynamic_state->dynamicStateCount; ++i)
    {
        log_info("  dynamic_states[%u]                 = %d",
                 i, dynamic_states[i]);
    }

    LOG_NK_STRUCT("vertex_input_binding", *vertex_input_info);
    LOG_NK_UINT("vertex_binding.binding", vertex_input_info->binding);
    LOG_NK_UINT("vertex_binding.stride", vertex_input_info->stride);
    LOG_NK_INT("vertex_binding.inputRate",
               vertex_input_info->inputRate);

    for (i = 0; i < 3; ++i)
    {
        log_info("Vertex attribute %u:", i);
        LOG_NK_UINT("  location", vertex_attributes[i].location);
        LOG_NK_UINT("  binding", vertex_attributes[i].binding);
        LOG_NK_INT("  format", vertex_attributes[i].format);
        LOG_NK_UINT("  offset", vertex_attributes[i].offset);
    }

    LOG_NK_STRUCT("vertex_input", *vertex_input);
    LOG_NK_INT("vertex_input.sType", vertex_input->sType);
    LOG_NK_UINT("vertex_input.vertexBindingDescriptionCount",
                vertex_input->vertexBindingDescriptionCount);
    LOG_NK_UINT("vertex_input.vertexAttributeDescriptionCount",
                vertex_input->vertexAttributeDescriptionCount);

    for (i = 0; i < pipeline_info->stageCount; ++i)
    {
        log_info("Shader stage %u:", i);
        LOG_NK_INT("  stage", shader_stages[i].stage);
        LOG_VK_HANDLE("  module", shader_stages[i].module);
        LOG_POINTER("  pName", shader_stages[i].pName);
    }

    LOG_NK_STRUCT("pipeline_info", *pipeline_info);
    LOG_NK_INT("pipeline_info.sType", pipeline_info->sType);
    LOG_NK_FLAGS("pipeline_info.flags", pipeline_info->flags);
    LOG_NK_UINT("pipeline_info.stageCount", pipeline_info->stageCount);
    LOG_VK_HANDLE("pipeline_info.layout", pipeline_info->layout);
    LOG_VK_HANDLE("pipeline_info.renderPass", pipeline_info->renderPass);
    LOG_NK_UINT("pipeline_info.subpass", pipeline_info->subpass);
    LOG_NK_INT("pipeline_info.basePipelineIndex",
               pipeline_info->basePipelineIndex);
    LOG_VK_HANDLE("pipeline_info.basePipelineHandle",
                  pipeline_info->basePipelineHandle);

    LOG_NK_INT("vkCreateGraphicsPipelines result", result);
}

NK_INTERN void
nk_glfw3_log_create_render_resources_config(
    const struct nk_glfw_device *dev,
    uint32_t framebuffer_width,
    uint32_t framebuffer_height)
{
    log_info("Create render resources configuration:");

    LOG_POINTER("dev", dev);
    LOG_UINT("framebuffer_width", framebuffer_width);
    LOG_UINT("framebuffer_height", framebuffer_height);
}

NK_INTERN void
nk_glfw3_log_device_create_config(
    VkDevice logical_device,
    VkPhysicalDevice physical_device,
    uint32_t graphics_queue_family_index,
    VkImageView *image_views,
    uint32_t image_views_len,
    VkFormat color_format,
    VkDeviceSize max_vertex_buffer,
    VkDeviceSize max_element_buffer,
    uint32_t framebuffer_width,
    uint32_t framebuffer_height)
{
    log_info("Vulkan device creation configuration:");

    LOG_VK_HANDLE("logical_device", logical_device);
    LOG_VK_HANDLE("physical_device", physical_device);
    LOG_UINT("graphics_queue_family_index",
             graphics_queue_family_index);
    LOG_POINTER("image_views", image_views);
    LOG_UINT("image_views_len", image_views_len);
    LOG_INT("color_format", color_format);
    LOG_NK_SIZE("max_vertex_buffer", max_vertex_buffer);
    LOG_NK_SIZE("max_element_buffer", max_element_buffer);
    LOG_UINT("framebuffer_width", framebuffer_width);
    LOG_UINT("framebuffer_height", framebuffer_height);
}

NK_INTERN void
nk_glfw3_log_device_upload_atlas_config(
    VkQueue graphics_queue,
    const void *image,
    int width,
    int height)
{
    log_info("Device atlas upload configuration:");

    LOG_VK_HANDLE("graphics_queue", graphics_queue);
    LOG_POINTER("image", (void *)image);
    LOG_INT("width", width);
    LOG_INT("height", height);
}
