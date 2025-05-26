#pragma once
#include "HashTable.h"
namespace bit
{
	template<class K, class Hash = HashFunc<K>>//写一个方法自己转换成整型
	class unordered_set
	{
		struct SetKeyOfT
		{
			K& operator()(const K& key)
			{
				return key;
			}
		};

	public:
		bool insert(const K& key)
		{
			return _ht.Insert(key);
		}


	private:
		hash_bucket::HashTable<K, K, SetKeyOfT, Hash> _ht;
	};
}