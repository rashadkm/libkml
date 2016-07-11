// Copyright 2008, Google Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice, 
//     this list of conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//  3. Neither the name of Google Inc. nor the names of its contributors may be
//     used to endorse or promote products derived from this software without
//     specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// This file contains the implementation of the internal UriParser class.
// kmlbase::UriParser is based on LUriParser
// from https://github.com/corporateshark/LUrlParser

#include "kml/base/uri_parser.h"
#include <algorithm>
#include <cstring>
#include <memory>
//#include "uriparser/Uri.h"

namespace kmlbase {

  UriParser* UriParser::CreateFromParse(const std::string& str) {
  
  UriParser* uri_parser = new UriParser;
  if (uri_parser->Parse(str.c_str())) {
    return uri_parser;
  }
  delete uri_parser;
  
  return NULL;
}

UriParser* UriParser::CreateResolvedUri(const string base,
                                        const string relative) {
  
  std::unique_ptr<UriParser> base_uri(CreateFromParse(base));
  if (!base_uri.get())
    {
      return NULL;
    }
  
  UriParser* resolved_uri = new UriParser;
  if (resolved_uri->Resolve(*base_uri.get(), relative)) {
    return resolved_uri;
  }
  delete resolved_uri;
  
  return NULL;
}
  

UriParser::UriParser()  
  : m_ErrorCode( UriParserError_Uninitialized ) {
  //  uri_parser_private_.reset(new UriParserPrivate);
}

UriParser::~UriParser() {
}

bool UriParser::Parse(const char* CurrentString) {
  /*
   *	<scheme>:<scheme-specific-part>
   *	<scheme> := [a-z\+\-\.]+
   *	For resiliency, programs interpreting URLs should treat upper case letters as equivalent to lower case in scheme names
   */
  
  // try to read scheme
  {
    const char* LocalString = strchr( CurrentString, ':' );

		if ( !LocalString )
		{
		  m_ErrorCode = UriParserError_NoUrlCharacter;
		  return false;		  
		}

		// save the scheme name
		m_Scheme = std::string( CurrentString, LocalString - CurrentString );

		if ( !IsSchemeValid( m_Scheme ) )
		{
		  m_ErrorCode = UriParserError_InvalidSchemeName;
		  return false;
		}

		// scheme should be lowercase
		std::transform( m_Scheme.begin(), m_Scheme.end(), m_Scheme.begin(), ::tolower );

		// skip ':'
		CurrentString = LocalString+1;
	}

	/*
	 *	//<user>:<password>@<host>:<port>/<url-path>
	 *	any ":", "@" and "/" must be normalized
	 */

	// skip "//"
  if ( *CurrentString++ != '/' ) { m_ErrorCode = UriParserError_NoDoubleSlash; return false; }
  if ( *CurrentString++ != '/' ) {  m_ErrorCode = UriParserError_NoDoubleSlash; return false; }

  if(m_Scheme == "file")
    if ( *CurrentString++ != '/' ) {  m_ErrorCode = UriParserError_NoDoubleSlash; return false; }

	// check if the user name and password are specified
	bool bHasUserName = false;

	const char* LocalString = CurrentString;

	while ( *LocalString )
	{
		if ( *LocalString == '@' )
		{
			// user name and password are specified
			bHasUserName = true;
			break;
		}
		else if ( *LocalString == '/' )
		{
			// end of <host>:<port> specification
			bHasUserName = false;
			break;
		}

		LocalString++;
	}

	// user name and password
	LocalString = CurrentString;

	if ( bHasUserName )
	{
		// read user name
		while ( *LocalString && *LocalString != ':' && *LocalString != '@' ) LocalString++;

		m_UserName = std::string( CurrentString, LocalString - CurrentString );

		// proceed with the current pointer
		CurrentString = LocalString;

		if ( *CurrentString == ':' )
		{
			// skip ':'
			CurrentString++;

			// read password
			LocalString = CurrentString;

			while ( *LocalString && *LocalString != '@' ) LocalString++;

			m_Password = std::string( CurrentString, LocalString - CurrentString );

			CurrentString = LocalString;
		}

		// skip '@'
		if ( *CurrentString != '@' )
		{
		  m_ErrorCode = UriParserError_NoAtSign;
		  return false;
		}

		CurrentString++;
	}

	bool bHasBracket = ( *CurrentString == '[' );

	// go ahead, read the host name
	LocalString = CurrentString;

	while ( *LocalString )
	{
		if ( bHasBracket && *LocalString == ']' )
		{
			// end of IPv6 address
			LocalString++;
			break;
		}
		else if ( !bHasBracket && ( *LocalString == ':' || *LocalString == '/' ) )
		{
			// port number is specified
			break;
		}

		LocalString++;
	}

	m_Host = std::string( CurrentString, LocalString - CurrentString );

	CurrentString = LocalString;

	// is port number specified?
	if ( *CurrentString == ':' )
	{
		CurrentString++;

		// read port number
		LocalString = CurrentString;

		while ( *LocalString && *LocalString != '/' ) LocalString++;

		m_Port = std::string( CurrentString, LocalString - CurrentString );

		CurrentString = LocalString;
	}

	// end of string
	if ( !*CurrentString )
	{
	  m_ErrorCode = UriParserError_UnexpectedEndOfLine;
	  return false;
	}

	// skip '/'
	if ( *CurrentString != '/' )
	{
	  m_ErrorCode = UriParserError_NoSlash;
	  return false;
	}

	CurrentString++;

	// parse the path
	LocalString = CurrentString;

	while ( *LocalString && *LocalString != '#' && *LocalString != '?' ) LocalString++;

	m_Path = std::string( CurrentString, LocalString - CurrentString );

	CurrentString = LocalString;

	// check for query
	if ( *CurrentString == '?' )
	{
		// skip '?'
		CurrentString++;

		// read query
		LocalString = CurrentString;

		while ( *LocalString && *LocalString != '#' ) LocalString++;

		m_Query = std::string( CurrentString, LocalString - CurrentString );

		CurrentString = LocalString;
	}

	// check for fragment
	if ( *CurrentString == '#' )
	{
		// skip '#'
		CurrentString++;

		// read fragment
		LocalString = CurrentString;

		while ( *LocalString ) LocalString++;

		m_Fragment = std::string( CurrentString, LocalString - CurrentString );

		CurrentString = LocalString;
	}

	m_ErrorCode = UriParserError_Ok;

  return true;
}

bool UriParser::Normalize() {
  return false; // uriNormalizeSyntaxA(uri_parser_private_->get_mutable_uri()) ==   URI_SUCCESS;
}

