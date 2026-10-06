/*
 * Nuklear - 1.32.0 - public domain
 * no warrenty implied; use at your own risk.
 * authored from 2015-2016 by Micha Mettke
 */
/*
 * ==============================================================
 *
 *                              API
 *
 * ===============================================================
 */
#ifndef NK_GLFW_VULKAN_H_
#define NK_GLFW_VULKAN_H_

unsigned char nuklearshaders_nuklear_vert_spv[] =
{
    0x03, 0x02, 0x23, 0x07, 0x00, 0x00, 0x01, 0x00, 0x0b, 0x00, 0x0d, 0x00,
    0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x02, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x47, 0x4c, 0x53, 0x4c, 0x2e, 0x73, 0x74, 0x64, 0x2e, 0x34, 0x35, 0x30,
    0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00,
    0x0a, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00,
    0x2a, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x03, 0x00, 0x02, 0x00, 0x00, 0x00, 0xc2, 0x01, 0x00, 0x00,
    0x04, 0x00, 0x09, 0x00, 0x47, 0x4c, 0x5f, 0x41, 0x52, 0x42, 0x5f, 0x73,
    0x65, 0x70, 0x61, 0x72, 0x61, 0x74, 0x65, 0x5f, 0x73, 0x68, 0x61, 0x64,
    0x65, 0x72, 0x5f, 0x6f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x73, 0x00, 0x00,
    0x04, 0x00, 0x0a, 0x00, 0x47, 0x4c, 0x5f, 0x47, 0x4f, 0x4f, 0x47, 0x4c,
    0x45, 0x5f, 0x63, 0x70, 0x70, 0x5f, 0x73, 0x74, 0x79, 0x6c, 0x65, 0x5f,
    0x6c, 0x69, 0x6e, 0x65, 0x5f, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x69,
    0x76, 0x65, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00, 0x47, 0x4c, 0x5f, 0x47,
    0x4f, 0x4f, 0x47, 0x4c, 0x45, 0x5f, 0x69, 0x6e, 0x63, 0x6c, 0x75, 0x64,
    0x65, 0x5f, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x69, 0x76, 0x65, 0x00,
    0x05, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e,
    0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x06, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x67, 0x6c, 0x5f, 0x50, 0x65, 0x72, 0x56, 0x65, 0x72, 0x74, 0x65, 0x78,
    0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x06, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x67, 0x6c, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74,
    0x69, 0x6f, 0x6e, 0x00, 0x05, 0x00, 0x03, 0x00, 0x0a, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x07, 0x00, 0x0e, 0x00, 0x00, 0x00,
    0x55, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x42, 0x75, 0x66, 0x66, 0x65,
    0x72, 0x4f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x00, 0x06, 0x00, 0x06, 0x00,
    0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x72, 0x6f, 0x6a,
    0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x00, 0x00, 0x05, 0x00, 0x03, 0x00,
    0x10, 0x00, 0x00, 0x00, 0x75, 0x62, 0x6f, 0x00, 0x05, 0x00, 0x05, 0x00,
    0x16, 0x00, 0x00, 0x00, 0x70, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e,
    0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x27, 0x00, 0x00, 0x00,
    0x66, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0x00, 0x00,
    0x05, 0x00, 0x04, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x63, 0x6f, 0x6c, 0x6f,
    0x72, 0x00, 0x00, 0x00, 0x05, 0x00, 0x04, 0x00, 0x42, 0x00, 0x00, 0x00,
    0x66, 0x72, 0x61, 0x67, 0x55, 0x76, 0x00, 0x00, 0x05, 0x00, 0x03, 0x00,
    0x43, 0x00, 0x00, 0x00, 0x75, 0x76, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x03, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00, 0x48, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00,
    0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 0x0e, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
    0x47, 0x00, 0x03, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x47, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00, 0x00,
    0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00,
    0x16, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x47, 0x00, 0x04, 0x00, 0x27, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x2a, 0x00, 0x00, 0x00,
    0x1e, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00,
    0x42, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x47, 0x00, 0x04, 0x00, 0x43, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x13, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x21, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x16, 0x00, 0x03, 0x00, 0x06, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x17, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x03, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x15, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x04, 0x00,
    0x0d, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x1e, 0x00, 0x03, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x04, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x0e, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x0f, 0x00, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00,
    0x11, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00,
    0x17, 0x00, 0x04, 0x00, 0x14, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x15, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00,
    0x15, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x2b, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0x20, 0x00, 0x04, 0x00,
    0x1e, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
    0x15, 0x00, 0x04, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x21, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00,
    0x22, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x3b, 0x00, 0x04, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x28, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00,
    0x29, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
    0x3b, 0x00, 0x04, 0x00, 0x29, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x2b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00,
    0x2c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x2b, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x7f, 0x43, 0x2b, 0x00, 0x04, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x36, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x04, 0x00, 0x41, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x14, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x41, 0x00, 0x00, 0x00,
    0x42, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00,
    0x15, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x36, 0x00, 0x05, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x02, 0x00,
    0x05, 0x00, 0x00, 0x00, 0x41, 0x00, 0x05, 0x00, 0x11, 0x00, 0x00, 0x00,
    0x12, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x3d, 0x00, 0x04, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00,
    0x12, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x14, 0x00, 0x00, 0x00,
    0x17, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x51, 0x00, 0x05, 0x00,
    0x06, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x1b, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x50, 0x00, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
    0x1a, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
    0x19, 0x00, 0x00, 0x00, 0x91, 0x00, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00,
    0x1d, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
    0x41, 0x00, 0x05, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00,
    0x0a, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00,
    0x1f, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00,
    0x22, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00,
    0x06, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00,
    0x7f, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00,
    0x24, 0x00, 0x00, 0x00, 0x41, 0x00, 0x06, 0x00, 0x22, 0x00, 0x00, 0x00,
    0x26, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x21, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 0x26, 0x00, 0x00, 0x00,
    0x25, 0x00, 0x00, 0x00, 0x41, 0x00, 0x05, 0x00, 0x2c, 0x00, 0x00, 0x00,
    0x2d, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x00, 0x00,
    0x3d, 0x00, 0x04, 0x00, 0x20, 0x00, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x00,
    0x2d, 0x00, 0x00, 0x00, 0x70, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x2f, 0x00, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x00, 0x88, 0x00, 0x05, 0x00,
    0x06, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x2f, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x41, 0x00, 0x05, 0x00, 0x2c, 0x00, 0x00, 0x00,
    0x32, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00,
    0x3d, 0x00, 0x04, 0x00, 0x20, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00,
    0x32, 0x00, 0x00, 0x00, 0x70, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x34, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x88, 0x00, 0x05, 0x00,
    0x06, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x41, 0x00, 0x05, 0x00, 0x2c, 0x00, 0x00, 0x00,
    0x37, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00,
    0x3d, 0x00, 0x04, 0x00, 0x20, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00,
    0x37, 0x00, 0x00, 0x00, 0x70, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x39, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x88, 0x00, 0x05, 0x00,
    0x06, 0x00, 0x00, 0x00, 0x3a, 0x00, 0x00, 0x00, 0x39, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x41, 0x00, 0x05, 0x00, 0x2c, 0x00, 0x00, 0x00,
    0x3c, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x00, 0x00,
    0x3d, 0x00, 0x04, 0x00, 0x20, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x00, 0x00,
    0x3c, 0x00, 0x00, 0x00, 0x70, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x3e, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x00, 0x00, 0x88, 0x00, 0x05, 0x00,
    0x06, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x50, 0x00, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00,
    0x3a, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00,
    0x27, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00,
    0x14, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00,
    0x3e, 0x00, 0x03, 0x00, 0x42, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00,
    0xfd, 0x00, 0x01, 0x00, 0x38, 0x00, 0x01, 0x00
};
unsigned int nuklearshaders_nuklear_vert_spv_len = 1856;
unsigned char nuklearshaders_nuklear_frag_spv[] =
{
    0x03, 0x02, 0x23, 0x07, 0x00, 0x00, 0x01, 0x00, 0x0b, 0x00, 0x0d, 0x00,
    0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x02, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x47, 0x4c, 0x53, 0x4c, 0x2e, 0x73, 0x74, 0x64, 0x2e, 0x34, 0x35, 0x30,
    0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x08, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00,
    0x11, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00,
    0x10, 0x00, 0x03, 0x00, 0x04, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x03, 0x00, 0x02, 0x00, 0x00, 0x00, 0xc2, 0x01, 0x00, 0x00,
    0x04, 0x00, 0x09, 0x00, 0x47, 0x4c, 0x5f, 0x41, 0x52, 0x42, 0x5f, 0x73,
    0x65, 0x70, 0x61, 0x72, 0x61, 0x74, 0x65, 0x5f, 0x73, 0x68, 0x61, 0x64,
    0x65, 0x72, 0x5f, 0x6f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x73, 0x00, 0x00,
    0x04, 0x00, 0x0a, 0x00, 0x47, 0x4c, 0x5f, 0x47, 0x4f, 0x4f, 0x47, 0x4c,
    0x45, 0x5f, 0x63, 0x70, 0x70, 0x5f, 0x73, 0x74, 0x79, 0x6c, 0x65, 0x5f,
    0x6c, 0x69, 0x6e, 0x65, 0x5f, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x69,
    0x76, 0x65, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00, 0x47, 0x4c, 0x5f, 0x47,
    0x4f, 0x4f, 0x47, 0x4c, 0x45, 0x5f, 0x69, 0x6e, 0x63, 0x6c, 0x75, 0x64,
    0x65, 0x5f, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x69, 0x76, 0x65, 0x00,
    0x05, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e,
    0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0x00, 0x00, 0x00,
    0x05, 0x00, 0x06, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x63, 0x75, 0x72, 0x72,
    0x65, 0x6e, 0x74, 0x54, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x00, 0x00,
    0x05, 0x00, 0x04, 0x00, 0x11, 0x00, 0x00, 0x00, 0x66, 0x72, 0x61, 0x67,
    0x55, 0x76, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 0x15, 0x00, 0x00, 0x00,
    0x6f, 0x75, 0x74, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0x00, 0x00, 0x00,
    0x05, 0x00, 0x05, 0x00, 0x17, 0x00, 0x00, 0x00, 0x66, 0x72, 0x61, 0x67,
    0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00,
    0x0d, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x47, 0x00, 0x04, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 0x11, 0x00, 0x00, 0x00,
    0x1e, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00,
    0x15, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x47, 0x00, 0x04, 0x00, 0x17, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x13, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x21, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x16, 0x00, 0x03, 0x00, 0x06, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x17, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x19, 0x00, 0x09, 0x00,
    0x0a, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x00, 0x03, 0x00,
    0x0b, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0x3b, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 0x0f, 0x00, 0x00, 0x00,
    0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00,
    0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
    0x3b, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x14, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00,
    0x14, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x04, 0x00, 0x16, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 0x16, 0x00, 0x00, 0x00,
    0x17, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x36, 0x00, 0x05, 0x00,
    0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x02, 0x00, 0x05, 0x00, 0x00, 0x00,
    0x3b, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0x0e, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00,
    0x0f, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00,
    0x57, 0x00, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00,
    0x0e, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00,
    0x07, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00,
    0x3d, 0x00, 0x04, 0x00, 0x07, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x85, 0x00, 0x05, 0x00, 0x07, 0x00, 0x00, 0x00,
    0x1a, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00,
    0x3e, 0x00, 0x03, 0x00, 0x15, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x00, 0x00,
    0xfd, 0x00, 0x01, 0x00, 0x38, 0x00, 0x01, 0x00
};
unsigned int nuklearshaders_nuklear_frag_spv_len = 860;

#include <assert.h>
#include <stddef.h>
#include <string.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

enum nk_glfw_init_state { NK_GLFW3_DEFAULT = 0, NK_GLFW3_INSTALL_CALLBACKS };

NK_API struct nk_context *
nk_glfw3_init(GLFWwindow *win, VkDevice logical_device,
              VkPhysicalDevice physical_device,
              uint32_t graphics_queue_family_index, VkImageView *image_views,
              uint32_t image_views_len, VkFormat color_format,
              enum nk_glfw_init_state init_state,
              VkDeviceSize max_vertex_buffer, VkDeviceSize max_element_buffer);
NK_API void nk_glfw3_shutdown(void);
NK_API void nk_glfw3_font_stash_begin(struct nk_font_atlas **atlas);
NK_API void nk_glfw3_font_stash_end(VkQueue graphics_queue);
NK_API void nk_glfw3_new_frame();
NK_API VkSemaphore nk_glfw3_render(VkQueue graphics_queue,
                                   uint32_t buffer_index,
                                   VkSemaphore wait_semaphore,
                                   enum nk_anti_aliasing AA);
NK_API void nk_glfw3_resize(uint32_t framebuffer_width,
                            uint32_t framebuffer_height);
NK_API void nk_glfw3_device_destroy(void);
NK_API void nk_glfw3_device_create(
    VkDevice logical_device, VkPhysicalDevice physical_device,
    uint32_t graphics_queue_family_index, VkImageView *image_views,
    uint32_t image_views_len, VkFormat color_format,
    VkDeviceSize max_vertex_buffer, VkDeviceSize max_element_buffer,
    uint32_t framebuffer_width, uint32_t framebuffer_height);

NK_API void nk_glfw3_char_callback(GLFWwindow *win, unsigned int codepoint);
NK_API void nk_glfw3_key_callback(GLFWwindow *win, int key, int scancode, int action, int mods);
NK_API void nk_glfw3_scroll_callback(GLFWwindow *win, double xoff, double yoff);
NK_API void nk_glfw3_mouse_button_callback(GLFWwindow *win, int button,
        int action, int mods);

#endif
/*
 * ==============================================================
 *
 *                          IMPLEMENTATION
 *
 * ===============================================================
 */
#ifdef NK_GLFW_VULKAN_IMPLEMENTATION
#undef NK_GLFW_VULKAN_IMPLEMENTATION
#include <stdlib.h>

#ifndef NK_GLFW_TEXT_MAX
#define NK_GLFW_TEXT_MAX 256
#endif
#ifndef NK_GLFW_DOUBLE_CLICK_LO
#define NK_GLFW_DOUBLE_CLICK_LO 0.02
#endif
#ifndef NK_GLFW_DOUBLE_CLICK_HI
#define NK_GLFW_DOUBLE_CLICK_HI 0.2
#endif
#ifndef NK_GLFW_MAX_TEXTURES
#define NK_GLFW_MAX_TEXTURES 256
#endif

#define VK_COLOR_COMPONENT_MASK_RGBA                                           \
    VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |                      \
        VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT

struct nk_glfw_vertex
{
    float position[2];
    float uv[2];
    nk_byte col[4];
};

struct nk_vulkan_texture_descriptor_set
{
    VkImageView image_view;
    VkDescriptorSet descriptor_set;
};

