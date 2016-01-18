/*--------------------------------------------------------------------------------
 _______________
|   /       \   | L   attice-based  | LeMonADE-Viewer:
|  /   ooo   \  | e   xtensible     | ---------------- 
| /  o\.|./o  \ | Mon te-Carlo      | An Open Source Visualization Tool for
|/  o\.\|/./o  \| A   lgorithm and  | for BFM-files generated by LeMonADE-software.
|  oo---0---oo  | D   evelopment    | See: https://github.com/LeMonADE-project/LeMonADE
|\  o/./|\.\o  /| E   nvironment    |
| \  o/.|.\o  / | -                 |
|  \   ooo   /  | Viewer            | Copyright (C) 2013-2015 by 
|___\_______/___|                   | LeMonADE-Viewer Principal Developers (see AUTHORS)
----------------------------------------------------------------------------------

This file is part of LeMonADE-Viewer.

LeMonADE-Viewer is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

LeMonADE-Viewer is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LeMonADE-Viewer.  If not, see <http://www.gnu.org/licenses/>.

--------------------------------------------------------------------------------*/


#include <LeMonADE/core/ConfigureSystem.h>
#include <LeMonADE/core/Ingredients.h>
#include <LeMonADE/feature/FeatureMoleculesIO.h>
#include <LeMonADE/feature/FeatureAttributes.h>
#include <LeMonADE/utility/RandomNumberGenerators.h>

#include <LeMonADE-Viewer/LeMonADEViewer.h>
#include <LeMonADE-Viewer/FeatureVisualize.h>

int main(int argc, char* argv[])
{
	//just as in the previous examples, we quickly define the features and basic
	//monomer type and create an instance of the thus defined system.

	typedef LOKI_TYPELIST_3(FeatureMoleculesIO,FeatureVisualize,FeatureAttributes) Features;

	// in most cases the number of connections of a monomer dosn't exceed 8 bonds
	const uint max_bonds=8;

	typedef ConfigureSystem<VectorInt3,Features,max_bonds> Config;
	typedef Ingredients<Config> IngredientsSystem;

	//seed the globally available random number generators
	RandomNumberGenerators random;
	random.seedAll();

	try{

		IngredientsSystem MyLeMonADESystem;

		// A bfm file of given filename will be read
		if ( argc < 2 )
		{
			std::cout << "usage: ./LeMonADE-Viewer filename\n";
			return 1;
		}

		std::string filename (argc>1?argv[1]:"testfile.bfm");


		LeMonADEViewer<IngredientsSystem> ShowLeMonADEViewer(MyLeMonADESystem, filename);

		ShowLeMonADEViewer.initialize();
		ShowLeMonADEViewer.execute();
		ShowLeMonADEViewer.cleanup();

	}
	catch(std::runtime_error& err){std::cerr<<err.what();}

	return 0;
}
