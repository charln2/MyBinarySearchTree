/** ===========================================================================
    nodedata.cpp
    Purpose: A generic object used so the BinTree is not tied to any 
             particular datatype beyond a NodeData object.

    It holds a string "data" and has methods for setting and comparing it to
    other NodeData objects.

    @author: Dr. Carol Zander (with modifications by Charlie Nguyen)
---------------------------------------------------------------------------- */
#include "nodedata.h"

//----------------------------------------------------------------------------
// constructors/destructor  

//NodeData::NodeData(string data) { }                 // default

NodeData::NodeData(const string& s) : data(s) {}    // cast string to NodeData
NodeData::NodeData(const NodeData& nd) : data(nd.data) {}  // copy
NodeData::~NodeData() {}            // needed so strings are deleted properly



//----------------------------------------------------------------------------
// operator= 

NodeData& NodeData::operator=(const NodeData& rhs) {
	if (this != &rhs) {
		data = rhs.data;
	}
	return *this;
}

//----------------------------------------------------------------------------
// operator==,!= 

bool NodeData::operator==(const NodeData& rhs) const {
	return data == rhs.data;
}

bool NodeData::operator!=(const NodeData& rhs) const {
	return data != rhs.data;
}

//----------------------------------------------------------------------------
// operator<,>,<=,>= 

bool NodeData::operator<(const NodeData& rhs) const {
	return data < rhs.data;
}

bool NodeData::operator>(const NodeData& rhs) const {
	return data > rhs.data;
}

bool NodeData::operator<=(const NodeData& rhs) const {
	return data <= rhs.data;
}

bool NodeData::operator>=(const NodeData& rhs) const {
	return data >= rhs.data;
}

//----------------------------------------------------------------------------
// setData 
// returns true if the data is set, false when bad data, i.e., is eof

bool NodeData::setData(istream& infile) {
	getline(infile, data);
	return !infile.eof();       // eof function is true when eof char is read
}

//----------------------------------------------------------------------------
// operator<< 

ostream& operator<<(ostream& output, const NodeData& nd) {
	output << nd.data;
	return output;
}
