#include "Factory.h"
#include "LinearGradient.h"
#include "Rgb.h"
#include "RgbAdapter.h"
#include "Core/Exception.h"

#include <exception>
#include <algorithm>
namespace ColorSchema
{
Factory::Factory() : schemaList{ L"LinearGradient" },
modelList{ L"rgb" }
{
}
std::unique_ptr<Gradient> Factory::MakeSchema(Schema schema) const
{
	switch (schema)
	{
	case Schema::LINEAR_GRADIENT:
		return std::make_unique<LinearGradient>();
	default:
		throw Core::Exception(L"Unknown color schema.");
	}
}
std::unique_ptr<Gradient> Factory::MakeSchema(const std::wstring & schema) const
{
	auto found = std::find(schemaList.begin(), schemaList.end(), schema);
	if (found == schemaList.end())
		throw Core::Exception (L"Parsing error. Unknown color schema.");
	return MakeSchema(static_cast<Schema>(found - schemaList.begin()));
}
std::unique_ptr<ColorModel> Factory::MakeModel(Model model) const
{
	switch (model)
	{
	case Model::RGB:
		return std::make_unique<Rgb>();
	default:
		throw Core::Exception(L"Unknown color model.");
	}
}
std::unique_ptr<ColorModel> Factory::MakeModel(const std::wstring & model) const
{
	auto found = std::find(modelList.begin(), modelList.end(), model);
	if (found == modelList.end())
		throw Core::Exception(L"Parsing error. Unknown color model.");
	return MakeModel(static_cast<Model>(found - modelList.begin()));
}
std::unique_ptr<AuraModelAdapter> Factory::MakeAdapter(Model model, const ColorModel& ref) const
{
	switch (model)
	{
	case Model::RGB:
		return std::make_unique<RgbAdapter>(dynamic_cast<const Rgb&>(ref));
	default:
		throw Core::Exception(L"Unknown color model.");
	}
}
std::unique_ptr<AuraModelAdapter> Factory::MakeAdapter(const std::wstring & model, const ColorModel& ref) const
{
	auto found = std::find(modelList.begin(), modelList.end(), model);
	if (found == modelList.end())
		throw Core::Exception(L"Parsing error. Unknown color model.");
	return MakeAdapter(static_cast<Model>(found - modelList.begin()), ref);
}
}