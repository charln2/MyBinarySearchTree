/** ===========================================================================
    nodedata.h
    Purpose: A generic class used so the BinTree is not tied to any
    particular datatype beyond a NodeData object.

    It holds a string "data" and has methods for setting and comparing it to
    other NodeData objects.

    @author: Dr. Carol Zander (with modifications by Charlie Nguyen)
---------------------------------------------------------------------------- */
#ifndef NODEDATA_H
#define NODEDATA_H
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

// simple class containing one string to use for testing
// not necessary to comment further

class NodeData {
	friend ostream& operator<<(ostream&, const NodeData&);

public:
	NodeData(const string& = "");      // default constructor, with opt. param
	NodeData(const NodeData&);         // copy constructor
	~NodeData();
	NodeData& operator=(const NodeData&);

	// set class data from data file
	// returns true if the data is set, false when bad data, i.e., is eof
	bool setData(istream&);

	bool operator==(const NodeData&) const;
	bool operator!=(const NodeData&) const;
	bool operator<(const NodeData&) const;
	bool operator>(const NodeData&) const;
	bool operator<=(const NodeData&) const;
	bool operator>=(const NodeData&) const;

private:
	string data;
};
#endif