struct nk_glfw_device
{
    struct nk_buffer cmds;
    struct nk_draw_null_texture tex_null;
    int max_vertex_buffer;
    int max_element_buffer;
    VkDevice logical_device;
    VkPhysicalDevice physical_device;
    VkImageView *image_views;
    uint32_t image_views_len;
    VkFormat color_format;
    VkFramebuffer *framebuffers;
    uint32_t framebuffers_len;
    VkCommandBuffer *command_buffers;
    uint32_t command_buffers_len;
    VkSampler sampler;
    VkCommandPool command_pool;
    VkSemaphore render_completed;
    VkBuffer vertex_buffer;
    VkDeviceMemory vertex_memory;
    void *mapped_vertex;
    VkBuffer index_buffer;
    VkDeviceMemory index_memory;
    void *mapped_index;
    VkBuffer uniform_buffer;
    VkDeviceMemory uniform_memory;
    void *mapped_uniform;
    VkRenderPass render_pass;
    VkDescriptorPool descriptor_pool;
    VkDescriptorSetLayout uniform_descriptor_set_layout;
    VkDescriptorSet uniform_descriptor_set;
    VkDescriptorSetLayout texture_descriptor_set_layout;
    struct nk_vulkan_texture_descriptor_set *texture_descriptor_sets;
    uint32_t texture_descriptor_sets_len;
    VkPipelineLayout pipeline_layout;
    VkPipeline pipeline;
    VkImage font_image;
    VkImageView font_image_view;
    VkDeviceMemory font_memory;
};

static struct nk_glfw
{
    GLFWwindow *win;
    int width, height;
    int display_width, display_height;
    struct nk_glfw_device vulkan;
    struct nk_context ctx;
    struct nk_font_atlas atlas;
    struct nk_vec2 fb_scale;
    unsigned int text[NK_GLFW_TEXT_MAX];
    nk_char key_events[NK_KEY_MAX];
    int text_len;
    struct nk_vec2 scroll;
    double last_button_click;
    int is_double_click_down;
    struct nk_vec2 double_click_pos;
    float delta_time_seconds_last;
} glfw;

struct Mat4f
{
    float m[16];
};

