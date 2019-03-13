#include "DataSourceReader.h"
#include "Core/Exception.h"

#include "Syntax/Identifier.h"
#include "Syntax/Keyword.h"
#include "Syntax/Number.h"
#include "Syntax/Trigger.h"
#include "Syntax/Any.h"

#include "DataSource/QuotedString.h"
#include "DataSource/NonQuotedString.h"
#include "ParsingError.h"

#include <sstream>
#include <algorithm>
#include <iomanip>
#include <functional>
#include <memory>

bool DataSourceReader::ProcessNode(Syntax::TokenNode * node)
{
	node->t->Process(cursor);
	return node->t->Success();
}
void DataSourceReader::NonQuotedUriReady()
{
	result.source = nonQuotedUri.Get<DataSource::NonQuotedString>()->Uri();
}
void DataSourceReader::QuotedUriReady()
{
	result.source = quotedUri.Get<DataSource::QuoutedString>()->Uri();
}
DataSourceReader::DataSourceReader() :
	root(nullptr),
	openQuote(std::make_unique<Syntax::Keyword>(L"'")),
	closeQuote(std::make_unique<Syntax::Keyword>(L"'")),
	schema(std::make_unique<Syntax::Identifier>()),
	schemaSlash(std::make_unique<Syntax::Keyword>(L"://")),
	nonQuotedUri(std::make_unique<Syntax::Trigger>(std::make_unique<DataSource::NonQuotedString>(), std::bind(&DataSourceReader::NonQuotedUriReady, this))),
	quotedUri(std::make_unique<Syntax::Trigger>(std::make_unique<DataSource::QuoutedString>(), std::bind(&DataSourceReader::QuotedUriReady, this))),
	end(std::make_unique<Syntax::Any>())
{
	root.Connect(&openQuote);
	root.Connect(&schema);
	openQuote.Connect(&schema);
	schema.Connect(&schemaSlash);
	schemaSlash.Connect(&quotedUri);
	schemaSlash.Connect(&nonQuotedUri);
	quotedUri.Connect(&closeQuote);
	closeQuote.Connect(&end);
	nonQuotedUri.Connect(&end);
}

Provider::SourceInfo DataSourceReader::operator()(Syntax::Cursor & it)
{
	cursor = it;
	Syntax::TokenNode* x = &root;
	cursor.NextData();
	for (; !(cursor.AtEnd() || x == &end); cursor.NextData())
	{
		auto found = std::find_if(x->next.begin(), x->next.end(), std::bind(&DataSourceReader::ProcessNode, this, std::placeholders::_1));
		if (found == x->next.end())
			throw ParsingError(L"Parsing error in DataSourceReader", cursor.Str(), cursor.Position());

		x = *found;
	}

	//------------------------>
	if (schema.Get<Syntax::Identifier>()->Value() == L"pdh")
		result.protocol = Provider::SourceInfo::Schema::PDH;

	it = cursor;
	return result;
}