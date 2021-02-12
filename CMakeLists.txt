cmake_minimum_required (VERSION 3.8)

message("Initializing PowerRoninSDK CMake")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
project ("PowerRoninSDK" CXX C ASM)

message("Com: ${CMAKE_CXX_COMPILER_ID}")

# -march=native
# -march=skylake-avx512
# -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mavx2
# -flto
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    SET(COVERAGE_COMPILE_FLAGS "-v -march=native -Ofast -MT")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COVERAGE_COMPILE_FLAGS}")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COVERAGE_COMPILE_FLAGS}")
    SET(CMAKE_STATIC_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${COVERAGE_LINK_FLAGS}")
    SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${COVERAGE_LINK_FLAGS}")
endif()

set(COMMON_SOURCES
	"Include/PowerRonin/Core/Kernel.hpp"
    "Include/PowerRonin/Aabb.hpp"
    "Include/PowerRonin/Blob.hpp"
    "Include/PowerRonin/InterruptHandler.hpp" 
    "Include/PowerRonin/Camera.hpp" 
    "Include/PowerRonin/Chrono.hpp" 
    "Include/PowerRonin/Collider.hpp" 
    "Include/PowerRonin/Components.hpp" 
    "Include/PowerRonin/Config.hpp" 
    "Include/PowerRonin/Core/Entry.hpp"
    "Include/PowerRonin/Core/Installer.hpp" 
    "Include/PowerRonin/Core/Subsystem.hpp" 
    "Include/PowerRonin/CSharpInterop.hpp"
    "Include/PowerRonin/Diagnostics.hpp" 
    "Include/PowerRonin/EcsBase.hpp" 
    "Include/PowerRonin/EntityMeta.hpp" 
    "Include/PowerRonin/Platform.hpp"
    "Include/PowerRonin/Exceptions.hpp" 
    "Include/PowerRonin/Fence.hpp" 
    "Include/PowerRonin/EditorCamera.hpp" 
    "Include/PowerRonin/Frustum.hpp"      
    "Include/PowerRonin/HybridObject.hpp"  
    "Include/PowerRonin/Input.hpp" 
    "Include/PowerRonin/Interrupt.hpp"
    "Include/PowerRonin/Json.hpp" 
    "Include/PowerRonin/Light.hpp" 
    "Include/PowerRonin/ManagedObject.hpp" 
    "Include/PowerRonin/Material.hpp" 
    "Include/PowerRonin/MathLib.hpp" 
    "Include/PowerRonin/Mesh.hpp"
    "Include/PowerRonin/MeshRenderer.hpp" 
    "Include/PowerRonin/MessageBox.hpp" 
    "Include/PowerRonin/PanicRoutine.hpp"
    "Include/PowerRonin/ProcessInfo.hpp"
    "Include/PowerRonin/Protocol.hpp" 
    "Include/PowerRonin/RenderState.hpp" 
    "Include/PowerRonin/ResourceManager.hpp" 
    "Include/PowerRonin/Rigidbody.hpp" 
    "Include/PowerRonin/Runtime.hpp" 
    "Include/PowerRonin/Scenery.hpp" 
    "Include/PowerRonin/Serial.hpp" 
    "Include/PowerRonin/Sun.hpp" 
    "Include/PowerRonin/Texture.hpp" 
    "Include/PowerRonin/TimeUtils.hpp" 
    "Include/PowerRonin/Transform.hpp" 
    "Include/PowerRonin/VisitOverload.hpp" 
    "Include/PowerRonin/Xorshift.hpp"
    "source/aabb.cpp" 
    "source/audio/audio.cpp"
    "source/audio/audio.hpp"
    "source/audio/audio_engine_core/Common/AkDefaultLowLevelIODispatcher.cpp" 
    "source/audio/audio_engine_core/Common/AkDefaultLowLevelIODispatcher.h" 
    "source/audio/audio_engine_core/Common/AkFileLocationBase.cpp" 
    "source/audio/audio_engine_core/Common/AkFileLocationBase.h" 
    "source/audio/audio_engine_core/Common/AkFilePackage.cpp" 
    "source/audio/audio_engine_core/Common/AkFilePackage.h" 
    "source/audio/audio_engine_core/Common/AkFilePackageLUT.cpp" 
    "source/audio/audio_engine_core/Common/AkFilePackageLUT.h" 
    "source/audio/audio_engine_core/Common/AkFilePackageLowLevelIO.h" 
    "source/audio/audio_engine_core/Common/AkMultipleFileLocation.cpp" 
    "source/audio/audio_engine_core/Common/AkMultipleFileLocation.h"
    "source/audio/audio_headers.hpp"
    "source/blob.cpp"  
    "source/break_interrupt_handler.cpp" 
    "source/Core/entry.cpp"
    "source/Core/installer.cpp" 
    "source/Core/kernel.cpp"
    "source/Core/subsystem.cpp" 
    "source/except.cpp" 
    "source/fence.cpp" 
    "source/flycam.cpp" 
    "source/frustum.cpp" 
    "source/gui/editor.cpp" 
    "source/gui/editor.hpp" 
    "source/gui/file_dialog_tool.cpp" 
    "source/gui/file_dialog_tool.hpp"
    "source/gui/font_headers.hpp" 
    "source/gui/gui.cpp" 
    "source/gui/gui.hpp" 
    "source/gui/gui_headers.hpp"
    "source/gui/scroll_roll_buffer.cpp" 
    "source/gui/scroll_roll_buffer.hpp" 
    "source/gui/terminal.cpp" 
    "source/gui/terminal.hpp"
    "source/gui/theme.cpp" 
    "source/gui/theme.hpp" 
    "source/gui/utils.hpp"
    "source/gui/widgets/config_editor.cpp" 
    "source/gui/widgets/config_editor.hpp"
    "source/gui/widgets/hierarchy.cpp"
    "source/gui/widgets/hierarchy.hpp" 
    "source/gui/widgets/inspector.cpp" 
    "source/gui/widgets/inspector.hpp"
    "source/gui/widgets/profiler.cpp" 
    "source/gui/widgets/profiler.hpp"
    "source/gui/widgets/ram_editor.hpp" 
    "source/gui/widgets/resource_viewer.cpp" 
    "source/gui/widgets/resource_viewer.hpp" 
    "source/gui/widgets/scenery_viewer.cpp" 
    "source/gui/widgets/scenery_viewer.hpp"
    "source/gui/window_names.hpp" 
    "source/hybrid.cpp" 
    "source/input.cpp" 
    "source/interrupt.cpp" 
    "source/managed_object.cpp" 
    "source/material.cpp"
    "source/material_runtime.cpp"
    "source/mesh.cpp" 
    "source/mesh_runtime.cpp" 
    "source/msgbox.cpp" 
    "source/panic_routine.cpp" 
    "source/physics/physics.cpp" 
    "source/physics/physics.hpp" 
    "source/physics/physics_headers.hpp"
    "source/platform/callback_hooks.cpp"
    "source/platform/callback_hooks.hpp" 
    "source/platform/input.cpp" 
    "source/platform/input.hpp" 
    "source/platform/platform.cpp"
    "source/platform/platform_headers.hpp"
    "source/platform/util.cpp" 
    "source/platform/util.hpp"
    "source/procinfo.cpp" 
    "source/proto.cpp" 
    "source/renderer.cpp"
    "source/renderer/clocks.cpp" 
    "source/renderer/clocks.hpp" 
    "source/renderer/gl_headers.hpp" 
    "source/renderer/gpu.cpp" 
    "source/renderer/gpu.hpp"
    "source/renderer/gui_renderer.cpp" 
    "source/renderer/gui_renderer.hpp" 
    "source/renderer/ishader.hpp"  
    "source/renderer/program_loader.cpp" 
    "source/renderer/program_loader.hpp" 
    "source/renderer/renderer.cpp" 
    "source/renderer/renderer.hpp" 
    "source/renderer/shader_bucket.cpp" 
    "source/renderer/shader_bucket.hpp" 
    "source/renderer/shader_bucket.hpp" 
    "source/renderer/shaders/bumped_diffuse.cpp" 
    "source/renderer/shaders/bumped_diffuse.hpp"
    "source/renderer/shaders/diffuse.cpp" 
    "source/renderer/shaders/diffuse.hpp"
    "source/renderer/shaders/skybox.cpp"
    "source/renderer/shaders/skybox.hpp"
    "source/renderer/shaders/unlit_textured.cpp"
    "source/renderer/shaders/unlit_textured.hpp" 
    "source/renderer/shared_uniforms.cpp"
    "source/renderer/shared_uniforms.hpp" 
    "source/renderer/stats.cpp" 
    "source/renderer/stats.hpp" 
    "source/renderer/uniform.cpp" 
    "source/renderer/uniform.hpp"
    "source/renderer/utils.cpp"
    "source/renderer/utils.hpp"  
    "source/renderer/views.hpp" 
    "source/resource_manager.cpp"  
    "source/runtime.cpp" 
    "source/scenery.cpp" 
    "source/scripting/assembly.cpp" 
    "source/scripting/assembly.hpp" 
    "source/scripting/environment.cpp" 
    "source/scripting/environment.hpp" 
    "source/scripting/helpers.cpp" 
    "source/scripting/helpers.hpp" 
    "source/scripting/instance_class.cpp" 
    "source/scripting/instance_class.hpp"
    "source/scripting/internal_calls.cpp" 
    "source/scripting/member_method.cpp"
    "source/scripting/member_method.hpp"
    "source/scripting/mono_headers.hpp" 
    "source/scripting/power_ronin.dll.hpp" 
    "source/scripting/scripting.cpp" 
    "source/scripting/scripting.hpp"
    "source/scripting/static_class.cpp" 
    "source/scripting/static_class.hpp"
    "source/scripting/static_method.cpp" 
    "source/scripting/static_method.hpp"
    "source/serial.cpp" 
    "source/shader.cpp" 
    "source/shader_runtime.cpp" 
    "source/sun.cpp" 
    "source/sysclock.cpp" 
    "source/sysclock.hpp" 
    "source/terminal_sink.hpp"    
    "source/texture.cpp" 
    "source/texture_runtime.cpp" 
    "source/time_utils.cpp" 
    "source/time_utils.cpp" 
    "source/transform.cpp" 
    "source/xorshift.cpp" 
    "source/camera.cpp" 
    "source/core/core.cpp" 
    "source/core/core.hpp")

if(WIN32)
    list(APPEND COMMON_SOURCES
        "source/audio/audio_engine_core/Win32/AkDefaultIOHookBlocking.cpp" 
        "source/audio/audio_engine_core/Win32/AkDefaultIOHookBlocking.h" 
        "source/audio/audio_engine_core/Win32/AkDefaultIOHookDeferred.cpp" 
        "source/audio/audio_engine_core/Win32/AkDefaultIOHookDeferred.h" 
        "source/audio/audio_engine_core/Win32/AkFileHelpers.h" 
        "source/audio/audio_engine_core/Win32/AkFilePackageLowLevelIOBlocking.h" 
        "source/audio/audio_engine_core/Win32/AkFilePackageLowLevelIODeferred.h")
else()
    list(APPEND COMMON_SOURCES
       "source/audio/audio_engine_core/POSIX/AkDefaultIOHookBlocking.cpp" 
       "source/audio/audio_engine_core/POSIX/AkDefaultIOHookBlocking.h" 
       "source/audio/audio_engine_core/POSIX/AkDefaultIOHookDeferred.cpp" 
       "source/audio/audio_engine_core/POSIX/AkDefaultIOHookDeferred.h" 
       "source/audio/audio_engine_core/POSIX/AkFileHelpers.h" 
       "source/audio/audio_engine_core/POSIX/AkFilePackageLowLevelIOBlocking.h" 
       "source/audio/audio_engine_core/POSIX/AkFilePackageLowLevelIODeferred.h")
endif()

# Add base engine
add_library("power_ronin_lib" STATIC ${COMMON_SOURCES})
set_property(TARGET "power_ronin_lib" PROPERTY "MSVC_RUNTIME_LIBRARY" "MultiThreaded")
set(ENGINE_PACKAGE "power_ronin_lib")

link_directories("")

add_subdirectory("${CMAKE_SOURCE_DIR}/extern/spdlog/")
add_subdirectory("${CMAKE_SOURCE_DIR}/extern/glfw/")
add_subdirectory("${CMAKE_SOURCE_DIR}/extern/json")
add_subdirectory("${CMAKE_SOURCE_DIR}/extern/bgfx")
add_subdirectory("${CMAKE_SOURCE_DIR}/extern/imgui")
add_subdirectory("${CMAKE_SOURCE_DIR}/extern/entt")
add_subdirectory("${CMAKE_SOURCE_DIR}/extern/assimp")
add_subdirectory("${CMAKE_SOURCE_DIR}/extern/glm")
add_subdirectory("${CMAKE_SOURCE_DIR}/extern/infoware")
add_subdirectory("${CMAKE_SOURCE_DIR}/extern/bullet3")

# Core Engine:

target_include_directories("power_ronin_lib" PRIVATE "${CMAKE_SOURCE_DIR}/extern/mono/include/mono-2.0")
target_include_directories("power_ronin_lib" PRIVATE "extern/wwise/SDK/include/")
target_link_libraries("power_ronin_lib" "${CMAKE_SOURCE_DIR}/extern/mono/lib/libmono-static-sgen.lib")
target_link_libraries("power_ronin_lib" "${CMAKE_SOURCE_DIR}/extern/mono/lib/mono-2.0-sgen.lib")

target_link_libraries("power_ronin_lib" "assimp")
target_link_libraries("power_ronin_lib" "EnTT")
target_link_libraries("power_ronin_lib" "imgui")
target_link_libraries("power_ronin_lib" "bgfx")
target_link_libraries("power_ronin_lib" "bimg")
target_link_libraries("power_ronin_lib" "bx")
target_link_libraries("power_ronin_lib" "spdlog")
target_link_libraries("power_ronin_lib" "glfw")
target_link_libraries("power_ronin_lib" "glm")
target_link_libraries("power_ronin_lib" "infoware")
target_link_libraries("power_ronin_lib" "BulletDynamics")
target_link_libraries("power_ronin_lib" "BulletCollision")
target_link_libraries("power_ronin_lib" "LinearMath")

if(WIN32) # Add windows only libraries
	target_link_libraries("power_ronin_lib" "${CMAKE_SOURCE_DIR}/extern/_windows/WS2_32.lib")
	target_link_libraries("power_ronin_lib" "${CMAKE_SOURCE_DIR}/extern/_windows/WinMM.lib")
	target_link_libraries("power_ronin_lib" "${CMAKE_SOURCE_DIR}/extern/_windows/bcrypt.lib")
    target_link_libraries("power_ronin_lib" "${CMAKE_SOURCE_DIR}/extern/wwise/SDK/x64_vc160/Release(StaticCRT)/lib/AkSoundEngine.lib")
    target_link_libraries("power_ronin_lib" "${CMAKE_SOURCE_DIR}/extern/wwise/SDK/x64_vc160/Release(StaticCRT)/lib/AkMemoryMgr.lib")
    target_link_libraries("power_ronin_lib" "${CMAKE_SOURCE_DIR}/extern/wwise/SDK/x64_vc160/Release(StaticCRT)/lib/AkStreamMgr.lib")
    target_link_libraries("power_ronin_lib" "${CMAKE_SOURCE_DIR}/extern/wwise/SDK/x64_vc160/Release(StaticCRT)/lib/AkMusicEngine.lib")
    target_link_libraries("power_ronin_lib" "${CMAKE_SOURCE_DIR}/extern/wwise/SDK/x64_vc160/Release(StaticCRT)/lib/AkSpatialAudio.lib")
else()
    if(UNIX AND NOT APPLE)
        target_link_libraries("power_ronin_lib" "${CMAKE_SOURCE_DIR}/extern/wwise/SDK/Linux_x64/Release/lib/AkSoundEngine.a")
        target_link_libraries("power_ronin_lib" "${CMAKE_SOURCE_DIR}/extern/wwise/SDK/Linux_x64/Release/lib/AkMemoryMgr.a")
        target_link_libraries("power_ronin_lib" "${CMAKE_SOURCE_DIR}/extern/wwise/SDK/Linux_x64/Release/lib/AkStreamMgr.a")
        target_link_libraries("power_ronin_lib" "${CMAKE_SOURCE_DIR}/extern/wwise/SDK/Linux_x64/Release/lib/AkMusicEngine.a")
        target_link_libraries("power_ronin_lib" "${CMAKE_SOURCE_DIR}/extern/wwise/SDK/Linux_x64/Release/lib/AkSpatialAudio.a")
    else()
        target_link_libraries("power_ronin_lib" "${CMAKE_SOURCE_DIR}/extern/wwise/SDK/Mac/Release/lib/AkSoundEngine.a")
        target_link_libraries("power_ronin_lib" "${CMAKE_SOURCE_DIR}/extern/wwise/SDK/Mac/Release/lib/AkMemoryMgr.a")
        target_link_libraries("power_ronin_lib" "${CMAKE_SOURCE_DIR}/extern/wwise/SDK/Mac/Release/lib/AkStreamMgr.a")
        target_link_libraries("power_ronin_lib" "${CMAKE_SOURCE_DIR}/extern/wwise/SDK/Mac/Release/lib/AkMusicEngine.a")
        target_link_libraries("power_ronin_lib" "${CMAKE_SOURCE_DIR}/extern/wwise/SDK/Mac/Release/lib/AkSpatialAudio.a")
    endif()
endif()

#add_compile_definitions(AUTO_TEC=false)
add_executable("power_ronin" WIN32 "entry.cpp")
set_property(TARGET "power_ronin" PROPERTY "MSVC_RUNTIME_LIBRARY" "MultiThreaded")
target_link_libraries("power_ronin" "power_ronin_lib")

remove_definitions(AUTO_TEC)

add_compile_definitions(AUTO_TEC=true)
add_executable("power_ronin_autotec" WIN32 "entry.cpp")
set_property(TARGET "power_ronin_autotec" PROPERTY "MSVC_RUNTIME_LIBRARY" "MultiThreaded")
target_link_libraries("power_ronin_autotec" "power_ronin_lib")

# Editor specific libraries:
add_subdirectory("${CMAKE_SOURCE_DIR}/extern/nativefiledialog")
target_link_libraries("power_ronin_autotec" "nativefiledialog")
