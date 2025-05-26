#pragma once
#include "HashTable.h"
namespace bit
{
	template<class K, class Hash = HashFunc<K>>
	class unordered_set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		typedef typename hash_bucket::HashTable<K, const K, SetKeyOfT, Hash>::Iterator iterator;
		typedef typename hash_bucket::HashTable<K, const K, SetKeyOfT, Hash>::ConstIterator const_iterator;


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

		pair<iterator, bool> insert(const K& key)
		{
			return _ht.Insert(key);
		}
	private:
		hash_bucket::HashTable<K, const K, SetKeyOfT, Hash> _ht;
	};

	void Print(const unordered_set<int>& s)
	{
		unordered_set<int>::const_iterator it = s.begin();
		while (it != s.end())
		{
			// *it += 1;
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}

	void test_set1()
	{
		unordered_set<int> s;
		s.insert(1);
		s.insert(12);
		s.insert(54);
		s.insert(107);

		unordered_set<int>::iterator it = s.begin();
		while (it != s.end())
		{
			// *it += 1;
			cout << *it << " ";
			++it;
		}
		cout << endl;

		for (auto e : s)
		{
			cout << e << " ";
		}
		cout << endl;
	}
}