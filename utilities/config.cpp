// Copyright 2016 Peter Wallström
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software distributed under the License is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and limitations under the License.

// while it is not required i like to request a few things
// 1. please do share any meaningfull/usefull changes/additions/fixes you make with me so that i could include it in any future version
// 2. likewise do share any ideas for improvements
// 3. If you make something comersiol or at least something you release publicly that relies on this code then i would like to know and maybe use in my CV
// 4. Please do include me in your credits

// config class
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git


#include <fstream>
#include <iostream>
#include "config.h"

namespace GLZ
{ 
	
	void glzConfig::load(std::string const inFilename)
	{
		std::ifstream configFile;
		configFile.open(inFilename.c_str(), std::ios::in);


		if(configFile.is_open())
		{
			std::string str;
			while(std::getline(configFile, str))
			{
				mFileData.push_back(str);
			}
			configFile.close();
		}
		else
		{
			configFile.close();
		}

	}


	void glzConfig::addString(std::string inLabel)
	{
		mFileData.push_back(inLabel);
	}

	std::string glzConfig::readString(std::string inLabel, std::string inFallback)
	{


		for(auto a : mFileData)
		{


			if(a.find(inLabel + ":") != std::string::npos)
			{
				std::string::size_type    start_position = 0;
				std::string::size_type    end_position = 0;				
				std::string               found_text;

				start_position = a.find("\"");
				if(start_position != std::string::npos)
				{
					++start_position; // start after the double quotes.
					// look for end position;
					end_position = a.find("\"", start_position);
					if(end_position != std::string::npos)
					{

						found_text = a.substr(start_position, end_position - start_position);
						return found_text;
					}
				}

			}

		}

		return inFallback;	
	}


	int glzConfig::readInt(std::string inLabel, int inFallback)
	{
		for(auto a : mFileData)
		{
			if(a.find(inLabel + ":") != std::string::npos)
			{
				std::string::size_type    start_position = 0;
				std::string::size_type    end_position = 0;
				std::string               found_text;

				start_position = a.find(":");

				start_position = a.find("\"", start_position);
				if(start_position != std::string::npos)
				{
					++start_position; // start after the double quotes.
					// look for end position;
					end_position = a.find("\"");
					if(end_position != std::string::npos)
					{
						return std::stoi(a.substr(start_position, end_position - start_position));
					}
				}

			}

		}

		return inFallback;
	}

	float glzConfig::readFloat(std::string inLabel, float inFallback)
	{
		for(auto a : mFileData)
		{
			if(a.find(inLabel + ":") != std::string::npos)
			{
				std::string::size_type    start_position = 0;
				std::string::size_type    end_position = 0;
				std::string               found_text;

				start_position = a.find(":");

				start_position = a.find("\"", start_position);
				if(start_position != std::string::npos)
				{
					++start_position; // start after the double quotes.
					// look for end position;
					end_position = a.find("\"");
					if(end_position != std::string::npos)
					{
						return std::stof(a.substr(start_position, end_position - start_position));
					}
				}

			}

		}

		return inFallback;
	}

	bool glzConfig::readBool(std::string inLabel, bool inFallback)
	{
		for(auto a : mFileData)
		{
			if(a.find(inLabel + ":") != std::string::npos)
			{
				std::string::size_type    start_position = 0;
				std::string::size_type    end_position = 0;
				std::string               found_text;

				start_position = a.find(":");

				start_position = a.find("\"", start_position);
				if(start_position != std::string::npos)
				{
					++start_position; // start after the double quotes.
					// look for end position;
					end_position = a.find("\"");
					if(end_position != std::string::npos)
					{
						found_text = a.substr(start_position, end_position - start_position);
						if(found_text == "true") return true;
						if(found_text == "True") return true;
						if(found_text == "TRUE") return true;
						if(found_text == "1") return true;

						if(found_text == "false") return false;
						if(found_text == "False") return false;
						if(found_text == "FALSE") return false;
						if(found_text == "0") return false;
					}
				}

			}

		}

		return inFallback;
	}

}