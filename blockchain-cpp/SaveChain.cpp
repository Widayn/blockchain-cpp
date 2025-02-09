/*****************************************************************//**
 * \file   SaveChain.cpp
 * \author WiDAYN
 * \date   26 March 2022
 *********************************************************************/
#include "SaveChain.h"
#include "StringUtil.h"
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include<boost/serialization/map.hpp>

bool SaveChain::save(BlockChain& blockChain, ini_t* config)
{
	const char* file = ini_get(config, "file", "blockchain");
	//д��
	ofstream ss(file, ios::binary);
	if (ss.is_open()) {
		boost::archive::binary_oarchive oa(ss);
		oa << blockChain;
		ss.close();
		StringUtil::printfSuccess("Saved blockChain");
		return true;
	}
	else {
		StringUtil::printfError("Saved blockChain error");
		return false;
	}
	return true;
}

bool SaveChain::load(BlockChain& blockChain, ini_t* config) {
	const char* file = ini_get(config, "file", "blockchain");
	ifstream is(file, std::ios::binary);
	if (is.is_open()) {
		boost::archive::binary_iarchive ia(is);
		ia >> blockChain;
		StringUtil::printfSuccess("Loaded blockChain");
	}
	is.close();
	return true;
}
