#pragma once
#include"HashTable.h"
using namespace std;

namespace bit
{
	template<class K, class V, class Hash = HashFunc<K>>
	class unoredered_map
	{
		struct MapKeyOfT
		{
			K& operator()(pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public :
		bool insert(pair<K, V>& kv)
		{
			return _ht.Insert(kv);
		}
	private:
		hash_bucket::HashTable<K, pair<K, V>, MapKeyOfT, Hash> _ht;
	};

}