#pragma once
#include "Syntax/Cursor.h"

#include "Syntax/Identifier.h"
#include "Syntax/Keyword.h"
#include "Syntax/Number.h"
#include "Syntax/Trigger.h"
#include "Syntax/TokenNode.h"
#include "Syntax/Any.h"

#include "ColorSchema/Gradient.h"
#include "ColorSchema/ColorModel.h"
#include "ColorSchema/Factory.h"

#include <string>
#include <memory>
#include <array>
class ColorSchemaReader
{
	Syntax::Cursor cursor;
	Syntax::TokenNode root;
	Syntax::TokenNode schema;
	Syntax::TokenNode schemaOpen;
	Syntax::TokenNode schemaClose;
	Syntax::TokenNode model;
	Syntax::TokenNode modelOpen;
	Syntax::TokenNode modelClose;
	Syntax::TokenNode component;
	Syntax::TokenNode componentSeparator;
	Syntax::TokenNode modelPos;
	Syntax::TokenNode modelPosVal;
	Syntax::TokenNode modelSeparator;
	Syntax::TokenNode end;
	int currentComponent;
	int modelComponents;
	const std::array<double, 2> autoPos;
	decltype(autoPos)::const_iterator autoPosVal;
	struct {
		std::unique_ptr<ColorSchema::Gradient> gradient;
		std::unique_ptr<ColorSchema::ColorModel> model;
		std::unique_ptr<ColorSchema::AuraModelAdapter> modelAdapter;
	} result;
	ColorSchema::Factory f;
private:
	void SchemaTrigger();
	void ModelTrigger();
	void ComponentTrigger();
	void ModelReady();
	bool ProcessNode(Syntax::TokenNode* node);
	double NextAutoPosVal();
public:
	ColorSchemaReader();
	std::unique_ptr<ColorSchema::Gradient> operator()(Syntax::Cursor& it);
};