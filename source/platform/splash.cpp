// *******************************************************************************
// The content of this file includes portions of the KerboGames Dreamcast Technology
// released in source code form as part of the SDK package.
// 
// Commercial License Usage
// 
// Licensees holding valid commercial licenses to the KerboGames Dreamcast Technology
// may use this file in accordance with the end user license agreement provided 
// with the software or, alternatively, in accordance with the terms contained in a
// written agreement between you and KerboGames.
// 
// Copyright (c) 20013-2020 KerboGames, MarioSieg.
// support@kerbogames.com
// *******************************************************************************

#include "../../extern/glad/include/glad/glad.h"
#include "../../extern/stb/stb_image.h"
#include "../../include/dce/mathlib.hpp"
#include "splash.hpp"
#include "platform_headers.hpp"
#include "util.hpp"

namespace {
	constexpr const char* const VERTEX_SHADER = "#version 110\n" "uniform mat4 mvp;\n" "attribute vec2 pos;\n" "varying vec2 texcoord;\n" "void main()\n" "{\n" "    gl_Position = mvp * vec4(pos, 0.0, 1.0);\n" "    texcoord = pos;\n" "}\n";

	constexpr const char* const FRAGMENT_SHADER = "#version 110\n" "uniform sampler2D tex;\n" "varying vec2 texcoord;\n" "void main()\n" "{\n" "    gl_FragColor = texture2D(tex, texcoord);\n" "}\n";

	constexpr float VERTICES[4][2]{{0.f, 0.f}, {1.f, 0.f}, {1.f, 1.f}, {0.f, 1.f}};

}

namespace dce::platform {

	auto SplashScreen::open(const int _ratio, GLFWmonitor* const _monitor, const char* const _image_path) -> bool {
		[[unlikely]] if (!_ratio) {
			return false;
		}

		const auto* const video_mode = glfwGetVideoMode(_monitor);
		[[unlikely]] if (!video_mode) {
			return false;
		}

		int width = video_mode->width;
		int height = video_mode->height;

		[[unlikely]] if (!width || !height) {
			return false;
		}

		width /= _ratio;
		height /= _ratio;

		[[unlikely]] if (!width || !height) {
			return false;
		}

		glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		this->window_ = glfwCreateWindow(width, height, "Starting Dreamcast Engine", nullptr, nullptr);
		[[unlikely]] if (!this->window_) {
			goto FATAL_ERROR;
		}
		center_window(this->window_, _monitor);
		{
			int x, y, channels;
			stbi_set_flip_vertically_on_load(true);
			this->splash_image_data_ = stbi_load(_image_path, &x, &y, &channels, STBI_rgb_alpha);
			stbi_set_flip_vertically_on_load(false);
			[[unlikely]] if (!this->splash_image_data_) {
				goto FATAL_ERROR;
			}

			this->splash_image_ = new(std::nothrow) GLFWimage;
			[[unlikely]] if (!this->splash_image_) {
				goto FATAL_ERROR;
			}

			this->splash_image_->width = this->width_ = x;
			this->splash_image_->height = this->height_ = y;
			this->splash_image_->pixels = this->splash_image_data_;
			this->image_path_ = _image_path;
		}
		glfwMakeContextCurrent(this->window_);
		glfwSwapInterval(1);
		gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		[[unlikely]] if (!gladLoadGL()) {
			goto FATAL_ERROR;
		}
		{
			GLuint texture, vertex_buffer;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->splash_image_->width, this->splash_image_->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->splash_image_data_);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			GLint mvp_location;
			GLuint program;
			GLint texture_location;
			GLint vpos_location;
			{
				const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
				glShaderSource(vertex_shader, 1, &VERTEX_SHADER, nullptr);
				glCompileShader(vertex_shader);

				const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
				glShaderSource(fragment_shader, 1, &FRAGMENT_SHADER, nullptr);
				glCompileShader(fragment_shader);

				program = glCreateProgram();
				glAttachShader(program, vertex_shader);
				glAttachShader(program, fragment_shader);
				glLinkProgram(program);

				mvp_location = glGetUniformLocation(program, "mvp");
				texture_location = glGetUniformLocation(program, "tex");
				vpos_location = glGetAttribLocation(program, "pos");

				glGenBuffers(1, &vertex_buffer);
				glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
				glBufferData(GL_ARRAY_BUFFER, sizeof VERTICES, VERTICES, GL_STATIC_DRAW);
			}

			glUseProgram(program);
			glUniform1i(texture_location, 0);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture);

			glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
			glEnableVertexAttribArray(vpos_location);
			glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof *VERTICES, nullptr);

			glfwShowWindow(this->window_);
			int w, h;
			glfwGetFramebufferSize(this->window_, &w, &h);
			const auto projection = math::ortho(.0f, 1.f, .0f, 1.f, .0f, 1.f);
			glfwPollEvents();
			glClearColor(1.f, 1.f, 1.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);
			glViewport(0, 0, w, h);
			glUniformMatrix4fv(mvp_location, 1, GL_FALSE, value_ptr(projection));
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			glfwSwapBuffers(this->window_);
		}

		glfwDefaultWindowHints();

		return this->is_visible_ = true;


	FATAL_ERROR : {
			[[unlikely]] if (this->window_) {
				glfwDestroyWindow(this->window_);
				this->window_ = nullptr;
			}

			[[unlikely]] if (this->splash_image_data_) {
				stbi_image_free(this->splash_image_data_);
				this->splash_image_data_ = nullptr;
			}

			[[unlikely]] if (this->splash_image_) {
				delete this->splash_image_;
				this->splash_image_ = nullptr;
			}
		}

		return false;
	}

	void SplashScreen::close() {
		[[unlikely]] if (!this->is_visible_ || !this->window_) {
			return;
		}

		glfwHideWindow(this->window_);
		glfwDestroyWindow(this->window_);

		[[likely]] if (this->splash_image_data_) {
			stbi_image_free(this->splash_image_data_);
		}

		delete this->splash_image_;

		this->splash_image_data_ = nullptr;
		this->splash_image_ = nullptr;

		this->is_visible_ = false;
		this->window_ = nullptr;
	}

	auto SplashScreen::get_width() const noexcept -> int {
		return this->width_;
	}

	auto SplashScreen::get_height() const noexcept -> int {
		return this->height_;
	}
}