 bool UriParser::Resolve(const UriParser& base, const std::string relative) {

   string url = base.baseuri() + "/" + relative ;
    
   if ( this->Parse( url.c_str()  ) ) {
     return true;
   }
 return false;

 }

bool UriParser::ToString(string* output) const {
  if (!output) {
    return false;
  }


  //*output = m_Scheme + m_Host + m_Port + m_Path+  m_Query + m_Fragment;
  *output = m_Scheme +  "://" + m_Host + m_Port;
  if( ! m_Path.empty() )
    *output += "/" + m_Path;

  if( ! m_Query.empty() )
    *output += m_Query;
  
  if ( ! m_Fragment.empty() )
    *output +=  "#" + m_Fragment;
  /*
  int chars_required;
  if (uriToStringCharsRequiredA(uri_parser_private_->get_mutable_uri(),
                                &chars_required) != URI_SUCCESS) {
    return false;
  }
  char* dest_str = (char*)malloc(chars_required+1);
  if (!dest_str) {
    return false;
  }
  int chars_written;
  if (uriToStringA(dest_str, uri_parser_private_->get_mutable_uri(),
                   chars_required+1, &chars_written) != URI_SUCCESS) {
    free(dest_str);
    return false;
  }
  *output = dest_str;
  free(dest_str);
  */
  if( ( *output).empty() )
    return false;
  
  return true;
}

bool UriParser::UriToFilename(const string& uri,
                              string* output) {
#ifdef WIN32
  return UriToWindowsFilename(uri, output);
#else
  return UriToUnixFilename(uri, output);
#endif
}

bool UriParser::UriToUnixFilename(const string& uri,
                                  string* output) {
  if (!output) {
    return false;
  }
  /*
  const int chars_required = static_cast<int>(uri.size()) + 1;
  char* filename = (char*)malloc(chars_required * sizeof(char));
  if (uriUriStringToUnixFilenameA(uri.c_str(), filename) != URI_SUCCESS) {
    free(filename);
    return false;
  }
  *output = filename;
  free(filename);
  */
  return true;
}

bool UriParser::UriToWindowsFilename(const string& uri,
                                     string* output) {
  if (!output) {
    return false;
  }
  /*
  const int chars_required = static_cast<int>(uri.size()) + 1;
  char* filename = (char*)malloc(chars_required * sizeof(char));
  if (uriUriStringToWindowsFilenameA(uri.c_str(), filename) != URI_SUCCESS) {
    free(filename);
    return false;
  }
  *output = filename;
  free(filename);
  */
  return true;
}

bool UriParser::FilenameToUri(const string& filename,
                              string* output) {
 if (filename.find('\\') != string::npos)
  return WindowsFilenameToUri(filename, output);
 else
  return UnixFilenameToUri(filename, output);
}

bool UriParser::UnixFilenameToUri(const string& filename,
                                  string* output) {
  if (!output) {
    return false;
  }
  /*
  const int chars_required = 7 + 3 * static_cast<int>(filename.size()) + 1;
  char* uri = (char*)malloc(chars_required * sizeof(char));
  if (uriUnixFilenameToUriStringA(filename.c_str(), uri) != URI_SUCCESS) {
    free(uri);
    return false;
  }
  *output = uri;
  free(uri);
  */
  return true;
}

bool UriParser::WindowsFilenameToUri(const string& filename,
                                     string* output) {
  if (!output) {
    return false;
  }
  /*
  const int chars_required = 8 + 3 * static_cast<int>(filename.size()) + 1;
  char* uri = (char*)malloc(chars_required * sizeof(char));
  if (uriWindowsFilenameToUriStringA(filename.c_str(), uri) != URI_SUCCESS) {
    free(uri);
    return false;
  }
  *output = uri;
  free(uri);
  */
  return true;
}

bool UriParser::GetScheme(string* scheme) const {
  if ( !IsValid() && m_Scheme.empty() ) {
    return false;
  }
  if ( scheme ) {
    *scheme = m_Scheme;
  }
  return true;
}

bool UriParser::GetHost(string* host) const {
  if ( !IsValid() && m_Host.empty() ) {
    return false;
  }

  if ( host ) {
    *host = m_Host;
  }

    return true;
}

bool UriParser::GetPort(string* port) const {
  
  if ( !IsValid() ) {
    return false;
  }
  int p = atoi( m_Port.c_str() );
  if ( p <= 0 || p > 65535 ) {
    return false;
  }
  /* if ( port ) { *port = p; } */
  
  if ( port ) { *port = m_Port;   return true; }

  return false;

}

bool UriParser::GetQuery(string* query) const {
  if ( !IsValid() && m_Query.empty() ) {
    return false;
  }
  if ( query ) {
    *query = m_Query;
    return true;  
  }
  return false;
}

bool UriParser::GetFragment(string* fragment) const {
  if ( !IsValid() || m_Fragment.empty() ) {
    return false;
  }
  if ( fragment ) {
    *fragment = m_Fragment;
  }
  return true;

}

bool UriParser::GetPath(string* path) const {
  /*
  if (!uri_parser_private_->get_uri()->pathHead ||
      !uri_parser_private_->get_uri()->pathTail) {
    return false;
  }
  if (path) {
    path->clear();
    UriPathSegmentA* segment = uri_parser_private_->get_uri()->pathHead;
    while (segment) {
      UriTextRangeA* text_range = &segment->text;
      if (!text_range || !text_range->first || !text_range->afterLast) {
        return false;  // Something is corrupt.
      }
      path->append(text_range->first,
                   text_range->afterLast - text_range->first);
      segment = segment->next;
      if (segment) {  // If there's a next segment append a separator.
        path->append("/");
      }
    }
  }
  */
  if ( !IsValid() || m_Path.empty() ) {
    return false;
  }
  if ( path ) {
    *path = m_Path;

  }
    return true;  
    //  return false;
}

}  // end namespace kmlbase
