#pragma once
#include "TreeBuilder.h"
#include "rapidjson/reader.h"
#include "rapidjson/document.h"
#include<Windows.h>
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

class JSONDialog;

class TreeBuilderReader
{
public:

	TreeBuilderReader(JSONDialog *dlg, HTREEITEM treeRoot, StringStream& is) :
		is_(is), dlg(dlg), treeRoot(treeRoot) {}

	bool operator()(Document& document) {
		TreeBuilder<Document> treeBuilder(dlg, treeRoot, document);
		Reader reader;
		parseResult_ = reader.Parse<rapidjson::kParseNumbersAsStringsFlag>(is_, treeBuilder);
		return !parseResult_.IsError();
	}

	const ParseResult& GetParseResult() const { return parseResult_; }

private:
	//TreeBuilderReader(const TreeBuilderReader&);
	//TreeBuilderReader& operator=(const TreeBuilderReader&);

	StringStream& is_;
	ParseResult parseResult_;
	JSONDialog *dlg;
	HTREEITEM treeRoot;
};

