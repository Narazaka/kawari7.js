//---------------------------------------------------------------------------
//
// TMMap - mapのようにアクセスできるmultimap -
//
//      Programed by NAKAUE.T (Thanks: しの、酔狂)
//
//---------------------------------------------------------------------------
#ifndef TMMAP_H
#define TMMAP_H
//---------------------------------------------------------------------------
#include <vector>
#include <map>
//---------------------------------------------------------------------------
template<class KeyType,class DataType> class TMMap
 : public std::multimap<KeyType,DataType> {
public:

	DataType& operator[](const KeyType& key)
	{
//		iterator it=lower_bound(key);
		typename std::multimap<KeyType,DataType>::iterator it;	// gcc対策
		it=this->lower_bound(key);
		// 2001/12/16 suikyo@yk.rim.or.jp : imortal entry bug
//		if(it==end()) it=insert(std::pair<KeyType,DataType>(key,DataType()));
		if(it==this->upper_bound(key)) it=this->insert(std::pair<KeyType,DataType>(key,DataType()));
		return((*it).second);
	}
/*
	const DataType& operator[](const KeyType& key) const
	{
		static DataType dummy;
		iterator it=lower_bound(key);
		if(it==end()) return(dummy);
		return((*it).second);
	}
*/
	void Add(const KeyType& key,const DataType& data)
	{
		this->insert(std::pair<KeyType,DataType>(key,data));
	}

};
//---------------------------------------------------------------------------
#endif
