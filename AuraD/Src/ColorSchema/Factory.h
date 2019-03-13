#pragma once
#include "Gradient.h"
#include "ColorModel.h"
#include "AuraModelAdapter.h"

#include <array>
#include <memory>
#include <string>
namespace ColorSchema
{
class Factory
{
	std::array<std::wstring, 1> schemaList;
	std::array<std::wstring, 1> modelList;
public:
	enum class Schema { LINEAR_GRADIENT };
	enum class Model { RGB };
	Factory();
	std::unique_ptr<Gradient> MakeSchema(Schema schema) const;
	std::unique_ptr<Gradient> MakeSchema(const std::wstring& schema) const;
	std::unique_ptr<ColorModel> MakeModel(Model model) const;
	std::unique_ptr<ColorModel> MakeModel(const std::wstring& model) const;
	std::unique_ptr<AuraModelAdapter> MakeAdapter(Model model, const ColorModel& ref) const;
	std::unique_ptr<AuraModelAdapter> MakeAdapter(const std::wstring& model, const ColorModel& ref) const;
};
}