//
// Copyright (c) 2016 - 2017 Mesh Consultants Inc.
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//


#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//#include <examples_linking_pragmas.h>


#include <rapidjson.h>
#include "opennurbs.h"

using namespace std;

int main(int argc, char* argv[])
{
	
	// Call once in your application to initialze opennurbs library
	ON::Begin();

	//default dump is to stdout
	ON_TextLog dump_to_stdout;
	dump_to_stdout.SetIndentSize(2);
	ON_TextLog* dump = &dump_to_stdout;
	FILE* dump_fp = 0;

	// open file containing opennurbs archive
	ON_wString ws_arg = "../../test/test_data.3dm";
	const wchar_t* wchar_arg = ws_arg;

	FILE* archive_fp = ON::OpenFile(wchar_arg, L"rb");
	if (!archive_fp)
	{
		cout << "Unable to read file" << endl;
		return 0;
	}

	//on model
	ONX_Model model;

	// create achive object from file pointer
	ON_BinaryFile archive(ON::read3dm, archive_fp);

	// read the contents of the file into "model"
	bool rc = model.Read(archive, dump);

	// close the file
	ON::CloseFile(archive_fp);

	// close the file
	ON::CloseFile(archive_fp);

	// print diagnostic
	if (rc)
		dump->Print("Successfully read.\n");
	else
		dump->Print("Errors during reading.\n");

	// see if everything is in good shape
	if (model.IsValid(dump))
	{
		dump->Print("Model is valid.\n");
	}
	else
	{
		dump->Print("Model is not valid.\n");
	}

	// create a text dump of the model
	bool verbose = true;
	if (verbose)
	{
		dump->PushIndent();
		model.Dump(*dump);
		dump->PopIndent();
	}

	// destroy this model
	model.Destroy();

	dump->PopIndent();


	return 0;
}