from pathlib import Path
import re

headers = [
    "src/engine/global_data.h",
    "src/engine/common.h",
    "src/engine/engine.h",

    "src/engine/widget/nuklear_config.h",
    "src/engine/widget/nuklear.h",
    "src/engine/widget/widget_renderer_api.h",
    "src/engine/widget/widget_renderer.h",
    "src/engine/widget/widget_renderer_helper.h",
    "src/engine/widget/widget.h",
    "src/engine/widget/nuklear_glfw_vulkan.h",

    "src/engine/util/ppm.h",
    "src/engine/util/file.h",
    "src/engine/array.h",
    "src/engine/m_vec3.h",

    "src/engine/res/res.h",
    "src/engine/handle/handle.h",

    "src/engine/sphere/sphere_renderer.h",
    "src/engine/sphere/icosahedron.h",
    "src/engine/sphere/icosphere.h",

    "src/engine/win/win.h",

    "src/engine/gfx/camera.h",
    "src/engine/gfx/vk_device.h",
    "src/engine/gfx/vk_instance.h",
    "src/engine/gfx/vk_swapchain.h",
    "src/engine/gfx/gfx.h",
    "src/engine/gfx/gfx_types.h",
    "src/engine/gfx/vk_util.h",

    "src/engine/frame.h",
    "src/engine/log/log.h",
    "src/engine/event/event.h",
    "src/engine/types.h",

    "src/engine/mem/arr.h",
    "src/engine/mem/mem.h",

    "src/engine/text/text_engine.h",
    "src/engine/text/text_renderer.h",
    "src/engine/text/text_common.h",
    "src/engine/text/text_geometry.h",
    "src/engine/text/text_block.h",
    "src/engine/text/text.h",

    "src/game/freecam.h",
    "src/game/voxel/voxel_renderer.h",
    "src/game/teapot/teapot.h",
    "src/game/softbody/softbody.h",
    "src/game/softbody/wireframe_renderer.h",
    "src/game/softbody/phash.h",
    "src/game/softbody/sbm.h",
    "src/game/softbody/softbody_renderer.h",
    "src/game/term.h",
    "src/game/input.h",
]


def guard_name(filename):
    # SRC/ENGINE/GLOBAL_DATA.H -> SRC_ENGINE_GLOBAL_DATA_H
    name = filename.upper()
    name = re.sub(r"[^A-Z0-9]", "_", name)

    if name[0].isdigit():
        name = "_" + name

    return name


for filename in headers:
    path = Path(filename)

    if not path.exists():
        print(f"Skipping missing file: {path}")
        continue

    text = path.read_text()

    # Avoid adding guards twice.
    if re.search(r"^\s*#ifndef\s+\w+", text, re.MULTILINE):
        print(f"Already guarded: {path}")
        continue

    guard = guard_name(filename)

    # Remove #pragma once if present.
    text = re.sub(
        r"^\s*#pragma\s+once\s*\n?",
        "",
        text,
        flags=re.MULTILINE,
    )

    text = text.lstrip("\n")

    guarded = (
        f"#ifndef {guard}\n"
        f"#define {guard}\n\n"
        f"{text.rstrip()}\n\n"
        f"#endif /* {guard} */\n"
    )

    path.write_text(guarded)
    print(f"Guarded: {path} -> {guard}")
