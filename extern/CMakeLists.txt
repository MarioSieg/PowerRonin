add_subdirectory("extern/spdlog/")
target_link_libraries("dreamcast_runtime"  "spdlog")

add_subdirectory("extern/glfw/")
target_link_libraries("dreamcast_runtime" "glfw")

add_subdirectory("extern/json")
#target_link_libraries("dreamcast_runtime" "json") Header only

add_subdirectory("extern/bgfx")
target_link_libraries("dreamcast_runtime" "bgfx")
target_link_libraries("dreamcast_runtime" "bimg")
target_link_libraries("dreamcast_runtime" "bx")

add_subdirectory("extern/imgui")
target_link_libraries("dreamcast_runtime" "imgui")

add_subdirectory("extern/entt")
target_link_libraries("dreamcast_runtime" "EnTT")

add_subdirectory("extern/assimp")
target_link_libraries("dreamcast_runtime" "assimp")

add_subdirectory("extern/glm")
target_link_libraries("dreamcast_runtime" "glm")

add_subdirectory("extern/infoware")
target_link_libraries("dreamcast_runtime" "infoware")

add_subdirectory("extern/nativefiledialog")
target_link_libraries("dreamcast_runtime" "nativefiledialog")

add_subdirectory("extern/bullet3")
target_link_libraries("dreamcast_runtime" "BulletDynamics")
target_link_libraries("dreamcast_runtime" "BulletCollision")
target_link_libraries("dreamcast_runtime" "LinearMath")

add_subdirectory("extern/luajit")
target_link_libraries("liblua_static")