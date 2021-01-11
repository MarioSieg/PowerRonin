#include "camera_matrices.hpp"

namespace power_ronin::renderer
{
	void calculate_camera_matrices(RenderData& _data)
	{
		_data.view_matrix = _data.editor_camera.view_matrix();
		_data.projection_matrix = _data.editor_camera.projection_matrix();
		_data.view_projection_matrix = _data.projection_matrix * _data.view_matrix;
		_data.camera_frustum.from_camera_matrix(_data.view_projection_matrix);
	}
}