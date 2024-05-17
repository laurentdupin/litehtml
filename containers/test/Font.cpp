#define _CRT_SECURE_NO_WARNINGS
#include "Font.h"
string readfile(string filename);
using namespace std;

Font::size_name Font::installed_fonts[] =
{
	{ 12, "terminus-12px.yaff" },
	{ 14, "terminus-14px.yaff" },
	{ 16, "terminus-16px.yaff" },
	{ 18, "terminus-18px.yaff" },
	{ 20, "terminus-20px.yaff" },
	{ 22, "terminus-22px.yaff" },
	{ 24, "terminus-24px.yaff" },
	{ 28, "terminus-28px.yaff" },
	{ 32, "terminus-32px.yaff" },
	{ 0, "" }
};

Font::Font(int size, int weight)
{
	// find most suitable font
	string name;
	if (size == 16 && weight == 700)
		name = "terminus-16px-bold.yaff";
	else
	{
		int min_diff = 1000;
		int n = 0;
		for (int i = 0; installed_fonts[i].size; i++)
		{
			int diff = abs(installed_fonts[i].size - size);
			if (diff < min_diff)
			{
				min_diff = diff;
				n = i;
			}
		}
		name = installed_fonts[n].name;
	}

	string font_cpp = __FILE__;
	auto i = font_cpp.find_last_of("\\/");
	string font_dir = font_cpp.substr(0, i) + "/fonts/";

	load(font_dir + name);
}

Bitmap Font::get_glyph(int ch, color color)
{
	if (glyphs[ch].width == 0)
	{
		Bitmap bmp(width, height, transparent);
		bmp.draw_rect(1, 1, width - 2, height - 2, color);
		return bmp;
	}
	else if (color != black)
	{
		Bitmap bmp = glyphs[ch];
		bmp.replace_color(black, color);
		return bmp;
	}
	else
	{
		return glyphs[ch];
	}
}

// load .yaff font file in an ad hoc manner (can't parse arbitrary yaff files)
void Font::load(string filename)
{
	string text = readfile(filename);
	
	string_vector lines;
	split_string(text, lines, "\n");

	int i;
	// parse header
	for (i = 0; i < (int)lines.size(); i++)
	{
		string line = lines[i];
		trim(line);
		if (line.empty() || line[0] == '#') continue; // skip empty lines and comments

		auto sep = line.find(':');
		if (sep == string::npos) return; // line without ':' - error

		auto key = line.substr(0, sep);   trim(key);
		auto val = line.substr(sep + 1);  trim(val);
		if (val.empty()) break; // end of header

		if (key == "cell-size")    sscanf(val.c_str(), "%d %d", &width, &height);
		else if (key == "ascent")  ascent = atoi(val.c_str());
		else if (key == "descent") descent = atoi(val.c_str());
	}

	// parse glyphs
	
	// only u+NNNN: label is recognized, all others are skipped
	auto parse_key = [&]() {
		int ch = -1;
		for (; i < (int)lines.size(); i++)
		{
			string line = lines[i];
			trim(line);
			if (line.empty()) continue;
			if (line.find(':') == string::npos) break; // start of glyph data
			if (line.substr(0, 2) == "u+")
				sscanf(line.c_str(), "u+%X:", (unsigned int*) &ch);
		}
		return ch;
	};
	
	auto parse_glyph = [&](int ch) {
		Bitmap& glyph = glyphs[ch] = Bitmap(width, height, transparent);
		for (int y = 0; i < (int)lines.size() && y < height; i++, y++)
		{
			string line = lines[i];
			trim(line);
			for (int x = 0; x < min((int)line.size(), width); x++)
			{
				if (line[x] == '@')
					glyph.set_pixel(x, y, black);
			}
		}
	};

	while (i < (int)lines.size())
	{
		int ch = parse_key();
		if (ch < 0) break;
		parse_glyph(ch);
	}

	x_height = glyphs[(int)'x'].find_picture(transparent).height;
}
