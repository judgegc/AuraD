#include "ColorSchemaReader.h"
#include "Core/Exception.h"
#include "ColorSchema/AuraModelAdapter.h"
#include "ParsingError.h"

#include <sstream>
#include <algorithm>
#include <functional>
#include <exception>
#include <iomanip>
#include <iostream>

void ColorSchemaReader::SchemaTrigger()
{
	result.gradient = f.MakeSchema(schema.Get<Syntax::Identifier>()->Value());
}

void ColorSchemaReader::ModelTrigger()
{
	result.model = f.MakeModel(model.Get<Syntax::Identifier>()->Value());
	result.modelAdapter = f.MakeAdapter(model.Get<Syntax::Identifier>()->Value(), *result.model);
	currentComponent = 0;
	modelComponents = result.model->Components();
}

void ColorSchemaReader::ComponentTrigger()
{
	if (currentComponent >= modelComponents)
		throw Core::Exception(L"Too many components.");

	result.model->SetComponent(currentComponent, component.Get<Syntax::Number>()->Value());
	++currentComponent;
}

void ColorSchemaReader::ModelReady()
{
	double pos = modelPosVal.Get<Syntax::Number>()->Value() == 0. ? NextAutoPosVal() : modelPosVal.Get<Syntax::Number>()->Value();
	result.gradient->AddStopColor(*result.modelAdapter, pos);
	modelPosVal.t = std::make_unique<Syntax::Number>();
}

bool ColorSchemaReader::ProcessNode(Syntax::TokenNode * node)
{
	node->t->Process(cursor);
	return node->t->Success();
}

double ColorSchemaReader::NextAutoPosVal()
{
	if (autoPosVal == autoPos.end())
		throw Core::Exception(L"Missing model stop pos.");
	return *autoPosVal++;
}

ColorSchemaReader::ColorSchemaReader() :
	root(nullptr),
	schema(std::make_unique<Syntax::Trigger>(std::move(std::make_unique<Syntax::Identifier>()), std::bind(&ColorSchemaReader::SchemaTrigger, this))),
	schemaOpen(std::make_unique<Syntax::Keyword>(L"(")),
	schemaClose(std::make_unique<Syntax::Trigger>(std::make_unique<Syntax::Keyword>(L")"), std::bind(&ColorSchemaReader::ModelReady, this))),
	model(std::make_unique<Syntax::Trigger>(std::make_unique<Syntax::Identifier>(), std::bind(&ColorSchemaReader::ModelTrigger, this))),
	modelOpen(std::make_unique<Syntax::Keyword>(L"(")),
	modelClose(std::make_unique<Syntax::Keyword>(L")")),
	component(std::make_unique<Syntax::Trigger>(std::make_unique<Syntax::Number>(), std::bind(&ColorSchemaReader::ComponentTrigger, this))),
	componentSeparator(std::make_unique<Syntax::Keyword>(L",")),
	modelPos(std::make_unique<Syntax::Keyword>(L":")),
	modelPosVal(std::make_unique<Syntax::Number>()),
	modelSeparator(std::make_unique<Syntax::Trigger>(std::make_unique<Syntax::Keyword>(L","), std::bind(&ColorSchemaReader::ModelReady, this))),
	end(std::make_unique<Syntax::Any>()),
	currentComponent(0),
	modelComponents(0),
	autoPos({ 0., 1. }),
	autoPosVal(autoPos.cbegin())
{
	root.Connect(&schema);
	schema.Connect(&schemaOpen);
	schemaOpen.Connect(&model);
	model.Connect(&modelOpen);
	modelOpen.Connect(&component);
	component.Connect(&modelClose);
	component.Connect(&componentSeparator);
	modelClose.Connect(&modelSeparator);
	modelClose.Connect(&modelPos);
	modelClose.Connect(&schemaClose);
	modelPos.Connect(&modelPosVal);
	modelPosVal.Connect(&modelSeparator);
	modelSeparator.Connect(&model);
	componentSeparator.Connect(&component);
	schemaClose.Connect(&end);
}

std::unique_ptr<ColorSchema::Gradient> ColorSchemaReader::operator()(Syntax::Cursor& it)
{
	autoPosVal = autoPos.cbegin();
	cursor = it;
	Syntax::TokenNode* x = &root;
	cursor.NextData();
	for (; !(cursor.AtEnd() || x == &end); cursor.NextData())
	{
		auto found = std::find_if(x->next.begin(), x->next.end(), std::bind(&ColorSchemaReader::ProcessNode, this, std::placeholders::_1));
		
		if (found == x->next.end())
			throw ParsingError(L"Parsing error in ColorSchemaReader", cursor.Str(), cursor.Position());

		x = *found;
	}
	it = cursor;
	return std::move(result.gradient);
}