void
log_nk_vulkan_texture_descriptor_sets(
    const struct nk_glfw_device *device
)
{
    if (device == NULL) {
        log_error("nk_glfw_device is NULL");
        return;
    }

    if (device->texture_descriptor_sets == NULL) {
        log_info("texture_descriptor_sets = NULL");
        return;
    }

    log_info(
        "texture descriptor sets: count=%" PRIu32,
        device->texture_descriptor_sets_len
    );

    for (uint32_t i = 0;
         i < device->texture_descriptor_sets_len;
         ++i) {
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


void
log_nk_glfw_device_settings(const struct nk_glfw_device *device)
{
    if (device == NULL) {
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

NK_INTERN void
nk_glfw3_log_find_memory_index_config(
    VkPhysicalDevice physical_device,
    uint32_t type_filter,
    VkMemoryPropertyFlags properties,
    unsigned int i)
{
    log_info("Find memory index configuration:");

    LOG_VK_HANDLE("physical_device", physical_device);
    LOG_UINT("type_filter", type_filter);

    LOG_NK_FLAGS("properties", properties);
    LOG_UINT("returned int:", i);
}


NK_INTERN uint32_t nk_glfw3_find_memory_index(
    VkPhysicalDevice physical_device, uint32_t type_filter,
    VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties mem_properties;
    uint32_t i;

    vkGetPhysicalDeviceMemoryProperties(physical_device, &mem_properties);
    for (i = 0; i < mem_properties.memoryTypeCount; i++)
    {
        if ((type_filter & (1 << i)) &&
                (mem_properties.memoryTypes[i].propertyFlags & properties) == properties)
        {
            // debug only output when found
#ifndef NDEBUG
            nk_glfw3_log_find_memory_index_config(
                physical_device,
                type_filter,
                properties,
                i
            );
#endif
            return i;
        }
    }


    assert(0);
    return 0;
}


static void
log_vk_sampler_create_info(const VkSamplerCreateInfo *info)
{
    if (info == NULL)
    {
        log_info("VkSamplerCreateInfo = NULL");
        return;
    }

    log_info("VkSamplerCreateInfo:");

    LOG_NK_INT("sType", info->sType);
    LOG_NK_POINTER("pNext", info->pNext);
    LOG_NK_FLAGS("flags", info->flags);

    LOG_NK_INT("magFilter", info->magFilter);
    LOG_NK_INT("minFilter", info->minFilter);
    LOG_NK_INT("mipmapMode", info->mipmapMode);

    LOG_NK_INT("addressModeU", info->addressModeU);
    LOG_NK_INT("addressModeV", info->addressModeV);
    LOG_NK_INT("addressModeW", info->addressModeW);

    LOG_NK_FLOAT("mipLodBias", info->mipLodBias);
    LOG_NK_UINT("anisotropyEnable", info->anisotropyEnable);
    LOG_NK_FLOAT("maxAnisotropy", info->maxAnisotropy);

    LOG_NK_UINT("compareEnable", info->compareEnable);
    LOG_NK_INT("compareOp", info->compareOp);

    LOG_NK_FLOAT("minLod", info->minLod);
    LOG_NK_FLOAT("maxLod", info->maxLod);

    LOG_NK_INT("borderColor", info->borderColor);
    LOG_NK_UINT("unnormalizedCoordinates", info->unnormalizedCoordinates);
}

NK_INTERN void nk_glfw3_create_sampler(struct nk_glfw_device *dev)
{
    VkResult result;
    VkSamplerCreateInfo sampler_info;
    memset(&sampler_info, 0, sizeof(VkSamplerCreateInfo));

    sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    sampler_info.pNext = NULL;
    sampler_info.maxAnisotropy = 1.0;
    sampler_info.magFilter = VK_FILTER_LINEAR;
    sampler_info.minFilter = VK_FILTER_LINEAR;
    sampler_info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sampler_info.mipLodBias = 0.0f;
    sampler_info.compareEnable = VK_FALSE;
    sampler_info.compareOp = VK_COMPARE_OP_ALWAYS;
    sampler_info.minLod = 0.0f;
    sampler_info.maxLod = 0.0f;
    sampler_info.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK;

    result = vkCreateSampler(dev->logical_device, &sampler_info, NULL, &dev->sampler);
#ifndef NDEBUG
    log_vk_sampler_create_info(&sampler_info);
#endif

    NK_ASSERT(result == VK_SUCCESS);
}


static void
log_vk_command_pool_create_info(const VkCommandPoolCreateInfo *info)
{
    if (info == NULL)
    {
        log_info("VkCommandPoolCreateInfo = NULL");
        return;
    }

    log_info("VkCommandPoolCreateInfo:");

    LOG_NK_INT("sType", info->sType);
    LOG_NK_POINTER("pNext", info->pNext);
    LOG_NK_FLAGS("flags", info->flags);
    LOG_NK_UINT("queueFamilyIndex", info->queueFamilyIndex);
}


NK_INTERN void
nk_glfw3_create_command_pool(struct nk_glfw_device *dev,
                             uint32_t graphics_queue_family_index)
{
    VkResult result;
    VkCommandPoolCreateInfo pool_info;
    memset(&pool_info, 0, sizeof(VkCommandPoolCreateInfo));

    pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    pool_info.queueFamilyIndex = graphics_queue_family_index;
    pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    result = vkCreateCommandPool(dev->logical_device, &pool_info, NULL,
                                 &dev->command_pool);

#ifndef NDEBUG
    log_vk_command_pool_create_info(&pool_info);
#endif

    NK_ASSERT(result == VK_SUCCESS);
}


static void
log_vk_command_buffer_allocate_info(
    const VkCommandBufferAllocateInfo *info
)
{
    if (info == NULL)
    {
        log_info("VkCommandBufferAllocateInfo = NULL");
        return;
    }

    log_info("VkCommandBufferAllocateInfo:");

    LOG_NK_INT("sType", info->sType);
    LOG_NK_POINTER("pNext", info->pNext);
    LOG_VK_HANDLE("commandPool", info->commandPool);
    LOG_NK_INT("level", info->level);
    LOG_NK_UINT("commandBufferCount", info->commandBufferCount);
}


NK_INTERN void nk_glfw3_create_command_buffers(struct nk_glfw_device *dev)
{
    VkResult result;
    VkCommandBufferAllocateInfo allocate_info;
    memset(&allocate_info, 0, sizeof(VkCommandBufferAllocateInfo));

    dev->command_buffers = (VkCommandBuffer *)malloc(dev->image_views_len * sizeof(VkCommandBuffer));
    dev->command_buffers_len = dev->image_views_len;

    allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocate_info.commandPool = dev->command_pool;
    allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocate_info.commandBufferCount = dev->command_buffers_len;

    result = vkAllocateCommandBuffers(dev->logical_device, &allocate_info, dev->command_buffers);

#ifndef NDEBUG
    log_vk_command_buffer_allocate_info(&allocate_info);
#endif

    NK_ASSERT(result == VK_SUCCESS);
}



static void
log_vk_semaphore_create_info(const VkSemaphoreCreateInfo *info)
{
    if (info == NULL)
    {
        log_info("VkSemaphoreCreateInfo = NULL");
        return;
    }

    log_info("VkSemaphoreCreateInfo:");

    LOG_NK_INT("sType", info->sType);
    LOG_NK_POINTER("pNext", info->pNext);
    LOG_NK_FLAGS("flags", info->flags);
}


NK_INTERN void nk_glfw3_create_semaphore(struct nk_glfw_device *dev)
{
    VkResult result;
    VkSemaphoreCreateInfo semaphore_info;
    memset(&semaphore_info, 0, sizeof(VkSemaphoreCreateInfo));

    semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    result = (vkCreateSemaphore(dev->logical_device, &semaphore_info, NULL,
                                &dev->render_completed));
				
    #ifndef NDEBUG
    log_vk_semaphore_create_info(&semaphore_info);    
    #endif
    
    NK_ASSERT(result == VK_SUCCESS);
}


static void
log_vk_buffer_create_info(const VkBufferCreateInfo *info)
{
    if (info == NULL)
    {
        log_info("VkBufferCreateInfo = NULL");
        return;
    }

    log_info("VkBufferCreateInfo:");

    LOG_NK_INT("sType", info->sType);
    LOG_NK_POINTER("pNext", info->pNext);
    LOG_NK_FLAGS("flags", info->flags);
    LOG_NK_SIZE("size", info->size);
    LOG_NK_FLAGS("usage", info->usage);
    LOG_NK_INT("sharingMode", info->sharingMode);
    LOG_NK_UINT("queueFamilyIndexCount",
                info->queueFamilyIndexCount);
    LOG_NK_POINTER("pQueueFamilyIndices",
                   info->pQueueFamilyIndices);
}

static void
log_vk_memory_allocate_info(const VkMemoryAllocateInfo *info)
{
    if (info == NULL) {
        log_info("VkMemoryAllocateInfo = NULL");
        return;
    }

    log_info("VkMemoryAllocateInfo:");

    LOG_NK_INT("sType", info->sType);
    LOG_NK_POINTER("pNext", info->pNext);
    LOG_NK_SIZE("allocationSize", info->allocationSize);
    LOG_NK_UINT("memoryTypeIndex", info->memoryTypeIndex);
}

static void
log_vk_memory_requirements(const VkMemoryRequirements *reqs)
{
    if (reqs == NULL) {
        log_info("VkMemoryRequirements = NULL");
        return;
    }

    log_info("VkMemoryRequirements:");

    LOG_NK_SIZE("size", reqs->size);
    LOG_NK_SIZE("alignment", reqs->alignment);
    LOG_NK_UINT("memoryTypeBits", reqs->memoryTypeBits);
}


NK_INTERN void nk_glfw3_create_buffer_and_memory(struct nk_glfw_device *dev,
        VkBuffer *buffer,
        VkBufferUsageFlags usage,
        VkDeviceMemory *memory,
        VkDeviceSize size)
{
    VkMemoryRequirements mem_reqs;
    VkResult result;
    VkBufferCreateInfo buffer_info;
    VkMemoryAllocateInfo alloc_info;

    memset(&buffer_info, 0, sizeof(VkBufferCreateInfo));
    buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    buffer_info.pNext = NULL;
    buffer_info.flags = 0;    
    buffer_info.size = size;
    buffer_info.usage = usage;
    buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    buffer_info.queueFamilyIndexCount = 0;
    buffer_info.pQueueFamilyIndices = NULL;    

    #ifndef NDEBUG
    log_vk_buffer_create_info(&buffer_info);    
    #endif

    result = vkCreateBuffer(dev->logical_device, &buffer_info, NULL, buffer);
    
    #ifndef NDEBUG
    LOG_VK_HANDLE("buffer", *buffer);
    #endif
	
    NK_ASSERT(result == VK_SUCCESS);

    vkGetBufferMemoryRequirements(dev->logical_device, *buffer, &mem_reqs);
    
    #ifndef NDEBUG
    log_vk_memory_requirements(&mem_reqs);
    #endif

    memset(&alloc_info, 0, sizeof(VkMemoryAllocateInfo));
    alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    alloc_info.pNext = NULL;
    alloc_info.allocationSize = mem_reqs.size;
    alloc_info.memoryTypeIndex = nk_glfw3_find_memory_index(
                                     dev->physical_device, mem_reqs.memoryTypeBits,
                                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                     VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    #ifndef NDEBUG
    log_vk_memory_allocate_info(&alloc_info);
    #endif

    result = vkAllocateMemory(dev->logical_device, &alloc_info, NULL, memory);
    NK_ASSERT(result == VK_SUCCESS);
    result = vkBindBufferMemory(dev->logical_device, *buffer, *memory, 0);
    
    
    NK_ASSERT(result == VK_SUCCESS);
}



static void
log_vk_attachment_description(const VkAttachmentDescription *attachment)
{
    if (attachment == NULL) {
        log_info("VkAttachmentDescription = NULL");
        return;
    }

    log_info("VkAttachmentDescription:");

    LOG_NK_FLAGS("flags", attachment->flags);
    LOG_NK_INT("format", attachment->format);
    LOG_NK_INT("samples", attachment->samples);
    LOG_NK_INT("loadOp", attachment->loadOp);
    LOG_NK_INT("storeOp", attachment->storeOp);
    LOG_NK_INT("stencilLoadOp", attachment->stencilLoadOp);
    LOG_NK_INT("stencilStoreOp", attachment->stencilStoreOp);
    LOG_NK_INT("initialLayout", attachment->initialLayout);
    LOG_NK_INT("finalLayout", attachment->finalLayout);
}

static void
log_vk_attachment_reference(const VkAttachmentReference *reference)
{
    if (reference == NULL) {
        log_info("VkAttachmentReference = NULL");
        return;
    }

    log_info("VkAttachmentReference:");

    LOG_NK_UINT("attachment", reference->attachment);
    LOG_NK_INT("layout", reference->layout);
}

static void
log_vk_subpass_dependency(const VkSubpassDependency *dependency)
{
    if (dependency == NULL) {
        log_info("VkSubpassDependency = NULL");
        return;
    }

    log_info("VkSubpassDependency:");

    LOG_NK_UINT("srcSubpass", dependency->srcSubpass);
    LOG_NK_UINT("dstSubpass", dependency->dstSubpass);
    LOG_NK_FLAGS("srcStageMask", dependency->srcStageMask);
    LOG_NK_FLAGS("dstStageMask", dependency->dstStageMask);
    LOG_NK_FLAGS("srcAccessMask", dependency->srcAccessMask);
    LOG_NK_FLAGS("dstAccessMask", dependency->dstAccessMask);
    LOG_NK_FLAGS("dependencyFlags", dependency->dependencyFlags);
}

static void
log_vk_subpass_description(const VkSubpassDescription *subpass)
{
    if (subpass == NULL) {
        log_info("VkSubpassDescription = NULL");
        return;
    }

    log_info("VkSubpassDescription:");

    LOG_NK_FLAGS("flags", subpass->flags);
    LOG_NK_INT("pipelineBindPoint", subpass->pipelineBindPoint);

    LOG_NK_UINT("inputAttachmentCount",
                subpass->inputAttachmentCount);
    LOG_NK_POINTER("pInputAttachments",
                   subpass->pInputAttachments);

    LOG_NK_UINT("colorAttachmentCount",
                subpass->colorAttachmentCount);
    LOG_NK_POINTER("pColorAttachments",
                   subpass->pColorAttachments);

    LOG_NK_POINTER("pResolveAttachments",
                   subpass->pResolveAttachments);

    LOG_NK_POINTER("pDepthStencilAttachment",
                   subpass->pDepthStencilAttachment);

    LOG_NK_UINT("preserveAttachmentCount",
                subpass->preserveAttachmentCount);
    LOG_NK_POINTER("pPreserveAttachments",
                   subpass->pPreserveAttachments);
}

static void
log_vk_render_pass_create_info(const VkRenderPassCreateInfo *info)
{
    if (info == NULL) {
        log_info("VkRenderPassCreateInfo = NULL");
        return;
    }

    log_info("VkRenderPassCreateInfo:");

    LOG_NK_INT("sType", info->sType);
    LOG_NK_POINTER("pNext", info->pNext);
    LOG_NK_FLAGS("flags", info->flags);

    LOG_NK_UINT("attachmentCount", info->attachmentCount);
    LOG_NK_POINTER("pAttachments", info->pAttachments);

    LOG_NK_UINT("subpassCount", info->subpassCount);
    LOG_NK_POINTER("pSubpasses", info->pSubpasses);

    LOG_NK_UINT("dependencyCount", info->dependencyCount);
    LOG_NK_POINTER("pDependencies", info->pDependencies);
}


NK_INTERN void nk_glfw3_create_render_pass(struct nk_glfw_device *dev)
{
    VkAttachmentDescription attachment;
    VkAttachmentReference color_reference;
    VkSubpassDependency subpass_dependency;
    VkSubpassDescription subpass_description;
    VkRenderPassCreateInfo render_pass_info;
    VkResult result;

    memset(&attachment, 0, sizeof(VkAttachmentDescription));
    attachment.format = dev->color_format;
    attachment.samples = VK_SAMPLE_COUNT_1_BIT;
    attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachment.finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    memset(&color_reference, 0, sizeof(VkAttachmentReference));
    color_reference.attachment = 0;
    color_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    memset(&subpass_dependency, 0, sizeof(VkSubpassDependency));
    subpass_dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    subpass_dependency.srcAccessMask = 0;
    subpass_dependency.srcStageMask =
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpass_dependency.dstSubpass = 0;
    subpass_dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT |
                                       VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    subpass_dependency.dstStageMask =
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

    memset(&subpass_description, 0, sizeof(VkSubpassDescription));
    subpass_description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass_description.colorAttachmentCount = 1;
    subpass_description.pColorAttachments = &color_reference;

    memset(&render_pass_info, 0, sizeof(VkRenderPassCreateInfo));
    render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    render_pass_info.attachmentCount = 1;
    render_pass_info.pAttachments = &attachment;
    render_pass_info.subpassCount = 1;
    render_pass_info.pSubpasses = &subpass_description;
    render_pass_info.dependencyCount = 1;
    render_pass_info.pDependencies = &subpass_dependency;
    
    #ifndef NDEBUG
    log_vk_attachment_description(&attachment);
    log_vk_attachment_reference(&color_reference);
    log_vk_subpass_dependency(&subpass_dependency);
    log_vk_subpass_description(&subpass_description);
    log_vk_render_pass_create_info(&render_pass_info);    
    #endif

    result = vkCreateRenderPass(dev->logical_device, &render_pass_info, NULL,
                                &dev->render_pass);
    NK_ASSERT(result == VK_SUCCESS);
}

static void
log_vk_framebuffer_create_info(
    const VkFramebufferCreateInfo *info
)
{
    if (info == NULL) {
        log_info("VkFramebufferCreateInfo = NULL");
        return;
    }

    log_info("VkFramebufferCreateInfo:");

    LOG_NK_INT("sType", info->sType);
    LOG_NK_POINTER("pNext", info->pNext);
    LOG_NK_FLAGS("flags", info->flags);

    LOG_VK_HANDLE("renderPass", info->renderPass);

    LOG_NK_UINT("attachmentCount", info->attachmentCount);
    LOG_NK_POINTER("pAttachments", info->pAttachments);

    LOG_NK_UINT("width", info->width);
    LOG_NK_UINT("height", info->height);
    LOG_NK_UINT("layers", info->layers);

    if (info->pAttachments != NULL) {
        LOG_VK_HANDLE("attachment[0]", info->pAttachments[0]);
    }
}


NK_INTERN void nk_glfw3_create_framebuffers(struct nk_glfw_device *dev,
        uint32_t framebuffer_width,
        uint32_t framebuffer_height)
{

    VkFramebufferCreateInfo framebuffer_create_info;
    uint32_t i;
    VkResult result;

    dev->framebuffers = (VkFramebuffer *)malloc(dev->image_views_len * sizeof(VkFramebuffer));

    memset(&framebuffer_create_info, 0, sizeof(VkFramebufferCreateInfo));
    framebuffer_create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebuffer_create_info.renderPass = dev->render_pass;
    framebuffer_create_info.attachmentCount = 1;
    framebuffer_create_info.width = framebuffer_width;
    framebuffer_create_info.height = framebuffer_height;
    framebuffer_create_info.layers = 1;
    for (i = 0; i < dev->image_views_len; i++)
    {
	#ifndef NDEBUG
	log_info("Creating framebuffer[%u]", i);
        log_vk_framebuffer_create_info(&framebuffer_create_info);
	#endif
	
        framebuffer_create_info.pAttachments = &dev->image_views[i];
        result = vkCreateFramebuffer(dev->logical_device, &framebuffer_create_info,
                                NULL, &dev->framebuffers[i]);
	#ifndef ndebug
	LOG_VK_HANDLE("framebuffer", dev->framebuffers[i]);
	#endif
        NK_ASSERT(result == VK_SUCCESS);
    }
    dev->framebuffers_len = dev->image_views_len;
}


static const char *
vk_descriptor_type_name(VkDescriptorType type)
{
    switch (type)
    {
    case VK_DESCRIPTOR_TYPE_SAMPLER:
        return "VK_DESCRIPTOR_TYPE_SAMPLER";
    case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
        return "VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER";
    case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
        return "VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE";
    case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
        return "VK_DESCRIPTOR_TYPE_STORAGE_IMAGE";
    case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:
        return "VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER";
    case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER:
        return "VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER";
    case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
        return "VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER";
    case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
        return "VK_DESCRIPTOR_TYPE_STORAGE_BUFFER";
    case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:
        return "VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC";
    case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC:
        return "VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC";
    case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
        return "VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT";
    default:
        return "VK_DESCRIPTOR_TYPE_UNKNOWN";
    }
}

static void
log_vk_descriptor_pool_size(
    const VkDescriptorPoolSize *pool_size,
    uint32_t index
)
{
    if (pool_size == NULL) {
        log_info("VkDescriptorPoolSize[%u] = NULL", index);
        return;
    }

    log_info("VkDescriptorPoolSize[%u]:", index);

    log_info("  %-32s = %s",
             "type",
             vk_descriptor_type_name(pool_size->type));

    LOG_NK_INT("type value", pool_size->type);
    LOG_NK_UINT("descriptorCount", pool_size->descriptorCount);
}

static void
log_vk_descriptor_pool_create_info(
    const VkDescriptorPoolCreateInfo *info
)
{
    uint32_t i;

    if (info == NULL) {
        log_info("VkDescriptorPoolCreateInfo = NULL");
        return;
    }

    log_info("VkDescriptorPoolCreateInfo:");

    LOG_NK_INT("sType", info->sType);
    LOG_NK_POINTER("pNext", info->pNext);
    LOG_NK_FLAGS("flags", info->flags);
    LOG_NK_UINT("maxSets", info->maxSets);
    LOG_NK_UINT("poolSizeCount", info->poolSizeCount);
    LOG_NK_POINTER("pPoolSizes", info->pPoolSizes);

    for (i = 0; i < info->poolSizeCount; i++) {
        log_vk_descriptor_pool_size(&info->pPoolSizes[i], i);
    }
}


NK_INTERN void nk_glfw3_create_descriptor_pool(struct nk_glfw_device *dev)
{
    VkDescriptorPoolSize pool_sizes[2];
    VkDescriptorPoolCreateInfo pool_info;
    VkResult result;

    memset(&pool_sizes, 0, sizeof(VkDescriptorPoolSize) * 2);
    pool_sizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    pool_sizes[0].descriptorCount = 1;
    pool_sizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    pool_sizes[1].descriptorCount = NK_GLFW_MAX_TEXTURES;

    memset(&pool_info, 0, sizeof(VkDescriptorPoolCreateInfo));
    pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    pool_info.poolSizeCount = 2;
    pool_info.pPoolSizes = pool_sizes;
    pool_info.maxSets = 1 + NK_GLFW_MAX_TEXTURES;

    #ifndef NDEBUG
    log_vk_descriptor_pool_create_info(&pool_info);    
    #endif
    
    result = vkCreateDescriptorPool(dev->logical_device, &pool_info, NULL,
                                    &dev->descriptor_pool);
    NK_ASSERT(result == VK_SUCCESS);
}

NK_INTERN void
nk_glfw3_log_uniform_descriptor_set_layout_config(
    const struct nk_glfw_device *dev,
    const VkDescriptorSetLayoutBinding *binding,
    const VkDescriptorSetLayoutCreateInfo *descriptor_set_info,
    VkResult result)
{
    log_info("Uniform descriptor set layout configuration:");

    LOG_VK_HANDLE("logical_device", dev->logical_device);
    LOG_VK_HANDLE("uniform_descriptor_set_layout",
                  dev->uniform_descriptor_set_layout);

    LOG_NK_STRUCT("binding", *binding);
    LOG_NK_UINT("binding.binding", binding->binding);
    LOG_NK_INT("binding.descriptorType", binding->descriptorType);
    LOG_NK_UINT("binding.descriptorCount", binding->descriptorCount);
    LOG_NK_FLAGS("binding.stageFlags", binding->stageFlags);
    LOG_POINTER("binding.pImmutableSamplers",
                binding->pImmutableSamplers);

    LOG_NK_STRUCT("descriptor_set_info", *descriptor_set_info);
    LOG_NK_INT("descriptor_set_info.sType", descriptor_set_info->sType);
    LOG_POINTER("descriptor_set_info.pNext",
                descriptor_set_info->pNext);
    LOG_NK_FLAGS("descriptor_set_info.flags",
                 descriptor_set_info->flags);
    LOG_NK_UINT("descriptor_set_info.bindingCount",
                descriptor_set_info->bindingCount);
    LOG_POINTER("descriptor_set_info.pBindings",
                descriptor_set_info->pBindings);

    LOG_NK_INT("vkCreateDescriptorSetLayout result", result);
}


NK_INTERN void
nk_glfw3_create_uniform_descriptor_set_layout(struct nk_glfw_device *dev)
{
    VkDescriptorSetLayoutBinding binding;
    VkDescriptorSetLayoutCreateInfo descriptor_set_info;
    VkResult result;

    memset(&binding, 0, sizeof(VkDescriptorSetLayoutBinding));
    binding.binding = 0;
    binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    binding.descriptorCount = 1;
    binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    memset(&descriptor_set_info, 0, sizeof(VkDescriptorSetLayoutCreateInfo));
    descriptor_set_info.sType =
        VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptor_set_info.bindingCount = 1;
    descriptor_set_info.pBindings = &binding;

    result =
        vkCreateDescriptorSetLayout(dev->logical_device, &descriptor_set_info,
                                    NULL, &dev->uniform_descriptor_set_layout);
    #ifndef NDEBUG
    nk_glfw3_log_uniform_descriptor_set_layout_config(
        dev,
        &binding,
        &descriptor_set_info,
        result
    );
    #endif


    NK_ASSERT(result == VK_SUCCESS);
}

NK_INTERN void
nk_glfw3_log_uniform_descriptor_set_config(
    const struct nk_glfw_device *dev,
    const VkDescriptorSetAllocateInfo *allocate_info,
    const VkDescriptorBufferInfo *buffer_info,
    const VkWriteDescriptorSet *descriptor_write,
    VkResult allocate_result)
{
    log_info("Uniform descriptor set allocation configuration:");

    LOG_VK_HANDLE("logical_device", dev->logical_device);
    LOG_VK_HANDLE("descriptor_pool", allocate_info->descriptorPool);
    LOG_VK_HANDLE("uniform_descriptor_set_layout",
                  dev->uniform_descriptor_set_layout);
    LOG_VK_HANDLE("uniform_descriptor_set",
                  dev->uniform_descriptor_set);

    LOG_NK_STRUCT("allocate_info", *allocate_info);
    LOG_NK_INT("allocate_info.sType", allocate_info->sType);
    LOG_POINTER("allocate_info.pNext", allocate_info->pNext);
    LOG_VK_HANDLE("allocate_info.descriptorPool",
                  allocate_info->descriptorPool);
    LOG_NK_UINT("allocate_info.descriptorSetCount",
                allocate_info->descriptorSetCount);
    LOG_POINTER("allocate_info.pSetLayouts",
                allocate_info->pSetLayouts);

    LOG_NK_STRUCT("buffer_info", *buffer_info);
    LOG_VK_HANDLE("buffer_info.buffer", buffer_info->buffer);
    LOG_NK_SIZE("buffer_info.offset", buffer_info->offset);
    LOG_NK_SIZE("buffer_info.range", buffer_info->range);

    LOG_NK_STRUCT("descriptor_write", *descriptor_write);
    LOG_NK_INT("descriptor_write.sType", descriptor_write->sType);
    LOG_POINTER("descriptor_write.pNext", descriptor_write->pNext);
    LOG_VK_HANDLE("descriptor_write.dstSet",
                  descriptor_write->dstSet);
    LOG_NK_UINT("descriptor_write.dstBinding",
                descriptor_write->dstBinding);
    LOG_NK_UINT("descriptor_write.dstArrayElement",
                descriptor_write->dstArrayElement);
    LOG_NK_INT("descriptor_write.descriptorType",
                descriptor_write->descriptorType);
    LOG_NK_UINT("descriptor_write.descriptorCount",
                descriptor_write->descriptorCount);
    LOG_POINTER("descriptor_write.pImageInfo",
                descriptor_write->pImageInfo);
    LOG_POINTER("descriptor_write.pBufferInfo",
                descriptor_write->pBufferInfo);
    LOG_POINTER("descriptor_write.pTexelBufferView",
                descriptor_write->pTexelBufferView);

    LOG_NK_INT("vkAllocateDescriptorSets result", allocate_result);
}


NK_INTERN void
nk_glfw3_create_and_update_uniform_descriptor_set(struct nk_glfw_device *dev)
{
    VkDescriptorSetAllocateInfo allocate_info;
    VkDescriptorBufferInfo buffer_info;
    VkWriteDescriptorSet descriptor_write;
    VkResult result;

    memset(&allocate_info, 0, sizeof(VkDescriptorSetAllocateInfo));
    allocate_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocate_info.descriptorPool = dev->descriptor_pool;
    allocate_info.descriptorSetCount = 1;
    allocate_info.pSetLayouts = &dev->uniform_descriptor_set_layout;

    result = vkAllocateDescriptorSets(dev->logical_device, &allocate_info,
                                      &dev->uniform_descriptor_set);
    NK_ASSERT(result == VK_SUCCESS);

    memset(&buffer_info, 0, sizeof(VkDescriptorBufferInfo));
    buffer_info.buffer = dev->uniform_buffer;
    buffer_info.offset = 0;
    buffer_info.range = sizeof(struct Mat4f);

    memset(&descriptor_write, 0, sizeof(VkWriteDescriptorSet));
    descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptor_write.dstSet = dev->uniform_descriptor_set;
    descriptor_write.dstBinding = 0;
    descriptor_write.dstArrayElement = 0;
    descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptor_write.descriptorCount = 1;
    descriptor_write.pBufferInfo = &buffer_info;

    #ifndef NDEBUG
    nk_glfw3_log_uniform_descriptor_set_config(
        dev,
        &allocate_info,
        &buffer_info,
        &descriptor_write,
        result
    );    
    #endif
    vkUpdateDescriptorSets(dev->logical_device, 1, &descriptor_write, 0, NULL);
}

NK_INTERN void
nk_glfw3_log_texture_descriptor_set_layout_config(
    const struct nk_glfw_device *dev,
    const VkDescriptorSetLayoutBinding *binding,
    const VkDescriptorSetLayoutCreateInfo *descriptor_set_info,
    VkResult result)
{
    log_info("Texture descriptor set layout configuration:");

    LOG_VK_HANDLE("logical_device", dev->logical_device);
    LOG_VK_HANDLE("texture_descriptor_set_layout",
                  dev->texture_descriptor_set_layout);

    LOG_NK_STRUCT("binding", *binding);
    LOG_NK_UINT("binding.binding", binding->binding);
    LOG_NK_INT("binding.descriptorType", binding->descriptorType);
    LOG_NK_UINT("binding.descriptorCount", binding->descriptorCount);
    LOG_NK_FLAGS("binding.stageFlags", binding->stageFlags);
    LOG_POINTER("binding.pImmutableSamplers",
                binding->pImmutableSamplers);

    LOG_NK_STRUCT("descriptor_set_info", *descriptor_set_info);
    LOG_NK_INT("descriptor_set_info.sType",
               descriptor_set_info->sType);
    LOG_POINTER("descriptor_set_info.pNext",
                descriptor_set_info->pNext);
    LOG_NK_FLAGS("descriptor_set_info.flags",
                 descriptor_set_info->flags);
    LOG_NK_UINT("descriptor_set_info.bindingCount",
                descriptor_set_info->bindingCount);
    LOG_POINTER("descriptor_set_info.pBindings",
                descriptor_set_info->pBindings);

    LOG_NK_INT("vkCreateDescriptorSetLayout result", result);
}


NK_INTERN void
nk_glfw3_create_texture_descriptor_set_layout(struct nk_glfw_device *dev)
{
    VkDescriptorSetLayoutBinding binding;
    VkDescriptorSetLayoutCreateInfo descriptor_set_info;
    VkResult result;

    memset(&binding, 0, sizeof(VkDescriptorSetLayoutBinding));
    binding.binding = 0;
    binding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    binding.descriptorCount = 1;
    binding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

    memset(&descriptor_set_info, 0, sizeof(VkDescriptorSetLayoutCreateInfo));
    descriptor_set_info.sType =
        VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptor_set_info.bindingCount = 1;
    descriptor_set_info.pBindings = &binding;

    result =
        vkCreateDescriptorSetLayout(dev->logical_device, &descriptor_set_info,
                                    NULL, &dev->texture_descriptor_set_layout);
    #ifndef NDEBUG
    nk_glfw3_log_texture_descriptor_set_layout_config(
        dev,
        &binding,
        &descriptor_set_info,
        result
    );
    #endif
    
    NK_ASSERT(result == VK_SUCCESS);
}

NK_INTERN void
nk_glfw3_log_texture_descriptor_set_data(
    const struct nk_glfw_device             *dev,
    const VkDescriptorSetLayout             *descriptor_set_layouts,
    const VkDescriptorSet                   *descriptor_sets,
    const VkDescriptorSetAllocateInfo       *allocate_info,
    VkResult                                  result)
{
    int i;

    LOG_POINTER("dev", dev);
    LOG_VK_HANDLE("logical_device", dev->logical_device);
    LOG_VK_HANDLE("descriptor_pool", dev->descriptor_pool);
    LOG_VK_HANDLE("texture_descriptor_set_layout",
                  dev->texture_descriptor_set_layout);

    LOG_POINTER("descriptor_set_layouts", descriptor_set_layouts);
    LOG_POINTER("descriptor_sets", descriptor_sets);
    LOG_POINTER("allocate_info", allocate_info);

    LOG_NK_INT("descriptor_set_count",
               allocate_info->descriptorSetCount);
    LOG_NK_INT("allocation_result", (int)result);
    LOG_NK_SIZE("texture_descriptor_sets_len",
                dev->texture_descriptor_sets_len);

    for (i = 0; i < NK_GLFW_MAX_TEXTURES; i++)
    {
        LOG_NK_INT("descriptor_set_index", i);

        LOG_VK_HANDLE("descriptor_set_layout",
                      descriptor_set_layouts[i]);

        LOG_VK_HANDLE("descriptor_set",
                      descriptor_sets[i]);

        if (dev->texture_descriptor_sets)
        {
            LOG_VK_HANDLE(
                "stored_descriptor_set",
                dev->texture_descriptor_sets[i].descriptor_set);
        }
    }
}


NK_INTERN void
nk_glfw3_create_texture_descriptor_sets(struct nk_glfw_device *dev)
{
    VkDescriptorSetLayout *descriptor_set_layouts;
    VkDescriptorSet *descriptor_sets;
    VkDescriptorSetAllocateInfo allocate_info;
    VkResult result;
    int i;

    descriptor_set_layouts = (VkDescriptorSetLayout *)malloc(
                                 NK_GLFW_MAX_TEXTURES * sizeof(VkDescriptorSetLayout));
    descriptor_sets = (VkDescriptorSet *)malloc(NK_GLFW_MAX_TEXTURES *
                      sizeof(VkDescriptorSet));

    dev->texture_descriptor_sets =
        (struct nk_vulkan_texture_descriptor_set *)malloc(
            NK_GLFW_MAX_TEXTURES *
            sizeof(struct nk_vulkan_texture_descriptor_set));
    dev->texture_descriptor_sets_len = 0;

    for (i = 0; i < NK_GLFW_MAX_TEXTURES; i++)
    {
        descriptor_set_layouts[i] = dev->texture_descriptor_set_layout;
        descriptor_sets[i] = dev->texture_descriptor_sets[i].descriptor_set;
    }

    memset(&allocate_info, 0, sizeof(VkDescriptorSetAllocateInfo));
    allocate_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocate_info.descriptorPool = dev->descriptor_pool;
    allocate_info.descriptorSetCount = NK_GLFW_MAX_TEXTURES;
    allocate_info.pSetLayouts = descriptor_set_layouts;

    result = vkAllocateDescriptorSets(dev->logical_device, &allocate_info,
                                      descriptor_sets);

				      
    NK_ASSERT(result == VK_SUCCESS);

    for (i = 0; i < NK_GLFW_MAX_TEXTURES; i++)
    {
        dev->texture_descriptor_sets[i].descriptor_set = descriptor_sets[i];
    }
    #ifndef NDEBUG
    nk_glfw3_log_texture_descriptor_set_data(
	dev,
	descriptor_set_layouts,
	descriptor_sets,
	&allocate_info,
	result);
    #endif    
    free(descriptor_set_layouts);
    free(descriptor_sets);
}

NK_INTERN void
nk_glfw3_log_pipeline_layout_data(
    const struct nk_glfw_device       *dev,
    const VkPipelineLayoutCreateInfo  *pipeline_layout_info,
    const VkDescriptorSetLayout       *descriptor_set_layouts,
    VkResult                           result)
{
    LOG_POINTER("dev", dev);

    LOG_VK_HANDLE("logical_device",
                  dev->logical_device);

    LOG_VK_HANDLE("uniform_descriptor_set_layout",
                  dev->uniform_descriptor_set_layout);

    LOG_VK_HANDLE("texture_descriptor_set_layout",
                  dev->texture_descriptor_set_layout);

    LOG_POINTER("pipeline_layout_info",
                pipeline_layout_info);

    LOG_NK_INT("pipeline_layout_info.sType",
               (int)pipeline_layout_info->sType);

    LOG_NK_UINT("pipeline_layout_info.setLayoutCount",
                pipeline_layout_info->setLayoutCount);

    LOG_POINTER("pipeline_layout_info.pSetLayouts",
                pipeline_layout_info->pSetLayouts);

    LOG_VK_HANDLE("descriptor_set_layouts[0]",
                  descriptor_set_layouts[0]);

    LOG_VK_HANDLE("descriptor_set_layouts[1]",
                  descriptor_set_layouts[1]);

    LOG_NK_INT("vkCreatePipelineLayout result",
               (int)result);

    if (result == VK_SUCCESS)
    {
        LOG_VK_HANDLE("pipeline_layout",
                      dev->pipeline_layout);
    }
}


NK_INTERN void nk_glfw3_create_pipeline_layout(struct nk_glfw_device *dev)
{
    VkPipelineLayoutCreateInfo pipeline_layout_info;
    VkDescriptorSetLayout descriptor_set_layouts[2];
    VkResult result;

    descriptor_set_layouts[0] = dev->uniform_descriptor_set_layout;
    descriptor_set_layouts[1] = dev->texture_descriptor_set_layout;

    memset(&pipeline_layout_info, 0, sizeof(VkPipelineLayoutCreateInfo));
    pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipeline_layout_info.setLayoutCount = 2;
    pipeline_layout_info.pSetLayouts = descriptor_set_layouts;

    result = (vkCreatePipelineLayout(dev->logical_device, &pipeline_layout_info,
                                     NULL, &dev->pipeline_layout));

    #ifndef NDEBUG
    nk_glfw3_log_pipeline_layout_data(
    dev,
    &pipeline_layout_info,
    descriptor_set_layouts,
    result);
    #endif
				     
    NK_ASSERT(result == VK_SUCCESS);
}

NK_INTERN void
nk_glfw3_log_create_shader_config(
    const struct nk_glfw_device *dev,
    const unsigned char *spv_shader,
    uint32_t size,
    VkShaderStageFlagBits stage_bit)
{
    log_info("Create shader configuration:");

    LOG_POINTER("dev", dev);
    LOG_POINTER("spv_shader", (void *)spv_shader);
    LOG_UINT("size", size);
    LOG_INT("stage_bit", stage_bit);
}


NK_INTERN VkPipelineShaderStageCreateInfo
nk_glfw3_create_shader(struct nk_glfw_device *dev, unsigned char *spv_shader,
                       uint32_t size, VkShaderStageFlagBits stage_bit)
{
    VkShaderModuleCreateInfo create_info;
    VkPipelineShaderStageCreateInfo shader_info;
    VkShaderModule module = NULL;
    VkResult result;

    #ifndef NDEBUG
    nk_glfw3_log_create_shader_config(
        dev,
        spv_shader,
        size,
        stage_bit
    );
    #endif

    memset(&create_info, 0, sizeof(VkShaderModuleCreateInfo));
    create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    create_info.codeSize = size;
    create_info.pCode = (const uint32_t *)spv_shader;
    result =
        vkCreateShaderModule(dev->logical_device, &create_info, NULL, &module);
    NK_ASSERT(result == VK_SUCCESS);

    memset(&shader_info, 0, sizeof(VkPipelineShaderStageCreateInfo));
    shader_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shader_info.stage = stage_bit;
    shader_info.module = module;
    shader_info.pName = "main";
    return shader_info;
}

NK_INTERN void
nk_glfw3_log_pipeline_configuration(
    const struct nk_glfw_device                    *dev,
    const VkPipelineInputAssemblyStateCreateInfo   *input_assembly_state,
    const VkPipelineRasterizationStateCreateInfo   *rasterization_state,
    const VkPipelineColorBlendAttachmentState      *attachment_state,
    const VkPipelineColorBlendStateCreateInfo      *color_blend_state,
    const VkPipelineViewportStateCreateInfo        *viewport_state,
    const VkPipelineMultisampleStateCreateInfo     *multisample_state,
    const VkPipelineDynamicStateCreateInfo         *dynamic_state,
    const VkDynamicState                            *dynamic_states,
    const VkPipelineShaderStageCreateInfo          *shader_stages,
    const VkVertexInputBindingDescription          *vertex_input_info,
    const VkVertexInputAttributeDescription        *vertex_attributes,
    const VkPipelineVertexInputStateCreateInfo     *vertex_input,
    const VkGraphicsPipelineCreateInfo             *pipeline_info,
    VkResult                                         result)
{
    int i;

    LOG_POINTER("dev", dev);
    LOG_VK_HANDLE("logical_device", dev->logical_device);
    LOG_VK_HANDLE("pipeline_layout", dev->pipeline_layout);
    LOG_VK_HANDLE("render_pass", dev->render_pass);

    LOG_NK_INT("input_assembly.topology",
               (int)input_assembly_state->topology);
    LOG_NK_INT("input_assembly.primitiveRestartEnable",
               (int)input_assembly_state->primitiveRestartEnable);

    LOG_NK_INT("rasterization.polygonMode",
               (int)rasterization_state->polygonMode);
    LOG_NK_FLAGS("rasterization.cullMode",
                 rasterization_state->cullMode);
    LOG_NK_INT("rasterization.frontFace",
               (int)rasterization_state->frontFace);
    LOG_NK_FLOAT("rasterization.lineWidth",
                 rasterization_state->lineWidth);

    LOG_NK_INT("blend.blendEnable",
               (int)attachment_state->blendEnable);
    LOG_NK_INT("blend.srcColorBlendFactor",
               (int)attachment_state->srcColorBlendFactor);
    LOG_NK_INT("blend.dstColorBlendFactor",
               (int)attachment_state->dstColorBlendFactor);
    LOG_NK_INT("blend.colorBlendOp",
               (int)attachment_state->colorBlendOp);
    LOG_NK_INT("blend.srcAlphaBlendFactor",
               (int)attachment_state->srcAlphaBlendFactor);
    LOG_NK_INT("blend.dstAlphaBlendFactor",
               (int)attachment_state->dstAlphaBlendFactor);
    LOG_NK_INT("blend.alphaBlendOp",
               (int)attachment_state->alphaBlendOp);
    LOG_NK_FLAGS("blend.colorWriteMask",
                 attachment_state->colorWriteMask);

    LOG_NK_UINT("color_blend.attachmentCount",
                color_blend_state->attachmentCount);

    LOG_NK_UINT("viewport.viewportCount",
                viewport_state->viewportCount);
    LOG_NK_UINT("viewport.scissorCount",
                viewport_state->scissorCount);

    LOG_NK_FLAGS("multisample.rasterizationSamples",
                 multisample_state->rasterizationSamples);

    LOG_NK_UINT("dynamic.dynamicStateCount",
                dynamic_state->dynamicStateCount);

    for (i = 0; i < (int)dynamic_state->dynamicStateCount; i++)
    {
        LOG_NK_INT("dynamic_state", (int)dynamic_states[i]);
    }

    for (i = 0; i < 2; i++)
    {
        LOG_NK_INT("shader_stage", (int)shader_stages[i].stage);
        LOG_VK_HANDLE("shader_module", shader_stages[i].module);
    }

    LOG_NK_UINT("vertex_input.binding",
                vertex_input_info->binding);
    LOG_NK_SIZE("vertex_input.stride",
                vertex_input_info->stride);
    LOG_NK_INT("vertex_input.inputRate",
               (int)vertex_input_info->inputRate);

    for (i = 0; i < 3; i++)
    {
        LOG_NK_UINT("vertex_attribute.location",
                    vertex_attributes[i].location);
        LOG_NK_INT("vertex_attribute.format",
                   (int)vertex_attributes[i].format);
        LOG_NK_UINT("vertex_attribute.offset",
                    vertex_attributes[i].offset);
    }

    LOG_NK_UINT("vertex.bindingDescriptionCount",
                vertex_input->vertexBindingDescriptionCount);
    LOG_NK_UINT("vertex.attributeDescriptionCount",
                vertex_input->vertexAttributeDescriptionCount);

    LOG_NK_UINT("pipeline.flags", pipeline_info->flags);
    LOG_NK_UINT("pipeline.stageCount", pipeline_info->stageCount);
    LOG_VK_HANDLE("pipeline.layout", pipeline_info->layout);
    LOG_VK_HANDLE("pipeline.renderPass", pipeline_info->renderPass);
    LOG_NK_INT("pipeline.basePipelineIndex",
               pipeline_info->basePipelineIndex);
    LOG_VK_HANDLE("pipeline.basePipelineHandle",
                  pipeline_info->basePipelineHandle);

    LOG_NK_INT("vkCreateGraphicsPipelines result",
               (int)result);

    if (result == VK_SUCCESS)
    {
        LOG_VK_HANDLE("pipeline", dev->pipeline);
    }
}


NK_INTERN void nk_glfw3_create_pipeline(struct nk_glfw_device *dev)
{
    VkPipelineInputAssemblyStateCreateInfo input_assembly_state;
    VkPipelineRasterizationStateCreateInfo rasterization_state;
    VkPipelineColorBlendAttachmentState attachment_state =
    {
        VK_TRUE,
        VK_BLEND_FACTOR_SRC_ALPHA,
        VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        VK_BLEND_OP_ADD,
        VK_BLEND_FACTOR_SRC_ALPHA,
        VK_BLEND_FACTOR_ONE,
        VK_BLEND_OP_ADD,
        VK_COLOR_COMPONENT_MASK_RGBA,
    };
    VkPipelineColorBlendStateCreateInfo color_blend_state;
    VkPipelineViewportStateCreateInfo viewport_state;
    VkPipelineMultisampleStateCreateInfo multisample_state;
    VkDynamicState dynamic_states[2] = {VK_DYNAMIC_STATE_VIEWPORT,
                                        VK_DYNAMIC_STATE_SCISSOR
                                       };
    VkPipelineDynamicStateCreateInfo dynamic_state;
    VkPipelineShaderStageCreateInfo shader_stages[2];
    VkVertexInputBindingDescription vertex_input_info;
    VkVertexInputAttributeDescription vertex_attribute_description[3];
    VkPipelineVertexInputStateCreateInfo vertex_input;
    VkGraphicsPipelineCreateInfo pipeline_info;
    VkResult result;

    memset(&input_assembly_state, 0,
           sizeof(VkPipelineInputAssemblyStateCreateInfo));
    input_assembly_state.sType =
        VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    input_assembly_state.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    input_assembly_state.primitiveRestartEnable = VK_FALSE;

    memset(&rasterization_state, 0,
           sizeof(VkPipelineRasterizationStateCreateInfo));
    rasterization_state.sType =
        VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterization_state.polygonMode = VK_POLYGON_MODE_FILL;
    rasterization_state.cullMode = VK_CULL_MODE_NONE;
    rasterization_state.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterization_state.lineWidth = 1.0f;

    memset(&color_blend_state, 0, sizeof(VkPipelineColorBlendStateCreateInfo));
    color_blend_state.sType =
        VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    color_blend_state.attachmentCount = 1;
    color_blend_state.pAttachments = &attachment_state;

    memset(&viewport_state, 0, sizeof(VkPipelineViewportStateCreateInfo));
    viewport_state.sType =
        VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewport_state.viewportCount = 1;
    viewport_state.scissorCount = 1;

    memset(&multisample_state, 0, sizeof(VkPipelineMultisampleStateCreateInfo));
    multisample_state.sType =
        VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisample_state.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    memset(&dynamic_state, 0, sizeof(VkPipelineDynamicStateCreateInfo));
    dynamic_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamic_state.pDynamicStates = dynamic_states;
    dynamic_state.dynamicStateCount = 2;

    shader_stages[0] = nk_glfw3_create_shader(
                           dev, nuklearshaders_nuklear_vert_spv,
                           nuklearshaders_nuklear_vert_spv_len, VK_SHADER_STAGE_VERTEX_BIT);
    shader_stages[1] = nk_glfw3_create_shader(
                           dev, nuklearshaders_nuklear_frag_spv,
                           nuklearshaders_nuklear_frag_spv_len, VK_SHADER_STAGE_FRAGMENT_BIT);

    memset(&vertex_input_info, 0, sizeof(VkVertexInputBindingDescription));
    vertex_input_info.binding = 0;
    vertex_input_info.stride = sizeof(struct nk_glfw_vertex);
    vertex_input_info.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    memset(&vertex_attribute_description, 0,
           sizeof(VkVertexInputAttributeDescription) * 3);
    vertex_attribute_description[0].location = 0;
    vertex_attribute_description[0].format = VK_FORMAT_R32G32_SFLOAT;
    vertex_attribute_description[0].offset =
        NK_OFFSETOF(struct nk_glfw_vertex, position);
    vertex_attribute_description[1].location = 1;
    vertex_attribute_description[1].format = VK_FORMAT_R32G32_SFLOAT;
    vertex_attribute_description[1].offset =
        NK_OFFSETOF(struct nk_glfw_vertex, uv);
    vertex_attribute_description[2].location = 2;
    vertex_attribute_description[2].format = VK_FORMAT_R8G8B8A8_UINT;
    vertex_attribute_description[2].offset =
        NK_OFFSETOF(struct nk_glfw_vertex, col);

    memset(&vertex_input, 0, sizeof(VkPipelineVertexInputStateCreateInfo));
    vertex_input.sType =
        VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertex_input.vertexBindingDescriptionCount = 1;
    vertex_input.pVertexBindingDescriptions = &vertex_input_info;
    vertex_input.vertexAttributeDescriptionCount = 3;
    vertex_input.pVertexAttributeDescriptions = vertex_attribute_description;

    memset(&pipeline_info, 0, sizeof(VkGraphicsPipelineCreateInfo));
    pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipeline_info.flags = 0;
    pipeline_info.stageCount = 2;
    pipeline_info.pStages = shader_stages;
    pipeline_info.pVertexInputState = &vertex_input;
    pipeline_info.pInputAssemblyState = &input_assembly_state;
    pipeline_info.pViewportState = &viewport_state;
    pipeline_info.pRasterizationState = &rasterization_state;
    pipeline_info.pMultisampleState = &multisample_state;
    pipeline_info.pColorBlendState = &color_blend_state;
    pipeline_info.pDynamicState = &dynamic_state;
    pipeline_info.layout = dev->pipeline_layout;
    pipeline_info.renderPass = dev->render_pass;
    pipeline_info.basePipelineIndex = -1;
    pipeline_info.basePipelineHandle = NULL;

    result = vkCreateGraphicsPipelines(dev->logical_device, NULL, 1,
                                       &pipeline_info, NULL, &dev->pipeline);

    #ifndef NDEBUG
    nk_glfw3_log_pipeline_configuration(
	dev,
	&input_assembly_state,
	&rasterization_state,
	&attachment_state,
	&color_blend_state,
	&viewport_state,
	&multisample_state,
	&dynamic_state,
	dynamic_states,
	shader_stages,
	&vertex_input_info,
	vertex_attribute_description,
	&vertex_input,
	&pipeline_info,
	result);    
    #endif
    NK_ASSERT(result == VK_SUCCESS);

    vkDestroyShaderModule(dev->logical_device, shader_stages[0].module, NULL);
    vkDestroyShaderModule(dev->logical_device, shader_stages[1].module, NULL);
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


NK_INTERN void nk_glfw3_create_render_resources(struct nk_glfw_device *dev,
        uint32_t framebuffer_width,
        uint32_t framebuffer_height)
{
    #ifndef NDEBUG
    nk_glfw3_log_create_render_resources_config(
        dev,
        framebuffer_width,
        framebuffer_height
    );    
    #endif 
    nk_glfw3_create_render_pass(dev);
    nk_glfw3_create_framebuffers(dev, framebuffer_width, framebuffer_height);
    nk_glfw3_create_descriptor_pool(dev);
    nk_glfw3_create_uniform_descriptor_set_layout(dev);
    nk_glfw3_create_and_update_uniform_descriptor_set(dev);
    nk_glfw3_create_texture_descriptor_set_layout(dev);
    nk_glfw3_create_texture_descriptor_sets(dev);
    nk_glfw3_create_pipeline_layout(dev);
    nk_glfw3_create_pipeline(dev);
}

NK_API void nk_glfw3_device_create(
    VkDevice logical_device, VkPhysicalDevice physical_device,
    uint32_t graphics_queue_family_index, VkImageView *image_views,
    uint32_t image_views_len, VkFormat color_format,
    VkDeviceSize max_vertex_buffer, VkDeviceSize max_element_buffer,
    uint32_t framebuffer_width, uint32_t framebuffer_height)
{
    struct nk_glfw_device *dev = &glfw.vulkan;
    dev->max_vertex_buffer = max_vertex_buffer;
    dev->max_element_buffer = max_element_buffer;
    nk_buffer_init_default(&dev->cmds);
    dev->logical_device = logical_device;
    dev->physical_device = physical_device;
    dev->image_views = image_views;
    dev->image_views_len = image_views_len;
    dev->color_format = color_format;
    dev->framebuffers = NULL;
    dev->framebuffers_len = 0;

    nk_glfw3_create_sampler(dev);
    nk_glfw3_create_command_pool(dev, graphics_queue_family_index);
    nk_glfw3_create_command_buffers(dev);
    nk_glfw3_create_semaphore(dev);

    nk_glfw3_create_buffer_and_memory(dev, &dev->vertex_buffer,
                                      VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                                      &dev->vertex_memory, max_vertex_buffer);
    nk_glfw3_create_buffer_and_memory(dev, &dev->index_buffer,
                                      VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                                      &dev->index_memory, max_element_buffer);
    nk_glfw3_create_buffer_and_memory( dev, &dev->uniform_buffer, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, &dev->uniform_memory, sizeof(struct Mat4f));

    vkMapMemory(dev->logical_device, dev->vertex_memory, 0, max_vertex_buffer, 0, &dev->mapped_vertex);
    vkMapMemory(dev->logical_device, dev->index_memory, 0, max_element_buffer, 0, &dev->mapped_index);
    vkMapMemory(dev->logical_device, dev->uniform_memory, 0, sizeof(struct Mat4f), 0, &dev->mapped_uniform);

    nk_glfw3_create_render_resources(dev, framebuffer_width, framebuffer_height);
}

NK_INTERN void nk_glfw3_device_upload_atlas(VkQueue graphics_queue,
        const void *image, int width,
        int height)
{
    struct nk_glfw_device *dev = &glfw.vulkan;

    VkImageCreateInfo image_info;
    VkResult result;
    VkMemoryRequirements mem_reqs;
    VkMemoryAllocateInfo alloc_info;
    VkBufferCreateInfo buffer_info;
    uint8_t *data = 0;
    VkCommandBufferBeginInfo begin_info;
    VkCommandBuffer command_buffer;
    VkImageMemoryBarrier image_memory_barrier;
    VkBufferImageCopy buffer_copy_region;
    VkImageMemoryBarrier image_shader_memory_barrier;
    VkFence fence;
    VkFenceCreateInfo fence_create;
    VkSubmitInfo submit_info;
    VkImageViewCreateInfo image_view_info;
    struct
    {
        VkDeviceMemory memory;
        VkBuffer buffer;
    } staging_buffer;

    memset(&image_info, 0, sizeof(VkImageCreateInfo));
    image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    image_info.imageType = VK_IMAGE_TYPE_2D;
    image_info.format = VK_FORMAT_R8G8B8A8_UNORM;
    image_info.extent.width = (uint32_t)width;
    image_info.extent.height = (uint32_t)height;
    image_info.extent.depth = 1;
    image_info.mipLevels = 1;
    image_info.arrayLayers = 1;
    image_info.samples = VK_SAMPLE_COUNT_1_BIT;
    image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
    image_info.usage =
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    result =
        vkCreateImage(dev->logical_device, &image_info, NULL, &dev->font_image);
    NK_ASSERT(result == VK_SUCCESS);

    vkGetImageMemoryRequirements(dev->logical_device, dev->font_image,
                                 &mem_reqs);

    memset(&alloc_info, 0, sizeof(VkMemoryAllocateInfo));
    alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    alloc_info.allocationSize = mem_reqs.size;
    alloc_info.memoryTypeIndex = nk_glfw3_find_memory_index(
                                     dev->physical_device, mem_reqs.memoryTypeBits,
                                     VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    result = vkAllocateMemory(dev->logical_device, &alloc_info, NULL,
                              &dev->font_memory);
    NK_ASSERT(result == VK_SUCCESS);
    result = vkBindImageMemory(dev->logical_device, dev->font_image,
                               dev->font_memory, 0);
    NK_ASSERT(result == VK_SUCCESS);

    memset(&buffer_info, 0, sizeof(VkBufferCreateInfo));
    buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    buffer_info.size = alloc_info.allocationSize;
    buffer_info.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    result = vkCreateBuffer(dev->logical_device, &buffer_info, NULL,
                            &staging_buffer.buffer);
    NK_ASSERT(result == VK_SUCCESS);
    vkGetBufferMemoryRequirements(dev->logical_device, staging_buffer.buffer,
                                  &mem_reqs);

    alloc_info.allocationSize = mem_reqs.size;
    alloc_info.memoryTypeIndex = nk_glfw3_find_memory_index(
                                     dev->physical_device, mem_reqs.memoryTypeBits,
                                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                     VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    result = vkAllocateMemory(dev->logical_device, &alloc_info, NULL,
                              &staging_buffer.memory);
    NK_ASSERT(result == VK_SUCCESS);
    result = vkBindBufferMemory(dev->logical_device, staging_buffer.buffer,
                                staging_buffer.memory, 0);
    NK_ASSERT(result == VK_SUCCESS);

    result = vkMapMemory(dev->logical_device, staging_buffer.memory, 0,
                         alloc_info.allocationSize, 0, (void **)&data);
    NK_ASSERT(result == VK_SUCCESS);
    memcpy(data, image, width * height * 4);
    vkUnmapMemory(dev->logical_device, staging_buffer.memory);

    memset(&begin_info, 0, sizeof(VkCommandBufferBeginInfo));
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    NK_ASSERT(dev->command_buffers_len > 0);
    /*
    use the same command buffer as for render as we are regenerating the
    buffer during render anyway
    */
    command_buffer = dev->command_buffers[0];
    result = vkBeginCommandBuffer(command_buffer, &begin_info);
    NK_ASSERT(result == VK_SUCCESS);

    memset(&image_memory_barrier, 0, sizeof(VkImageMemoryBarrier));
    image_memory_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    image_memory_barrier.image = dev->font_image;
    image_memory_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    image_memory_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    image_memory_barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    image_memory_barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    image_memory_barrier.subresourceRange.aspectMask =
        VK_IMAGE_ASPECT_COLOR_BIT;
    image_memory_barrier.subresourceRange.levelCount = 1;
    image_memory_barrier.subresourceRange.layerCount = 1;
    image_memory_barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

    vkCmdPipelineBarrier(command_buffer, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                         VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, NULL, 0, NULL, 1,
                         &image_memory_barrier);

    memset(&buffer_copy_region, 0, sizeof(VkBufferImageCopy));
    buffer_copy_region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    buffer_copy_region.imageSubresource.layerCount = 1;
    buffer_copy_region.imageExtent.width = (uint32_t)width;
    buffer_copy_region.imageExtent.height = (uint32_t)height;
    buffer_copy_region.imageExtent.depth = 1;

    vkCmdCopyBufferToImage(
        command_buffer, staging_buffer.buffer, dev->font_image,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &buffer_copy_region);

    memset(&image_shader_memory_barrier, 0, sizeof(VkImageMemoryBarrier));
    image_shader_memory_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    image_shader_memory_barrier.image = dev->font_image;
    image_shader_memory_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    image_shader_memory_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    image_shader_memory_barrier.oldLayout =
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    image_shader_memory_barrier.newLayout =
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    image_shader_memory_barrier.subresourceRange.aspectMask =
        VK_IMAGE_ASPECT_COLOR_BIT;
    image_shader_memory_barrier.subresourceRange.levelCount = 1;
    image_shader_memory_barrier.subresourceRange.layerCount = 1;
    image_shader_memory_barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT,
    image_shader_memory_barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT,

    vkCmdPipelineBarrier(command_buffer, VK_PIPELINE_STAGE_TRANSFER_BIT,
                         VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, NULL, 0,
                         NULL, 1, &image_shader_memory_barrier);

    result = vkEndCommandBuffer(command_buffer);
    NK_ASSERT(result == VK_SUCCESS);

    memset(&fence_create, 0, sizeof(VkFenceCreateInfo));
    fence_create.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

    result = vkCreateFence(dev->logical_device, &fence_create, NULL, &fence);
    NK_ASSERT(result == VK_SUCCESS);

    memset(&submit_info, 0, sizeof(VkSubmitInfo));
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &command_buffer;

    result = vkQueueSubmit(graphics_queue, 1, &submit_info, fence);
    NK_ASSERT(result == VK_SUCCESS);
    result =
        vkWaitForFences(dev->logical_device, 1, &fence, VK_TRUE, UINT64_MAX);
    NK_ASSERT(result == VK_SUCCESS);

    vkDestroyFence(dev->logical_device, fence, NULL);

    vkFreeMemory(dev->logical_device, staging_buffer.memory, NULL);
    vkDestroyBuffer(dev->logical_device, staging_buffer.buffer, NULL);

    memset(&image_view_info, 0, sizeof(VkImageViewCreateInfo));
    image_view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    image_view_info.image = dev->font_image;
    image_view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    image_view_info.format = image_info.format;
    image_view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    image_view_info.subresourceRange.layerCount = 1;
    image_view_info.subresourceRange.levelCount = 1;

    result = vkCreateImageView(dev->logical_device, &image_view_info, NULL,
                               &dev->font_image_view);
    NK_ASSERT(result == VK_SUCCESS);
}

NK_INTERN void nk_glfw3_destroy_render_resources(struct nk_glfw_device *dev)
{
    uint32_t i;

    vkDestroyPipeline(dev->logical_device, dev->pipeline, NULL);
    vkDestroyPipelineLayout(dev->logical_device, dev->pipeline_layout, NULL);
    vkDestroyDescriptorSetLayout(dev->logical_device,
                                 dev->texture_descriptor_set_layout, NULL);
    vkDestroyDescriptorSetLayout(dev->logical_device,
                                 dev->uniform_descriptor_set_layout, NULL);
    vkDestroyDescriptorPool(dev->logical_device, dev->descriptor_pool, NULL);
    for (i = 0; i < dev->framebuffers_len; i++)
    {
        vkDestroyFramebuffer(dev->logical_device, dev->framebuffers[i], NULL);
    }
    free(dev->framebuffers);
    dev->framebuffers_len = 0;
    free(dev->texture_descriptor_sets);
    dev->texture_descriptor_sets_len = 0;
    vkDestroyRenderPass(dev->logical_device, dev->render_pass, NULL);
}

NK_API void nk_glfw3_resize(uint32_t framebuffer_width,
                            uint32_t framebuffer_height)
{
    struct nk_glfw_device *dev = &glfw.vulkan;
    glfwGetWindowSize(glfw.win, &glfw.width, &glfw.height);
    glfwGetFramebufferSize(glfw.win, &glfw.display_width, &glfw.display_height);

    nk_glfw3_destroy_render_resources(dev);
    nk_glfw3_create_render_resources(dev, framebuffer_width,
                                     framebuffer_height);
}

NK_API void nk_glfw3_device_destroy(void)
{
    struct nk_glfw_device *dev = &glfw.vulkan;

    vkDeviceWaitIdle(dev->logical_device);

    nk_glfw3_destroy_render_resources(dev);

    vkFreeCommandBuffers(dev->logical_device, dev->command_pool,
                         dev->command_buffers_len, dev->command_buffers);
    vkDestroyCommandPool(dev->logical_device, dev->command_pool, NULL);
    vkDestroySemaphore(dev->logical_device, dev->render_completed, NULL);

    vkUnmapMemory(dev->logical_device, dev->vertex_memory);
    vkUnmapMemory(dev->logical_device, dev->index_memory);
    vkUnmapMemory(dev->logical_device, dev->uniform_memory);

    vkFreeMemory(dev->logical_device, dev->vertex_memory, NULL);
    vkFreeMemory(dev->logical_device, dev->index_memory, NULL);
    vkFreeMemory(dev->logical_device, dev->uniform_memory, NULL);

    vkDestroyBuffer(dev->logical_device, dev->vertex_buffer, NULL);
    vkDestroyBuffer(dev->logical_device, dev->index_buffer, NULL);
    vkDestroyBuffer(dev->logical_device, dev->uniform_buffer, NULL);

    vkDestroySampler(dev->logical_device, dev->sampler, NULL);

    vkFreeMemory(dev->logical_device, dev->font_memory, NULL);
    vkDestroyImage(dev->logical_device, dev->font_image, NULL);
    vkDestroyImageView(dev->logical_device, dev->font_image_view, NULL);

    free(dev->command_buffers);
    nk_buffer_free(&dev->cmds);
}

NK_API
void nk_glfw3_shutdown(void)
{
    nk_font_atlas_clear(&glfw.atlas);
    nk_free(&glfw.ctx);
    nk_glfw3_device_destroy();
    memset(&glfw, 0, sizeof(glfw));
}

NK_API void nk_glfw3_font_stash_begin(struct nk_font_atlas **atlas)
{
    nk_font_atlas_init_default(&glfw.atlas);
    nk_font_atlas_begin(&glfw.atlas);
    *atlas = &glfw.atlas;
}

NK_API void nk_glfw3_font_stash_end(VkQueue graphics_queue)
{
    struct nk_glfw_device *dev = &glfw.vulkan;

    const void *image;
    int w, h;
    image = nk_font_atlas_bake(&glfw.atlas, &w, &h, NK_FONT_ATLAS_RGBA32);
    nk_glfw3_device_upload_atlas(graphics_queue, image, w, h);
    nk_font_atlas_end(&glfw.atlas, nk_handle_ptr(dev->font_image_view),
                      &dev->tex_null);
    if (glfw.atlas.default_font)
    {
        nk_style_set_font(&glfw.ctx, &glfw.atlas.default_font->handle);
    }
}

NK_API void nk_glfw3_new_frame(void)
{
    int i;
    double x, y;
    struct nk_context *ctx = &glfw.ctx;
    struct GLFWwindow *win = glfw.win;
    nk_char* k_state = glfw.key_events;

    /* update the timer */
    float delta_time_now = (float)glfwGetTime();
    glfw.ctx.delta_time_seconds = delta_time_now - glfw.delta_time_seconds_last;
    glfw.delta_time_seconds_last = delta_time_now;

    glfwGetWindowSize(win, &glfw.width, &glfw.height);
    glfwGetFramebufferSize(win, &glfw.display_width, &glfw.display_height);
    glfw.fb_scale.x = (float)glfw.display_width/(float)glfw.width;
    glfw.fb_scale.y = (float)glfw.display_height/(float)glfw.height;

    nk_input_begin(ctx);
    for (i = 0; i < glfw.text_len; ++i)
        nk_input_unicode(ctx, glfw.text[i]);

#ifdef NK_GLFW_VULKAN_MOUSE_GRABBING
    /* optional grabbing behavior */
    if (ctx->input.mouse.grab)
        glfwSetInputMode(glfw.win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    else if (ctx->input.mouse.ungrab)
        glfwSetInputMode(glfw.win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
#endif

    if (k_state[NK_KEY_DEL] >= 0) nk_input_key(ctx, NK_KEY_DEL, k_state[NK_KEY_DEL]);
    if (k_state[NK_KEY_ENTER] >= 0) nk_input_key(ctx, NK_KEY_ENTER, k_state[NK_KEY_ENTER]);

    if (k_state[NK_KEY_TEXT_RESET_MODE] >= 0) nk_input_key(ctx, NK_KEY_TEXT_RESET_MODE, k_state[NK_KEY_TEXT_RESET_MODE]);

    if (k_state[NK_KEY_TAB] >= 0) nk_input_key(ctx, NK_KEY_TAB, k_state[NK_KEY_TAB]);
    if (k_state[NK_KEY_BACKSPACE] >= 0) nk_input_key(ctx, NK_KEY_BACKSPACE, k_state[NK_KEY_BACKSPACE]);
    if (k_state[NK_KEY_UP] >= 0) nk_input_key(ctx, NK_KEY_UP, k_state[NK_KEY_UP]);
    if (k_state[NK_KEY_DOWN] >= 0) nk_input_key(ctx, NK_KEY_DOWN, k_state[NK_KEY_DOWN]);
    if (k_state[NK_KEY_ALT] >= 0) nk_input_key(ctx, NK_KEY_ALT, k_state[NK_KEY_ALT]);
    if (k_state[NK_KEY_SCROLL_UP] >= 0) nk_input_key(ctx, NK_KEY_SCROLL_UP, k_state[NK_KEY_SCROLL_UP]);
    if (k_state[NK_KEY_SCROLL_DOWN] >= 0) nk_input_key(ctx, NK_KEY_SCROLL_DOWN, k_state[NK_KEY_SCROLL_DOWN]);
    if (k_state[NK_KEY_F1] >= 0) nk_input_key(ctx, NK_KEY_F1, k_state[NK_KEY_F1]);
    if (k_state[NK_KEY_F2] >= 0) nk_input_key(ctx, NK_KEY_F2, k_state[NK_KEY_F2]);
    if (k_state[NK_KEY_F3] >= 0) nk_input_key(ctx, NK_KEY_F3, k_state[NK_KEY_F3]);
    if (k_state[NK_KEY_F4] >= 0) nk_input_key(ctx, NK_KEY_F4, k_state[NK_KEY_F4]);
    if (k_state[NK_KEY_F5] >= 0) nk_input_key(ctx, NK_KEY_F5, k_state[NK_KEY_F5]);
    if (k_state[NK_KEY_F6] >= 0) nk_input_key(ctx, NK_KEY_F6, k_state[NK_KEY_F6]);
    if (k_state[NK_KEY_F7] >= 0) nk_input_key(ctx, NK_KEY_F7, k_state[NK_KEY_F7]);
    if (k_state[NK_KEY_F8] >= 0) nk_input_key(ctx, NK_KEY_F8, k_state[NK_KEY_F8]);
    if (k_state[NK_KEY_F9] >= 0) nk_input_key(ctx, NK_KEY_F9, k_state[NK_KEY_F9]);
    if (k_state[NK_KEY_F10] >= 0) nk_input_key(ctx, NK_KEY_F10, k_state[NK_KEY_F10]);
    if (k_state[NK_KEY_F11] >= 0) nk_input_key(ctx, NK_KEY_F11, k_state[NK_KEY_F11]);
    if (k_state[NK_KEY_F12] >= 0) nk_input_key(ctx, NK_KEY_F12, k_state[NK_KEY_F12]);

    if (k_state[NK_KEY_TEXT_INSERT_MODE] >= 0) nk_input_key(ctx, NK_KEY_TEXT_INSERT_MODE, k_state[NK_KEY_TEXT_INSERT_MODE]);
    if (k_state[NK_KEY_TEXT_REPLACE_MODE] >= 0) nk_input_key(ctx, NK_KEY_TEXT_REPLACE_MODE, k_state[NK_KEY_TEXT_REPLACE_MODE]);

    nk_input_key(ctx, NK_KEY_TEXT_START, glfwGetKey(win, GLFW_KEY_HOME) == GLFW_PRESS);
    nk_input_key(ctx, NK_KEY_TEXT_END, glfwGetKey(win, GLFW_KEY_END) == GLFW_PRESS);
    nk_input_key(ctx, NK_KEY_SCROLL_START, glfwGetKey(win, GLFW_KEY_HOME) == GLFW_PRESS);
    nk_input_key(ctx, NK_KEY_SCROLL_END, glfwGetKey(win, GLFW_KEY_END) == GLFW_PRESS);
    nk_input_key(ctx, NK_KEY_SHIFT, glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS||
                 glfwGetKey(win, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS);

    if (glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
            glfwGetKey(win, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
    {
        /* Note these are physical keys and won't respect any layouts/key mapping */
        if (k_state[NK_KEY_COPY] >= 0) nk_input_key(ctx, NK_KEY_COPY, k_state[NK_KEY_COPY]);
        if (k_state[NK_KEY_PASTE] >= 0) nk_input_key(ctx, NK_KEY_PASTE, k_state[NK_KEY_PASTE]);
        if (k_state[NK_KEY_CUT] >= 0) nk_input_key(ctx, NK_KEY_CUT, k_state[NK_KEY_CUT]);
        if (k_state[NK_KEY_TEXT_UNDO] >= 0) nk_input_key(ctx, NK_KEY_TEXT_UNDO, k_state[NK_KEY_TEXT_UNDO]);
        if (k_state[NK_KEY_TEXT_REDO] >= 0) nk_input_key(ctx, NK_KEY_TEXT_REDO, k_state[NK_KEY_TEXT_REDO]);
        if (k_state[NK_KEY_TEXT_LINE_START] >= 0) nk_input_key(ctx, NK_KEY_TEXT_LINE_START, k_state[NK_KEY_TEXT_LINE_START]);
        if (k_state[NK_KEY_TEXT_LINE_END] >= 0) nk_input_key(ctx, NK_KEY_TEXT_LINE_END, k_state[NK_KEY_TEXT_LINE_END]);
        if (k_state[NK_KEY_TEXT_SELECT_ALL] >= 0) nk_input_key(ctx, NK_KEY_TEXT_SELECT_ALL, k_state[NK_KEY_TEXT_SELECT_ALL]);
        if (k_state[NK_KEY_LEFT] >= 0) nk_input_key(ctx, NK_KEY_TEXT_WORD_LEFT, k_state[NK_KEY_LEFT]);
        if (k_state[NK_KEY_RIGHT] >= 0) nk_input_key(ctx, NK_KEY_TEXT_WORD_RIGHT, k_state[NK_KEY_RIGHT]);
    }
    else
    {
        if (k_state[NK_KEY_LEFT] >= 0) nk_input_key(ctx, NK_KEY_LEFT, k_state[NK_KEY_LEFT]);
        if (k_state[NK_KEY_RIGHT] >= 0) nk_input_key(ctx, NK_KEY_RIGHT, k_state[NK_KEY_RIGHT]);
        nk_input_key(ctx, NK_KEY_COPY, 0);
        nk_input_key(ctx, NK_KEY_PASTE, 0);
        nk_input_key(ctx, NK_KEY_CUT, 0);
    }

    glfwGetCursorPos(win, &x, &y);
    nk_input_motion(ctx, (int)x, (int)y);
#ifdef NK_GLFW_VULKAN_MOUSE_GRABBING
    if (ctx->input.mouse.grabbed)
    {
        glfwSetCursorPos(glfw.win, ctx->input.mouse.prev.x,
                         ctx->input.mouse.prev.y);
        ctx->input.mouse.pos.x = ctx->input.mouse.prev.x;
        ctx->input.mouse.pos.y = ctx->input.mouse.prev.y;
    }
#endif
    nk_input_button(ctx, NK_BUTTON_LEFT, (int)x, (int)y,
                    glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) ==
                    GLFW_PRESS);
    nk_input_button(ctx, NK_BUTTON_MIDDLE, (int)x, (int)y,
                    glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_MIDDLE) ==
                    GLFW_PRESS);
    nk_input_button(ctx, NK_BUTTON_RIGHT, (int)x, (int)y,
                    glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_RIGHT) ==
                    GLFW_PRESS);
    nk_input_button(ctx, NK_BUTTON_DOUBLE, (int)glfw.double_click_pos.x,
                    (int)glfw.double_click_pos.y, glfw.is_double_click_down);
    nk_input_button(ctx, NK_BUTTON_X1, (int)x, (int)y, glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_4) == GLFW_PRESS);
    nk_input_button(ctx, NK_BUTTON_X2, (int)x, (int)y, glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_5) == GLFW_PRESS);
    nk_input_scroll(ctx, glfw.scroll);
    nk_input_end(&glfw.ctx);

    /* clear after nk_input_end (-1 since we're doing up/down boolean) */
    memset(glfw.key_events, -1, sizeof(glfw.key_events));

    glfw.text_len = 0;
    glfw.scroll = nk_vec2(0, 0);
}

NK_INTERN void update_texture_descriptor_set(
    struct nk_glfw_device *dev,
    struct nk_vulkan_texture_descriptor_set *texture_descriptor_set,
    VkImageView image_view)
{
    VkDescriptorImageInfo descriptor_image_info;
    VkWriteDescriptorSet descriptor_write;

    texture_descriptor_set->image_view = image_view;

    memset(&descriptor_image_info, 0, sizeof(VkDescriptorImageInfo));
    descriptor_image_info.sampler = dev->sampler;
    descriptor_image_info.imageView = texture_descriptor_set->image_view;
    descriptor_image_info.imageLayout =
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    memset(&descriptor_write, 0, sizeof(VkWriteDescriptorSet));
    descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptor_write.dstSet = texture_descriptor_set->descriptor_set;
    descriptor_write.dstBinding = 0;
    descriptor_write.dstArrayElement = 0;
    descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptor_write.descriptorCount = 1;
    descriptor_write.pImageInfo = &descriptor_image_info;

    vkUpdateDescriptorSets(dev->logical_device, 1, &descriptor_write, 0, NULL);
}

/*
 * Nuklear UI commands
        │
        ▼
nk_convert(...)
        │
        ├── dev->mapped_vertex ──► VkBuffer: dev->vertex_buffer
        └── dev->mapped_index  ──► VkBuffer: dev->index_buffer
                                      │
                                      ▼
                              Vulkan draw commands
			      
    1. The uniform buffer is updated directly

    At the beginning:
    c

    memcpy(dev->mapped_uniform, &projection, sizeof(projection));

    dev->mapped_uniform is a CPU pointer returned earlier by vkMapMemory. The projection matrix is copied into mapped Vulkan memory.

    That memory is associated with:
    c

    dev->uniform_descriptor_set

    The descriptor set is bound here:
    
    2. nk_buffer_init_fixed wraps mapped memory

    These calls do not allocate Vulkan memory:
    c

    nk_buffer_init_fixed(&vbuf, dev->mapped_vertex,
			 (size_t)dev->max_vertex_buffer);

    nk_buffer_init_fixed(&ebuf, dev->mapped_index,
			 (size_t)dev->max_element_buffer);

    They create Nuklear buffer objects that point at already-existing memory:
    text

    vbuf → dev->mapped_vertex
    ebuf → dev->mapped_index

    The mapped pointers were presumably created during backend initialization by mapping the memory bound to:
    c

    dev->vertex_buffer
    dev->index_buffer    
    3. nk_convert writes vertices and indices

    This call converts Nuklear’s internal draw-command queue into GPU-renderable data:
    c

    nk_convert(&glfw.ctx, &dev->cmds, &vbuf, &ebuf, &config);

    It generally performs two related operations:

	Converts widget geometry into struct nk_glfw_vertex records.
	Produces index data for drawing that geometry.
	Fills dev->cmds with the resulting draw commands and clipping rectangles.

    The vertex layout says that each vertex contains:
    c

    struct nk_glfw_vertex {
	position;  // float
	uv;        // float
	col;       // packed R8G8B8A8 color
    };

    The layout description:
    c

    NK_VERTEX_POSITION
    NK_VERTEX_TEXCOORD
    NK_VERTEX_COLOR

    must match the vertex input state used when dev->pipeline was created.

    After conversion, the memory conceptually looks like:
    text

    dev->mapped_vertex:
	vertex[0]
	vertex[1]
	vertex[2]
	...

    dev->mapped_index:
	index[0]
	index[1]
	index[2]
	...

    4. The same buffers are bound to the command buffer

    Before drawing:
    c

    vkCmdBindVertexBuffers(command_buffer, 0, 1,
			   &dev->vertex_buffer, &doffset);

    vkCmdBindIndexBuffer(command_buffer, dev->index_buffer, 0,
			 VK_INDEX_TYPE_UINT16);

    Since doffset is zero, Vulkan reads vertices from the beginning of dev->vertex_buffer.

    Likewise, the index buffer is read from offset zero and interpreted as 16-bit indices.

    The important distinction is:
    text

    mapped_vertex / mapped_index
	CPU virtual addresses used for writing

    vertex_buffer / index_buffer
	Vulkan handles used for GPU reading    

    5. Each Nuklear draw command becomes one Vulkan draw

    This loop walks over Nuklear’s generated draw commands:
    c

    nk_draw_foreach(cmd, &glfw.ctx, &dev->cmds)

    For each command, it:

	Selects the appropriate texture descriptor set.
	Sets a scissor rectangle from cmd->clip_rect.
	Issues an indexed draw.

    c

    vkCmdSetScissor(command_buffer, 0, 1, &scissor);

    vkCmdDrawIndexed(command_buffer,
		     cmd->elem_count,
		     1,
		     index_offset,
		     0,
		     0);

    cmd->elem_count is the number of indices for that draw. index_offset advances through the combined index buffer:
    c

    index_offset += cmd->elem_count;

    Nuklear packs all converted geometry into one vertex buffer and one index buffer, then uses different index ranges for each draw command.	
    6. How the pipeline uses this data

    The pipeline is bound before the buffers:
    c

    vkCmdBindPipeline(command_buffer,
		      VK_PIPELINE_BIND_POINT_GRAPHICS,
		      dev->pipeline);

    The pipeline likely expects:
    text

    binding 0:
	position: float2
	uv:       float2
	color:    normalized unsigned bytes

    descriptor set 0:
	projection uniform buffer

    descriptor set 1:
	Nuklear texture/sampler

    The vertex buffer supplies attributes to the vertex shader:
    text

    vertex_buffer → position, UV, color

    The descriptor sets supply non-vertex resources:
    text

    set 0 → projection matrix
    set 1 → current texture and sampler

    Thus:
    text

    pipeline
      ├── defines how vertex data is interpreted
      ├── runs the shaders
      └── defines blending/rasterization behavior

    vertex/index buffers
      └── contain the actual Nuklear geometry

    descriptor sets
      ├── contain the projection uniform
      └── contain the texture used by each draw command

    The pipeline does not copy the data from the buffers. It reads the buffers when vkCmdDrawIndexed executes on the GPU.
    Important synchronization issue

    This implementation appears to use one shared set of mapped vertex and index buffers:
    c

    dev->mapped_vertex
    dev->mapped_index			  

    If the CPU writes new Nuklear data into those buffers while the GPU is still rendering the previous frame, the data can be overwritten too early. The backend must ensure that the previous submission has finished before reusing the buffers, or use per-frame buffers:
    text

    frame 0 → vertex_buffer[0], index_buffer[0]
    frame 1 → vertex_buffer[1], index_buffer[1]
    frame 2 → vertex_buffer[2], index_buffer[2]

    The buffer_index argument selects the framebuffer and command buffer:
    c

    dev->framebuffers[buffer_index]
    dev->command_buffers[buffer_index]

    But in the code shown, it does not select separate vertex/index buffers. Therefore, synchronization around those shared buffers is especially important.

    Also, this line appears to be missing inside the texture block:
    c

    current_texture = cmd->texture.ptr;

    Without updating current_texture, the condition remains true for every textured command, so the texture descriptor set may be rebound unnecessarily.
 * 
 * */
NK_API
VkSemaphore nk_glfw3_render(VkQueue graphics_queue, uint32_t buffer_index,
                            VkSemaphore wait_semaphore,
                            enum nk_anti_aliasing AA)
{
    struct nk_glfw_device *dev = &glfw.vulkan;
    struct nk_buffer vbuf, ebuf;

    struct Mat4f projection =
    {
        {
            2.0f, 0.0f, 0.0f, 0.0f, 0.0f, -2.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
            0.0f, -1.0f, 1.0f, 0.0f, 1.0f
        },
    };

    VkCommandBufferBeginInfo begin_info;
    VkClearValue clear_value = {{{0.0f, 0.0f, 0.0f, 0.0f}}};
    VkRenderPassBeginInfo render_pass_begin_nfo;
    VkCommandBuffer command_buffer;
    VkResult result;
    VkViewport viewport;

    VkDeviceSize doffset = 0;
    VkImageView current_texture = NULL;
    uint32_t index_offset = 0;
    VkRect2D scissor;
    uint32_t wait_semaphore_count;
    VkSemaphore *wait_semaphores;
    VkPipelineStageFlags wait_stage = 
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    VkSubmitInfo submit_info;

    projection.m[0] /= glfw.width;
    projection.m[5] /= glfw.height;

    memcpy(dev->mapped_uniform, &projection, sizeof(projection));

    memset(&begin_info, 0, sizeof(VkCommandBufferBeginInfo));
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    memset(&render_pass_begin_nfo, 0, sizeof(VkRenderPassBeginInfo));
    render_pass_begin_nfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    render_pass_begin_nfo.renderPass = dev->render_pass;
    render_pass_begin_nfo.renderArea.extent.width = (uint32_t)(glfw.width * glfw.fb_scale.x);
    render_pass_begin_nfo.renderArea.extent.height = (uint32_t)(glfw.height * glfw.fb_scale.y);
    render_pass_begin_nfo.clearValueCount = 1;
    render_pass_begin_nfo.pClearValues = &clear_value;
    render_pass_begin_nfo.framebuffer = dev->framebuffers[buffer_index];

    command_buffer = dev->command_buffers[buffer_index];

    result = vkBeginCommandBuffer(command_buffer, &begin_info);
    NK_ASSERT(result == VK_SUCCESS);
    vkCmdBeginRenderPass(command_buffer, &render_pass_begin_nfo,
                         VK_SUBPASS_CONTENTS_INLINE);

    memset(&viewport, 0, sizeof(VkViewport));
    viewport.width = (float)(glfw.width * glfw.fb_scale.x);
    viewport.height = (float)(glfw.height * glfw.fb_scale.y);
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(command_buffer, 0, 1, &viewport);

    vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                      dev->pipeline);
    vkCmdBindDescriptorSets(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                            dev->pipeline_layout, 0, 1,
                            &dev->uniform_descriptor_set, 0, NULL);
    {
        /* convert from command queue into draw list and draw to screen */
        const struct nk_draw_command *cmd;
        /* load draw vertices & elements directly into vertex + element buffer
         */
        {
            /* fill convert configuration */
            struct nk_convert_config config;
            static const struct nk_draw_vertex_layout_element vertex_layout[] =
            {
                {
                    NK_VERTEX_POSITION, NK_FORMAT_FLOAT,
                    NK_OFFSETOF(struct nk_glfw_vertex, position)
                },
                {
                    NK_VERTEX_TEXCOORD, NK_FORMAT_FLOAT,
                    NK_OFFSETOF(struct nk_glfw_vertex, uv)
                },
                {
                    NK_VERTEX_COLOR, NK_FORMAT_R8G8B8A8,
                    NK_OFFSETOF(struct nk_glfw_vertex, col)
                },
                {NK_VERTEX_LAYOUT_END}
            };
            NK_MEMSET(&config, 0, sizeof(config));
            config.vertex_layout = vertex_layout;
            config.vertex_size = sizeof(struct nk_glfw_vertex);
            config.vertex_alignment = NK_ALIGNOF(struct nk_glfw_vertex);
            config.tex_null = dev->tex_null;
            config.circle_segment_count = 22;
            config.curve_segment_count = 22;
            config.arc_segment_count = 22;
            config.global_alpha = 1.0f;
            config.shape_AA = AA;
            config.line_AA = AA;

            /* setup buffers to load vertices and elements */
            nk_buffer_init_fixed(&vbuf, dev->mapped_vertex,
                                 (size_t)dev->max_vertex_buffer);
            nk_buffer_init_fixed(&ebuf, dev->mapped_index,
                                 (size_t)dev->max_element_buffer);
            nk_convert(&glfw.ctx, &dev->cmds, &vbuf, &ebuf, &config);
        }

        /* iterate over and execute each draw command */

        vkCmdBindVertexBuffers(command_buffer, 0, 1, &dev->vertex_buffer,
                               &doffset);
        vkCmdBindIndexBuffer(command_buffer, dev->index_buffer, 0,
                             VK_INDEX_TYPE_UINT16);

        nk_draw_foreach(cmd, &glfw.ctx, &dev->cmds)
        {
            if (!cmd->texture.ptr)
            {
                continue;
            }
            if (cmd->texture.ptr && cmd->texture.ptr != current_texture)
            {
                int found = 0;
                uint32_t i;
                for (i = 0; i < dev->texture_descriptor_sets_len; i++)
                {
                    if (dev->texture_descriptor_sets[i].image_view ==
                            cmd->texture.ptr)
                    {
                        found = 1;
                        break;
                    }
                }

                if (!found)
                {
                    update_texture_descriptor_set(
                        dev, &dev->texture_descriptor_sets[i],
                        (VkImageView)cmd->texture.ptr);
                    dev->texture_descriptor_sets_len++;
                }
                vkCmdBindDescriptorSets(
                    command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                    dev->pipeline_layout, 1, 1,
                    &dev->texture_descriptor_sets[i].descriptor_set, 0, NULL);
            }

            if (!cmd->elem_count)
                continue;

            scissor.offset.x = (int32_t)(NK_MAX(cmd->clip_rect.x, 0.f) * glfw.fb_scale.x);
            scissor.offset.y = (int32_t)(NK_MAX(cmd->clip_rect.y, 0.f) * glfw.fb_scale.y);
            scissor.extent.width = (uint32_t)(cmd->clip_rect.w * glfw.fb_scale.x);
            scissor.extent.height = (uint32_t)(cmd->clip_rect.h * glfw.fb_scale.y);
            vkCmdSetScissor(command_buffer, 0, 1, &scissor);
            vkCmdDrawIndexed(command_buffer, cmd->elem_count, 1, index_offset,
                             0, 0);
            index_offset += cmd->elem_count;
        }
        nk_clear(&glfw.ctx);
    }

    vkCmdEndRenderPass(command_buffer);
    result = vkEndCommandBuffer(command_buffer);
    NK_ASSERT(result == VK_SUCCESS);

    if (wait_semaphore)
    {
        wait_semaphore_count = 1;
        wait_semaphores = &wait_semaphore;
    }
    else
    {
        wait_semaphore_count = 0;
        wait_semaphores = NULL;
    }

    memset(&submit_info, 0, sizeof(VkSubmitInfo));
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &command_buffer;
    submit_info.pWaitDstStageMask = &wait_stage;
    submit_info.waitSemaphoreCount = wait_semaphore_count;
    submit_info.pWaitSemaphores = wait_semaphores;
    submit_info.signalSemaphoreCount = 1;
    submit_info.pSignalSemaphores = &dev->render_completed;

    result = vkQueueSubmit(graphics_queue, 1, &submit_info, NULL);
    NK_ASSERT(result == VK_SUCCESS);

    return dev->render_completed;
}

NK_API void nk_glfw3_char_callback(GLFWwindow *win, unsigned int codepoint)
{
    (void)win;
    if (glfw.text_len < NK_GLFW_TEXT_MAX)
        glfw.text[glfw.text_len++] = codepoint;
}

NK_API void
nk_glfw3_key_callback(GLFWwindow *win, int key, int scancode, int action, int mods)
{
    static int insert_toggle = 0;
    /*
     * convert GLFW_REPEAT to down (technically GLFW_RELEASE, GLFW_PRESS, GLFW_REPEAT are
     * already 0, 1, 2 but just to be clearer)
     */
    nk_char a = (action == GLFW_RELEASE) ? nk_false : nk_true;

    NK_UNUSED(win);
    NK_UNUSED(scancode);
    NK_UNUSED(mods);

    switch (key)
    {
    case GLFW_KEY_DELETE:
        glfw.key_events[NK_KEY_DEL] = a;
        break;
    case GLFW_KEY_TAB:
        glfw.key_events[NK_KEY_TAB] = a;
        break;
    case GLFW_KEY_BACKSPACE:
        glfw.key_events[NK_KEY_BACKSPACE] = a;
        break;
    case GLFW_KEY_UP:
        glfw.key_events[NK_KEY_UP] = a;
        break;
    case GLFW_KEY_DOWN:
        glfw.key_events[NK_KEY_DOWN] = a;
        break;
    case GLFW_KEY_LEFT:
        glfw.key_events[NK_KEY_LEFT] = a;
        break;
    case GLFW_KEY_RIGHT:
        glfw.key_events[NK_KEY_RIGHT] = a;
        break;
    case GLFW_KEY_ESCAPE:
        glfw.key_events[NK_KEY_TEXT_RESET_MODE] = a;
        break;

    case GLFW_KEY_LEFT_ALT:
    case GLFW_KEY_RIGHT_ALT:
        glfw.key_events[NK_KEY_ALT] = a;
        break;
    case GLFW_KEY_PAGE_UP:
        glfw.key_events[NK_KEY_SCROLL_UP] = a;
        break;
    case GLFW_KEY_PAGE_DOWN:
        glfw.key_events[NK_KEY_SCROLL_DOWN] = a;
        break;
    case GLFW_KEY_F1:
        glfw.key_events[NK_KEY_F1] = a;
        break;
    case GLFW_KEY_F2:
        glfw.key_events[NK_KEY_F2] = a;
        break;
    case GLFW_KEY_F3:
        glfw.key_events[NK_KEY_F3] = a;
        break;
    case GLFW_KEY_F4:
        glfw.key_events[NK_KEY_F4] = a;
        break;
    case GLFW_KEY_F5:
        glfw.key_events[NK_KEY_F5] = a;
        break;
    case GLFW_KEY_F6:
        glfw.key_events[NK_KEY_F6] = a;
        break;
    case GLFW_KEY_F7:
        glfw.key_events[NK_KEY_F7] = a;
        break;
    case GLFW_KEY_F8:
        glfw.key_events[NK_KEY_F8] = a;
        break;
    case GLFW_KEY_F9:
        glfw.key_events[NK_KEY_F9] = a;
        break;
    case GLFW_KEY_F10:
        glfw.key_events[NK_KEY_F10] = a;
        break;
    case GLFW_KEY_F11:
        glfw.key_events[NK_KEY_F11] = a;
        break;
    case GLFW_KEY_F12:
        glfw.key_events[NK_KEY_F12] = a;
        break;

    /* have to add all keys used for nuklear to get correct repeat behavior
     * NOTE these are scancodes so your custom layout won't matter unfortunately
     * Also while including everything will prevent unnecessary input calls,
     * only the ones with visible effects really matter, ie paste, undo, redo
     * selecting all, copying or cutting 40 times before you release the keys
     * doesn't actually cause any visible problems */

    case GLFW_KEY_C:
        glfw.key_events[NK_KEY_COPY] = a;
        break;
    case GLFW_KEY_V:
        glfw.key_events[NK_KEY_PASTE] = a;
        break;
    case GLFW_KEY_X:
        glfw.key_events[NK_KEY_CUT] = a;
        break;
    case GLFW_KEY_Z:
        glfw.key_events[NK_KEY_TEXT_UNDO] = a;
        break;
    case GLFW_KEY_R:
        glfw.key_events[NK_KEY_TEXT_REDO] = a;
        break;
    case GLFW_KEY_B:
        glfw.key_events[NK_KEY_TEXT_LINE_START] = a;
        break;
    case GLFW_KEY_E:
        glfw.key_events[NK_KEY_TEXT_LINE_END] = a;
        break;
    case GLFW_KEY_A:
        glfw.key_events[NK_KEY_TEXT_SELECT_ALL] = a;
        break;

    case GLFW_KEY_ENTER:
    case GLFW_KEY_KP_ENTER:
        glfw.key_events[NK_KEY_ENTER] = a;
        break;
    case GLFW_KEY_INSERT:
        /* Only switch on release to avoid repeat issues
         * kind of confusing since we have to negate it but we're already
         * hacking it since Nuklear treats them as two separate keys rather
         * than a single toggle state */
        if (!a)
        {
            insert_toggle = !insert_toggle;
            if (insert_toggle)
            {
                glfw.key_events[NK_KEY_TEXT_INSERT_MODE] = !a;
                /* glfw.key_events[NK_KEY_TEXT_REPLACE_MODE] = a; */
            }
            else
            {
                /* glfw.key_events[NK_KEY_TEXT_INSERT_MODE] = a; */
                glfw.key_events[NK_KEY_TEXT_REPLACE_MODE] = !a;
            }
        }
        break;
    default:
        ;
    }
}

NK_API void nk_glfw3_scroll_callback(GLFWwindow *win, double xoff,
                                     double yoff)
{
    (void)win;
    (void)xoff;
    glfw.scroll.x += (float)xoff;
    glfw.scroll.y += (float)yoff;
}

NK_API void nk_glfw3_mouse_button_callback(GLFWwindow *window, int button,
        int action, int mods)
{
    double x, y;
    NK_UNUSED(mods);
    if (button != GLFW_MOUSE_BUTTON_LEFT)
        return;
    glfwGetCursorPos(window, &x, &y);
    if (action == GLFW_PRESS)
    {
        double dt = glfwGetTime() - glfw.last_button_click;
        if (dt > NK_GLFW_DOUBLE_CLICK_LO && dt < NK_GLFW_DOUBLE_CLICK_HI)
        {
            glfw.is_double_click_down = nk_true;
            glfw.double_click_pos = nk_vec2((float)x, (float)y);
        }
        glfw.last_button_click = glfwGetTime();
    }
    else
        glfw.is_double_click_down = nk_false;
}

NK_INTERN void nk_glfw3_clipboard_paste(nk_handle usr,
                                        struct nk_text_edit *edit)
{
    const char *text = glfwGetClipboardString(glfw.win);
    if (text)
        nk_textedit_paste(edit, text, nk_strlen(text));
    (void)usr;
}

NK_INTERN void nk_glfw3_clipboard_copy(nk_handle usr, const char *text,
                                       int len)
{
    char *str = 0;
    (void)usr;
    if (!len)
        return;
    str = (char *)malloc((size_t)len + 1);
    if (!str)
        return;
    memcpy(str, text, (size_t)len);
    str[len] = '\0';
    glfwSetClipboardString(glfw.win, str);
    free(str);
}

NK_API struct nk_context *
nk_glfw3_init(GLFWwindow *win, VkDevice logical_device,
              VkPhysicalDevice physical_device,
              uint32_t graphics_queue_family_index, VkImageView *image_views,
              uint32_t image_views_len, VkFormat color_format,
              enum nk_glfw_init_state init_state,
              VkDeviceSize max_vertex_buffer, VkDeviceSize max_element_buffer)
{
    memset(&glfw, 0, sizeof(struct nk_glfw));
    glfw.win = win;
    if (init_state == NK_GLFW3_INSTALL_CALLBACKS)
    {
        glfwSetScrollCallback(win, nk_glfw3_scroll_callback);
        glfwSetCharCallback(win, nk_glfw3_char_callback);
        glfwSetKeyCallback(win, nk_glfw3_key_callback);
        glfwSetMouseButtonCallback(win, nk_glfw3_mouse_button_callback);
    }
    nk_init_default(&glfw.ctx, 0);
    glfw.ctx.clip.copy = nk_glfw3_clipboard_copy;
    glfw.ctx.clip.paste = nk_glfw3_clipboard_paste;
    glfw.ctx.clip.userdata = nk_handle_ptr(0);
    glfw.last_button_click = 0;

    glfwGetWindowSize(win, &glfw.width, &glfw.height);
    glfwGetFramebufferSize(win, &glfw.display_width, &glfw.display_height);

    nk_glfw3_device_create(logical_device, physical_device,
                           graphics_queue_family_index, image_views,
                           image_views_len, color_format, max_vertex_buffer,
                           max_element_buffer, (uint32_t)glfw.display_width,
                           (uint32_t)glfw.display_height);

    glfw.is_double_click_down = nk_false;
    glfw.double_click_pos = nk_vec2(0, 0);

    return &glfw.ctx;
}

#endif
