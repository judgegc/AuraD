#pragma once
#include "Syntax/Cursor.h"
#include "Syntax/TokenNode.h"

#include "Provider/SourceInfo.h"

class DataSourceReader
{
public:
	DataSourceReader();
	Provider::SourceInfo operator()(Syntax::Cursor& it);
private:
	Syntax::TokenNode root;
	Syntax::TokenNode openQuote;
	Syntax::TokenNode closeQuote;
	Syntax::TokenNode schema;
	Syntax::TokenNode schemaSlash;
	Syntax::TokenNode nonQuotedUri;
	Syntax::TokenNode quotedUri;
	Syntax::TokenNode end;

	Syntax::Cursor cursor;
	Provider::SourceInfo result;
private:
	bool ProcessNode(Syntax::TokenNode * node);
	void NonQuotedUriReady();
	void QuotedUriReady();
};
