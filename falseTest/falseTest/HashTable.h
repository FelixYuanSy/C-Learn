#define _CRT_SECURE_NO_WARNINGS 1

#include<vector>
#include<string>
using namespace std;

template<class K>
class HashFunc
{
public:
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};

// 特化
template<>
class HashFunc<string>
{
public:
	size_t operator()(const string& key)
	{
		size_t hash = 0;
		for (auto ch : key)
		{
			hash += ch;
			hash *= 131;
		}

		return hash;
	}
};


namespace hash_bucket
{
	template<class T>
	struct HashNode
	{
		T _data;
		HashNode<T>* _next;
		HashNode(const T& data)
			:_data(data)
			, _next(nullptr)
		{
		}
	};

	// 前置声明
	template<class K, class T, class KeyOfT, class Hash>
	class HashTable;

	template<class K, class T, class Ref, class Ptr, class KeyOfT, class Hash>
	struct __HTIterator
	{
		typedef HashNode<T> Node;
		typedef HashTable<K, T, KeyOfT, Hash> HT;
		typedef __HTIterator<K, T, Ref, Ptr, KeyOfT, Hash> Self;

		Node* _node;
		const HT* _ht;

		__HTIterator(Node* node, const HT* ht)
			:_node(node)
			, _ht(ht)
		{
		}

		Ref operator*()
		{
			return _node->_data;
		}

		Ptr operator->()
		{
			return &_node->_data;
		}

		Self operator++()
		{
			if (_node->_next)
			{
				_node = _node->_next;
			}
			else
			{
				// 找下一个桶
				KeyOfT kot;
				Hash hs;
				size_t hashi = hs(kot(_node->_data)) % _ht->_tables.size();
				++hashi;
				while (hashi < _ht->_tables.size())
				{
					if (_ht->_tables[hashi])
					{
						_node = _ht->_tables[hashi];
						break;
					}
					else
					{
						++hashi;
					}
				}

				if (hashi == _ht->_tables.size())
				{
					_node = nullptr;
				}
			}

			return *this;
		}

		bool operator!=(const Self& s)
		{
			return _node != s._node;
		}

		bool operator==(const Self& s)
		{
			return _node == s._node;
		}
	};

	template<class K, class T, class KeyOfT, class Hash>
	class HashTable
	{
		template<class K, class T, class Ref, class Ptr, class KeyOfT, class Hash>
		friend struct __HTIterator;

		typedef HashNode<T> Node;
	public:
		typedef __HTIterator<K, T, T&, T*, KeyOfT, Hash> Iterator;
		typedef __HTIterator<K, T, const T&, const T*, KeyOfT, Hash> ConstIterator;


		Iterator Begin() //从第一个数据节点开始
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				if (cur)
				{
					return Iterator(cur, this);
				}
			}

			return End();
		}

		Iterator End()
		{
			return Iterator(nullptr, this);
		}

		ConstIterator Begin() const
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				if (cur)
				{
					return ConstIterator(cur, this);
				}
			}

			return End();
		}

		ConstIterator End() const
		{
			return ConstIterator(nullptr, this);
		}

		HashTable()
		{
			_tables.resize(__stl_next_prime(1), nullptr);
		}

		~HashTable()
		{
			// 依次把每个桶释放
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_tables[i] = nullptr;
			}
		}

		inline unsigned long __stl_next_prime(unsigned long n)
		{
			// Note: assumes long is at least 32 bits.
			static const int __stl_num_primes = 28;
			static const unsigned long __stl_prime_list[__stl_num_primes] =
			{
				53, 97, 193, 389, 769,
				1543, 3079, 6151, 12289, 24593,
				49157, 98317, 196613, 393241, 786433,
				1572869, 3145739, 6291469, 12582917, 25165843,
				50331653, 100663319, 201326611, 402653189, 805306457,
				1610612741, 3221225473, 4294967291
			};
			const unsigned long* first = __stl_prime_list;
			const unsigned long* last = __stl_prime_list + __stl_num_primes;
			const unsigned long* pos = lower_bound(first, last, n);
			return pos == last ? *(last - 1) : *pos;
		}

		pair<Iterator, bool> Insert(const T& data)
		{
			KeyOfT kot;
			Iterator it = Find(kot(data));
			if (it != End())
				return { it, false };

			Hash hs;
			// 负载因子到1就扩容
			if (_n == _tables.size())
			{
				size_t newSize = __stl_next_prime(_tables.size() + 1);
				vector<Node*> newtables(newSize, nullptr);
				// 遍历旧表，把旧表的节点挪动到新表
				for (size_t i = 0; i < _tables.size(); i++)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;

						// cur头插到新表
						size_t hashi = hs(kot(cur->_data)) % newSize;
						cur->_next = newtables[hashi];
						newtables[hashi] = cur;

						cur = next;
					}

					_tables[i] = nullptr;
				}


				_tables.swap(newtables);
			}

			size_t hashi = hs(kot(data)) % _tables.size();
			Node* newnode = new Node(data);

			// 头插到桶里面
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			++_n;
			return { Iterator(newnode, this), true };
		}

		Iterator Find(const K& key)
		{
			Hash hs;
			size_t hashi = hs(key) % _tables.size();
			Node* cur = _tables[hashi];
			KeyOfT kot;
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					return Iterator(cur, this);
				}

				cur = cur->_next;
			}

			return End();
		}

		bool Erase(const K& key)
		{
			Hash hs;
			KeyOfT kot;

			size_t hashi = hs(key) % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					// 删除
					if (prev == nullptr)
					{
						// 头删
						_tables[hashi] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}

					delete cur;
					return true;
				}

				prev = cur;
				cur = cur->_next;
			}

			return false;
		}
	private:
		//vector<list<pair<K, V>>> _tables;
		vector<Node*> _tables;  // 指针数组
		size_t _n = 0;			// 表中存储数据个数
	};
}