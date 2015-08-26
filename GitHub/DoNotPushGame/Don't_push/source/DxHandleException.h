#pragma once
#include <stdexcept>
class DxGHandle_runtime_error : public std::runtime_error {
public:
	explicit DxGHandle_runtime_error(const std::string& what_arg) : std::runtime_error("DxGHandle_runtime_error_runtime_error : " + what_arg) {}
	explicit DxGHandle_runtime_error(const char* what_arg) : std::runtime_error(std::string("DxGHandle_runtime_error_runtime_error : ") + what_arg) {}
};
class DxSHandle_runtime_error : public std::runtime_error {
public:
	explicit DxSHandle_runtime_error(const std::string& what_arg) : std::runtime_error("DxSHandle_runtime_error_runtime_error : " + what_arg) {}
	explicit DxSHandle_runtime_error(const char* what_arg) : std::runtime_error(std::string("DxSHandle_runtime_error_runtime_error : ") + what_arg) {}
};
