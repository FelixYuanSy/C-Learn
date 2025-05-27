#pragma once
#include "HashTable.h"
#include <iostream>
namespace bit
{
	template<class K, class V, class Hash = HashFunc<K>>
	class unordered_map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename hash_bucket::HashTable<K, pair<const K, V>, MapKeyOfT, Hash>::Iterator iterator;
		typedef typename hash_bucket::HashTable<K, pair<const K, V>, MapKeyOfT, Hash>::ConstIterator const_iterator;


		iterator begin()
		{
			return _ht.Begin();
		}

		iterator end()
		{
			return _ht.End();
		}

		const_iterator begin() const
		{
			return _ht.Begin();
		}

		const_iterator end() const
		{
			return _ht.End();
		}

		pair<iterator, bool> insert(const pair<K, V>& kv)
		{
			return _ht.Insert(kv);
		}

		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = _ht.Insert(make_pair(key, V()));
			return ret.first->second;
		}

	private:
		hash_bucket::HashTable<K, pair<const K, V>, MapKeyOfT, Hash> _ht;
	};

	void Print(const unordered_map<string, string>& dict)
	{
		unordered_map<string, string>::const_iterator it = dict.begin();
		while (it != dict.end())
		{
			//it->first += 'x';
			//it->second += 'x';

			cout << it->first << " " << it->second;
			++it;
		}
		cout << endl;
	}

	//void test_map1()
	//{
	//	unordered_map<string, string> dict;
	//	unordered_map<string, string>::iterator it = dict.begin();
	//	while (it != dict.end())
	//	{
	//		//it->first += 'x';
	//		it->second += 'x';

	//		cout << it->first << " " << it->second;
	//		++it;
	//	}
	//	cout << endl;

	//	string arr[] = { "ƻ", "", "ƻ", "", "ƻ", "ƻ", "",
	//	"ƻ", "㽶", "ƻ", "㽶" };

	//	unordered_map<string, int> countMap;
	//	for (const auto& str : arr)
	//	{
	//		countMap[str]++;
	//	}

	//	for (const auto& e : countMap)
	//	{
	//		cout << e.first << ":" << e.second << endl;
	//	}
	//	cout << endl;
	//}
}
