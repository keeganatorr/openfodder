/*
 *  Cannon Fodder
 *  ------------------------
 *
 *  Copyright (C) 2008-2017 Robert Crossfield
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "stdafx.hpp"

cResources::cResources( std::string pDataPath ) {

	mDataPath = pDataPath;
}

std::shared_ptr<std::vector<uint8>> cResources::fileGet( std::string pFilename ) {
	std::vector< cResource_File >::iterator		fileIT;

	std::transform( pFilename.begin(), pFilename.end(), pFilename.begin(), ::tolower );
	
	auto File = local_FileRead( pFilename, "" );
	if (File->size())
		return File;

	File = local_FileRead( pFilename, mDataPath.c_str() );
	if (File->size())
		return File;

	// This is rather hacky
	std::transform( pFilename.begin(), pFilename.end(), pFilename.begin(), ::toupper );
	File = local_FileRead( pFilename, "" );
	if (File->size())
		return File;

	File = local_FileRead( pFilename, mDataPath.c_str() );
	return File;
}

size_t cResources::fileLoadTo( const std::string& pFilename, uint8* pTarget ) {

	auto File = fileGet( pFilename );

	if (File->size()) {
		std::memcpy( pTarget, File->data(), File->size() );
		return File->size();
	}

	return false;
}
